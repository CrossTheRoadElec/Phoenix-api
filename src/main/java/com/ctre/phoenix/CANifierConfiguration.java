package com.ctre.phoenix;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.VelocityPeriod;




public class CANifierConfiguration extends CustomParamConfiguration{
	public VelocityPeriod velocityMeasurementPeriod;
	public int velocityMeasurementWindow;
    public boolean clearPositionOnLimitF;
    public boolean clearPositionOnLimitR;
    public boolean clearPositionOnQuadIdx;
    public CANifierConfiguration() {
		velocityMeasurementPeriod = VelocityPeriod.Period_100Ms; 
		velocityMeasurementWindow = 64;
	    clearPositionOnLimitF = false;
        clearPositionOnLimitR = false;
        clearPositionOnQuadIdx = false;

    }

	public String toString() {
		return toString("");
	}

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
