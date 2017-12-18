#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"
#include "ctre/phoenix/CCI/MotController_CCI.h"

using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

TalonSRX::TalonSRX(int deviceNumber) :
		BaseMotorController(deviceNumber | 0x02040000) {
}

ctre::phoenix::ErrorCode TalonSRX::ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice,
		int pidIdx, int timeoutMs) {
	return BaseMotorController::ConfigSelectedFeedbackSensor(feedbackDevice,
			pidIdx, timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice,
		int pidIdx, int timeoutMs) {
	return BaseMotorController::ConfigSelectedFeedbackSensor(feedbackDevice,
			pidIdx, timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::SetStatusFramePeriod(StatusFrameEnhanced frame,
		int periodMs, int timeoutMs) {
	return BaseMotorController::SetStatusFramePeriod(frame, periodMs, timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::SetStatusFramePeriod(StatusFrame frame,
		int periodMs, int timeoutMs) {
	return BaseMotorController::SetStatusFramePeriod(frame, periodMs, timeoutMs);
}
int TalonSRX::GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs) {
	int periodMs = 0;
	BaseMotorController::GetStatusFramePeriod(frame, timeoutMs);
	return periodMs;
}
int TalonSRX::GetStatusFramePeriod(StatusFrame frame, int timeoutMs) {
	int periodMs = 0;
	BaseMotorController::GetStatusFramePeriod(frame, timeoutMs);
	return periodMs;
}
ctre::phoenix::ErrorCode TalonSRX::ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
		int timeoutMs) {
	return BaseMotorController::ConfigVelocityMeasurementPeriod(period,
			timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::ConfigVelocityMeasurementWindow(int windowSize,
		int timeoutMs) {
	return BaseMotorController::ConfigVelocityMeasurementWindow(windowSize,
			timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::ConfigForwardLimitSwitchSource(
		LimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int timeoutMs) {

	return BaseMotorController::ConfigForwardLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::ConfigReverseLimitSwitchSource(
		LimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int timeoutMs) {
	return BaseMotorController::ConfigReverseLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, timeoutMs);
}

ctre::phoenix::ErrorCode TalonSRX::ConfigForwardLimitSwitchSource(
		RemoteLimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs) {

	return BaseMotorController::ConfigForwardLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, deviceID, timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::ConfigReverseLimitSwitchSource(
		RemoteLimitSwitchSource limitSwitchSource,
		LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs) {

	return BaseMotorController::ConfigReverseLimitSwitchSource(
			limitSwitchSource, normalOpenOrClose, deviceID, timeoutMs);
}

//------ Current Lim ----------//
ctre::phoenix::ErrorCode TalonSRX::ConfigPeakCurrentLimit(int amps, int timeoutMs) {
	return c_MotController_ConfigPeakCurrentLimit(m_handle, amps, timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::ConfigPeakCurrentDuration(int milliseconds, int timeoutMs) {
	return c_MotController_ConfigPeakCurrentDuration(m_handle, milliseconds,
			timeoutMs);
}
ctre::phoenix::ErrorCode TalonSRX::ConfigContinuousCurrentLimit(int amps, int timeoutMs) {
	return c_MotController_ConfigPeakCurrentDuration(m_handle, amps, timeoutMs);
}
void TalonSRX::EnableCurrentLimit(bool enable) {
	c_MotController_EnableCurrentLimit(m_handle, enable);
}

