package com.ctre.phoenix.motorcontrol.can;

public class SlotConfiguration{

    public double kP;
    public double kI;
    public double kD;
    public double kF;
    public int integralZone;
    public int allowableClosedloopError;
    public double maxIntegralAccumulator;
    public double closedLoopPeakOutput;
    public int closedLoopPeriod;

    public SlotConfiguration() {

        kP = 0.0;
        kI = 0.0;
        kD = 0.0;
        kF = 0.0;
        integralZone = 0;
        allowableClosedloopError = 0;
        maxIntegralAccumulator = 0.0;
        closedLoopPeakOutput = 1.0;
        closedLoopPeriod = 1;
    }

	public String toString() {
		return toString("");
	}

    public String toString(String prependString) {

        String retstr = prependString + ".kP = " + String.valueOf(kP) + ";\n";
        retstr += prependString + ".kI = " + String.valueOf(kI) + ";\n";
        retstr += prependString + ".kD = " + String.valueOf(kD) + ";\n";
        retstr += prependString + ".kF = " + String.valueOf(kF) + ";\n";
        retstr += prependString + ".integralZone = " + String.valueOf(integralZone) + ";\n";
        retstr += prependString + ".allowableClosedloopError = " + String.valueOf(allowableClosedloopError) + ";\n";
        retstr += prependString + ".maxIntegralAccumulator = " + String.valueOf(maxIntegralAccumulator) + ";\n";
        retstr += prependString + ".closedLoopPeakOutput = " + String.valueOf(closedLoopPeakOutput) + ";\n";
        retstr += prependString + ".closedLoopPeriod = " + String.valueOf(closedLoopPeriod) + ";\n";

        return retstr;

    }

} // class SlotConfiguration

