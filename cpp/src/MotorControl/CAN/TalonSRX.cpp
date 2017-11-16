#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"
#include "ctre/phoenix/CCI/MotController_CCI.h"
//#include "ctre/phoenix/LowLevel/MotController_LowLevel.h"

using namespace CTRE::MotorControl::CAN;

TalonSRX::TalonSRX(int deviceNumber) :
		BaseMotorController(deviceNumber | 0x02040000) {
}

 //------ Current Lim ----------//
ErrorCode TalonSRX::ConfigPeakCurrentLimit(int amps, int timeoutMs)
{
	return c_MotController_ConfigPeakCurrentLimit(m_handle, amps, timeoutMs);
}
ErrorCode TalonSRX::ConfigPeakCurrentDuration(int milliseconds, int timeoutMs)
{
	return c_MotController_ConfigPeakCurrentDuration(m_handle, milliseconds, timeoutMs);
}
ErrorCode TalonSRX::ConfigContinuousCurrentLimit(int amps, int timeoutMs)
{
	return c_MotController_ConfigPeakCurrentDuration(m_handle, amps, timeoutMs);
}
void TalonSRX::EnableCurrentLimit(bool enable)
{
	c_MotController_EnableCurrentLimit(m_handle, enable);
}

