package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum RemoteFeedbackDevice {
    //NOTE: None was removed as it doesn't exist in firmware
    //TODO: Add None to firmware and add None back in
	
    SensorSum(9),
	SensorDifference(10),
	RemoteSensor0(11),
	RemoteSensor1(12),
	SoftwareEmulatedSensor(15);
	
	public final int value;
	RemoteFeedbackDevice(int initValue)
	{
		this.value = initValue;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, RemoteFeedbackDevice> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, RemoteFeedbackDevice>();
		for (RemoteFeedbackDevice type : RemoteFeedbackDevice.values()) {
			_map.put(type.value, type);
		}
    }
    /** public lookup to convert int to enum */
	public static RemoteFeedbackDevice valueOf(int value) {
		RemoteFeedbackDevice retval = _map.get(value);
		if (retval != null)
			return retval;
		return RemoteSensor0;
	}
    public static RemoteFeedbackDevice valueOf(double value) {
        return valueOf((int) value); 
    }
	public FeedbackDevice getFeedbackDevice() {
		switch (value) {
			case 9:  return FeedbackDevice.SensorSum;
			case 10: return FeedbackDevice.SensorDifference;
			case 12: return FeedbackDevice.RemoteSensor1;
			case 15: return FeedbackDevice.SoftwareEmulatedSensor;
			default: return FeedbackDevice.RemoteSensor0;
		}
	}
    public String toString() {
        switch(value) {
            case 9 : return "RemoteFeedbackDevice.SensorSum";
            case 10: return "RemoteFeedbackDevice.SensorDifference";
            case 11: return "RemoteFeedbackDevice.RemoteSensor0";
            case 12: return "RemoteFeedbackDevice.RemoteSensor1";
            case 15: return "RemoteFeedbackDevice.SoftwareEmulatedSensor";
            default: return "InvalidValue";
        }

    }
};
