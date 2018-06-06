package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.VictorSPXSlotConfiguration;
import com.ctre.phoenix.motorcontrol.RemoteLimitSwitchSource;

public class VictorSPXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {
	VictorSPXSlotConfiguration Slot_0;
    VictorSPXSlotConfiguration Slot_1;
    VictorSPXSlotConfiguration Slot_2;
    VictorSPXSlotConfiguration Slot_3;
    RemoteLimitSwitchSource ForwardLimitSwitchSource;
    RemoteLimitSwitchSource ReverseLimitSwitchSource;
    int ForwardLimitSwitchDeviceID;
    int ReverseLimitSwitchDeviceID;
	
	VictorSPXConfiguration() {
        ForwardLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;
        ReverseLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;

	}

}

