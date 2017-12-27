#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/MotorControl/SensorCollection.h"
#include "ctre/phoenix/CCI/MotController_CCI.h"
#include "ctre/phoenix/LowLevel/MotControllerWithBuffer_LowLevel.h"
#include "../WpilibSpeedController.h"

using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol::lowlevel;

//--------------------- Constructors -----------------------------//
/**
 * Constructor for motor controllers.
 * @param deviceNumber The CAN ID of the Motor Controller [0,62]
 */
BaseMotorController::BaseMotorController(int arbId) {
	m_handle = c_MotController_Create1(arbId);
	_arbId = arbId;

	_wpilibSpeedController = new WpilibSpeedController(this);

	_sensorColl = new motorcontrol::SensorCollection((void*) m_handle);
}

BaseMotorController::~BaseMotorController() {
	delete _wpilibSpeedController;
	_wpilibSpeedController = 0;
	delete _sensorColl;
	_sensorColl = 0;
}

void* BaseMotorController::GetHandle() {
	return m_handle;
}
/**
 * Returns the Device ID
 *
 * @return Device number.
 */
int BaseMotorController::GetDeviceID() {
	int devID = 0;
	(void) c_MotController_GetDeviceNumber(m_handle, &devID);
	return devID;
}
//------ Set output routines. ----------//
/**
 * Puts motor controller into PercentOutput mode.
 * @param value Percent output [-1,+1]
 */
void BaseMotorController::Set(double value) {
	Set(ControlMode::PercentOutput, value, 0);
}
/**
 * @param Mode Sets the appropriate output on the talon, depending on the mode.
 *
 * In PercentOutput, the output is between -1.0 and 1.0, with 0.0 as stopped.
 * In Current mode, output value is in amperes.
 * In Velocity mode, output value is in position change / 100ms.
 * In Position mode, output value is in encoder ticks or an analog value,
 *   depending on the sensor.
 * In Follower mode, the output value is the integer device ID of the talon to
 * duplicate.
 *
 * @param value The setpoint value, as described above.
 */
void BaseMotorController::Set(ControlMode Mode, double value) {
	Set(Mode, value, 0);
}
void BaseMotorController::Set(ControlMode mode, double demand0,
		double demand1) {
	m_controlMode = mode;
	m_sendMode = mode;
	m_setPoint = demand0;

	uint32_t work;
	switch (m_controlMode) {
	case ControlMode::PercentOutput:
		//case ControlMode::TimedPercentOutput:
		c_MotController_SetDemand(m_handle, (int) m_sendMode,
				(int) (1023 * demand0), 1023 * demand1);
		break;
	case ControlMode::Follower:
		/* did caller specify device ID */
		if ((0 <= demand0) && (demand0 <= 62)) { // [0,62]
			work = (uint32_t) GetBaseID();
			work >>= 16;
			work <<= 8;
			work |= (uint8_t) demand0;
		} else {
			work = (uint32_t) demand0;
		}
		c_MotController_SetDemand(m_handle, (int) m_sendMode, work, 0);
		break;
	case ControlMode::Velocity:
	case ControlMode::Position:
	case ControlMode::MotionMagic:
	case ControlMode::MotionMagicArc:
	case ControlMode::MotionProfile:
		c_MotController_SetDemand(m_handle, (int) m_sendMode, (int) (demand0),
				1023 * demand1);
		break;
	case ControlMode::Current:
		c_MotController_SetDemand(m_handle, (int) m_sendMode,
				(int) (1000 * demand0), 0); /* milliamps */
		break;
	case ControlMode::Disabled:
		/* fall thru...*/
	default:
		c_MotController_SetDemand(m_handle, (int) m_sendMode, 0, 0);
		break;
	}
}
/**
 * Neutral the motor output by setting control mode to disabled.
 */
void BaseMotorController::NeutralOutput() {
	Set(ControlMode::Disabled, 0);
}
/**
 * Sets the mode of operation during neutral throttle output.
 *
 * @param neutralMode
 *            The desired mode of operation when the Controller output
 *            throttle is neutral (ie brake/coast)
 **/
