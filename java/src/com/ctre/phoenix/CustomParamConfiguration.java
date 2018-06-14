package com.ctre.phoenix;

public abstract class CustomParamConfiguration{
	public int customParam_0;
	public int customParam_1;
	public CustomParamConfiguration() {
		customParam_0 = 0;
		customParam_1 = 0;
	}
    public String toString(String prependString) {
        String retstr = prependString + ".customParam_0 = " + String.valueOf(customParam_0) + ";\n";
        retstr += prependString + ".customParam_1 = " + String.valueOf(customParam_1) + ";\n";

        return retstr;
    }

}
