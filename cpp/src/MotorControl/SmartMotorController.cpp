/*
 *  Software License Agreement
 *
 * Copyright (C) Cross The Road Electronics.  All rights
 * reserved.
 * 
 * Cross The Road Electronics (CTRE) licenses to you the right to 
 * use, publish, and distribute copies of CRF (Cross The Road) firmware files (*.crf) and Software
 *API Libraries ONLY when in use with Cross The Road Electronics hardware products.
 * 
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * CROSS THE ROAD ELECTRONICS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
 */
#ifndef CTR_EXCLUDE_WPILIB_CLASSES
#include "ctre/phoenix/MotorControl/SmartMotorController.h"
#include "ctre/phoenix/CTRLogger.h"

#include <chrono>
#include <sstream>
#include <thread>

#include "HAL/HAL.h"
#include "LiveWindow/LiveWindow.h"
#include "WPIErrors.h"
#include "Utility.h"

namespace CTRE {namespace MotorControl
{
/**
 * Number of adc engineering units per 0 to 3.3V sweep.
 * This is necessary for scaling Analog Position in rotations/RPM.
 */
const double kNativeAdcUnitsPerRotation = 1024.0;
/**
 * Number of pulse width engineering units per full rotation.
 * This is necessary for scaling Pulse Width Decoded Position in rotations/RPM.
 */
const double kNativePwdUnitsPerRotation = 4096.0;
/**
 * Number of minutes per 100ms unit.  Useful for scaling velocities
 * measured by Talon's 100ms timebase to rotations per minute.
 */
const double kMinutesPer100msUnit = 1.0 / 600.0;

constexpr unsigned int SmartMotorController::kDelayForSolicitedSignalsUs;



/**
 * Constructor for the SmartMotorController device.
 *
 * @param deviceNumber The CAN ID of the Talon SRX
 */
SmartMotorController::SmartMotorController(int deviceNumber)
    : m_deviceNumber(deviceNumber),
      m_handle(c_TalonSRX_Create1(deviceNumber)),
      m_safetyHelper(new frc::MotorSafetyHelper(this)) {
  ApplyControlMode(m_sendMode);
  c_Logger_Log(c_TalonSRX_SetProfileSlotSelect(m_handle, m_profile), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetProfileSlotSelect").c_str(), frc::GetStackTrace(2).c_str());
//  frc::LiveWindow::GetInstance()->AddActuator("SmartMotorController", m_deviceNumber, this);
}
/**
 * Constructor for the SmartMotorController device.
 *
 * @param deviceNumber    The CAN ID of the Talon SRX
 * @param controlPeriodMs The period in ms to send the CAN control frame.
 *                        Period is bounded to [1ms,95ms].
 */
SmartMotorController::SmartMotorController(int deviceNumber, int controlPeriodMs)
    : m_deviceNumber(deviceNumber),
      m_handle(c_TalonSRX_Create2(deviceNumber, controlPeriodMs)),
      m_safetyHelper(new frc::MotorSafetyHelper(this)) {
  ApplyControlMode(m_sendMode);
  c_Logger_Log(c_TalonSRX_SetProfileSlotSelect(m_handle, m_profile), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetProfileSlotSelect").c_str(), frc::GetStackTrace(2).c_str());
//  frc::LiveWindow::GetInstance()->AddActuator("SmartMotorController", m_deviceNumber, this);
}

SmartMotorController::~SmartMotorController() {
//  if (m_table != nullptr) m_table->RemoveTableListener(this);
  if (m_hasBeenMoved) return;
  Disable();
}

int SmartMotorController::GetDeviceID() {
	return m_deviceNumber;
}
/**
 * Write out the PID value as seen in the PIDOutput base object.
 *
 * @deprecated Call Set instead.
 *
 * @param output Write out the PercentVbus value as was computed by the
 *               PIDController
 */
void SmartMotorController::PIDWrite(double output) {
  if (GetControlMode() == ControlMode::SmartControlMode::kPercentVbus) {
    Set(output);
  } else {
    wpi_setWPIErrorWithContext(IncompatibleMode,
                               "PID only supported in PercentVbus mode");
  }
}

/**
 * Retrieve the current sensor value. Equivalent to Get().
 *
 * @return The current sensor value of the Talon.
 */
double SmartMotorController::PIDGet() { return Get(); }

/**
 * Gets the current status of the Talon (usually a sensor value).
 *
 * In Current mode: returns output current.
 * In Speed mode: returns current speed.
 * In Position mode: returns current sensor position.
 * In PercentVbus and Follower modes: returns current applied throttle.
 *
 * @return The current sensor value of the Talon.
 */
double SmartMotorController::Get() const {
  int value;
  switch (m_controlMode) {
    case ControlMode::SmartControlMode::kVoltage:
      return GetOutputVoltage();
    case ControlMode::SmartControlMode::kCurrent:
      return GetOutputCurrent();
    case ControlMode::SmartControlMode::kSpeed:
      c_Logger_Log(c_TalonSRX_GetSensorVelocity(m_handle, &value), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetSensorVelocity").c_str(), frc::GetStackTrace(2).c_str());
      return ScaleNativeUnitsToRpm(m_feedbackDevice, value);
    case ControlMode::SmartControlMode::kPosition:
      c_Logger_Log(c_TalonSRX_GetSensorPosition(m_handle, &value),("TalonSRX " + std::to_string(m_deviceNumber) + " GetSensorPosition").c_str(), frc::GetStackTrace(2).c_str());
      return ScaleNativeUnitsToRotations(m_feedbackDevice, value);
    case ControlMode::SmartControlMode::kPercentVbus:
    case ControlMode::SmartControlMode::kFollower:
    default:
      c_Logger_Log(c_TalonSRX_GetAppliedThrottle(m_handle, &value), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetAppliedThrottle").c_str(), frc::GetStackTrace(2).c_str());
      return static_cast<double>(value) / 1023.0;
  }
}

/**
 * Sets the appropriate output on the talon, depending on the mode.
 *
 * In PercentVbus, the output is between -1.0 and 1.0, with 0.0 as stopped.
 * In Voltage mode, output value is in volts.
 * In Current mode, output value is in amperes.
 * In Speed mode, output value is in position change / 10ms.
 * In Position mode, output value is in encoder ticks or an analog value,
 * depending on the sensor.
 * In Follower mode, the output value is the integer device ID of the talon to
 * duplicate.
 *
 * @param outputValue The setpoint value, as described above.
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
void SmartMotorController::Set(double value) {
  /* feed safety helper since caller just updated our output */
  m_safetyHelper->Feed();

  if (m_stopped) {
    EnableControl();
    m_stopped = false;
  }

  if (m_controlEnabled) {
    m_setPoint = value; /* cache set point for GetSetpoint() */
    CTR_Code status = OKAY;
    switch (m_sendMode) {
      case ControlMode::SmartControlMode::kDisabled:{
          c_TalonSRX_Set(m_handle, value);
          status = OKAY;
        } break;
      case ControlMode::SmartControlMode::kPercentVbus: {
        c_TalonSRX_Set(m_handle, m_isInverted ? -value : value);
        status = OKAY;
      } break;
      case ControlMode::SmartControlMode::kFollower: {
        status = c_TalonSRX_SetDemand(m_handle, static_cast<int>(value));
      } break;
      case ControlMode::SmartControlMode::kVoltage: {
        // Voltage is an 8.8 fixed point number.
        int volts = static_cast<int>((m_isInverted ? -value : value) * 256);
        status = c_TalonSRX_SetDemand(m_handle, volts);
      } break;
      case ControlMode::SmartControlMode::kSpeed:
        /* if the caller has provided scaling info, apply it */
        status = c_TalonSRX_SetDemand(m_handle, ScaleVelocityToNativeUnits(
            m_feedbackDevice, m_isInverted ? -value : value));
        break;
      case ControlMode::SmartControlMode::kPosition:
        status = c_TalonSRX_SetDemand(m_handle, 
            ScaleRotationsToNativeUnits(m_feedbackDevice, value));
        break;
      case ControlMode::SmartControlMode::kCurrent: {
        double milliamperes = (m_isInverted ? -value : value) * 1000.0; /* mA*/
        status = c_TalonSRX_SetDemand(m_handle, milliamperes);
      } break;
      case ControlMode::SmartControlMode::kMotionProfile: {
        status = c_TalonSRX_SetDemand(m_handle, static_cast<int>(value));
      } break;
      case ControlMode::SmartControlMode::kMotionMagic:
			status = c_TalonSRX_SetDemand(m_handle, ScaleRotationsToNativeUnits(m_feedbackDevice, value));
          break;
      default:
	    status = IncompatibleMode;
        break;
    }
	status = c_TalonSRX_SetModeSelect(m_handle, m_sendMode);
	
	c_Logger_Log(status, ("TalonSRX " + std::to_string(m_deviceNumber) + " Controller Set").c_str(), frc::GetStackTrace(2).c_str());
  }
}

/**
 * Sets the setpoint to value. Equivalent to Set().
 */
void SmartMotorController::SetSetpoint(double value) { Set(value); }

/**
 * Resets the integral term and disables the controller.
 */
void SmartMotorController::Reset() {
  ClearIaccum();
  Disable();
}

/**
 * Disables control of the talon, causing the motor to brake or coast
 * depending on its mode (see the Talon SRX Software Reference manual
 * for more information).
 */
void SmartMotorController::Disable() {
  c_Logger_Log(c_TalonSRX_SetModeSelect(m_handle, static_cast<int>(ControlMode::SmartControlMode::kDisabled)), ("TalonSRX" + std::to_string(m_deviceNumber) + "SetModeSelect").c_str(), frc::GetStackTrace(2).c_str());
  m_controlEnabled = false;
}

/**
 * Enables control of the Talon, allowing the motor to move.
 */
void SmartMotorController::EnableControl() {
	SetTalonControlMode(m_sendMode);
  m_controlEnabled = true;
}

/**
 * Enables control of the Talon, allowing the motor to move.
 */
void SmartMotorController::Enable() { EnableControl(); }

/**
 * @return Whether the Talon is currently enabled.
 */
bool SmartMotorController::IsControlEnabled() const { return m_controlEnabled; }

/**
 * @return Whether the Talon is currently enabled.
 */
bool SmartMotorController::IsEnabled() const { return IsControlEnabled(); }

/**
 * @param p Proportional constant to use in PID loop.
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
void SmartMotorController::SetP(double p) {
  c_Logger_Log(c_TalonSRX_SetPgain(m_handle, m_profile, p), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetPgain").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Set the integration constant of the currently selected profile.
 *
 * @param i Integration constant for the currently selected PID profile.
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
void SmartMotorController::SetI(double i) {
  c_Logger_Log(c_TalonSRX_SetIgain(m_handle, m_profile, i), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetIgain").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Set the derivative constant of the currently selected profile.
 *
 * @param d Derivative constant for the currently selected PID profile.
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
void SmartMotorController::SetD(double d) {
  c_Logger_Log(c_TalonSRX_SetDgain(m_handle, m_profile, d), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetDgain").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Set the feedforward value of the currently selected profile.
 *
 * @param f Feedforward constant for the currently selected PID profile.
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
void SmartMotorController::SetF(double f) {
  c_Logger_Log(c_TalonSRX_SetFgain(m_handle, m_profile, f), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetFgain").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Set the Izone to a nonzero value to auto clear the integral accumulator
 * when the absolute value of CloseLoopError exceeds Izone.
 *
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
void SmartMotorController::SetIzone(unsigned iz) {
  c_Logger_Log(c_TalonSRX_SetIzone(m_handle, m_profile, iz), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetIzone").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * SRX has two available slots for PID.
 * @param slotIdx one or zero depending on which slot caller wants.
 */
void SmartMotorController::SelectProfileSlot(int slotIdx) {
  m_profile = (slotIdx == 0) ? 0 : 1; /* only get two slots for now */
  c_Logger_Log(c_TalonSRX_SetProfileSlotSelect(m_handle, m_profile), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetProfileSlotSelect").c_str(), frc::GetStackTrace(2).c_str());
  ApplyUsageStats(UsageFlags::MultiProfile);
}

/**
 * Sets control values for closed loop control.
 *
 * @param p Proportional constant.
 * @param i Integration constant.
 * @param d Differential constant.
 *
 * This function does not modify F-gain.  Considerable passing a zero for f
 * using the four-parameter function.
 */
void SmartMotorController::SetPID(double p, double i, double d) {
  SetP(p);
  SetI(i);
  SetD(d);
}

/**
 * Sets control values for closed loop control.
 *
 * @param p Proportional constant.
 * @param i Integration constant.
 * @param d Differential constant.
 * @param f Feedforward constant.
 */
void SmartMotorController::SetPID(double p, double i, double d, double f) {
  SetP(p);
  SetI(i);
  SetD(d);
  SetF(f);
}

/**
 * Select the feedback device to use in closed-loop
 */
void SmartMotorController::SetFeedbackDevice(FeedbackDevice feedbackDevice) {
  /* save the selection so that future setters/getters know which scalars to
   * apply
   */
  m_feedbackDevice = feedbackDevice;
  /* pass feedback to actual CAN frame */
  c_Logger_Log(c_TalonSRX_SetFeedbackDeviceSelect(m_handle, static_cast<int>(feedbackDevice)), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetFeedbackDeviceSelect").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Select the feedback device to use in closed-loop
 */
void SmartMotorController::SetStatusFrameRateMs(StatusFrameRate stateFrame, int periodMs) {
      c_Logger_Log(c_TalonSRX_SetStatusFrameRate(m_handle, static_cast<int>(stateFrame), periodMs), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetStatusFrameRate").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Get the current proportional constant.
 *
 * @return double proportional constant for current profile.
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
double SmartMotorController::GetP() const {
  TalonSRX_CCI::param_t param = m_profile ? TalonSRX_CCI::eProfileParamSlot1_P
                                         : TalonSRX_CCI::eProfileParamSlot0_P;
  // Update the info in m_impl.
  CTR_Code status = c_TalonSRX_RequestParam(m_handle, param);
  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  double p;
  status = c_TalonSRX_GetPgain(m_handle, m_profile, &p);
  c_Logger_Log(status, ("TalonSRX " + std::to_string(m_deviceNumber) + "Get P").c_str(), frc::GetStackTrace(2).c_str());
  return p;
}

/**
 * TODO documentation (see CANJaguar.cpp)
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
double SmartMotorController::GetI() const {
  TalonSRX_CCI::param_t param = m_profile ? TalonSRX_CCI::eProfileParamSlot1_I
                                         : TalonSRX_CCI::eProfileParamSlot0_I;
  // Update the info in m_impl.
  CTR_Code status = c_TalonSRX_RequestParam(m_handle, param);
  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));

  double i;
  status = c_TalonSRX_GetIgain(m_handle, m_profile, &i);
  c_Logger_Log(status, ("TalonSRX " + std::to_string(m_deviceNumber) + "Get I").c_str(), frc::GetStackTrace(2).c_str());
  return i;
}

/**
 * TODO documentation (see CANJaguar.cpp)
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
double SmartMotorController::GetD() const {
  TalonSRX_CCI::param_t param = m_profile ? TalonSRX_CCI::eProfileParamSlot1_D
                                         : TalonSRX_CCI::eProfileParamSlot0_D;
  // Update the info in m_impl.
  CTR_Code status = c_TalonSRX_RequestParam(m_handle, param);
  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  double d;
  status = c_TalonSRX_GetDgain(m_handle, m_profile, &d);
  c_Logger_Log(status, ("TalonSRX " + std::to_string(m_deviceNumber) + "Get D").c_str(), frc::GetStackTrace(2).c_str());
  return d;
}

/**
 *
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
double SmartMotorController::GetF() const {
  TalonSRX_CCI::param_t param = m_profile ? TalonSRX_CCI::eProfileParamSlot1_F
                                         : TalonSRX_CCI::eProfileParamSlot0_F;
  // Update the info in m_impl.
  CTR_Code status = c_TalonSRX_RequestParam(m_handle, param);

  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  double f;
  status = c_TalonSRX_GetFgain(m_handle, m_profile, &f);
  c_Logger_Log(status, ("TalonSRX " + std::to_string(m_deviceNumber) + "Get F").c_str(), frc::GetStackTrace(2).c_str());
  return f;
}

/**
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
int SmartMotorController::GetIzone() const {
  TalonSRX_CCI::param_t param = m_profile
                                   ? TalonSRX_CCI::eProfileParamSlot1_IZone
                                   : TalonSRX_CCI::eProfileParamSlot0_IZone;
  // Update the info in m_impl.
  CTR_Code status = c_TalonSRX_RequestParam(m_handle, param);
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));

  int iz;
  status = c_TalonSRX_GetIzone(m_handle, m_profile, &iz);
  c_Logger_Log(status, ("TalonSRX " + std::to_string(m_deviceNumber) + " Get I Zone").c_str(), frc::GetStackTrace(2).c_str());
  return iz;
}

/**
 * @return the current setpoint; ie, whatever was last passed to Set().
 */
double SmartMotorController::GetSetpoint() const { return m_setPoint; }

/**
 * Returns the voltage coming in from the battery.
 *
 * @return The input voltage in volts.
 */
double SmartMotorController::GetBusVoltage() const {
  double voltage;
  c_Logger_Log(c_TalonSRX_GetBatteryV(m_handle, &voltage), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetBatteryV").c_str(), frc::GetStackTrace(2).c_str());
  return voltage;
}

/**
 * @return The voltage being output by the Talon, in Volts.
 */
double SmartMotorController::GetOutputVoltage() const {
  int throttle11;
  c_Logger_Log(c_TalonSRX_GetAppliedThrottle(m_handle, &throttle11), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetAppliedThrottle").c_str(), frc::GetStackTrace(2).c_str());
  double voltage = GetBusVoltage() * (static_cast<double>(throttle11) / 1023.0);
  return voltage;
}

/**
 *  Returns the current going through the Talon, in Amperes.
 */
double SmartMotorController::GetOutputCurrent() const {
  double current;

  c_Logger_Log(c_TalonSRX_GetCurrent(m_handle, &current), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetCurrent").c_str(), frc::GetStackTrace(2).c_str());

  return current;
}

/**
 *  Returns temperature of Talon, in degrees Celsius.
 */
double SmartMotorController::GetTemperature() const {
  double temp;

  c_Logger_Log(c_TalonSRX_GetTemp(m_handle, &temp), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetTemp").c_str(), frc::GetStackTrace(2).c_str());
  return temp;
}

/**
 * Set the position value of the selected sensor.  This is useful for zero-ing
 * quadrature encoders.
 *
 * Continuous sensors (like analog encoderes) can also partially be set (the
 * portion of the postion based on overflows).
 */
void SmartMotorController::SetPosition(double pos) {
  int32_t nativePos = ScaleRotationsToNativeUnits(m_feedbackDevice, pos);
  c_Logger_Log(c_TalonSRX_SetSensorPosition(m_handle, nativePos), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetSensorPosition").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * TODO documentation (see CANJaguar.cpp)
 *
 * @return The position of the sensor currently providing feedback.
 *         When using analog sensors, 0 units corresponds to 0V, 1023
 *         units corresponds to 3.3V.
 *         When using an analog encoder (wrapping around 1023 => 0 is
 *         possible) the units are still 3.3V per 1023 units.
 *         When using quadrature, each unit is a quadrature edge (4X) mode.
 */
double SmartMotorController::GetPosition() const {
  int32_t position;
  c_Logger_Log(c_TalonSRX_GetSensorPosition(m_handle, &position), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetSensorPosition").c_str(), frc::GetStackTrace(2).c_str());
  return ScaleNativeUnitsToRotations(m_feedbackDevice, position);
}

/**
 * If sensor and motor are out of phase, sensor can be inverted
 * (position and velocity multiplied by -1).
 * @see GetPosition and @see GetSpeed.
 */
void SmartMotorController::SetSensorDirection(bool reverseSensor) {
  c_Logger_Log(c_TalonSRX_SetRevFeedbackSensor(m_handle, reverseSensor ? 1 : 0), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetRevFeedbackSensor").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Flips the sign (multiplies by negative one) the throttle values going into
 * the motor on the talon in closed loop modes.  Typically the application
 * should use SetSensorDirection to keep sensor and motor in phase.
 * @see SetSensorDirection
 * However this routine is helpful for reversing the motor direction
 * when Talon is in slave mode, or when using a single-direction position
 * sensor in a closed-loop mode.
 *
 * @param reverseOutput True if motor output should be flipped; False if not.
 */
void SmartMotorController::SetClosedLoopOutputDirection(bool reverseOutput) {
  c_Logger_Log(c_TalonSRX_SetRevMotDuringCloseLoopEn(m_handle, reverseOutput ? 1 : 0), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetRevMotDuringCloseLoopEn").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Returns the current error in the controller.
 *
 * @return the difference between the setpoint and the sensor value.
 */
int SmartMotorController::GetClosedLoopError() const {
  int error;
  /* retrieve the closed loop error in native units */
  c_Logger_Log(c_TalonSRX_GetCloseLoopErr(m_handle, &error), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetCloseLoopErr").c_str(), frc::GetStackTrace(2).c_str());
  return error;
}

/**
 * Set the allowable closed loop error.
 *
 * @param allowableCloseLoopError allowable closed loop error for selected
 *                                profile.
 *
 * Units: mA for Curent closed loop.
 *        Talon Native Units for position and velocity.
 */
void SmartMotorController::SetAllowableClosedLoopErr(uint32_t allowableCloseLoopError) {
  /* grab param enum */
  TalonSRX_CCI::param_t param;
  if (m_profile == 1) {
    param = TalonSRX_CCI::eProfileParamSlot1_AllowableClosedLoopErr;
  } else {
    param = TalonSRX_CCI::eProfileParamSlot0_AllowableClosedLoopErr;
  }
  /* send allowable close loop er in native units */
  ConfigSetParameter(param, allowableCloseLoopError);
}

/**
 * TODO documentation (see CANJaguar.cpp)
 *
 * @returns The speed of the sensor currently providing feedback.
 *
 * The speed units will be in the sensor's native ticks per 100ms.
 *
 * For analog sensors, 3.3V corresponds to 1023 units. So a speed of 200
 * equates to ~0.645 dV per 100ms or 6.451 dV per second. If this is an analog
 * encoder, that likely means 1.9548 rotations per sec. For quadrature
 * encoders, each unit corresponds a quadrature edge (4X). So a 250 count
 * encoder will produce 1000 edge events per rotation. An example speed of 200
 * would then equate to 20% of a rotation per 100ms, or 10 rotations per second.
 */
double SmartMotorController::GetSpeed() const {
  int32_t speed;
  c_Logger_Log(c_TalonSRX_GetSensorVelocity(m_handle, &speed), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetSensorVelocity").c_str(), frc::GetStackTrace(2).c_str());
  return ScaleNativeUnitsToRpm(m_feedbackDevice, speed);
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 * whether it is actually being used for feedback.
 *
 * @returns The 24bit analog value.  The bottom ten bits is the ADC (0 - 1023)
 *          on the analog pin of the Talon. The upper 14 bits tracks the
 *          overflows and underflows (continuous sensor).
 */
int SmartMotorController::GetAnalogIn() const {
  int position;
  c_Logger_Log(c_TalonSRX_GetAnalogInWithOv(m_handle, &position), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetAnalogInWithOv").c_str(), frc::GetStackTrace(2).c_str());
  return position;
}

void SmartMotorController::SetAnalogPosition(int newPosition) {
  c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eAinPosition, newPosition), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 * whether it is actually being used for feedback.
 *
 * @returns The ADC (0 - 1023) on analog pin of the Talon.
 */
int SmartMotorController::GetAnalogInRaw() const { return GetAnalogIn() & 0x3FF; }

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 * whether it is actually being used for feedback.
 *
 * @returns The value (0 - 1023) on the analog pin of the Talon.
 */
int SmartMotorController::GetAnalogInVel() const {
  int vel;
  c_Logger_Log(c_TalonSRX_GetAnalogInVel(m_handle, &vel), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetAnalogInVel").c_str(), frc::GetStackTrace(2).c_str());
  return vel;
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 * whether it is actually being used for feedback.
 *
 * @returns The value (0 - 1023) on the analog pin of the Talon.
 */
int SmartMotorController::GetEncPosition() const {
  int position;
  c_Logger_Log(c_TalonSRX_GetEncPosition(m_handle, &position), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetEncPosition").c_str(), frc::GetStackTrace(2).c_str());
  return position;
}
void SmartMotorController::SetEncPosition(int newPosition) {
  c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eEncPosition, newPosition), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 * whether it is actually being used for feedback.
 *
 * @returns The value (0 - 1023) on the analog pin of the Talon.
 */
int SmartMotorController::GetEncVel() const {
  int vel;
  c_Logger_Log(c_TalonSRX_GetEncVel(m_handle, &vel), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetEncVel").c_str(), frc::GetStackTrace(2).c_str());
  return vel;
}
int SmartMotorController::GetPulseWidthPosition() const {
  int param;
  c_Logger_Log(c_TalonSRX_GetPulseWidthPosition(m_handle, &param), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetPulseWidthPosition").c_str(), frc::GetStackTrace(2).c_str());
  return param;
}
void SmartMotorController::SetPulseWidthPosition(int newPosition) {
  c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::ePwdPosition, newPosition), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}
int SmartMotorController::GetPulseWidthVelocity() const {
  int param;
  c_Logger_Log(c_TalonSRX_GetPulseWidthVelocity(m_handle, &param), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetPulseWidthVelocity").c_str(), frc::GetStackTrace(2).c_str());
  return param;
}
int SmartMotorController::GetPulseWidthRiseToFallUs() const {
  int param;
  c_Logger_Log(c_TalonSRX_GetPulseWidthRiseToFallUs(m_handle, &param), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetPulseWidthRiseToFallUs").c_str(), frc::GetStackTrace(2).c_str());
  return param;
}
int SmartMotorController::GetPulseWidthRiseToRiseUs() const {
  int param;
  c_Logger_Log(c_TalonSRX_GetPulseWidthRiseToRiseUs(m_handle, &param), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetPulseWidthRiseToRiseUs").c_str(), frc::GetStackTrace(2).c_str());
  return param;
}

/**
 * @param which feedback sensor to check it if is connected.
 * @return status of caller's specified sensor type.
 */
SmartMotorController::FeedbackDeviceStatus SmartMotorController::IsSensorPresent(
    FeedbackDevice feedbackDevice) const {
  FeedbackDeviceStatus retval = FeedbackStatusUnknown;
  int param;
  /* detecting sensor health depends on which sensor caller cares about */
  switch (feedbackDevice) {
    case QuadEncoder:
    case AnalogPot:
    case AnalogEncoder:
    case EncRising:
    case EncFalling:
      /* no real good way to tell if these sensor
        are actually present so return status unknown. */
      break;
    case PulseWidth:
    case CtreMagEncoder_Relative:
    case CtreMagEncoder_Absolute:
      /* all of these require pulse width signal to be present. */
      CTR_Code status = c_Logger_Log(c_TalonSRX_IsPulseWidthSensorPresent(m_handle, &param), ("TalonSRX " + std::to_string(m_deviceNumber) + " IsPulseWidthSensorPresent").c_str(), frc::GetStackTrace(2).c_str());
      if (status != OKAY) {
        /* we're not getting status info, signal unknown status */
      } else {
        /* param is updated */
        if (param) {
          /* pulse signal is present, sensor must be working since it always
            generates a pulse waveform.*/
          retval = FeedbackStatusPresent;
        } else {
          /* no pulse present, sensor disconnected */
          retval = FeedbackStatusNotPresent;
        }
      }
      break;
  }
  return retval;
}

/**
 * @return IO level of QUADA pin.
 */
int SmartMotorController::GetPinStateQuadA() const {
  int retval;
  c_Logger_Log(c_TalonSRX_GetQuadApin(m_handle, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetQuadApin").c_str(), frc::GetStackTrace(2).c_str());
  return retval;
}

/**
 * @return IO level of QUADB pin.
 */
int SmartMotorController::GetPinStateQuadB() const {
  int retval;
  c_Logger_Log(c_TalonSRX_GetQuadBpin(m_handle, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetQuadBpin").c_str(), frc::GetStackTrace(2).c_str());
  return retval;
}

/**
 * @return IO level of QUAD Index pin.
 */
int SmartMotorController::GetPinStateQuadIdx() const {
  int retval;
  c_Logger_Log(c_TalonSRX_GetQuadIdxpin(m_handle, &retval), "GetQuadIdxpin", frc::GetStackTrace(2).c_str());
  return retval;
}

/**
 * @return '1' iff forward limit switch is closed, 0 iff switch is open.
 * This function works regardless if limit switch feature is enabled.
 */
int SmartMotorController::IsFwdLimitSwitchClosed() const {
  int retval;
  c_Logger_Log(c_TalonSRX_GetLimitSwitchClosedFor(m_handle,
      &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetLimitSwitchClosedFor").c_str(), frc::GetStackTrace(2).c_str()); /* rename this func, '1' => open, '0' => closed */
  return retval ? 0 : 1;
}

/**
 * @return '1' iff reverse limit switch is closed, 0 iff switch is open.
 * This function works regardless if limit switch feature is enabled.
 */
int SmartMotorController::IsRevLimitSwitchClosed() const {
  int retval;
  c_Logger_Log(c_TalonSRX_GetLimitSwitchClosedRev(m_handle,
      &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetLimitSwitchClosedRev").c_str(), frc::GetStackTrace(2).c_str()); /* rename this func, '1' => open, '0' => closed */
  return retval ? 0 : 1;
}

/**
 * @return '1' if ClearPosOnLimF is enabled.
 */
int SmartMotorController::IsZeroSensorPositionOnForwardLimitEnabled() const {
	int retval;
	c_Logger_Log(c_TalonSRX_GetClearPosOnLimF(m_handle, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetClearPosOnLimF").c_str(), frc::GetStackTrace(2).c_str());
	return retval;
}

/**
 * @return '1' if ClearPosOnLimR is enabled.
 */
int SmartMotorController::IsZeroSensorPositionOnReverseLimitEnabled() const {
	int retval;
	c_Logger_Log(c_TalonSRX_GetClearPosOnLimR(m_handle, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetClearPosOnLimR").c_str(), frc::GetStackTrace(2).c_str());
	return retval;
}

/**
 * @return '1' if ClearPosOnLimIdx is enabled.
 */
int SmartMotorController::IsZeroSensorPositionOnIndexEnabled() const {
	int retval;
	c_Logger_Log(c_TalonSRX_GetClearPosOnIdx(m_handle, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetClearPosOnIdx").c_str(), frc::GetStackTrace(2).c_str());
	return retval;
}

/*
 * Simple accessor for tracked rise eventso index pin.
 * @return number of rising edges on idx pin.
 */
int SmartMotorController::GetNumberOfQuadIdxRises() const {
  int rises;
  c_Logger_Log(c_TalonSRX_GetEncIndexRiseEvents(m_handle, 
      &rises),( "TalonSRX" + std::to_string(m_deviceNumber) + " GetEncIndexRiseEvents").c_str(), frc::GetStackTrace(2).c_str()); /* rename this func, '1' => open, '0' => closed */
  return rises;
}

/*
 * @param rises integral value to set into index-rises register.  Great way to
 *              zero the index count.
 */
void SmartMotorController::SetNumberOfQuadIdxRises(int rises) {
  c_Logger_Log(c_TalonSRX_SetParam(m_handle,
      TalonSRX_CCI::eEncIndexRiseEvents,
      rises), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str()); /* rename this func, '1' => open, '0' => closed */
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
bool SmartMotorController::GetForwardLimitOK() const {
  int limSwit = 0;
  int softLim = 0;
  c_Logger_Log(c_TalonSRX_GetFault_ForSoftLim(m_handle, &softLim), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_ForSoftLim").c_str(), frc::GetStackTrace(2).c_str());
  c_Logger_Log(c_TalonSRX_GetFault_ForLim(m_handle, &limSwit), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_ForLim").c_str(), frc::GetStackTrace(2).c_str());
  /* If either fault is asserted, signal caller we are disabled (with false?) */
  return (softLim | limSwit) ? false : true;
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
bool SmartMotorController::GetReverseLimitOK() const {
  int limSwit = 0;
  int softLim = 0;
  c_Logger_Log(c_TalonSRX_GetFault_RevSoftLim(m_handle, &softLim), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_RevSoftLim").c_str(), frc::GetStackTrace(2).c_str());
  c_Logger_Log(c_TalonSRX_GetFault_RevLim(m_handle, &limSwit), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_RevLim").c_str(), frc::GetStackTrace(2).c_str());
  /* If either fault is asserted, signal caller we are disabled (with false?) */
  return (softLim | limSwit) ? false : true;
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
uint16_t SmartMotorController::GetFaults() const {
  uint16_t retval = 0;
  int val;

  /* temperature */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetFault_OverTemp(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_OverTemp").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kTemperatureFault : 0;

  /* voltage */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetFault_UnderVoltage(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_UnderVoltage").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kBusVoltageFault : 0;

  /* fwd-limit-switch */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetFault_ForLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_ForLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kFwdLimitSwitch : 0;

  /* rev-limit-switch */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetFault_RevLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_RevLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kRevLimitSwitch : 0;

  /* fwd-soft-limit */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetFault_ForSoftLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_ForSoftLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kFwdSoftLimit : 0;

  /* rev-soft-limit */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetFault_RevSoftLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetFault_RevSoftLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kRevSoftLimit : 0;

  return retval;
}

uint16_t SmartMotorController::GetStickyFaults() const {
  uint16_t retval = 0;
  int val;

  /* temperature */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetStckyFault_OverTemp(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetStckyFault_OverTemp").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kTemperatureFault : 0;

  /* voltage */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetStckyFault_UnderVoltage(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetStckyFault_UnderVoltage").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kBusVoltageFault : 0;

  /* fwd-limit-switch */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetStckyFault_ForLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetStckyFault_ForLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kFwdLimitSwitch : 0;

  /* rev-limit-switch */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetStckyFault_RevLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetStckyFault_RevLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kRevLimitSwitch : 0;

  /* fwd-soft-limit */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetStckyFault_ForSoftLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetStckyFault_ForSoftLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kFwdSoftLimit : 0;

  /* rev-soft-limit */
  val = 0;
  c_Logger_Log(c_TalonSRX_GetStckyFault_RevSoftLim(m_handle, &val), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetStckyFault_RevSoftLim").c_str(), frc::GetStackTrace(2).c_str());
  retval |= (val) ? kRevSoftLimit : 0;

  return retval;
}

void SmartMotorController::ClearStickyFaults() {
  c_Logger_Log(c_TalonSRX_ClearStickyFaults(m_handle), ("TalonSRX " + std::to_string(m_deviceNumber) + " ClearStickyFaults").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Set the maximum voltage change rate.  This ramp rate is in affect regardless
 * of which control mode the TALON is in.
 *
 * When in PercentVbus or Voltage output mode, the rate at which the voltage
 * changes can be limited to reduce current spikes.  Set this to 0.0 to disable
 * rate limiting.
 *
 * @param rampRate The maximum rate of voltage change in Percent Voltage mode
 *                 in V/s.
 */
void SmartMotorController::SetVoltageRampRate(double rampRate) {
  /* Caller is expressing ramp as Voltage per sec, assuming 12V is full.
          Talon's throttle ramp is in dThrot/d10ms.  1023 is full fwd, -1023 is
     full rev. */
  double rampRatedThrotPer10ms = (rampRate * 1023.0 / 12.0) / 100;
  ApplyUsageStats(UsageFlags::VRampRate);
      c_Logger_Log(c_TalonSRX_SetRampThrottle(m_handle, static_cast<int>(rampRatedThrotPer10ms)), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetRampThrottle").c_str(), frc::GetStackTrace(2).c_str());
}

void SmartMotorController::SetVoltageCompensationRampRate(double rampRate) {
  /* when in voltage compensation mode, the voltage compensation rate
    directly caps the change in target voltage */
  c_Logger_Log(c_TalonSRX_SetVoltageCompensationRate(m_handle, rampRate / 1000), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetVoltageCompensationRate").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Sets a voltage change rate that applies only when a close loop control mode
 * is enabled.
 * This allows close loop specific ramp behavior.
 *
 * @param rampRate The maximum rate of voltage change in Percent Voltage mode
 *                 in V/s.
 */
void SmartMotorController::SetCloseLoopRampRate(double rampRate) {
  c_Logger_Log(c_TalonSRX_SetCloseLoopRampRate(m_handle,
      m_profile, rampRate * 1023.0 / 12.0 / 1000.0), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetCloseLoopRampRate").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * @return The version of the firmware running on the Talon
 */
int SmartMotorController::GetFirmwareVersion() const {
  int firmwareVersion;
  c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eFirmVers), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  
  c_Logger_Log(c_TalonSRX_GetParamResponseInt32(m_handle, TalonSRX_CCI::eFirmVers, &firmwareVersion), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponseInt32").c_str(), frc::GetStackTrace(2).c_str());

  /* only sent once on boot */
  // CTR_Code status = c_Logger_Log(c_TalonSRX_GetFirmVers(firmwareVersion), "GetFirmVers", frc::GetStackTrace(2).c_str());
  // if (status != OKAY) {
  //  wpi_setErrorWithContext(status, HAL_GetErrorMessage(status));
  //}

  return firmwareVersion;
}

/**
 * @return The accumulator for I gain.
 */
int SmartMotorController::GetIaccum() const {
  c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::ePidIaccum), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  int iaccum;
  c_Logger_Log(c_TalonSRX_GetParamResponseInt32(m_handle, TalonSRX_CCI::ePidIaccum, &iaccum), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponseInt32").c_str(), frc::GetStackTrace(2).c_str());
  return iaccum;
}

/**
 * Clear the accumulator for I gain.
 */
void SmartMotorController::ClearIaccum() {
  c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::ePidIaccum, 0), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
void SmartMotorController::ConfigNeutralMode(NeutralMode mode) {
  switch (mode) {
    default:
    case kNeutralMode_Jumper:
      // use default setting in flash based on webdash/BrakeCal button selection
      c_Logger_Log(c_TalonSRX_SetOverrideBrakeType(m_handle,
          TalonSRX_CCI::kBrakeOverride_UseDefaultsFromFlash), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetOverrideBrakeType").c_str(), frc::GetStackTrace(2).c_str());
      break;
    case kNeutralMode_Brake:
      c_Logger_Log(c_TalonSRX_SetOverrideBrakeType(m_handle,
          TalonSRX_CCI::kBrakeOverride_OverrideBrake), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetOverrideBrakeType").c_str(), frc::GetStackTrace(2).c_str());
      break;
    case kNeutralMode_Coast:
      c_Logger_Log(c_TalonSRX_SetOverrideBrakeType(m_handle, 
          TalonSRX_CCI::kBrakeOverride_OverrideCoast), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetOverrideBrakeType").c_str(), frc::GetStackTrace(2).c_str());
      break;
  }
}

/**
 * @return nonzero if brake is enabled during neutral.  Zero if coast is enabled
 * during neutral.
 */
int SmartMotorController::GetBrakeEnableDuringNeutral() const {
  int brakeEn = 0;
  c_Logger_Log(c_TalonSRX_GetBrakeIsEnabled(m_handle, &brakeEn), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetBrakeIsEnabled").c_str(), frc::GetStackTrace(2).c_str());
  return brakeEn;
}

/**
 * Configure how many codes per revolution are generated by your encoder.
 *
 * @param codesPerRev The number of counts per revolution.
 */
void SmartMotorController::ConfigEncoderCodesPerRev(uint16_t codesPerRev) {
  /* first save the scalar so that all getters/setter work as the user expects
   */
  m_codesPerRev = codesPerRev;
  /* next send the scalar to the Talon over CAN.  This is so that the Talon can
   * report it to whoever needs it, like the webdash.  Don't bother checking
   * the return, this is only for instrumentation and is not necessary for
   * Talon functionality.
   */
  (void)c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eNumberEncoderCPR, m_codesPerRev), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Configure the number of turns on the potentiometer.
 *
 * @param turns The number of turns of the potentiometer.
 */
void SmartMotorController::ConfigPotentiometerTurns(uint16_t turns) {
  /* first save the scalar so that all getters/setter work as the user expects
   */
  m_numPotTurns = turns;
  /* next send the scalar to the Talon over CAN.  This is so that the Talon can
   * report it to whoever needs it, like the webdash.  Don't bother checking
   * the return, this is only for instrumentation and is not necessary for
   * Talon functionality.
   */
  (void)c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eNumberPotTurns, m_numPotTurns), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * @deprecated not implemented
 */
void SmartMotorController::ConfigSoftPositionLimits(double forwardLimitPosition,
                                        double reverseLimitPosition) {
  ConfigLimitMode(1);
  ConfigForwardLimit(forwardLimitPosition);
  ConfigReverseLimit(reverseLimitPosition);
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
void SmartMotorController::DisableSoftPositionLimits() {
  ConfigLimitMode(0);
}

/**
 * Overrides the forward and reverse limit switch enables.
 *
 * Unlike ConfigLimitMode, this function allows individual control of forward
 * and reverse limit switch enables.
 * Unlike ConfigLimitMode, this function does not affect the soft-limit features
 * of Talon SRX.
 * @see ConfigLimitMode()
 */
void SmartMotorController::ConfigLimitSwitchOverrides(bool bForwardLimitSwitchEn,
                                          bool bReverseLimitSwitchEn) {
  int fwdRevEnable;
  /* chose correct signal value based on caller's requests enables */
  if (!bForwardLimitSwitchEn) {
    /* caller wants Forward Limit Switch OFF */
    if (!bReverseLimitSwitchEn) {
      /* caller wants both OFF */
      fwdRevEnable = TalonSRX_CCI::kLimitSwitchOverride_DisableFwd_DisableRev;
    } else {
      /* caller Forward OFF and Reverse ON */
      fwdRevEnable = TalonSRX_CCI::kLimitSwitchOverride_DisableFwd_EnableRev;
    }
  } else {
    /* caller wants Forward Limit Switch ON */
    if (!bReverseLimitSwitchEn) {
      /* caller wants Forward ON and Reverse OFF */
      fwdRevEnable = TalonSRX_CCI::kLimitSwitchOverride_EnableFwd_DisableRev;
    } else {
      /* caller wants both ON */
      fwdRevEnable = TalonSRX_CCI::kLimitSwitchOverride_EnableFwd_EnableRev;
    }
  }
  /* update signal and error check code */
  c_Logger_Log(c_TalonSRX_SetOverrideLimitSwitchEn(m_handle, fwdRevEnable), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetOverrideLimitSwitchEn").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Configures the soft limit enable (wear leveled persistent memory).
 * Also sets the limit switch overrides.
 */
void SmartMotorController::ConfigLimitMode(int mode) {
  switch (mode) {
    case 0: /** Only use switches for limits */
      /* turn OFF both limits. SRX has individual enables and polarity for each
       * limit switch.*/
      c_Logger_Log(c_TalonSRX_SetForwardSoftEnable(m_handle, false), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetForwardSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
      c_Logger_Log(c_TalonSRX_SetReverseSoftEnable(m_handle, false), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetReverseSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
      /* override enable the limit switches, this circumvents the webdash */
      c_Logger_Log(c_TalonSRX_SetOverrideLimitSwitchEn(m_handle,
          TalonSRX_CCI::kLimitSwitchOverride_EnableFwd_EnableRev), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetOverrideLimitSwitchEn").c_str(), frc::GetStackTrace(2).c_str());
      break;
    case 1: /** Use both switches and soft limits */
      /* turn on both limits. SRX has individual enables and polarity for each
       * limit switch.*/
      c_Logger_Log(c_TalonSRX_SetForwardSoftEnable(m_handle, true), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetForwardSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
      c_Logger_Log(c_TalonSRX_SetReverseSoftEnable(m_handle, true), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetReverseSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
      /* override enable the limit switches, this circumvents the webdash */
      c_Logger_Log(c_TalonSRX_SetOverrideLimitSwitchEn(m_handle,
          TalonSRX_CCI::kLimitSwitchOverride_EnableFwd_EnableRev), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetOverrideLimitSwitchEn").c_str(), frc::GetStackTrace(2).c_str());
      break;

    case 2:
      // disable both limit switches and soft limits

      /* turn on both limits. SRX has individual enables and polarity for each
       * limit switch.*/
      c_Logger_Log(c_TalonSRX_SetForwardSoftEnable(m_handle, false), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetForwardSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
      c_Logger_Log(c_TalonSRX_SetReverseSoftEnable(m_handle, false), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetReverseSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
      /* override enable the limit switches, this circumvents the webdash */
      c_Logger_Log(c_TalonSRX_SetOverrideLimitSwitchEn(m_handle,
          TalonSRX_CCI::kLimitSwitchOverride_DisableFwd_DisableRev), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetOverrideLimitSwitchEn").c_str(), frc::GetStackTrace(2).c_str());
      break;
  }
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
void SmartMotorController::ConfigForwardLimit(double forwardLimitPosition) {
  int32_t nativeLimitPos =
      ScaleRotationsToNativeUnits(m_feedbackDevice, forwardLimitPosition);
  c_Logger_Log(c_TalonSRX_SetForwardSoftLimit(m_handle, nativeLimitPos), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetForwardSoftLimit").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Set the Forward Soft Limit Enable.
 *
 * This is the same setting that is in the Web-Based Configuration.
 *
 * @param bForwardSoftLimitEn true to enable Soft limit, false to disable.
 */
void SmartMotorController::ConfigForwardSoftLimitEnable(bool bForwardSoftLimitEn) {
  c_Logger_Log(c_TalonSRX_SetForwardSoftEnable(m_handle, bForwardSoftLimitEn), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetForwardSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
  ApplyUsageStats(UsageFlags::ForwardSoftLimit);
}

/**
 * Set the Reverse Soft Limit Enable.
 *
 * This is the same setting that is in the Web-Based Configuration.
 *
 * @param bReverseSoftLimitEn true to enable Soft limit, false to disable.
 */
void SmartMotorController::ConfigReverseSoftLimitEnable(bool bReverseSoftLimitEn) {
  c_Logger_Log(c_TalonSRX_SetReverseSoftEnable(m_handle, bReverseSoftLimitEn), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetReverseSoftEnable").c_str(), frc::GetStackTrace(2).c_str());
  ApplyUsageStats(UsageFlags::ReverseSoftLimit);
}

/**
 * Change the fwd limit switch setting to normally open or closed.
 * Talon will disable momentarilly if the Talon's current setting
 * is dissimilar to the caller's requested setting.
 *
 * Since Talon saves setting to flash this should only affect
 * a given Talon initially during robot install.
 *
 * @param normallyOpen true for normally open.  false for normally closed.
 */
void SmartMotorController::ConfigFwdLimitSwitchNormallyOpen(bool normallyOpen) {
      c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eOnBoot_LimitSwitch_Forward_NormallyClosed,
                       normallyOpen ? 0 : 1), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * Change the rev limit switch setting to normally open or closed.
 * Talon will disable momentarilly if the Talon's current setting
 * is dissimilar to the caller's requested setting.
 *
 * Since Talon saves setting to flash this should only affect
 * a given Talon initially during robot install.
 *
 * @param normallyOpen true for normally open.  false for normally closed.
 */
void SmartMotorController::ConfigRevLimitSwitchNormallyOpen(bool normallyOpen) {
    c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eOnBoot_LimitSwitch_Reverse_NormallyClosed,
                  normallyOpen ? 0 : 1), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
void SmartMotorController::ConfigReverseLimit(double reverseLimitPosition) {
  int32_t nativeLimitPos =
      ScaleRotationsToNativeUnits(m_feedbackDevice, reverseLimitPosition);
  c_Logger_Log(c_TalonSRX_SetReverseSoftLimit(m_handle, nativeLimitPos), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetReverseSoftLimit").c_str(), frc::GetStackTrace(2).c_str());
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
void SmartMotorController::ConfigMaxOutputVoltage(double voltage) {
  /* config peak throttle when in closed-loop mode in the fwd and rev direction.
   */
  ConfigPeakOutputVoltage(voltage, -voltage);
}

void SmartMotorController::ConfigPeakOutputVoltage(double forwardVoltage,
                                       double reverseVoltage) {
  /* bounds checking */
  if (forwardVoltage > 12)
    forwardVoltage = 12;
  else if (forwardVoltage < 0)
    forwardVoltage = 0;
  if (reverseVoltage > 0)
    reverseVoltage = 0;
  else if (reverseVoltage < -12)
    reverseVoltage = -12;
  /* config calls */
  ConfigSetParameter(TalonSRX_CCI::ePeakPosOutput, 1023 * forwardVoltage / 12.0);
  ConfigSetParameter(TalonSRX_CCI::ePeakNegOutput, 1023 * reverseVoltage / 12.0);
}

void SmartMotorController::ConfigNominalOutputVoltage(double forwardVoltage,
                                          double reverseVoltage) {
  /* bounds checking */
  if (forwardVoltage > 12)
    forwardVoltage = 12;
  else if (forwardVoltage < 0)
    forwardVoltage = 0;
  if (reverseVoltage > 0)
    reverseVoltage = 0;
  else if (reverseVoltage < -12)
    reverseVoltage = -12;
  /* config calls */
  ConfigSetParameter(TalonSRX_CCI::eNominalPosOutput,
                     1023 * forwardVoltage / 12.0);
  ConfigSetParameter(TalonSRX_CCI::eNominalNegOutput,
                     1023 * reverseVoltage / 12.0);
}

/**
 * General set frame.  Since the parameter is a general integral type, this can
 * be used for testing future features.
 */
int SmartMotorController::ConfigSetParameter(uint32_t paramEnum, double value) {
  CTR_Code status;
  /* config peak throttle when in closed-loop mode in the positive direction. */
  status = c_Logger_Log(c_TalonSRX_SetParam(m_handle, (TalonSRX_CCI::param_t)paramEnum, value), "", frc::GetStackTrace(2).c_str());
  return status;
}

/**
 * General get frame.  Since the parameter is a general integral type, this can
 * be used for testing future features.
 */
bool SmartMotorController::GetParameter(uint32_t paramEnum, double& dvalue) const {
  bool retval = true;
  /* send the request frame */
  CTR_Code status = c_Logger_Log(c_TalonSRX_RequestParam(m_handle, (TalonSRX_CCI::param_t)paramEnum), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
  if (status != OKAY) {
    retval = false;
  }
  /* small yield for getting response */
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  /* get the last received update */
  status = c_Logger_Log(c_TalonSRX_GetParamResponse(m_handle, (TalonSRX_CCI::param_t)paramEnum, &dvalue), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponse").c_str(), frc::GetStackTrace(2).c_str());
  if (status != OKAY) {
    retval = false;
  }
  return retval;
}

/**
 * TODO documentation (see CANJaguar.cpp)
 */
void SmartMotorController::ConfigFaultTime(double faultTime) {
  /* SRX does not have fault time.  SRX motor drive is only disabled for soft
   * limits and limit-switch faults. */
  wpi_setWPIErrorWithContext(IncompatibleMode, "Fault Time not supported.");
}
  
  void SmartMotorController::ApplyUsageStats(UsageFlags Usage)
  {
	if((Usage & m_usageHist) == 0)
	{  
		m_usageHist |= Usage;

		HAL_Report(HALUsageReporting::kResourceType_CANTalonSRX, m_deviceNumber + 1, m_usageHist);
	}
  }
  
  SmartMotorController::UsageFlags SmartMotorController::ControlModeUsage(ControlMode::SmartControlMode mode)
  {
	  switch (mode)
	  {
		case ControlMode::SmartControlMode::kPercentVbus:
			{return UsageFlags::PercentVbus; }
		case ControlMode::SmartControlMode::kPosition:
			{return UsageFlags::Position; }
		case ControlMode::SmartControlMode::kSpeed:
			{return UsageFlags::Speed; }
		case ControlMode::SmartControlMode::kCurrent:
			{return UsageFlags::Current; }
		case ControlMode::SmartControlMode::kVoltage:
			{return UsageFlags::Voltage; }
		case ControlMode::SmartControlMode::kFollower:
			{return UsageFlags::Follower; }
		case ControlMode::SmartControlMode::kMotionProfile:
			{return UsageFlags::MotionProfile; }
		case ControlMode::SmartControlMode::kMotionMagic:
			{return UsageFlags::MotionMagic; }
		default:
			{return UsageFlags::Default; }
	  }
  }
  
  
/**
 * Fixup the sendMode so Set() serializes the correct demand value.
 * Also fills the modeSelecet in the control frame to disabled.
 * @param mode Control mode to ultimately enter once user calls Set().
 * @see Set()
 */
void SmartMotorController::ApplyControlMode(ControlMode::SmartControlMode talonMode) {
  m_sendMode = talonMode;
  ApplyUsageStats(ControlModeUsage(talonMode));

  // Keep the talon disabled until Set() is called.
  c_Logger_Log(c_TalonSRX_SetModeSelect(m_handle, static_cast<int>(ControlMode::SmartControlMode::kDisabled)), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetModeSelect").c_str(), frc::GetStackTrace(2).c_str());
}


void SmartMotorController::SetControlMode(ControlMode::BasicControlMode mode) {
	ControlMode::SmartControlMode promotedBasic = ControlMode::Promote(mode);
	SetControlMode(promotedBasic);
}
void SmartMotorController::SetControlMode(ControlMode::SmartControlMode mode) {
	if(m_sendMode == mode) { /*Do nothing*/ }
	else {
		ApplyControlMode(mode);
	}
}
  
void SmartMotorController::SetTalonControlMode(ControlMode::SmartControlMode talonControlMode) {

  if (m_sendMode == talonControlMode) {
    /* we already are in this mode, don't perform disable workaround */
  } else {
    ApplyControlMode(talonControlMode);
  }
}
/**
 * TODO documentation (see CANJaguar.cpp)
 */
ControlMode::SmartControlMode SmartMotorController::GetControlMode() const {
  return m_sendMode;
}

void SmartMotorController::SetExpiration(double timeout) {
  m_safetyHelper->SetExpiration(timeout);
}

double SmartMotorController::GetExpiration() const {
  return m_safetyHelper->GetExpiration();
}

bool SmartMotorController::IsAlive() const { return m_safetyHelper->IsAlive(); }

bool SmartMotorController::IsSafetyEnabled() const {
  return m_safetyHelper->IsSafetyEnabled();
}

void SmartMotorController::SetSafetyEnabled(bool enabled) {
  m_safetyHelper->SetSafetyEnabled(enabled);
}

void SmartMotorController::GetDescription(std::ostringstream& desc){
  desc << "SmartMotorController ID " << m_deviceNumber;
}

/**
 * @param devToLookup FeedbackDevice to lookup the scalar for.  Because Talon
 *                    allows multiple sensors to be attached simultaneously,
 *                    caller must specify which sensor to lookup.
 * @return The number of native Talon units per rotation of the selected
 *         sensor. Zero if the necessary sensor information is not available.
 * @see ConfigEncoderCodesPerRev
 * @see ConfigPotentiometerTurns
 */
double SmartMotorController::GetNativeUnitsPerRotationScalar(
    FeedbackDevice devToLookup) const {
  bool scalingAvail = false;
  double retval = 0;
  switch (devToLookup) {
    case QuadEncoder: {
      /* When caller wants to lookup Quadrature, the QEI may be in 1x if the
       * selected feedback is edge counter. Additionally if the quadrature
       * source is the CTRE Mag encoder, then the CPR is known. This is nice in
       * that the calling app does not require knowing the CPR at all. So do
       * both checks here.
       */
      int32_t qeiPulsePerCount = 4; /* default to 4x */
      switch (m_feedbackDevice) {
        case CtreMagEncoder_Relative:
        case CtreMagEncoder_Absolute:
          /* we assume the quadrature signal comes from the MagEnc,
            of which we know the CPR already */
          retval = kNativePwdUnitsPerRotation;
          scalingAvail = true;
          break;
        case EncRising: /* Talon's QEI is setup for 1x, so perform 1x math */
        case EncFalling:
          qeiPulsePerCount = 1;
          break;
        case QuadEncoder: /* Talon's QEI is 4x */
        default:
          // pulse width and everything else, assume its regular quad use.
          break;
      }
      if (scalingAvail) {
        /* already deduced the scalar above, we're done. */
      } else {
        /* we couldn't deduce the scalar just based on the selection */
        if (0 == m_codesPerRev) {
          /* caller has never set the CPR.  Most likely caller
           * is just using engineering units so fall to the
           * bottom of this func.
           */
        } else {
          /* Talon expects PPR units */
          retval = qeiPulsePerCount * m_codesPerRev;
          scalingAvail = true;
        }
      }
    } break;
    case EncRising:
    case EncFalling:
      if (0 == m_codesPerRev) {
        /* caller has never set the CPR.  Most likely caller
         * is just using engineering units so fall to the
         * bottom of this func.
         */
      } else {
        /* Talon expects PPR units */
        retval = 1 * m_codesPerRev;
        scalingAvail = true;
      }
      break;
    case AnalogPot:
    case AnalogEncoder:
      if (0 == m_numPotTurns) {
        /* caller has never set the CPR.  Most likely caller
         * is just using engineering units so fall to the
         * bottom of this func.
         */
      } else {
        retval =
            static_cast<double>(kNativeAdcUnitsPerRotation) / m_numPotTurns;
        scalingAvail = true;
      }
      break;
    case CtreMagEncoder_Relative:
    case CtreMagEncoder_Absolute:
    case PulseWidth:
      retval = kNativePwdUnitsPerRotation;
      scalingAvail = true;
      break;
  }
  /* handle any detected errors */
  /* if scaling information is not possible, signal caller
   * by returning zero
   */
  if (false == scalingAvail) retval = 0;
  return retval;
}

/**
 * @param fullRotations double precision value representing number of
 *                      rotations of selected feedback sensor. If user has
 *                      never called the config routine for the selected
 *                      sensor, then the caller is likely passing rotations
 *                      in engineering units already, in which case it is
 *                      returned as is.
 * @see ConfigPotentiometerTurns
 * @see ConfigEncoderCodesPerRev
 * @return fullRotations in native engineering units of the Talon SRX firmware.
 */
int32_t SmartMotorController::ScaleRotationsToNativeUnits(FeedbackDevice devToLookup,
                                              double fullRotations) const {
  /* first assume we don't have config info, prep the default return */
  int32_t retval = static_cast<int32_t>(fullRotations);
  /* retrieve scaling info */
  double scalar = GetNativeUnitsPerRotationScalar(devToLookup);
  /* apply scalar if its available */
  if (scalar > 0) retval = static_cast<int32_t>(fullRotations * scalar);
  return retval;
}

/**
 * @param rpm double precision value representing number of rotations per
 *            minute of selected feedback sensor. If user has never called
 *            the config routine for the selected sensor, then the caller is
 *            likely passing rotations in engineering units already, in which
 *            case it is returned as is.
 * @see ConfigPotentiometerTurns
 * @see ConfigEncoderCodesPerRev
 * @return sensor velocity in native engineering units of the Talon SRX
 *         firmware.
 */
int32_t SmartMotorController::ScaleVelocityToNativeUnits(FeedbackDevice devToLookup,
                                             double rpm) const {
  /* first assume we don't have config info, prep the default return */
  int32_t retval = static_cast<int32_t>(rpm);
  /* retrieve scaling info */
  double scalar = GetNativeUnitsPerRotationScalar(devToLookup);
  /* apply scalar if its available */
  if (scalar > 0) {
    retval = static_cast<int32_t>(rpm * kMinutesPer100msUnit * scalar);
  }
  return retval;
}

/**
 * @param nativePos integral position of the feedback sensor in native Talon
 *                  SRX units. If user has never called the config routine for
 *                  the selected sensor, then the return will be in TALON SRX
 *                  units as well to match the behavior in the 2015 season.
 * @see ConfigPotentiometerTurns
 * @see ConfigEncoderCodesPerRev
 * @return double precision number of rotations, unless config was never
 *         performed.
 */
double SmartMotorController::ScaleNativeUnitsToRotations(FeedbackDevice devToLookup,
                                             int32_t nativePos) const {
  /* first assume we don't have config info, prep the default return */
  double retval = static_cast<double>(nativePos);
  /* retrieve scaling info */
  double scalar = GetNativeUnitsPerRotationScalar(devToLookup);
  /* apply scalar if its available */
  if (scalar > 0) retval = static_cast<double>(nativePos) / scalar;
  return retval;
}

/**
 * @param nativeVel integral velocity of the feedback sensor in native Talon
 *                  SRX units. If user has never called the config routine for
 *                  the selected sensor, then the return will be in TALON SRX
 *                  units as well to match the behavior in the 2015 season.
 * @see ConfigPotentiometerTurns
 * @see ConfigEncoderCodesPerRev
 * @return double precision of sensor velocity in RPM, unless config was never
 *         performed.
 */
double SmartMotorController::ScaleNativeUnitsToRpm(FeedbackDevice devToLookup,
                                       int32_t nativeVel) const {
  /* first assume we don't have config info, prep the default return */
  double retval = static_cast<double>(nativeVel);
  /* retrieve scaling info */
  double scalar = GetNativeUnitsPerRotationScalar(devToLookup);
  /* apply scalar if its available */
  if (scalar > 0)
    retval = static_cast<double>(nativeVel) / (scalar * kMinutesPer100msUnit);
  return retval;
}

/**
 * Enables Talon SRX to automatically zero the Sensor Position whenever an
 * edge is detected on the index signal.
 *
 * @param enable     boolean input, pass true to enable feature or false to
 *                   disable.
 * @param risingEdge boolean input, pass true to clear the position on rising
 *                   edge, pass false to clear the position on falling edge.
 */
void SmartMotorController::EnableZeroSensorPositionOnIndex(bool enable, bool risingEdge) {
  if (enable) {
    /* enable the feature, update the edge polarity first to ensure
      it is correct before the feature is enabled. */
    ConfigSetParameter(TalonSRX_CCI::eQuadIdxPolarity, risingEdge ? 1 : 0);
    ConfigSetParameter(TalonSRX_CCI::eClearPositionOnIdx, 1);
  } else {
    /* disable the feature first, then update the edge polarity. */
    ConfigSetParameter(TalonSRX_CCI::eClearPositionOnIdx, 0);
    ConfigSetParameter(TalonSRX_CCI::eQuadIdxPolarity, risingEdge ? 1 : 0);
  }
  ApplyUsageStats(UsageFlags::ZeroSensorI);
}

/**
 * Enables Talon SRX to automatically zero the Sensor Position whenever an
 * edge is detected on the Forward Limit Switch signal.
 *
 * @param enable     boolean input, pass true to enable feature or false to
 *                   disable.
 */
void SmartMotorController::EnableZeroSensorPositionOnForwardLimit(bool enable){
	ConfigSetParameter(TalonSRX_CCI::eClearPositionOnLimitF, enable ? 1 : 0);
	ApplyUsageStats(UsageFlags::ZeroSensorF);
}

/**
 * Enables Talon SRX to automatically zero the Sensor Position whenever an
 * edge is detected on the Reverse Limit Switch signal.
 *
 * @param enable     boolean input, pass true to enable feature or false to
 *                   disable.
 */
void SmartMotorController::EnableZeroSensorPositionOnReverseLimit(bool enable){
	ConfigSetParameter(TalonSRX_CCI::eClearPositionOnLimitR, enable ? 1 : 0);
	ApplyUsageStats(UsageFlags::ZeroSensorR);
}

/**
* @param voltage       Motor voltage to output when closed loop features are being used (Position,
*                      Speed, Motion Profile, Motion Magic, etc.) in volts.
*                      Pass 0 to disable feature.  Input should be within [0.0 V,255.0 V]
*/
void SmartMotorController::SetNominalClosedLoopVoltage(double voltage){
	c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eNominalBatteryVoltage, voltage), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
* Disables the nominal closed loop voltage compensation.
* Same as calling SetNominalClosedLoopVoltage(0).
*/
void SmartMotorController::DisableNominalClosedLoopVoltage(){
	SetNominalClosedLoopVoltage(0.0);
}

/**
* @return the currently selected nominal closed loop voltage. Zero (Default) means feature is disabled.
*/
double SmartMotorController::GetNominalClosedLoopVoltage(){
  c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eNominalBatteryVoltage), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());

  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  
    /* get the last received update */
  double retval;
  c_Logger_Log(c_TalonSRX_GetParamResponse(m_handle, TalonSRX_CCI::eNominalBatteryVoltage, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponse").c_str(), frc::GetStackTrace(2).c_str());
  
  return retval;
}

/**
* Sets the duration of time that the Talon measures for each velocity measurement (which occures at each 1ms process loop).
* The default value is 100, which means that every process loop (1ms), the Talon will measure the change in position
* between now and 100ms ago, and will insert into a rolling average.
*
* Decreasing this from the default (100ms) will yield a less-resolute measurement since there is less time for the sensor to change.
* This will be perceived as increased granularity in the measurement (or stair-stepping).  But doing so will also decrease the latency 
* between sensor motion and measurement.
* 
* Regardles of this setting value, native velocity units are still in change-in-sensor-per-100ms.
* 
* @param period      Support period enum.  Curent valid values are 1,2,5,10,20,25,50, or 100ms.
*/
void SmartMotorController::SetVelocityMeasurementPeriod(VelocityMeasurementPeriod period){
	c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eSampleVelocityPeriod, (int32_t)period), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

/**
* Sets the window size of the rolling average used in velocity measurement.
* The default value is 64, which means that every process loop (1ms), the Talon will insert a velocity measurement 
* into a windowed averager with a history of 64 samples.
* Each sample is inserted every 1ms regardless of what Period is selected. 
* As a result the window is practically in ms units.
* 
* @param windowSize    Window size of rolling average.
*/
void SmartMotorController::SetVelocityMeasurementWindow(uint32_t windowSize){
	c_Logger_Log(c_TalonSRX_SetParam(m_handle, TalonSRX_CCI::eSampleVelocityWindow, (int32_t)windowSize), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetParam").c_str(), frc::GetStackTrace(2).c_str());
}

SmartMotorController::VelocityMeasurementPeriod SmartMotorController::GetVelocityMeasurementPeriod(){
  c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eSampleVelocityPeriod), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());

  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  
    /* get the last received update */
  int32_t retval;
  c_Logger_Log(c_TalonSRX_GetParamResponseInt32(m_handle, TalonSRX_CCI::eSampleVelocityPeriod, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponseInt32").c_str(), frc::GetStackTrace(2).c_str());
  
  return (SmartMotorController::VelocityMeasurementPeriod)retval;
}

uint32_t SmartMotorController::GetVelocityMeasurementWindow(){
  c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eSampleVelocityWindow), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());

  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  
    /* get the last received update */
  int32_t retval;
  c_Logger_Log(c_TalonSRX_GetParamResponseInt32(m_handle, TalonSRX_CCI::eSampleVelocityWindow, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponseInt32").c_str(), frc::GetStackTrace(2).c_str());
  
  return (uint32_t)retval;
}

/**
 * Calling application can opt to speed up the handshaking between the robot API
 * and the Talon to increase the download rate of the Talon's Motion Profile.
 * Ideally the period should be no more than half the period of a trajectory
 * point.
 */
void SmartMotorController::ChangeMotionControlFramePeriod(int periodMs) {
  c_TalonSRX_ChangeMotionControlFramePeriod(m_handle, periodMs);
}

/**
 * Clear the buffered motion profile in both Talon RAM (bottom), and in the API
 * (top).
 *
 * Be sure to check GetMotionProfileStatus() to know when the buffer is actually
 * cleared.
 */
void SmartMotorController::ClearMotionProfileTrajectories() {
  c_TalonSRX_ClearMotionProfileTrajectories(m_handle);
}

/**
 * Retrieve just the buffer count for the api-level (top) buffer.
 *
 * This routine performs no CAN or data structure lookups, so its fast and ideal
 * if caller needs to quickly poll the progress of trajectory points being
 * emptied into Talon's RAM. Otherwise just use GetMotionProfileStatus.
 *
 * @return number of trajectory points in the top buffer.
 */
int SmartMotorController::GetMotionProfileTopLevelBufferCount() {
  return c_TalonSRX_GetMotionProfileTopLevelBufferCount(m_handle);
}

/**
 * Push another trajectory point into the top level buffer (which is emptied
 * into the Talon's bottom buffer as room allows).
 *
 * @param trajPt the trajectory point to insert into buffer.
 * @return true if trajectory point push ok. CTR_BufferFull if buffer is full
 *         due to kMotionProfileTopBufferCapacity.
 */
bool SmartMotorController::PushMotionProfileTrajectory(const TrajectoryPoint& trajPt) {
  /* convert positiona and velocity to native units */
  int32_t targPos = ScaleRotationsToNativeUnits(m_feedbackDevice, trajPt.position);
  int32_t targVel = ScaleVelocityToNativeUnits(m_feedbackDevice, trajPt.velocity);
  /* bounds check signals that require it */
  uint32_t profileSlotSelect = (trajPt.profileSlotSelect) ? 1 : 0;
  uint8_t timeDurMs = (trajPt.timeDurMs >= 255)
                          ? 255
                          : trajPt.timeDurMs; /* cap time to 255ms */
  /* send it to the top level buffer */
  CTR_Code status = c_Logger_Log(c_TalonSRX_PushMotionProfileTrajectory(m_handle,
      targPos, targVel, profileSlotSelect, timeDurMs, trajPt.velocityOnly,
      trajPt.isLastPoint, trajPt.zeroPos), ("TalonSRX " + std::to_string(m_deviceNumber) + " PushMotionProfileTrajectory").c_str(), frc::GetStackTrace(2).c_str());
  return (status == OKAY) ? true : false;
}

/**
 * @return true if api-level (top) buffer is full.
 */
bool SmartMotorController::IsMotionProfileTopLevelBufferFull() {
  return c_TalonSRX_IsMotionProfileTopLevelBufferFull(m_handle);
}

/**
 * This must be called periodically to funnel the trajectory points from the
 * API's top level buffer to the Talon's bottom level buffer.  Recommendation
 * is to call this twice as fast as the executation rate of the motion profile.
 * So if MP is running with 20ms trajectory points, try calling this routine
 * every 10ms.  All motion profile functions are thread-safe through the use of
 * a mutex, so there is no harm in having the caller utilize threading.
 */
void SmartMotorController::ProcessMotionProfileBuffer() {
  c_TalonSRX_ProcessMotionProfileBuffer(m_handle);
}

/**
 * Retrieve all status information.
 *
 * Since this all comes from one CAN frame, its ideal to have one routine to
 * retrieve the frame once and decode everything.
 *
 * @param [out] motionProfileStatus contains all progress information on the
 *                                  currently running MP.
 */
void SmartMotorController::GetMotionProfileStatus(
    MotionProfileStatus& motionProfileStatus) {
  int32_t flags;
  int32_t profileSlotSelect;
  int32_t targPos, targVel;
  int32_t topBufferRem, topBufferCnt, btmBufferCnt;
  int32_t outputEnable;
  /* retrieve all motion profile signals from status frame */
  c_Logger_Log(c_TalonSRX_GetMotionProfileStatus(m_handle, 
      &flags, &profileSlotSelect, &targPos, &targVel, &topBufferRem, &topBufferCnt,
      &btmBufferCnt, &outputEnable), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetMotionProfileStatus").c_str(), frc::GetStackTrace(2).c_str());
  /* completely update the caller's structure */
  motionProfileStatus.topBufferRem = topBufferRem;
  motionProfileStatus.topBufferCnt = topBufferCnt;
  motionProfileStatus.btmBufferCnt = btmBufferCnt;
  motionProfileStatus.hasUnderrun =
      (flags & TalonSRX_CCI::kMotionProfileFlag_HasUnderrun) ? true : false;
  motionProfileStatus.isUnderrun =
      (flags & TalonSRX_CCI::kMotionProfileFlag_IsUnderrun) ? true : false;
  motionProfileStatus.activePointValid =
      (flags & TalonSRX_CCI::kMotionProfileFlag_ActTraj_IsValid) ? true : false;
  motionProfileStatus.activePoint.isLastPoint =
      (flags & TalonSRX_CCI::kMotionProfileFlag_ActTraj_IsLast) ? true : false;
  motionProfileStatus.activePoint.velocityOnly =
      (flags & TalonSRX_CCI::kMotionProfileFlag_ActTraj_VelOnly) ? true : false;
  motionProfileStatus.activePoint.position =
      ScaleNativeUnitsToRotations(m_feedbackDevice, targPos);
  motionProfileStatus.activePoint.velocity =
      ScaleNativeUnitsToRpm(m_feedbackDevice, targVel);
  motionProfileStatus.activePoint.profileSlotSelect = profileSlotSelect;
  switch (outputEnable) {
    case TalonSRX_CCI::kMotionProf_Disabled:
      motionProfileStatus.outputEnable = SetValueMotionProfileDisable;
      break;
    case TalonSRX_CCI::kMotionProf_Enable:
      motionProfileStatus.outputEnable = SetValueMotionProfileEnable;
      break;
    case TalonSRX_CCI::kMotionProf_Hold:
      motionProfileStatus.outputEnable = SetValueMotionProfileHold;
      break;
    default:
      motionProfileStatus.outputEnable = SetValueMotionProfileDisable;
      break;
  }
  motionProfileStatus.activePoint.zeroPos =
      false; /* this signal is only used sending pts to Talon */
  motionProfileStatus.activePoint.timeDurMs =
      0; /* this signal is only used sending pts to Talon */

}

/**
 * Clear the hasUnderrun flag in Talon's Motion Profile Executer when MPE is
 * ready for another point, but the low level buffer is empty.
 *
 * Once the Motion Profile Executer sets the hasUnderrun flag, it stays set
 * until Robot Application clears it with this routine, which ensures Robot
 * Application gets a chance to instrument or react.  Caller could also check
 * the isUnderrun flag which automatically clears when fault condition is
 * removed.
 */
void SmartMotorController::ClearMotionProfileHasUnderrun() {
  ConfigSetParameter(TalonSRX_CCI::eMotionProfileHasUnderrunErr, 0);
}
/**
 * Set the Cruise Velocity used in Motion Magic Control Mode.
 * @param motmagicCruiseVeloc Cruise(peak) velocity in RPM.
 */
int SmartMotorController::SetMotionMagicCruiseVelocity(double motMagicCruiseVeloc)
{
	int32_t velNative = ScaleVelocityToNativeUnits(m_feedbackDevice, motMagicCruiseVeloc);
	return ConfigSetParameter(TalonSRX_CCI::eMotMag_VelCruise, (double)velNative);
}
/**
 * Set the Acceleration used in Motion Magic Control Mode.
 * @param motMagicAccel Accerleration in RPM per second.
 */
int SmartMotorController::SetMotionMagicAcceleration(double motMagicAccel)
{
	int accel = ScaleVelocityToNativeUnits(m_feedbackDevice, motMagicAccel);
	return ConfigSetParameter(TalonSRX_CCI::eMotMag_Accel, accel);
}
/**
 * @return polled motion magic cruise velocity setting from Talon.
 * RPM if units are configured, velocity native units otherwise.
 */
double SmartMotorController::GetMotionMagicCruiseVelocity()
{
// Update the info in m_impl.
  c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eMotMag_VelCruise), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
  // small yield for getting response
  std::this_thread::sleep_for(
      std::chrono::microseconds(kDelayForSolicitedSignalsUs));
  
    /* get the last received update */
  double retval;
  c_Logger_Log(c_TalonSRX_GetParamResponse(m_handle, TalonSRX_CCI::eMotMag_VelCruise, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponse").c_str(), frc::GetStackTrace(2).c_str());
  
  return ScaleNativeUnitsToRpm(m_feedbackDevice, (int32_t)retval);
}
/**
 * @return polled motion magic acceleration setting from Talon.
 * RPM per second if units are configured, velocity native units per second otherwise.
 */
double SmartMotorController::GetMotionMagicAcceleration() {
	// Update the info in m_impl.
	c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eMotMag_Accel), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
	// small yield for getting response
	std::this_thread::sleep_for(
			std::chrono::microseconds(kDelayForSolicitedSignalsUs));

	/* get the last received update */
	double retval;
	c_Logger_Log(c_TalonSRX_GetParamResponse(m_handle, TalonSRX_CCI::eMotMag_Accel, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponse").c_str(), frc::GetStackTrace(2).c_str());

	return ScaleNativeUnitsToRpm(m_feedbackDevice, (int32_t) retval);
}

  /**
   * @return current Motion Magic trajectory point's target velocity.
   * RPM if units are configured, velocity native units otherwise.
   */
  double SmartMotorController::GetMotionMagicActTrajVelocity()
  {
	int32_t retval;
	c_Logger_Log(c_TalonSRX_GetMotionMagic_ActiveTrajVelocity(m_handle, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetMotionMagic_ActiveTrajVelocity").c_str(), frc::GetStackTrace(2).c_str());
	
	return ScaleNativeUnitsToRpm(m_feedbackDevice, (int32_t) retval);
  }
  /**
   * @return current Motion Magic trajectory point's target position.
   * Rotations if units are configured, position native units otherwise.
   */
  double SmartMotorController::GetMotionMagicActTrajPosition()
  {
	int32_t retval;
	c_Logger_Log(c_TalonSRX_GetMotionMagic_ActiveTrajPosition(m_handle, &retval), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetMotionMagic_ActiveTrajPosition").c_str(), frc::GetStackTrace(2).c_str());
	
	return ScaleNativeUnitsToRotations(m_feedbackDevice, (int32_t) retval);
  }


int SmartMotorController::SetCurrentLimit(uint32_t amps) {
	return ConfigSetParameter(TalonSRX_CCI::eCurrentLimThreshold, amps);
}
int SmartMotorController::EnableCurrentLimit(bool enable) {
	return c_Logger_Log(c_TalonSRX_SetCurrentLimEnable(m_handle, enable), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetCurrentLimEnable").c_str(), frc::GetStackTrace(2).c_str());
	ApplyUsageStats(UsageFlags::CurrentLimit);
}
/**
 * @return true iff a reset has occured since last call.
 */
bool SmartMotorController::HasResetOccured() {
	return c_TalonSRX_HasResetOccured(m_handle);
}
int SmartMotorController::GetCustomParam0(int32_t & value) {
	// Update the info in m_impl.
	CTR_Code status = c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eCustomParam0), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
	// small yield for getting response
	std::this_thread::sleep_for(
			std::chrono::microseconds(kDelayForSolicitedSignalsUs));

	/* get the last received update */
	status = c_Logger_Log(c_TalonSRX_GetParamResponseInt32(m_handle, TalonSRX_CCI::eCustomParam0, &value), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponseInt32").c_str(), frc::GetStackTrace(2).c_str());

	return status;

}
int SmartMotorController::GetCustomParam1(int32_t & value) {
	// Update the info in m_impl.
	CTR_Code status = c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::eCustomParam1), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
	// small yield for getting response
	std::this_thread::sleep_for(
			std::chrono::microseconds(kDelayForSolicitedSignalsUs));

	/* get the last received update */
	status = c_Logger_Log(c_TalonSRX_GetParamResponseInt32(m_handle, TalonSRX_CCI::eCustomParam1, &value), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponseInt32").c_str(), frc::GetStackTrace(2).c_str());

	return status;
}
int SmartMotorController::IsPersStorageSaving(bool & isSaving) {
	// Update the info in m_impl.
	CTR_Code status = c_Logger_Log(c_TalonSRX_RequestParam(m_handle, TalonSRX_CCI::ePersStorageSaving), ("TalonSRX " + std::to_string(m_deviceNumber) + " RequestParam").c_str(), frc::GetStackTrace(2).c_str());
	// small yield for getting response
	std::this_thread::sleep_for(
			std::chrono::microseconds(kDelayForSolicitedSignalsUs));

	/* get the last received update */
	int32_t temp;
	status = c_Logger_Log(c_TalonSRX_GetParamResponseInt32(m_handle, TalonSRX_CCI::ePersStorageSaving, &temp), ("TalonSRX " + std::to_string(m_deviceNumber) + " GetParamResponseInt32").c_str(), frc::GetStackTrace(2).c_str());

	/* default to true if value is not sensble */
	isSaving = true;
	if (status == 0 && (temp == 0))
		isSaving = false;

	return status;
}
int SmartMotorController::SetCustomParam0(int32_t value)
{
	return ConfigSetParameter(TalonSRX_CCI::eCustomParam0, value);
}
int SmartMotorController::SetCustomParam1(int32_t value)
{
	return ConfigSetParameter(TalonSRX_CCI::eCustomParam1, value);
}

int SmartMotorController::GetGadgeteerStatus(IGadgeteerUartClient::GadgeteerUartStatus & status) {
	//return m_impl->GetGadgeteerStatus(status); //TODO: Fix Low-level
	return 0;
}

/**
 * Common interface for inverting direction of a speed controller.
 *
 * Only works in PercentVbus, speed, and Voltage modes.
 *
 * @param isInverted The state of inversion, true is inverted.
 */
void SmartMotorController::SetInverted(bool isInverted) { m_isInverted = isInverted; }

/**
 * Common interface for the inverting direction of a speed controller.
 *
 * @return isInverted The state of inversion, true is inverted.
 */
bool SmartMotorController::GetInverted() const { return m_isInverted; }

void SmartMotorController::SetDataPortOutputPeriod(uint32_t periodMs)
{
	c_Logger_Log(c_TalonSRX_SetDataPortOutputPeriodMs(m_handle, periodMs), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetDataPortOutputPeriodMs").c_str(), frc::GetStackTrace(2).c_str());
}
void SmartMotorController::SetDataPortOutputEnable(uint32_t idx, bool enable)
{
	c_Logger_Log(c_TalonSRX_SetDataPortOutputEnable(m_handle, idx, enable), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetDataPortOutputEnable").c_str(), frc::GetStackTrace(2).c_str());
}
void SmartMotorController::SetDataPortOutput(uint32_t idx, uint32_t OnTimeMs)
{
	c_Logger_Log(c_TalonSRX_SetDataPortOutputOnTimeMs(m_handle, idx, OnTimeMs), ("TalonSRX " + std::to_string(m_deviceNumber) + " SetDataPortOutputOnTimeMs").c_str(), frc::GetStackTrace(2).c_str());
}



/**
 * Common interface for stopping the motor until the next Set() call.
 *
 * Part of the MotorSafety interface.
 *
 * @deprecated Call Disable instead.
 */
void SmartMotorController::StopMotor() {
  Disable();
  m_stopped = true;
}


/*
void SmartMotorController::ValueChanged(ITable* source, llvm::StringRef key,
                            std::shared_ptr<nt::Value> value, bool isNew) {
  if (key == "Mode" && value->IsDouble())
    SetControlMode(
        static_cast<ControlMode::SmartControlMode>(value->GetDouble()));
  if (key == "p" && value->IsDouble()) SetP(value->GetDouble());
  if (key == "i" && value->IsDouble()) SetI(value->GetDouble());
  if (key == "d" && value->IsDouble()) SetD(value->GetDouble());
  if (key == "f" && value->IsDouble()) SetF(value->GetDouble());
  if (key == "Enabled" && value->IsBoolean()) {
    if (value->GetBoolean()) {
      Enable();
    } else {
      Disable();
    }
  }
  if (key == "Value" && value->IsDouble()) Set(value->GetDouble());
}

void SmartMotorController::UpdateTable() {
  if (m_table != nullptr) {
    m_table->PutString("Type", "SmartMotorController");
    m_table->PutNumber("Mode", m_controlMode);
    m_table->PutNumber("p", GetP());
    m_table->PutNumber("i", GetI());
    m_table->PutNumber("d", GetD());
    m_table->PutNumber("f", GetF());
    m_table->PutBoolean("Enabled", IsControlEnabled());
    m_table->PutNumber("Value", Get());
  }
}

void SmartMotorController::StartLiveWindowMode() {
  if (m_table != nullptr) {
    m_table->AddTableListener(this, true);
  }
}

void SmartMotorController::StopLiveWindowMode() {
  if (m_table != nullptr) {
    m_table->RemoveTableListener(this);
  }
}

std::string SmartMotorController::GetSmartDashboardType() const {
  return "CANSpeedController";
}

void SmartMotorController::InitTable(std::shared_ptr<ITable> subTable) {
  m_table = subTable;
  UpdateTable();
}

std::shared_ptr<ITable> SmartMotorController::GetTable() const { return m_table; }
*/

}}
#endif // CTR_EXCLUDE_WPILIB_CLASSES