void BaseMotorController::SetNeutralMode(NeutralMode neutralMode) {
	c_MotController_SetNeutralMode(m_handle, neutralMode);
}
void BaseMotorController::EnableHeadingHold(bool enable) {
	c_MotController_EnableHeadingHold(m_handle, enable);
}
void BaseMotorController::SelectDemandType(bool value) {
	c_MotController_SelectDemandType(m_handle, value);
}

//------ Invert behavior ----------//
/**
 * Sets the phase of the sensor. Use when controller forward/reverse output
 * doesn't correlate to appropriate forward/reverse reading of sensor.
 *
 * @param PhaseSensor
 *            Indicates whether to invert the phase of the sensor.
 **/
void BaseMotorController::SetSensorPhase(bool PhaseSensor) {
	c_MotController_SetSensorPhase(m_handle, PhaseSensor);
}

/**
 * Inverts the output of the motor controller. LEDs, sensor phase, and limit
 * switches will also be inverted to match the new forward/reverse
 * directions.
 *
 * @param invert
 *            Invert state to set.
 **/
void BaseMotorController::SetInverted(bool invert) {
	_invert = invert; /* cache for getter */
	c_MotController_SetInverted(m_handle, _invert);
}
bool BaseMotorController::GetInverted() {
	return _invert;
}

//----- general output shaping ------------------//
/**
 * Configures the open-loop ramp rate of throttle output.
 *
 * @param secondsFromNeutralToFull
 *            Minimum desired time to go from neutral to full throttle. A
 *            value of '0' will disable the ramp.
 * @param timeoutMs
 *            Timeout value in ms. Function will generate error if config is
 *            not successful within timeout.
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigOpenloopRamp(
		double secondsFromNeutralToFull, int timeoutMs) {
	return c_MotController_ConfigOpenLoopRamp(m_handle,
			secondsFromNeutralToFull, timeoutMs);
}

/**
 * Configures the closed-loop ramp rate of throttle output.
 *
 * @param secondsFromNeutralToFull
 *            Minimum desired time to go from neutral to full throttle. A
 *            value of '0' will disable the ramp.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigClosedloopRamp(
		double secondsFromNeutralToFull, int timeoutMs) {
	return c_MotController_ConfigClosedLoopRamp(m_handle,
			secondsFromNeutralToFull, timeoutMs);
}

/**
 * Configures the forward peak output percentage.
 *
 * @param percentOut
 *            Desired peak output percentage.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigPeakOutputForward(double percentOut,
		int timeoutMs) {
	return c_MotController_ConfigPeakOutputForward(m_handle, percentOut,
			timeoutMs);
}

/**
 * Configures the reverse peak output percentage.
 *
 * @param percentOut
 *            Desired peak output percentage.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigPeakOutputReverse(double percentOut,
		int timeoutMs) {
	return c_MotController_ConfigPeakOutputReverse(m_handle, percentOut,
			timeoutMs);
}
/**
 * Configures the forward nominal output percentage.
 *
 * @param percentOut
 *            Nominal (minimum) percent output.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigNominalOutputForward(double percentOut,
		int timeoutMs) {
	return c_MotController_ConfigNominalOutputForward(m_handle, percentOut,
			timeoutMs);
}
/**
 * Configures the reverse nominal output percentage.
 *
 * @param percentOut
 *            Nominal (minimum) percent output.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigNominalOutputReverse(double percentOut,
		int timeoutMs) {
	return c_MotController_ConfigNominalOutputReverse(m_handle, percentOut,
			timeoutMs);
}
/**
 * Configures the output deadband percentage.
 *
 * @param percentDeadband
 *            Desired deadband percentage. Minimum is 0.1%, Maximum is
 *            25%.  Pass 0.04 for 4%.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigNeutralDeadband(double percentDeadband,
		int timeoutMs) {
	return c_MotController_ConfigNeutralDeadband(m_handle, percentDeadband,
			timeoutMs);
}

//------ Voltage Compensation ----------//
/**
 * Configures the Voltage Compensation saturation voltage.
 *
 * @param voltage
 *            TO-DO: Comment me!
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigVoltageCompSaturation(double voltage,
		int timeoutMs) {
	return c_MotController_ConfigVoltageCompSaturation(m_handle, voltage,
			timeoutMs);
}

/**
 * Configures the voltage measurement filter.
 *
 * @param filterWindowSamples
 *            Number of samples in the rolling average of voltage
 *            measurement.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigVoltageMeasurementFilter(
		int filterWindowSamples, int timeoutMs) {
	return c_MotController_ConfigVoltageMeasurementFilter(m_handle,
			filterWindowSamples, timeoutMs);
}

/**
 * Enables voltage compensation. If enabled, voltage compensation works in
 * all control modes.
 *
 * @param enable
 *            Enable state of voltage compensation.
 **/
