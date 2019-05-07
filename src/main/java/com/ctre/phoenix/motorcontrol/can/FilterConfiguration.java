package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.RemoteSensorSource;

/**
 * Configurations for filters
 */
public class FilterConfiguration {

    /**
     * Remote Sensor's device ID
     */
    public int remoteSensorDeviceID;
    /**
	 * The remote sensor device and signal type to bind.
     */
    public RemoteSensorSource remoteSensorSource;

    public FilterConfiguration() {
        remoteSensorDeviceID = 0;
        remoteSensorSource = RemoteSensorSource.Off;
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
        String retstr = prependString + ".remoteSensorDeviceID = " + String.valueOf(remoteSensorDeviceID) + ";\n";
        retstr += prependString + ".remoteSensorSource = " + remoteSensorSource.toString() + ";\n";
        return retstr;
    }

}; // struct FilterConfiguration

