#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/CCI/MotController_CCI.h"
#include "ctre/phoenix/LowLevel/MotControllerWithBuffer_LowLevel.h"
#include "../WpilibSpeedController.h"

using namespace CTRE::Phoenix::MotorControl;
using namespace CTRE::Phoenix::MotorControl::CAN;
using namespace CTRE::Phoenix::MotorControl::LowLevel;

//--------------------- Constructors -----------------------------//
/**
 * Constructor for the CANTalon device.
 * @param deviceNumber The CAN ID of the Talon SRX
 * @param externalEnable pass true to prevent sending enable frames.
 *  	This can be useful when having one device enable the Talon, and
 * 		another to control it.
 */
BaseMotorController::BaseMotorController(int arbId) {
	m_handle = c_MotController_Create1(arbId);
	_arbId = arbId;

	_wpilibSpeedController = new WpilibSpeedController(this);

	//_sensColl = new SensorCollection(_ll);
}

BaseMotorController::~BaseMotorController()
{
	delete _wpilibSpeedController;
	_wpilibSpeedController = 0;
}

void* BaseMotorController::GetHandle()
{
	return m_handle;
}
int BaseMotorController::GetDeviceID()
{
	int devID = 0;
	(void)c_MotController_GetDeviceNumber(m_handle, &devID);
	return devID;
}
//------ Set output routines. ----------//
/**
 * Puts motor controller into PercentOutput mode.
 * @param value Percent output [-1,+1]
 */