void BaseMotorController::EnableVoltageCompensation(bool enable) {
	c_MotController_EnableVoltageCompensation(m_handle, enable);
}

//------ General Status ----------//
/**
 * Gets the bus voltage seen by the motor controller.
 *
 * @return The bus voltage value (in volts).
 */
double BaseMotorController::GetBusVoltage() {
	double param = 0;
	c_MotController_GetBusVoltage(m_handle, &param);
	return param;
}

/**
 * Gets the output percentage of the motor controller.
 *
 * @return Output of the motor controller (in percent).
 */
double BaseMotorController::GetMotorOutputPercent() {
	double param = 0;
	c_MotController_GetMotorOutputPercent(m_handle, &param);
	return param;
}

/**
 * @return applied voltage to motor
 */
double BaseMotorController::GetMotorOutputVoltage() {
	return GetBusVoltage() * GetMotorOutputPercent();
}

/**
 * Gets the output current of the motor controller.
 *
 * @return The output current (in amps).
 */
double BaseMotorController::GetOutputCurrent() {
	double param = 0;
	c_MotController_GetOutputCurrent(m_handle, &param);
	return param;
}
/**
 * Gets the temperature of the motor controller.
 *
 * @return Temperature of the motor controller (in °C)
 */
double BaseMotorController::GetTemperature() {
	double param = 0;
	c_MotController_GetTemperature(m_handle, &param);
	return param;
}

//------ sensor selection ----------//
/**
 * Select the remote feedback device for the motor controller.
 *
 * @param feedbackDevice
 *            Remote Feedback Device to select.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigSelectedFeedbackSensor(
		RemoteFeedbackDevice feedbackDevice, int pidIdx, int timeoutMs) {
	return c_MotController_ConfigSelectedFeedbackSensor(m_handle,
			feedbackDevice, pidIdx, timeoutMs);
}

/**
 * Select the feedback device for the motor controller.
 *
 * @param feedbackDevice
 *            Feedback Device to select.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigSelectedFeedbackSensor(
		FeedbackDevice feedbackDevice, int pidIdx, int timeoutMs) {
	return c_MotController_ConfigSelectedFeedbackSensor(m_handle,
			feedbackDevice, pidIdx, timeoutMs);
}
ErrorCode BaseMotorController::ConfigRemoteFeedbackFilter(int deviceID,
		RemoteSensorSource remoteSensorSource, int remoteOrdinal,
		int timeoutMs) {
	return c_MotController_ConfigRemoteFeedbackFilter(m_handle, deviceID,
			(int) remoteSensorSource, remoteOrdinal, timeoutMs);
}
ErrorCode BaseMotorController::ConfigSensorTerm(SensorTerm sensorTerm,
		FeedbackDevice feedbackDevice, int timeoutMs) {
	return c_MotController_ConfigSensorTerm(m_handle, (int) sensorTerm,
			(int) feedbackDevice, timeoutMs);
}
//------- sensor status --------- //
/**
 * Get the selected sensor position.
 *
 * @return Position of selected sensor (in Raw Sensor Units).
 */
