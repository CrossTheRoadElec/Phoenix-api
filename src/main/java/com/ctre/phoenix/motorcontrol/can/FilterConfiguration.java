package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.RemoteSensorSource;

public class FilterConfiguration {

    public int remoteSensorDeviceID;
    public RemoteSensorSource remoteSensorSource;

    public FilterConfiguration() {
        remoteSensorDeviceID = 0;
        remoteSensorSource = RemoteSensorSource.Off;
    }

	public String toString() {
		return toString("");
	}

    public String toString(String prependString) {
        String retstr = prependString + ".remoteSensorDeviceID = " + String.valueOf(remoteSensorDeviceID) + ";\n";
        retstr += prependString + ".remoteSensorSource = " + remoteSensorSource.toString() + ";\n";
        return retstr;
    }

}; // struct FilterConfiguration

