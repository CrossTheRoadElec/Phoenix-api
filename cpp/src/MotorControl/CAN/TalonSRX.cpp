#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"
#include "ctre/phoenix/CCI/MotController_CCI.h"

using namespace CTRE::Phoenix::MotorControl::CAN;
using namespace CTRE::Phoenix::MotorControl;

TalonSRX::TalonSRX(int deviceNumber) :
		BaseMotorController(deviceNumber | 0x02040000) {
}

ErrorCode TalonSRX::ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice,
		int timeoutMs) {
	return BaseMotorController::ConfigSelectedFeedbackSensor(feedbackDevice,
			timeoutMs);
}
ErrorCode TalonSRX::SetStatusFramePeriod(StatusFrameEnhanced frame,
		int periodMs, int timeoutMs) {
	return BaseMotorController::SetStatusFramePeriod(frame, periodMs, timeoutMs);
}
int TalonSRX::GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs) {
	int periodMs = 0;
	BaseMotorController::GetStatusFramePeriod(frame, timeoutMs);
	return periodMs;
}

ErrorCode TalonSRX::ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
		int timeoutMs) {
	return BaseMotorController::ConfigVelocityMeasurementPeriod(period,
			timeoutMs);
}
ErrorCode TalonSRX::ConfigVelocityMeasurementWindow(int windowSize,
		int timeoutMs) {
	return BaseMotorController::ConfigVelocityMeasurementWindow(windowSize,
			timeoutMs);
}

ErrorCode TalonSRX::ConfigForwardLimitSwitchSource(
		LimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int timeoutMs) {

	return BaseMotorController::ConfigForwardLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, timeoutMs);
}
ErrorCode TalonSRX::ConfigReverseLimitSwitchSource(
		LimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int timeoutMs) {
	return BaseMotorController::ConfigReverseLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, timeoutMs);
}

ErrorCode TalonSRX::ConfigForwardLimitSwitchSource(
		RemoteLimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs) {

	return BaseMotorController::ConfigForwardLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, deviceID, timeoutMs);
}
ErrorCode TalonSRX::ConfigReverseLimitSwitchSource(
		RemoteLimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs) {

	return BaseMotorController::ConfigReverseLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, deviceID, timeoutMs);
}

//------ Current Lim ----------//
ErrorCode TalonSRX::ConfigPeakCurrentLimit(int amps, int timeoutMs) {
	return c_MotController_ConfigPeakCurrentLimit(m_handle, amps, timeoutMs);
}
ErrorCode TalonSRX::ConfigPeakCurrentDuration(int milliseconds, int timeoutMs) {
	return c_MotController_ConfigPeakCurrentDuration(m_handle, milliseconds,
			timeoutMs);
}
ErrorCode TalonSRX::ConfigContinuousCurrentLimit(int amps, int timeoutMs) {
	return c_MotController_ConfigPeakCurrentDuration(m_handle, amps, timeoutMs);
}
void TalonSRX::EnableCurrentLimit(bool enable) {
	c_MotController_EnableCurrentLimit(m_handle, enable);
}

