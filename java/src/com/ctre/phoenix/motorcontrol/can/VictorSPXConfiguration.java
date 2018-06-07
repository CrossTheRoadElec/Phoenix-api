package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.VictorSPXPIDSetConfiguration;
import com.ctre.phoenix.motorcontrol.RemoteLimitSwitchSource;

public class VictorSPXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {
	VictorSPXPIDSetConfiguration PrimaryPID;
    VictorSPXPIDSetConfiguration AuxilaryPID;
    RemoteLimitSwitchSource ForwardLimitSwitchSource;
    RemoteLimitSwitchSource ReverseLimitSwitchSource;
	
	VictorSPXConfiguration() {
        ForwardLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;
        ReverseLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;

	}

}

