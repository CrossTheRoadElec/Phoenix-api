package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum FeedbackDevice {
	None(-1),

	QuadEncoder(0),
	Analog(2),
	Tachometer(4),
	PulseWidthEncodedPosition(8),

	SensorSum(9),
	SensorDifference(10),
	RemoteSensor0(11),
	RemoteSensor1(12),
	SoftwareEmulatedSensor(15),

	CTRE_MagEncoder_Absolute(8),
	CTRE_MagEncoder_Relative(0);
	
	
	public final int value;
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
    /** public lookup to convert int to enum */
	public static FeedbackDevice valueOf(int value) {
		FeedbackDevice retval = _map.get(value);
		if (retval != null)
			return retval;
		return QuadEncoder;
	}
    public static FeedbackDevice valueOf(double value) {
        return valueOf((int) value); 
    }
    public String toString() {
        switch(value) {
            case -1: return "FeedbackDevice.None";
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