int BaseMotorController::GetSelectedSensorPosition(int pidIdx) {
	int retval;
	c_MotController_GetSelectedSensorPosition(m_handle, &retval, pidIdx);
	return retval;
}
/**
 * Get the selected sensor velocity.
 *
 * @return selected sensor (in Raw Sensor Units) per 100ms.
 */
int BaseMotorController::GetSelectedSensorVelocity(int pidIdx) {
	int retval;
	c_MotController_GetSelectedSensorVelocity(m_handle, &retval, pidIdx);
	return retval;
}
/**
 * Sets the sensor position to the given value.
 *
 * @param sensorPos
 *            Position to set for the selected sensor (in Raw Sensor Units).
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::SetSelectedSensorPosition(int sensorPos,
		int pidIdx, int timeoutMs) {
	return c_MotController_SetSelectedSensorPosition(m_handle, sensorPos,
			pidIdx, timeoutMs);
}

//-----	- status frame period changes ----------//
/**
 * Sets the period of the given control frame.
 *
 * @param frame
 *            Frame whose period is to be changed.
 * @param periodMs
 *            Period in ms for the given frame.
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::SetControlFramePeriod(ControlFrame frame,
		int periodMs) {
	return c_MotController_SetControlFramePeriod(m_handle, frame, periodMs);
}
ErrorCode BaseMotorController::SetStatusFramePeriod(StatusFrame frame,
		int periodMs, int timeoutMs) {
	return c_MotController_SetStatusFramePeriod(m_handle, frame, periodMs,
			timeoutMs);
}
ErrorCode BaseMotorController::SetStatusFramePeriod(StatusFrameEnhanced frame,
		int periodMs, int timeoutMs) {
	return c_MotController_SetStatusFramePeriod(m_handle, frame, periodMs,
			timeoutMs);
}
/**
 * Gets the period of the given status frame.
 *
 * @param frame
 *            Frame to get the period of.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Period of the given status frame.
 */
int BaseMotorController::GetStatusFramePeriod(StatusFrame frame,
		int timeoutMs) {
	int periodMs = 0;
	c_MotController_GetStatusFramePeriod(m_handle, frame, &periodMs, timeoutMs);
	return periodMs;
}

/**
 * Gets the period of the given status frame.
 *
 * @param frame
 *            Frame to get the period of.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Period of the given status frame.
 */
int BaseMotorController::GetStatusFramePeriod(StatusFrameEnhanced frame,
		int timeoutMs) {
	int periodMs = 0;
	c_MotController_GetStatusFramePeriod(m_handle, frame, &periodMs, timeoutMs);
	return periodMs;
}

//----- velocity signal conditionaing ------//

/**
 * Sets the period over which velocity measurements are taken.
 *
 * @param period
 *            Desired period for the velocity measurement. @see
 *            #VelocityMeasPeriod
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigVelocityMeasurementPeriod(
		VelocityMeasPeriod period, int timeoutMs) {
	return c_MotController_ConfigVelocityMeasurementPeriod(m_handle, period,
			timeoutMs);
}
/**
 * Sets the number of velocity samples used in the rolling average velocity
 * measurement.
 *
 * @param windowSize
 *            Number of samples in the rolling average of velocity
 *            measurement.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigVelocityMeasurementWindow(int windowSize,
		int timeoutMs) {
	return c_MotController_ConfigVelocityMeasurementWindow(m_handle, windowSize,
			timeoutMs);
}

//------ remote limit switch ----------//
/**
 * Configures the forward limit switch for a remote source.
 *
 * @param type
 *            Remote limit switch source. @see #LimitSwitchSource
 * @param normalOpenOrClose
 *            Setting for normally open or normally closed.
 * @param deviceID
 *            Device ID of remote source.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigForwardLimitSwitchSource(
		RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int deviceID, int timeoutMs) {
	LimitSwitchSource cciType = LimitSwitchRoutines::Promote(type);
	return c_MotController_ConfigForwardLimitSwitchSource(m_handle, cciType,
			normalOpenOrClose, deviceID, timeoutMs);
}

ErrorCode BaseMotorController::ConfigReverseLimitSwitchSource(
		RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int deviceID, int timeoutMs) {
	LimitSwitchSource cciType = LimitSwitchRoutines::Promote(type);
	return c_MotController_ConfigReverseLimitSwitchSource(m_handle, cciType,
			normalOpenOrClose, deviceID, timeoutMs);
}
/**
 * Sets the enable state for limit switches.
 *
 * @param enable
 *            Enable state for limit switches.
 **/
