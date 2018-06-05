package com.ctre.phoenix.motorcontrol.can;

public class SlotConfiguration{
    public double kP;
    public double kI;
    public double kD;
    public double kF;
    public double IntegralZone;
    public double AllowableClosedloopError;
    public double MaxIntegralAccumulator;
    public double ClosedLoopPeakOutput;
    public int ClosedLoopPeriod;
    SlotConfiguration(){
		this.kP = 0.0;
		this.kI = 0.0;
		this.kD = 0.0;
		this.kF = 0.0;
		this.IntegralZone = 0.0;
		this.AllowableClosedloopError = 0.0;
		this.MaxIntegralAccumulator = 0.0;
		this.ClosedLoopPeakOutput = 1.0;
		this.ClosedLoopPeriod = 1;
    }
}

