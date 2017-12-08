#pragma once

namespace CTRE
{
namespace MotorControl
{
struct StickyFaults {
	bool HardwareFailure;
	bool UnderVoltage;
	bool OverTemp;
	bool ForwardLimitSwitch;
	bool ReverseLimitSwitch;
	bool ForwardSoftLimit;
	bool ReverseSoftLimit;
	bool MsgOverflow;
	bool ResetDuringEn;

	//!< True iff any of the above flags are true.
	bool HasAnyFault() {
		return HardwareFailure | UnderVoltage | OverTemp | ForwardLimitSwitch
				| ReverseLimitSwitch | ForwardSoftLimit | ReverseSoftLimit
				| MsgOverflow | ResetDuringEn;
	}
};

}
}

