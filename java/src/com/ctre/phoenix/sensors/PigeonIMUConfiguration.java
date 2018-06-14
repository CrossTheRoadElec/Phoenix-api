package com.ctre.phoenix.sensors;

import com.ctre.phoenix.CustomParamConfiguration;

public class PigeonIMUConfiguration extends CustomParamConfiguration {
	public boolean temperatureCompensationDisable;
	public PigeonIMUConfiguration() {
		temperatureCompensationDisable = false;
	}
    public String toString(String prependString) {
        String retstr = prependString + ".temperatureCompensationDisable = " + String.valueOf(temperatureCompensationDisable) + ";\n";
        retstr += super.toString(prependString);

        return retstr;
    }

}