void BaseMotorController::OverrideLimitSwitchesEnable(bool enable) {
	c_MotController_OverrideLimitSwitchesEnable(m_handle, enable);
}

//------ local limit switch ----------//

ErrorCode BaseMotorController::ConfigForwardLimitSwitchSource(
		LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int timeoutMs) {
	return c_MotController_ConfigForwardLimitSwitchSource(m_handle, type,
			normalOpenOrClose, 0, timeoutMs);
}
ErrorCode BaseMotorController::ConfigReverseLimitSwitchSource(
		LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int timeoutMs) {
	return c_MotController_ConfigReverseLimitSwitchSource(m_handle, type,
			normalOpenOrClose, 0, timeoutMs);
}

//------ soft limit ----------//
/**
 * Configures the forward soft limit threshold.
 *
 * @param forwardSensorLimit
 *            Forward Sensor Position Limit (in Raw Sensor Units).
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigForwardSoftLimitThreshold(int forwardSensorLimit,
		int timeoutMs) {
	return c_MotController_ConfigForwardSoftLimitThreshold(m_handle, forwardSensorLimit,
			timeoutMs);
}

/**
 * Configures the reverse soft limit threshold.
 *
 * @param reverseSensorLimit
 *            Reverse Sensor Position Limit (in Raw Sensor Units).
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigReverseSoftLimitThreshold(int reverseSensorLimit,
		int timeoutMs) {
	return c_MotController_ConfigReverseSoftLimitThreshold(m_handle, reverseSensorLimit,
			timeoutMs);
}

/**
 * Configures the forward soft limit enable .
 *
 * @param forwardSensorLimit
 *            Forward Sensor Position Limit (in Raw Sensor Units).
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigForwardSoftLimitEnable(bool enable,
		int timeoutMs) {
	return c_MotController_ConfigForwardSoftLimitEnable(m_handle, enable,
			timeoutMs);
}


/**
 * Configures the reverse soft limit enable.
 *
 * @param reverseSensorLimit
 *            Reverse Sensor Position Limit (in Raw Sensor Units).
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigReverseSoftLimitEnable(bool enable,
		int timeoutMs) {
	return c_MotController_ConfigReverseSoftLimitEnable(m_handle, enable,
			timeoutMs);
}

/**
 * Sets the enable state for soft limit switches.
 *
 * @param enable
 *            Enable state for soft limit switches.
 **/
void BaseMotorController::OverrideSoftLimitsEnable(bool enable) {
	c_MotController_OverrideSoftLimitsEnable(m_handle, enable);
}

//------ Current Lim ----------//
/* not available in base */

