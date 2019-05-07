package com.ctre.phoenix.sensors;

import com.ctre.phoenix.CustomParamConfiguration;

/**
 * Configurables available to Pigeon
 */
public class PigeonIMUConfiguration extends CustomParamConfiguration {
	public PigeonIMUConfiguration() {}

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
        String retstr = super.toString(prependString);

        return retstr;
    }

}
