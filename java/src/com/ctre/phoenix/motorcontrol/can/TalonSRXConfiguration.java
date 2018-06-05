package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class TalonSRXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {
    public int PeakCurrentLimit;
    public int PeakCurrentDuration;
    public int ContinuousCurrentLimit;
    public TalonSRXConfiguration() {
        this.PeakCurrentLimit = 0;
        this.PeakCurrentDuration = 0;
        this.ContinuousCurrentLimit = 0;
    }
}

