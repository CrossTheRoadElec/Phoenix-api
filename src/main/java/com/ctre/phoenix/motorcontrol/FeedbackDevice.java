package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose the feedback device for a selected sensor
 */
public enum FeedbackDevice {
    //NOTE: None was removed as it doesn't exist in firmware
	//TODO: Add None to firmware and add None back in
	
	/**
	 * Quadrature encoder
	 */
	QuadEncoder(0),
	/**
	 * Analog potentiometer/encoder
	 */
	Analog(2),
	/**
	 * Tachometer
	 */
	Tachometer(4),
	/**
	 * CTRE Mag Encoder in Relative mode or
	 * any other device that uses PWM to encode its output
	 */
	PulseWidthEncodedPosition(8),

	/**
	 * Sum0 + Sum1
	 */
	SensorSum(9),
	/**
	 * Diff0 - Diff1
	 */
	SensorDifference(10),
	/**
	 * Sensor configured in RemoteFilter0
	 */
	RemoteSensor0(11),
	/**
	 * Sensor configured in RemoteFilter1
	 */
	RemoteSensor1(12),
	/**
	 * Motor Controller will fake a sensor based on applied motor output.
	 */
	SoftwareEmulatedSensor(15),

	/**
	 * CTR mag encoder configured in absolute, is the same 
	 * as a PWM sensor.
	 */
	CTRE_MagEncoder_Absolute(8),
	/**
	 * CTR mag encoder configured in relative, is the same 
	 * as an quadrature encoder sensor.
	 */
	CTRE_MagEncoder_Relative(0);
	
	/** Value of Feedback Device */
	public final int value;

	/**
	 * Create Feedback device of initValue
	 * @param initValue Value of FeedbackDevice
	 */
	FeedbackDevice(int initValue)
	{
		this.value = initValue;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, FeedbackDevice> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, FeedbackDevice>();
		for (FeedbackDevice type : FeedbackDevice.values()) {
			_map.put(type.value, type);
		}
    }
	/**
	 * Get FeedbackDevice from specified value
	 * @param value Value of FeedbackDevice
	 * @return FeedbackDevice of specified value
	 */
	public static FeedbackDevice valueOf(int value) {
		FeedbackDevice retval = _map.get(value);
		if (retval != null)
			return retval;
		return QuadEncoder;
	}
	/**
	 * Get FeedbackDevice from specified value
	 * @param value Value of FeedbackDevice
	 * @return FeedbackDevice of specified value
	 */
    public static FeedbackDevice valueOf(double value) {
        return valueOf((int) value); 
	}
	
	/**
	 * @return string representation of specified FeedbackDevice
	 */
    public String toString() {
        switch(value) {
            case 0 : return "FeedbackDevice.QuadEncoder";
            case 2 : return "FeedbackDevice.Analog";
            case 4 : return "FeedbackDevice.Tachometer";
            case 8 : return "FeedbackDevice.PulseWidthEncodedPosition";
            case 9 : return "FeedbackDevice.SensorSum";
            case 10: return "FeedbackDevice.SensorDifference";
            case 11: return "FeedbackDevice.RemoteSensor0";
            case 12: return "FeedbackDevice.RemoteSensor1";
            case 15: return "FeedbackDevice.SoftwareEmulatedSensor";
            default: return "InvalidValue";

        }

    }

};
