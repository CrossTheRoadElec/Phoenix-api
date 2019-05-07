package com.ctre.phoenix;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.VelocityPeriod;



/**
 * Configurables available to CANifier
 */
public class CANifierConfiguration extends CustomParamConfiguration{
    /** 
     * Velocity measurement period to use
     */
    public VelocityPeriod velocityMeasurementPeriod;
    /**
     * Velocity measurement window to use
     */
    public int velocityMeasurementWindow;
    /**
     * Whether to clear sensor position on forward limit
     */
    public boolean clearPositionOnLimitF;
    /**
     * Whether to clear sensor position on reverse limit
     */
    public boolean clearPositionOnLimitR;
    /**
     * Whether to clear sensor position on index
     */
    public boolean clearPositionOnQuadIdx;

    public CANifierConfiguration() {
		velocityMeasurementPeriod = VelocityPeriod.Period_100Ms; 
		velocityMeasurementWindow = 64;
	    clearPositionOnLimitF = false;
        clearPositionOnLimitR = false;
        clearPositionOnQuadIdx = false;

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

        String retstr = prependString + ".velocityMeasurementPeriod = " + velocityMeasurementPeriod.toString() + ";\n";
        retstr += prependString + ".velocityMeasurementWindow = " + String.valueOf(velocityMeasurementWindow) + ";\n";
        retstr += prependString + ".clearPositionOnLimitF = " + String.valueOf(clearPositionOnLimitF) + ";\n";
        retstr += prependString + ".clearPositionOnLimitR = " + String.valueOf(clearPositionOnLimitR) + ";\n";
        retstr += prependString + ".clearPositionOnQuadIdx = " + String.valueOf(clearPositionOnQuadIdx) + ";\n";


        retstr += super.toString(prependString);

        return retstr;
    }

}
