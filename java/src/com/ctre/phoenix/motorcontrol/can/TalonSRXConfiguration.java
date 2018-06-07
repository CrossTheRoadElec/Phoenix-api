package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.TalonSRXPIDSetConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;

public class TalonSRXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {
	TalonSRXPIDSetConfiguration PrimaryPID;
    TalonSRXPIDSetConfiguration AuxilaryPID;
    LimitSwitchSource ForwardLimitSwitchSource;
    LimitSwitchSource ReverseLimitSwitchSource;

    int PeakCurrentLimit;
    int PeakCurrentDuration;
    int ContinuousCurrentLimit;

	public TalonSRXConfiguration() {
    	ForwardLimitSwitchSource = LimitSwitchSource.Deactivated;
        ReverseLimitSwitchSource = LimitSwitchSource.Deactivated;
        PeakCurrentLimit = 0;
        PeakCurrentDuration = 0;
        ContinuousCurrentLimit = 0;
	}
}

