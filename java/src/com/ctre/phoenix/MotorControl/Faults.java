package com.ctre.phoenix.MotorControl;

public class Faults {
	boolean HardwareFailure;
	boolean UnderVoltage;
	boolean OverTemp;
	boolean ForwardLimitSwitch;
	boolean ReverseLimitSwitch;
	boolean ForwardSoftLimit;
	boolean ReverseSoftLimit;
	boolean MsgOverflow;
	boolean ResetDuringEn;

	//!< True iff any of the above flags are true.
	boolean hasAnyFault() {
		return HardwareFailure | UnderVoltage | OverTemp | ForwardLimitSwitch
				| ReverseLimitSwitch | ForwardSoftLimit | ReverseSoftLimit
				| MsgOverflow | ResetDuringEn;
	}
};

