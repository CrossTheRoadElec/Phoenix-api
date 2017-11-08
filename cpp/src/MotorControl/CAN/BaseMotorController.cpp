#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/LowLevel/MotControllerWithBuffer_LowLevel.h"
#include "ctre/phoenix/LowLevel/MotController_LowLevel.h"

using namespace CTRE::MotorControl::CAN;
//--------------------- Constructors -----------------------------//
/**
 * Constructor for the CANTalon device.
 * @param deviceNumber The CAN ID of the Talon SRX
 * @param externalEnable pass true to prevent sending enable frames.
 *  	This can be useful when having one device enable the Talon, and
 * 		another to control it.
 */
BaseMotorController::BaseMotorController(int arbId) {
	_ll = new MotController_LowLevel(arbId);
	_arbId = arbId;
	//_sensColl = new SensorCollection(_ll);
}

MotController_LowLevel & BaseMotorController::GetLowLevel()
{
	return *_ll;
}
int BaseMotorController::GetDeviceID()
{
	return _ll->GetDeviceNumber();
}
//------ Set output routines. ----------//
/**
 * Sets the appropriate output on the talon, depending on the mode.
 *
 * In PercentOutput, the output is between -1.0 and 1.0, with 0.0 as stopped.
 * In Voltage mode, output value is in volts.
 * In Current mode, output value is in amperes.
 * In Speed mode, output value is in position change / 100ms.
 * In Position mode, output value is in encoder ticks or an analog value,
 *   depending on the sensor.
 * In Follower mode, the output value is the integer device ID of the talon to
 * duplicate.
 *
 * @param outputValue The setpoint value, as described above.
 * @see SelectProfileSlot to choose between the two sets of gains.
 */
