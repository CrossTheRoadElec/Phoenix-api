package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose the remote feedback device for a motor controller
 */
public enum RemoteFeedbackDevice {
    //NOTE: None was removed as it doesn't exist in firmware
    //TODO: Add None to firmware and add None back in
	
	/**
	 * Use Sum0 + Sum1
	 */
	SensorSum(9),
	/**
	 * Use Diff0 - Diff1
	 */
	SensorDifference(10),
	/**
	 * Use the sensor configured
	 * in remote filter0
	 */
	RemoteSensor0(11),
	/**
	 * Use the sensor configured
	 * in remote filter1
	 */
	RemoteSensor1(12),
	/**
	 * Motor Controller will fake a sensor based on applied motor output.
	 */
	SoftwareEmulatedSensor(15);

	/**
	 * Value of RemoteFeedbackDevice
	 */
	public final int value;
	/**
	 * Create RemoteFeedbackDevice of initValue
	 * @param initValue Value of RemoteFeedbackDevice
	 */
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
	/**
	 * Get RemoteFeedbackDevice from specified value
	 * @param value Value of RemoteFeedbackDevice
	 * @return RemoteFeedbackDevice of specified value
	 */
	public static RemoteFeedbackDevice valueOf(int value) {
		RemoteFeedbackDevice retval = _map.get(value);
		if (retval != null)
			return retval;
		return RemoteSensor0;
	}
	/**
	 * Get RemoteFeedbackDevice from specified value
	 * @param value Value of RemoteFeedbackDevice
	 * @return RemoteFeedbackDevice of specified value
	 */
    public static RemoteFeedbackDevice valueOf(double value) {
        return valueOf((int) value); 
	}
	/**
	 * @return FeedbackDevice of RemoteFeedbackDevice
	 */
	public FeedbackDevice getFeedbackDevice() {
		switch (value) {
			case 9:  return FeedbackDevice.SensorSum;
			case 10: return FeedbackDevice.SensorDifference;
			case 12: return FeedbackDevice.RemoteSensor1;
			case 15: return FeedbackDevice.SoftwareEmulatedSensor;
			default: return FeedbackDevice.RemoteSensor0;
		}
	}
	/**
	 * @return String representation of selected feedback device
	 */
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