//------ General Close loop ----------//
/**
 * Sets the 'P' constant in the given parameter slot.
 *
 * @param slotIdx
 *            Parameter slot for the constant.
 * @param value
 *            Value of the P constant.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::Config_kP(int slotIdx, double value,
		int timeoutMs) {
	return c_MotController_Config_kP(m_handle, slotIdx, value, timeoutMs);
}

/**
 * Sets the 'I' constant in the given parameter slot.
 *
 * @param slotIdx
 *            Parameter slot for the constant.
 * @param value
 *            Value of the I constant.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::Config_kI(int slotIdx, double value,
		int timeoutMs) {
	return c_MotController_Config_kI(m_handle, slotIdx, value, timeoutMs);
}

/**
 * Sets the 'D' constant in the given parameter slot.
 *
 * @param slotIdx
 *            Parameter slot for the constant.
 * @param value
 *            Value of the D constant.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::Config_kD(int slotIdx, double value,
		int timeoutMs) {
	return c_MotController_Config_kD(m_handle, slotIdx, value, timeoutMs);
}

/**
 * Sets the 'F' constant in the given parameter slot.
 *
 * @param slotIdx
 *            Parameter slot for the constant.
 * @param value
 *            Value of the F constant.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::Config_kF(int slotIdx, double value,
		int timeoutMs) {
	return c_MotController_Config_kF(m_handle, slotIdx, value, timeoutMs);
}

/**
 * Sets the Integral Zone constant in the given parameter slot.
 *
 * @param slotIdx
 *            Parameter slot for the constant.
 * @param izone
 *            Value of the Integral Zone constant.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::Config_IntegralZone(int slotIdx, int izone,
		int timeoutMs) {
	return c_MotController_Config_IntegralZone(m_handle, slotIdx, izone,
			timeoutMs);
}

/**
 * Sets the allowable closed-loop error in the given parameter slot.
 *
 * @param slotIdx
 *            Parameter slot for the constant.
 * @param allowableClosedLoopError
 *            Value of the allowable closed-loop error.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigAllowableClosedloopError(int slotIdx,
		int allowableCloseLoopError, int timeoutMs) {
	return c_MotController_ConfigAllowableClosedloopError(m_handle, slotIdx,
			allowableCloseLoopError, timeoutMs);
}

/**
 * Sets the maximum integral accumulator in the given parameter slot.
 *
 * @param slotIdx
 *            Parameter slot for the constant.
 * @param iaccum
 *            Value of the maximum integral accumulator.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigMaxIntegralAccumulator(int slotIdx,
		double iaccum, int timeoutMs) {
	return c_MotController_ConfigMaxIntegralAccumulator(m_handle, slotIdx,
			iaccum, timeoutMs);
}

/**
 * Sets the integral accumulator.
 *
 * @param iaccum
 *            Value to set for the integral accumulator.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::SetIntegralAccumulator(double iaccum, int pidIdx,
		int timeoutMs) {
	return c_MotController_SetIntegralAccumulator(m_handle, iaccum, pidIdx,
			timeoutMs);
}

/**
 * Gets the closed-loop error.
 *
 * @param slotIdx
 *            Parameter slot of the constant.
 * @return Closed-loop error value.
 */
int BaseMotorController::GetClosedLoopError(int pidIdx) {
	int closedLoopError = 0;
	c_MotController_GetClosedLoopError(m_handle, &closedLoopError, pidIdx);
	return closedLoopError;
}

/**
 * Gets the iaccum value.
 *
 * @return Integral accumulator value.
 */
double BaseMotorController::GetIntegralAccumulator(int pidIdx) {
	double iaccum = 0;
	c_MotController_GetIntegralAccumulator(m_handle, &iaccum, pidIdx);
	return iaccum;
}


/**
 * Gets the derivative of the closed-loop error.
 *
 * @param slotIdx
 *            Parameter slot of the constant.
 * @return The error derivative value.
 */
double BaseMotorController::GetErrorDerivative(int pidIdx) {
	double derror = 0;
	c_MotController_GetErrorDerivative(m_handle, &derror, pidIdx);
	return derror;
}

/**
 * Selects which profile slot to use for closed-loop control.
 *
 * @param slotIdx
 *            Profile slot to select.
 **/
ErrorCode BaseMotorController::SelectProfileSlot(int slotIdx, int pidIdx) {
	return c_MotController_SelectProfileSlot(m_handle, slotIdx, pidIdx);
}

int BaseMotorController::GetClosedLoopTarget(int pidIdx) {
	int param = 0;
	c_MotController_GetClosedLoopError(m_handle, &param, pidIdx);
	return param;
}
int BaseMotorController::GetActiveTrajectoryPosition() {
	int param = 0;
	c_MotController_GetActiveTrajectoryPosition(m_handle, &param);
	return param;
}
int BaseMotorController::GetActiveTrajectoryVelocity() {
	int param = 0;
	c_MotController_GetActiveTrajectoryVelocity(m_handle, &param);
	return param;
}
double BaseMotorController::GetActiveTrajectoryHeading() {
	double param = 0;
	c_MotController_GetActiveTrajectoryHeading(m_handle, &param);
	return param;
}

