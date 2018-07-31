package com.ctre.phoenix;

public abstract class CustomParamConfiguration{
	public int customParam0;
	public int customParam1;
	public boolean enableOptimizations;
	public CustomParamConfiguration() {
		customParam0 = 0;
		customParam1 = 0;
		enableOptimizations = true;
	}

	public String toString() {
		return toString("");
	}

    public String toString(String prependString) {
        String retstr = prependString + ".customParam0 = " + String.valueOf(customParam0) + ";\n";
        retstr += prependString + ".customParam1 = " + String.valueOf(customParam1) + ";\n";

        return retstr;
    }

}
