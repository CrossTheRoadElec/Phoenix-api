package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class TalonSRX extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration
		implements CANBusAddressableConfiguration {
    int PeakCurrentLimit;
    int PeakCurrentDuration;
    int ContinuousCurrentLimit;
    TalonSRXConfiguration() {
        PeakCurrentLimit = 0;
        PeakCurrentDuration = 0;
        ContinuousCurrentLimit = 0;
    }
}