//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//

/**
 * Sets the Motion Magic Cruise Velocity.
 *
 * @param sensorUnitsPer100ms
 *            Motion Magic Cruise Velocity (in Raw Sensor Units per 100 ms).
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigMotionCruiseVelocity(
		int sensorUnitsPer100ms, int timeoutMs) {
	return c_MotController_ConfigMotionCruiseVelocity(m_handle,
			sensorUnitsPer100ms, timeoutMs);
}
/**
 * Sets the Motion Magic Acceleration.
 *
 * @param sensorUnitsPer100msPerSec
 *            Motion Magic Acceleration (in Raw Sensor Units per 100 ms per
 *            second).
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigMotionAcceleration(
		int sensorUnitsPer100msPerSec, int timeoutMs) {
	return c_MotController_ConfigMotionAcceleration(m_handle,
			sensorUnitsPer100msPerSec, timeoutMs);
}

//------ Motion Profile Buffer ----------//
void BaseMotorController::ClearMotionProfileTrajectories() {
	c_MotController_ClearMotionProfileTrajectories(m_handle);
}
int BaseMotorController::GetMotionProfileTopLevelBufferCount() {
	int param = 0;
	c_MotController_GetMotionProfileTopLevelBufferCount(m_handle, &param);
	return param;
}
ErrorCode BaseMotorController::PushMotionProfileTrajectory(
		const ctre::phoenix::motion::TrajectoryPoint & trajPt) {
	ErrorCode retval = c_MotController_PushMotionProfileTrajectory(m_handle,
			trajPt.position, trajPt.velocity, trajPt.headingDeg,
			trajPt.profileSlotSelect, trajPt.isLastPoint, trajPt.zeroPos);
	return retval;
}
bool BaseMotorController::IsMotionProfileTopLevelBufferFull() {
	bool retval = false;
	c_MotController_IsMotionProfileTopLevelBufferFull(m_handle, &retval);
	return retval;
}
void BaseMotorController::ProcessMotionProfileBuffer() {
	c_MotController_ProcessMotionProfileBuffer(m_handle);
}
ErrorCode BaseMotorController::GetMotionProfileStatus(
		ctre::phoenix::motion::MotionProfileStatus & statusToFill) {

	int outputEnable = 0;

	ErrorCode retval = c_MotController_GetMotionProfileStatus(m_handle,
			&statusToFill.topBufferRem, &statusToFill.topBufferCnt,
			&statusToFill.btmBufferCnt, &statusToFill.hasUnderrun,
			&statusToFill.isUnderrun, &statusToFill.activePointValid,
			&statusToFill.isLast, &statusToFill.profileSlotSelect,
			&outputEnable);

	statusToFill.outputEnable =
			(ctre::phoenix::motion::SetValueMotionProfile) outputEnable;

	return retval;
}
ErrorCode BaseMotorController::ClearMotionProfileHasUnderrun(int timeoutMs) {
	return c_MotController_ClearMotionProfileHasUnderrun(m_handle, timeoutMs);
}
ErrorCode BaseMotorController::ChangeMotionControlFramePeriod(int periodMs) {
	return c_MotController_ChangeMotionControlFramePeriod(m_handle, periodMs);
}

//------ error ----------//
/**
 * Gets the last error generated by this object.
 *
 * @return Last Error Code generated by a function.
 */
ErrorCode BaseMotorController::GetLastError() {
	return c_MotController_GetLastError(m_handle);
}

