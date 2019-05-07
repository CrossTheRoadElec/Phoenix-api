package com.ctre.phoenix;

/**
 * Configurables for any custom param configs
 */
public abstract class CustomParamConfiguration{
	/**
	 * Custom Param 0
	 */
	public int customParam0;
	/**
	 * Custom Param 1
	 */
	public int customParam1;
	/**
	 * Enable optimizations for ConfigAll (defaults true)
	 */
	public boolean enableOptimizations;
	
	public CustomParamConfiguration() {
		customParam0 = 0;
		customParam1 = 0;
		enableOptimizations = true;
	}

    /**
     * @return string representation of currently selected configs
     */
	public String toString() {
		return toString("");
	}

    /**
     * @param prependString String to prepend to all the configs
     * @return string representation fo currently selected configs
     */
    public String toString(String prependString) {
        String retstr = prependString + ".customParam0 = " + String.valueOf(customParam0) + ";\n";
        retstr += prependString + ".customParam1 = " + String.valueOf(customParam1) + ";\n";

        return retstr;
    }

}
