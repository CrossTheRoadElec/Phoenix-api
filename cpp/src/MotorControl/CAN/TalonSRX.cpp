#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"
#include "ctre/phoenix/LowLevel/MotController_LowLevel.h"

using namespace CTRE::MotorControl::CAN;

TalonSRX::TalonSRX(int deviceNumber) :
		BaseMotorController(deviceNumber | 0x02040000) {
}

 //------ Current Lim ----------//
ErrorCode TalonSRX::ConfigPeakCurrentLimit(int amps, int timeoutMs)
{
	return GetLowLevel().ConfigPeakCurrentLimit(amps, timeoutMs);
}
ErrorCode TalonSRX::ConfigPeakCurrentDuration(int milliseconds, int timeoutMs)
{
	return GetLowLevel().ConfigPeakCurrentDuration(milliseconds, timeoutMs);
}
ErrorCode TalonSRX::ConfigContinuousCurrentLimit(int amps, int timeoutMs)
{
	return GetLowLevel().ConfigPeakCurrentDuration(amps, timeoutMs);
}
void TalonSRX::EnableCurrentLimit(bool enable)
{
	GetLowLevel().EnableCurrentLimit(enable);
}