//------ Faults ----------//
ErrorCode BaseMotorController::GetFaults(Faults & toFill) {
	int faultBits;
	ErrorCode retval = c_MotController_GetFaults(m_handle, &faultBits);
	toFill = Faults(faultBits);
	return retval;
}
ErrorCode BaseMotorController::GetStickyFaults(StickyFaults & toFill) {
	int faultBits;
	ErrorCode retval = c_MotController_GetStickyFaults(m_handle, &faultBits);
	toFill = StickyFaults(faultBits);
	return retval;
}
ErrorCode BaseMotorController::ClearStickyFaults(int timeoutMs) {
	return c_MotController_ClearStickyFaults(m_handle, timeoutMs);
}

//------ Firmware ----------//
/**
 * Gets the firmware version of the device.
 *
 * @return Firmware version of device.
 */
int BaseMotorController::GetFirmwareVersion() {
	int retval = -1;
	c_MotController_GetFirmwareVersion(m_handle, &retval);
	return retval;
}
/**
 * Returns true if the device has reset since last call.
 *
 * @return Has a Device Reset Occurred?
 */
bool BaseMotorController::HasResetOccurred() {
	bool retval = false;
	c_MotController_HasResetOccurred(m_handle, &retval);
	return retval;
}

//------ Custom Persistent Params ----------//
/**
 * Sets the value of a custom parameter.
 *
 * @param newValue
 *            Value for custom parameter.
 * @param paramIndex
 *            Index of custom parameter.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigSetCustomParam(int newValue,
		int paramIndex, int timeoutMs) {
	return c_MotController_ConfigSetCustomParam(m_handle, newValue, paramIndex,
			timeoutMs);
}

/**
 * Gets the value of a custom parameter.
 *
 * @param paramIndex
 *            Index of custom parameter.
 * @param timoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Value of the custom param.
 */
int BaseMotorController::ConfigGetCustomParam(int paramIndex, int timeoutMs) {
	int readValue;
	c_MotController_ConfigGetCustomParam(m_handle, &readValue, paramIndex,
			timeoutMs);
	return readValue;
}

//------ Generic Param API  ----------//
/**
 * Sets a parameter.
 *
 * @param param
 *            Parameter enumeration.
 * @param value
 *            Value of parameter.
 * @param subValue
 *            Subvalue for parameter. Maximum value of 255.
 * @param ordinal
 *            Ordinal of parameter.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Error Code generated by function. 0 indicates no error.
 */
ErrorCode BaseMotorController::ConfigSetParameter(ParamEnum param, double value,
		uint8_t subValue, int ordinal, int timeoutMs) {
	return c_MotController_ConfigSetParameter(m_handle, param, value, subValue,
			ordinal, timeoutMs);
}

/**
 * Gets a parameter.
 *
 * @param param
 *            Parameter enumeration.
 * @param ordinal
 *            Ordinal of parameter.
 * @param timeoutMs
 *            Timeout value in ms. @see #ConfigOpenLoopRamp
 * @return Value of parameter.
 */
double BaseMotorController::ConfigGetParameter(ParamEnum param, int ordinal,
		int timeoutMs) {
	double value = 0;
	c_MotController_ConfigGetParameter(m_handle, param, &value, ordinal,
			timeoutMs);
	return (double) value;
}

//------ Misc. ----------//
int BaseMotorController::GetBaseID() {
	return _arbId;
}

// ----- Follower ------//
void BaseMotorController::Follow(IMotorController & masterToFollow) {
	uint32_t baseId = masterToFollow.GetBaseID();
	uint32_t id24 = (uint16_t) (baseId >> 0x10);
	id24 <<= 8;
	id24 |= (uint8_t) (baseId);
	Set(ControlMode::Follower, (double) id24);
}
void BaseMotorController::ValueUpdated() {
	//do nothing
}
// ----- WPILIB ------//
frc::SpeedController & BaseMotorController::GetWPILIB_SpeedController() {
	return *_wpilibSpeedController;
}
/**
 * @retrieve object that can get/set individual RAW sensor values.
 */
ctre::phoenix::motorcontrol::SensorCollection & BaseMotorController::GetSensorCollection() {
	return *_sensorColl;
}

