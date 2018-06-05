package com.ctre.phoenix.motorcontrol.can;

public class SlotConfiguration{
    public double config_kP;
    public double config_kI;
    public double config_kD;
    public double config_kF;
    public double config_IntegralZone;
    public double configAllowableClosedloopError;
    public double configMaxIntegralAccumulator;
    public double configClosedLoopPeakOutput;
    public int configClosedLoopPeriod;
    SlotConfiguration(){
		kP = 0.0;
		kI = 0.0;
		kD = 0.0;
		kF = 0.0;
		IntegralZone = 0.0;
		AllowableClosedloopError = 0.0;
		MaxIntegralAccumulator = 0.0;
		ClosedLoopPeakOutput = 1.0;
		ClosedLoopPeriod = 1;
    }
}

