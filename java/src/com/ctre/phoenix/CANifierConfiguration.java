package com.ctre.phoenix;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.VelocityPeriod;




public class CANifierConfiguration extends CustomParamConfiguration{
	public VelocityPeriod velocityMeasurementPeriod;
	public int velocityMeasurementWindow;
	public CANifierConfiguration() {
		velocityMeasurementPeriod = VelocityPeriod.Period_100Ms; 
		velocityMeasurementWindow = 64;
	}
    public String toString(String prependString) {

        String retstr = prependString + ".velocityMeasurementPeriod = " + velocityMeasurementPeriod.toString() + ";\n";
        retstr += prependString + ".velocityMeasurementWindow = " + String.valueOf(velocityMeasurementWindow) + ";\n";

        retstr += super.toString(prependString);

        return retstr;
    }

}
