package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class TalonSRXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration
		implements CANBusAddressableConfiguration {
    public int PeakCurrentLimit;
    public int PeakCurrentDuration;
    public int ContinuousCurrentLimit;
    public TalonSRXConfiguration() {
        PeakCurrentLimit = 0;
        PeakCurrentDuration = 0;
        ContinuousCurrentLimit = 0;
    }
}