void BaseMotorController::Set(ControlMode Mode, float value) {
	Set(Mode, value, 0);
}
void BaseMotorController::Set(ControlMode mode, float demand0, float demand1) {
	m_controlMode = mode;
	m_sendMode = mode;
	m_setPoint = demand0;

	int status = 0;

	switch (m_controlMode) {
	case ControlMode::PercentOutput:
	case ControlMode::TimedPercentOutput:
		_ll->SetDemand(m_sendMode, (int) (1023 * demand0), 0);
		break;
	case ControlMode::Follower:
		_ll->SetDemand(m_sendMode, (int) (demand0), 0);
		break;
	default:
		_ll->SetDemand(m_sendMode, 0, 0);
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
	SetLastError(status);
}
void BaseMotorController::NeutralOutput() {
	Set(ControlMode::Disabled, 0);
}
void BaseMotorController::SetNeutralMode(NeutralMode neutralMode) {
	_ll->SetNeutralMode(neutralMode);
}

//------ Invert behavior ----------//
void BaseMotorController::SetSensorPhase(bool PhaseSensor) {
	_ll->SetSensorPhase(PhaseSensor);
}
void BaseMotorController::SetInverted(bool invert) {
	_invert = invert; /* cache for getter */
	_ll->SetInverted(_invert);
}
bool BaseMotorController::GetInverted() {
	return _invert;
}

//----- general output shaping ------------------//
ErrorCode BaseMotorController::ConfigOpenloopRamp(
		float secondsFromNeutralToFull, int timeoutMs) {
	return _ll->ConfigOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
}
ErrorCode BaseMotorController::ConfigClosedloopRamp(
		float secondsFromNeutralToFull, int timeoutMs) {
	return _ll->ConfigClosedloopRamp(secondsFromNeutralToFull, timeoutMs);
}
ErrorCode BaseMotorController::ConfigPeakOutputForward(float percentOut,
		int timeoutMs) {
	return _ll->ConfigPeakOutputForward(percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigPeakOutputReverse(float percentOut,
		int timeoutMs) {
	return _ll->ConfigPeakOutputReverse(percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigNominalOutputForward(float percentOut,
		int timeoutMs) {
	return _ll->ConfigNominalOutputForward(percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigNominalOutputReverse(float percentOut,
		int timeoutMs) {
	return _ll->ConfigNominalOutputReverse(percentOut, timeoutMs);
}
ErrorCode BaseMotorController::ConfigOpenLoopNeutralDeadband(
		float percentDeadband, int timeoutMs) {
	return _ll->ConfigOpenLoopNeutralDeadband(percentDeadband, timeoutMs);
}
ErrorCode BaseMotorController::ConfigClosedLoopNeutralDeadband(
		float percentDeadband, int timeoutMs) {
	return _ll->ConfigClosedLoopNeutralDeadband(percentDeadband, timeoutMs);
}

//------ Voltage Compensation ----------//
ErrorCode BaseMotorController::ConfigVoltageCompSaturation(float voltage,
		int timeoutMs) {
	return _ll->ConfigVoltageCompSaturation(voltage, timeoutMs);
}
ErrorCode BaseMotorController::ConfigVoltageMeasurementFilter(
		int filterWindowSamples, int timeoutMs) {
	return _ll->ConfigVoltageMeasurementFilter(filterWindowSamples, timeoutMs);
}
void BaseMotorController::EnableVoltageCompensation(bool enable) {
	_ll->EnableVoltageCompensation(enable);
}

//------ General Status ----------//
ErrorCode BaseMotorController::GetBusVoltage(float & param) {
	return _ll->GetBusVoltage(param);
}
ErrorCode BaseMotorController::GetMotorOutputPercent(float & param) {
	return _ll->GetMotorOutputPercent(param);
}
ErrorCode BaseMotorController::GetMotorOutputVoltage(float & param) {
	ErrorCode er;
	float v, p;
	er = GetBusVoltage(v);
	GetMotorOutputPercent(p);

	param = v * p;
	return er;
}
ErrorCode BaseMotorController::GetOutputCurrent(float & param) {
	return _ll->GetOutputCurrent(param);
}
ErrorCode BaseMotorController::GetTemperature(float & param) {
	return _ll->GetTemperature(param);
}

//------ sensor selection ----------//
ErrorCode BaseMotorController::ConfigSelectedFeedbackSensor(
		RemoteFeedbackDevice feedbackDevice, int timeoutMs) {
	/* we may break this into two APIs */
	ErrorCode e1 = _ll->ConfigRemoteFeedbackFilter(feedbackDevice._arbId,
			feedbackDevice._peripheralIndex, feedbackDevice._reserved,
			timeoutMs);

	ErrorCode e2 = _ll->ConfigSelectedFeedbackSensor(
			FeedbackDevice::RemoteSensor, timeoutMs);

	if (e1 == ErrorCode::OK) {
		return e2;
	}
	return e1;
}
ErrorCode BaseMotorController::ConfigSelectedFeedbackSensor(
		FeedbackDevice feedbackDevice, int timeoutMs) {
	return _ll->ConfigSelectedFeedbackSensor(feedbackDevice, timeoutMs);
}

//------- sensor status --------- //
int BaseMotorController::GetSelectedSensorPosition() {
	int retval;
	SetLastError(_ll->GetSelectedSensorPosition(retval));
	return retval;
}
int BaseMotorController::GetSelectedSensorVelocity() {
	int retval;
	ErrorCode err = _ll->GetSelectedSensorVelocity(retval);
	SetLastError(err);
	return retval;
}
ErrorCode BaseMotorController::SetSelectedSensorPosition(int sensorPos,
		int timeoutMs) {
	return _ll->SetSelectedSensorPosition(sensorPos, timeoutMs);
}

//------ status frame period changes ----------//
ErrorCode BaseMotorController::SetControlFramePeriod(ControlFrame frame,
		int periodMs) {
	return _ll->SetControlFramePeriod(frame, periodMs);
}
ErrorCode BaseMotorController::SetStatusFramePeriod(StatusFrame frame,
		int periodMs, int timeoutMs) {
	return _ll->SetStatusFramePeriod(frame, periodMs, timeoutMs);
}
ErrorCode BaseMotorController::SetStatusFramePeriod(StatusFrameEnhanced frame,
		int periodMs, int timeoutMs) {
	return _ll->SetStatusFramePeriod(frame, periodMs, timeoutMs);
}
ErrorCode BaseMotorController::GetStatusFramePeriod(StatusFrame frame,
		int & periodMs, int timeoutMs) {
	return _ll->GetStatusFramePeriod(frame, periodMs, timeoutMs);
}
ErrorCode BaseMotorController::GetStatusFramePeriod(StatusFrameEnhanced frame,
		int & periodMs, int timeoutMs) {
	return _ll->GetStatusFramePeriod(frame, periodMs, timeoutMs);
}

//----- velocity signal conditionaing ------//
ErrorCode BaseMotorController::ConfigVelocityMeasurementPeriod(
		VelocityMeasPeriod period, int timeoutMs) {
	return _ll->ConfigVelocityMeasurementPeriod(period, timeoutMs);
}
ErrorCode BaseMotorController::ConfigVelocityMeasurementWindow(int windowSize,
		int timeoutMs) {
	return _ll->ConfigVelocityMeasurementWindow(windowSize, timeoutMs);
}

//------ remote limit switch ----------//
ErrorCode BaseMotorController::ConfigForwardLimitSwitchSource(
		RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int deviceID, int timeoutMs) {
	LimitSwitchSource cciType = LimitSwitchRoutines::Promote(type);
	return _ll->ConfigForwardLimitSwitchSource(cciType, normalOpenOrClose,
			deviceID, timeoutMs);
}

ErrorCode BaseMotorController::ConfigReverseLimitSwitchSource(
		RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int deviceID, int timeoutMs) {
	LimitSwitchSource cciType = LimitSwitchRoutines::Promote(type);
	return _ll->ConfigReverseLimitSwitchSource(cciType, normalOpenOrClose,
			deviceID, timeoutMs);
}
void BaseMotorController::EnableLimitSwitches(bool enable) {
	_ll->EnableLimitSwitches(enable);
}

//------ local limit switch ----------//
ErrorCode BaseMotorController::ConfigForwardLimitSwitchSource(
		LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int timeoutMs) {
	return _ll->ConfigForwardLimitSwitchSource(type, normalOpenOrClose, 0,
			timeoutMs);
}
ErrorCode BaseMotorController::ConfigReverseLimitSwitchSource(
		LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
		int timeoutMs) {
	return _ll->ConfigReverseLimitSwitchSource(type, normalOpenOrClose, 0,
			timeoutMs);
}

//------ soft limit ----------//
ErrorCode BaseMotorController::ConfigForwardSoftLimit(int forwardSensorLimit,
		int timeoutMs) {
	return _ll->ConfigForwardSoftLimit(forwardSensorLimit, timeoutMs);
}

ErrorCode BaseMotorController::ConfigReverseSoftLimit(int reverseSensorLimit,
		int timeoutMs) {
	return _ll->ConfigReverseSoftLimit(reverseSensorLimit, timeoutMs);
}

void BaseMotorController::EnableSoftLimits(bool enable) {
	_ll->EnableSoftLimits(enable);
}

//------ Current Lim ----------//
/* not available in base */

//------ General Close loop ----------//
ErrorCode BaseMotorController::Config_kP(int slotIdx, float value,
		int timeoutMs) {
	return _ll->Config_kP(slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_kI(int slotIdx, float value,
		int timeoutMs) {
	return _ll->Config_kI(slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_kD(int slotIdx, float value,
		int timeoutMs) {
	return _ll->Config_kD(slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_kF(int slotIdx, float value,
		int timeoutMs) {
	return _ll->Config_kF(slotIdx, value, timeoutMs);
}
ErrorCode BaseMotorController::Config_IntegralZone(int slotIdx, int izone,
		int timeoutMs) {
	return _ll->Config_IntegralZone(slotIdx, izone, timeoutMs);
}
ErrorCode BaseMotorController::ConfigAllowableClosedloopError(int slotIdx,
		int allowableCloseLoopError, int timeoutMs) {
	return _ll->ConfigAllowableClosedloopError(slotIdx, allowableCloseLoopError,
			timeoutMs);
}
ErrorCode BaseMotorController::ConfigMaxIntegralAccumulator(int slotIdx,
		float iaccum, int timeoutMs) {
	return _ll->ConfigMaxIntegralAccumulator(slotIdx, iaccum, timeoutMs);
}

ErrorCode BaseMotorController::SetIntegralAccumulator(float iaccum,
		int timeoutMs) {
	return _ll->SetIntegralAccumulator(iaccum, timeoutMs);
}

ErrorCode BaseMotorController::GetClosedLoopError(int & closedLoopError) {
	return SetLastError(_ll->GetClosedLoopError(closedLoopError, 0));
}
ErrorCode BaseMotorController::GetIntegralAccumulator(float & iaccum) {
	return _ll->GetIntegralAccumulator(iaccum, 0);
}
ErrorCode BaseMotorController::GetErrorDerivative(float & derror) {
	return SetLastError(_ll->GetErrorDerivative(derror, 0));
}
/**
 * SRX has two available slots for PID.
 * @param slotIdx one or zero depending on which slot caller wants.
 */
void BaseMotorController::SelectProfileSlot(int slotIdx) {
	m_profile = slotIdx; /* only get two slots for now */
	_ll->SelectProfileSlot(m_profile);
}

//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
ErrorCode BaseMotorController::ConfigMotionCruiseVelocity(
		int sensorUnitsPer100ms, int timeoutMs) {
	return ErrorCode::FeatureNotSupported;
}
ErrorCode BaseMotorController::ConfigMotionAcceleration(
		int sensorUnitsPer100msPerSec, int timeoutMs) {
	return ErrorCode::FeatureNotSupported;
}

//------ Motion Profile Buffer ----------//
//void BaseMotorController::ClearMotionProfileTrajectories()
//{
//	_ll->ClearMotionProfileTrajectories();
//}
//int BaseMotorController::GetMotionProfileTopLevelBufferCount()
//{
//	return _ll->GetMotionProfileTopLevelBufferCount();
//}
//bool BaseMotorController::IsMotionProfileTopLevelBufferFull()
//{
//	return _ll->IsMotionProfileTopLevelBufferFull();
//}
//void BaseMotorController::ProcessMotionProfileBuffer()
//{
//	_ll->ProcessMotionProfileBuffer();
//}
//void BaseMotorController::GetMotionProfileStatus(Motion.MotionProfileStatus statusToFill)
//{
//	_ll->GetMotionProfileStatus(statusToFill);
//}
//ErrorCode BaseMotorController::PushMotionProfileTrajectory(Motion.TrajectoryPoint trajPt)
//{
//	return _ll->PushMotionProfileTrajectory(trajPt);
//}
//void BaseMotorController::ClearMotionProfileHasUnderrun(int timeoutMs)
//{
//	_ll->ClearMotionProfileHasUnderrun(timeoutMs);
//}

//------ error ----------//
ErrorCode BaseMotorController::GetLastError() {
	return _lastError;
}
ErrorCode BaseMotorController::SetLastError(int error) {
	_lastError = (ErrorCode) error;
	return _lastError;
}
ErrorCode BaseMotorController::SetLastError(ErrorCode error) {
	_lastError = (ErrorCode) error;
	return _lastError;
}

//------ Faults ----------//
ErrorCode BaseMotorController::GetFaults(Faults toFill) {
	return ErrorCode::FeatureNotSupported;
}
ErrorCode BaseMotorController::GetStickyFaults(Faults toFill) {
	return ErrorCode::FeatureNotSupported;
}
ErrorCode BaseMotorController::ClearStickyFaults() {
	return ErrorCode::FeatureNotSupported;
}

//------ Firmware ----------//
int BaseMotorController::GetFirmwareVersion() {
	return _ll->GetFirmwareVersion();
}
bool BaseMotorController::HasResetOccured() {
	return _ll->HasResetOccured();
}

//------ Custom Persistent Params ----------//
ErrorCode BaseMotorController::ConfigSetCustomParam(int newValue,
		int paramIndex, int timeoutMs) {
	return _ll->ConfigSetCustomParam(newValue, paramIndex, timeoutMs);
}
ErrorCode BaseMotorController::ConfigGetCustomParam(int & readValue,
		int paramIndex, int timeoutMs) {
	return _ll->ConfigGetCustomParam(readValue, paramIndex, timeoutMs);
}

//------ Generic Param API, typically not used ----------//
ErrorCode BaseMotorController::ConfigSetParameter(ParamEnum param, float value,
		uint8_t subValue, int ordinal, int timeoutMs) {
	return _ll->ConfigSetParameter(param, value, subValue, ordinal, timeoutMs);

}
ErrorCode BaseMotorController::ConfigGetParameter(ParamEnum param,
		float & value, int ordinal, int timeoutMs) {
	ErrorCode retval = _ll->ConfigGetParameter(param, value, ordinal, timeoutMs);

	return SetLastError(retval);
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
	id24 |= (uint8_t) (baseId >> 0x00);
	Set(ControlMode::Follower, (float)id24);
}
void BaseMotorController::ValueUpdated() {
	//do nothing
}