void BaseMotorController::Set(float value) {
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
void BaseMotorController::Set(ControlMode Mode, float value) {
	Set(Mode, value, 0);
}
void BaseMotorController::Set(ControlMode mode, float demand0, float demand1) {
	m_controlMode = mode;
	m_sendMode = mode;
	m_setPoint = demand0;

	uint32_t work;
	switch (m_controlMode) {
		case ControlMode::PercentOutput:
		case ControlMode::TimedPercentOutput:
			c_MotController_SetDemand(m_handle, (int)m_sendMode, (int) (1023 * demand0), 1023 *demand1);
			break;
		case ControlMode::Follower:
			/* did caller specify device ID */
			if ( (0 <= demand0) && (demand0 <= 62)) { // [0,62]
				work = (uint32_t)GetBaseID();
				work >>= 16;
				work <<= 8;
				work |= (uint8_t)demand0;
			} else {
				work = (uint32_t)demand0;
			}
			c_MotController_SetDemand(m_handle, (int)m_sendMode, work, 0);
			break;

		case ControlMode::Velocity:
		case ControlMode::Position:
		case ControlMode::MotionMagic:
		case ControlMode::MotionMagicArc:
		case ControlMode::MotionProfile:
			c_MotController_SetDemand(m_handle, (int)m_sendMode, (int) (demand0), 1023 * demand1);
			break;
		case ControlMode::Current:
			c_MotController_SetDemand(m_handle, (int)m_sendMode, (int) (1000 * demand0), 0); /* milliamps */
			break;
		case ControlMode::Disabled:
			/* fall thru...*/
		default:
			c_MotController_SetDemand(m_handle, (int)m_sendMode, 0, 0);
			break;
	}
	//
	//switch (m_controlMode)
	//{
	//    case ControlMode::PercentOutput:
	//        status = _cci.SetDemand((int)m_sendMode, (int)demand0);
	//        break;
	//    case ControlMode::Follower:
	//        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
	//        break;
	//    case ControlMode::Velocity:
	//        /* if the caller has provided scaling info, apply it */
	//        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
	//        break;
	//    case ControlMode::Position:
	//        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
	//        break;
	//    case ControlMode::MotionProfile:
	//        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
	//        break;
	//    case ControlMode::MotionMagic:
	//        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
	//        break;
	//    default:
	//        Debug.Print("The CTRE MotorController does not support this control mode.");
	//        break;
	//}
	//SetLastError(status);
}
void BaseMotorController::NeutralOutput() {
	Set(ControlMode::Disabled, 0);
}
void BaseMotorController::SetNeutralMode(NeutralMode neutralMode) {
	c_MotController_SetNeutralMode(m_handle, neutralMode);
}

//------ Invert behavior ----------//
void BaseMotorController::SetSensorPhase(bool PhaseSensor) {
	c_MotController_SetSensorPhase(m_handle, PhaseSensor);
}
void BaseMotorController::SetInverted(bool invert) {
	_invert = invert; /* cache for getter */
	c_MotController_SetInverted(m_handle, _invert);
}
bool BaseMotorController::GetInverted() {
	return _invert;
}

//----- general output shaping ------------------//
ErrorCode BaseMotorController::ConfigOpenloopRamp(
		float secondsFromNeutralToFull, int timeoutMs) {
	return c_MotController_ConfigOpenLoopRamp(m_handle, secondsFromNeutralToFull, timeoutMs);
}
ErrorCode BaseMotorController::ConfigClosedloopRamp(
		float secondsFromNeutralToFull, int timeoutMs) {
	return c_MotController_ConfigClosedLoopRamp(m_handle, secondsFromNeutralToFull, timeoutMs);
}
ErrorCode BaseMotorController::ConfigPeakOutputForward(float percentOut,
		int timeoutMs) {
	return c_MotController_ConfigPeakOutputForward(m_handle, percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigPeakOutputReverse(float percentOut,
		int timeoutMs) {
	return c_MotController_ConfigPeakOutputReverse(m_handle, percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigNominalOutputForward(float percentOut,
		int timeoutMs) {
	return c_MotController_ConfigNominalOutputForward(m_handle, percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigNominalOutputReverse(float percentOut,
		int timeoutMs) {
	return c_MotController_ConfigNominalOutputReverse(m_handle, percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigNeutralDeadband(
		float percentDeadband, int timeoutMs) {
	return c_MotController_ConfigNeutralDeadband(m_handle, percentDeadband, timeoutMs);
}

//------ Voltage Compensation ----------//
ErrorCode BaseMotorController::ConfigVoltageCompSaturation(float voltage,
		int timeoutMs) {
	return c_MotController_ConfigVoltageCompSaturation(m_handle, voltage, timeoutMs);
}
ErrorCode BaseMotorController::ConfigVoltageMeasurementFilter(
		int filterWindowSamples, int timeoutMs) {
	return c_MotController_ConfigVoltageMeasurementFilter(m_handle, filterWindowSamples, timeoutMs);
}
void BaseMotorController::EnableVoltageCompensation(bool enable) {
	c_MotController_EnableVoltageCompensation(m_handle, enable);
}

//------ General Status ----------//
float BaseMotorController::GetBusVoltage() {
	float param = 0;
	c_MotController_GetBusVoltage(m_handle, &param);
	return param;
}
float BaseMotorController::GetMotorOutputPercent() {
	float param = 0;
	c_MotController_GetMotorOutputPercent(m_handle, &param);
	return param;
}
float BaseMotorController::GetMotorOutputVoltage() {
	return GetBusVoltage() * GetMotorOutputPercent();
}
float BaseMotorController::GetOutputCurrent() {
	float param = 0;
	c_MotController_GetOutputCurrent(m_handle, &param);
	return param;
}
float BaseMotorController::GetTemperature() {
	float param = 0;
	c_MotController_GetTemperature(m_handle, &param);
	return param;
}

//------ sensor selection ----------//
ErrorCode BaseMotorController::ConfigSelectedFeedbackSensor(
		RemoteFeedbackDevice feedbackDevice, int timeoutMs) {
	/* we may break this into two APIs */
	ErrorCode e1 = c_MotController_ConfigRemoteFeedbackFilter(m_handle, feedbackDevice._arbId,
			feedbackDevice._peripheralIndex, feedbackDevice._reserved,
			timeoutMs);

	ErrorCode e2 = c_MotController_ConfigSelectedFeedbackSensor(m_handle,
			FeedbackDevice::RemoteSensor, timeoutMs);

	if (e1 == ErrorCode::OK) {
		return e2;
	}
	return e1;
}
ErrorCode BaseMotorController::ConfigSelectedFeedbackSensor(
		FeedbackDevice feedbackDevice, int timeoutMs) {
	return c_MotController_ConfigSelectedFeedbackSensor(m_handle, feedbackDevice, timeoutMs);
}

//------- sensor status --------- //
int BaseMotorController::GetSelectedSensorPosition() {
	int retval;
	c_MotController_GetSelectedSensorPosition(m_handle, &retval);
	return retval;
}
int BaseMotorController::GetSelectedSensorVelocity() {
	int retval;
	c_MotController_GetSelectedSensorVelocity(m_handle, &retval);
	return retval;
}
ErrorCode BaseMotorController::SetSelectedSensorPosition(int sensorPos,
		int timeoutMs) {
	return c_MotController_SetSelectedSensorPosition(m_handle, sensorPos, timeoutMs);
}

//------ status frame period changes ----------//
ErrorCode BaseMotorController::SetControlFramePeriod(ControlFrame frame,
		int periodMs) {
	return c_MotController_SetControlFramePeriod(m_handle, frame, periodMs);
}
ErrorCode BaseMotorController::SetStatusFramePeriod(StatusFrame frame,
		int periodMs, int timeoutMs) {
	return c_MotController_SetStatusFramePeriod(m_handle, frame, periodMs, timeoutMs);
}
ErrorCode BaseMotorController::SetStatusFramePeriod(StatusFrameEnhanced frame,
		int periodMs, int timeoutMs) {
	return c_MotController_SetStatusFramePeriod(m_handle, frame, periodMs, timeoutMs);
}
int BaseMotorController::GetStatusFramePeriod(StatusFrame frame,
		int timeoutMs) {
	int periodMs = 0;
	c_MotController_GetStatusFramePeriod(m_handle, frame, &periodMs, timeoutMs);
	return periodMs;
}
int BaseMotorController::GetStatusFramePeriod(StatusFrameEnhanced frame,
		int timeoutMs) {
	int periodMs = 0;
	c_MotController_GetStatusFramePeriod(m_handle, frame, &periodMs, timeoutMs);
	return periodMs;
}

//----- velocity signal conditionaing ------//
ErrorCode BaseMotorController::ConfigVelocityMeasurementPeriod(
		VelocityMeasPeriod period, int timeoutMs) {
	return c_MotController_ConfigVelocityMeasurementPeriod(m_handle, period, timeoutMs);
}
ErrorCode BaseMotorController::ConfigVelocityMeasurementWindow(int windowSize,
		int timeoutMs) {
	return c_MotController_ConfigVelocityMeasurementWindow(m_handle, windowSize, timeoutMs);
}

//------ remote limit switch ----------//
ErrorCode BaseMotorController::ConfigForwardLimitSwitchSource(
		RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int deviceID, int timeoutMs) {
	LimitSwitchSource cciType = LimitSwitchRoutines::Promote(type);
	return c_MotController_ConfigForwardLimitSwitchSource(m_handle, cciType, normalOpenOrClose,
			deviceID, timeoutMs);
}

ErrorCode BaseMotorController::ConfigReverseLimitSwitchSource(
		RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int deviceID, int timeoutMs) {
	LimitSwitchSource cciType = LimitSwitchRoutines::Promote(type);
	return c_MotController_ConfigReverseLimitSwitchSource(m_handle, cciType, normalOpenOrClose,
			deviceID, timeoutMs);
}
void BaseMotorController::EnableLimitSwitches(bool enable) {
	c_MotController_EnableLimitSwitches(m_handle, enable);
}

//------ local limit switch ----------//
ErrorCode BaseMotorController::ConfigForwardLimitSwitchSource(
		LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int timeoutMs) {
	return c_MotController_ConfigForwardLimitSwitchSource(m_handle, type, normalOpenOrClose, 0,
			timeoutMs);
}
ErrorCode BaseMotorController::ConfigReverseLimitSwitchSource(
		LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int timeoutMs) {
	return c_MotController_ConfigReverseLimitSwitchSource(m_handle, type, normalOpenOrClose, 0,
			timeoutMs);
}

//------ soft limit ----------//
ErrorCode BaseMotorController::ConfigForwardSoftLimit(int forwardSensorLimit,
		int timeoutMs) {
	return c_MotController_ConfigForwardSoftLimit(m_handle, forwardSensorLimit, timeoutMs);
}

ErrorCode BaseMotorController::ConfigReverseSoftLimit(int reverseSensorLimit,
		int timeoutMs) {
	return c_MotController_ConfigReverseSoftLimit(m_handle, reverseSensorLimit, timeoutMs);
}

void BaseMotorController::EnableSoftLimits(bool enable) {
	c_MotController_EnableSoftLimits(m_handle, enable);
}

//------ Current Lim ----------//
/* not available in base */

//------ General Close loop ----------//
ErrorCode BaseMotorController::Config_kP(int slotIdx, float value,
		int timeoutMs) {
	return c_MotController_Config_kP(m_handle, slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_kI(int slotIdx, float value,
		int timeoutMs) {
	return c_MotController_Config_kI(m_handle, slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_kD(int slotIdx, float value,
		int timeoutMs) {
	return c_MotController_Config_kD(m_handle, slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_kF(int slotIdx, float value,
		int timeoutMs) {
	return c_MotController_Config_kF(m_handle, slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_IntegralZone(int slotIdx, int izone,
		int timeoutMs) {
	return c_MotController_Config_IntegralZone(m_handle, slotIdx, izone, timeoutMs);
}
ErrorCode BaseMotorController::ConfigAllowableClosedloopError(int slotIdx,
		int allowableCloseLoopError, int timeoutMs) {
	return c_MotController_ConfigAllowableClosedloopError(m_handle, slotIdx, allowableCloseLoopError,
			timeoutMs);
}
ErrorCode BaseMotorController::ConfigMaxIntegralAccumulator(int slotIdx,
		float iaccum, int timeoutMs) {
	return c_MotController_ConfigMaxIntegralAccumulator(m_handle, slotIdx, iaccum, timeoutMs);
}

ErrorCode BaseMotorController::SetIntegralAccumulator(float iaccum,
		int timeoutMs) {
	return c_MotController_SetIntegralAccumulator(m_handle, iaccum, timeoutMs);
}

int BaseMotorController::GetClosedLoopError() {
	int closedLoopError = 0;
	c_MotController_GetClosedLoopError(m_handle, &closedLoopError, 0);
	return closedLoopError;
}
float BaseMotorController::GetIntegralAccumulator() {
	float iaccum = 0;
	c_MotController_GetIntegralAccumulator(m_handle, &iaccum, 0);
	return iaccum;
}
float BaseMotorController::GetErrorDerivative() {
	float derror = 0;
	c_MotController_GetErrorDerivative(m_handle, &derror, 0);
	return derror;
}
/**
 * SRX has two available slots for PID.
 * @param slotIdx one or zero depending on which slot caller wants.
 */
void BaseMotorController::SelectProfileSlot(int slotIdx) {
	m_profile = slotIdx; /* only get two slots for now */
	c_MotController_SelectProfileSlot(m_handle, m_profile);
}

//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
ErrorCode BaseMotorController::ConfigMotionCruiseVelocity(
		int sensorUnitsPer100ms, int timeoutMs) {
	return c_MotController_ConfigMotionCruiseVelocity(m_handle,
			sensorUnitsPer100ms, timeoutMs);
}
ErrorCode BaseMotorController::ConfigMotionAcceleration(
		int sensorUnitsPer100msPerSec, int timeoutMs) {
	return c_MotController_ConfigMotionAcceleration(m_handle,
			sensorUnitsPer100msPerSec, timeoutMs);
}

//------ Motion Profile Buffer ----------//
//void BaseMotorController::ClearMotionProfileTrajectories()
//{
//	c_MotController_ClearMotionProfileTrajectories();
//}
//int BaseMotorController::GetMotionProfileTopLevelBufferCount()
//{
//	return c_MotController_GetMotionProfileTopLevelBufferCount();
//}
//bool BaseMotorController::IsMotionProfileTopLevelBufferFull()
//{
//	return c_MotController_IsMotionProfileTopLevelBufferFull();
//}
//void BaseMotorController::ProcessMotionProfileBuffer()
//{
//	c_MotController_ProcessMotionProfileBuffer();
//}
//void BaseMotorController::GetMotionProfileStatus(Motion.MotionProfileStatus statusToFill)
//{
//	c_MotController_GetMotionProfileStatus(statusToFill);
//}
//ErrorCode BaseMotorController::PushMotionProfileTrajectory(Motion.TrajectoryPoint trajPt)
//{
//	return c_MotController_PushMotionProfileTrajectory(trajPt);
//}
//void BaseMotorController::ClearMotionProfileHasUnderrun(int timeoutMs)
//{
//	c_MotController_ClearMotionProfileHasUnderrun(timeoutMs);
//}

//------ error ----------//
ErrorCode BaseMotorController::GetLastError() {
	return c_MotController_GetLastError(m_handle);
}

//------ Faults ----------//
ErrorCode BaseMotorController::GetFaults(Faults & toFill) {
	return ErrorCode::NotImplemented; // 	return SetLastError(_ll->GetFaults(toFill));
}
ErrorCode BaseMotorController::GetStickyFaults(StickyFaults & toFill) {
	return ErrorCode::NotImplemented; // return SetLastError(_ll->GetStickyFaults(toFill));
}
ErrorCode BaseMotorController::ClearStickyFaults(int timeoutMs) {
	return ErrorCode::NotImplemented; // return SetLastError(_ll->ClearStickyFaults(timeoutMs));
}

//------ Firmware ----------//
int BaseMotorController::GetFirmwareVersion() {
	int retval = -1;
	c_MotController_GetFirmwareVersion(m_handle, &retval);
	return retval;
}
bool BaseMotorController::HasResetOccured() {
	bool retval = false;
	c_MotController_HasResetOccurred(m_handle, &retval);
	return retval;
}

//------ Custom Persistent Params ----------//
ErrorCode BaseMotorController::ConfigSetCustomParam(int newValue,
		int paramIndex, int timeoutMs) {
	return c_MotController_ConfigSetCustomParam(m_handle, newValue, paramIndex, timeoutMs);
}
int BaseMotorController::ConfigGetCustomParam(
		int paramIndex, int timeoutMs) {
	int readValue;
	c_MotController_ConfigGetCustomParam(m_handle, &readValue, paramIndex, timeoutMs);
	return readValue;
}

//------ Generic Param API, typically not used ----------//
ErrorCode BaseMotorController::ConfigSetParameter(ParamEnum param, float value,
		uint8_t subValue, int ordinal, int timeoutMs) {
	return c_MotController_ConfigSetParameter(m_handle, param, value, subValue, ordinal, timeoutMs);

}
float BaseMotorController::ConfigGetParameter(ParamEnum param, int ordinal, int timeoutMs) {
	float value = 0;
	c_MotController_ConfigGetParameter(m_handle, param, &value, ordinal, timeoutMs);
	return value;
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
	Set(ControlMode::Follower, (float)id24);
}
void BaseMotorController::ValueUpdated() {
	//do nothing
}
// ----- WPILIB ------//
frc::SpeedController & BaseMotorController::GetWPILIB_SpeedController()
{
	return *_wpilibSpeedController;
}
