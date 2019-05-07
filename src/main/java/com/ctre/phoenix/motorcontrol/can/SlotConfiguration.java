package com.ctre.phoenix.motorcontrol.can;

/**
 * Configurables available to a slot
 */
public class SlotConfiguration{

    /**
     * P Gain
	 *
	 * This is multiplied by closed loop error in sensor units.  
	 * Note the closed loop output interprets a final value of 1023 as full output.  
	 * So use a gain of '0.25' to get full output if err is 4096u (Mag Encoder 1 rotation)
     */
    public double kP;
    /**
     * I Gain
     *
	 * This is multiplied by accumulated closed loop error in sensor units every PID Loop.  
	 * Note the closed loop output interprets a final value of 1023 as full output.  
	 * So use a gain of '0.00025' to get full output if err is 4096u for 1000 loops (accumulater holds 4,096,000),
	 * [which is equivalent to one CTRE mag encoder rotation for 1000 milliseconds].
     */
    public double kI;
    /**
     * D Gain
	 *
	 * This is multiplied by derivative error (sensor units per PID loop, typically 1ms).  
	 * Note the closed loop output interprets a final value of 1023 as full output.  
	 * So use a gain of '250' to get full output if derr is 4096u (Mag Encoder 1 rotation) per 1000 loops (typ 1 sec)
     */
    public double kD;
    /**
     * F Gain
	 *
	 * See documentation for calculation details.  
	 * If using velocity, motion magic, or motion profile, 
	 * use (1023 * duty-cycle / sensor-velocity-sensor-units-per-100ms).
	 *
     */
    public double kF;
    /**
     * Integral zone (in native units)
	 * 
	 * If the (absolute) closed-loop error is outside of this zone, integral
	 * accumulator is automatically cleared. This ensures than integral wind up
	 * events will stop after the sensor gets far enough from its target.
	 *
     */
    public int integralZone;
    /**
     * Allowable closed loop error to neutral (in native units)
     */
    public int allowableClosedloopError;
    /**
     * Max integral accumulator (in native units)
     */
    public double maxIntegralAccumulator;
    /**
     * Peak output from closed loop [0,1]
     */
    public double closedLoopPeakOutput;
    /**
     * Desired period of closed loop [1,64]ms
     */
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

    /**
     * @return String representation of configs
     */
	public String toString() {
		return toString("");
	}

    /**
     * @param prependString
     *              String to prepend to configs
     * @return String representation of configs
     */
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

