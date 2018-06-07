package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.RemoteSensorSource;

public class SlotConfiguration{

    public double kP;
    public double kI;
    public double kD;
    public double kF;
    public int IntegralZone;
    public int AllowableClosedloopError;
    public double MaxIntegralAccumulator;
    public double ClosedLoopPeakOutput;
    public int ClosedLoopPeriod;

    public SlotConfiguration() {

        kP = 0.0;
        kI = 0.0;
        kD = 0.0;
        kF = 0.0;
        IntegralZone = 0;
        AllowableClosedloopError = 0;
        MaxIntegralAccumulator = 0.0;
        ClosedLoopPeakOutput = 1.0;
        ClosedLoopPeriod = 1;
    }
} // class SlotConfiguration

