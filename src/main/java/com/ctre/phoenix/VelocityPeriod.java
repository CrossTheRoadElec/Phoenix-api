package com.ctre.phoenix;

import java.util.HashMap;

/** 
* Enum for velocity periods used for CANifier 
*/ 
public enum VelocityPeriod { 
	/**
	 * 1ms velocity measurement period
	 */
	Period_1Ms(1), 
	/**
	 * 2ms velocity measurement period
	 */
	Period_2Ms(2), 
	/**
	 * 5ms velocity measurement period
	 */
	Period_5Ms(5), 
	/**
	 * 10ms velocity measurement period
	 */
	Period_10Ms(10), 
	/**
	 * 20ms velocity measurement period
	 */
	Period_20Ms(20), 
	/**
	 * 25ms velocity measurement period
	 */
	Period_25Ms(25), 
	/**
	 * 50ms velocity measurement period
	 */
	Period_50Ms(50), 
	/**
	 * 100ms velocity measurement period
	 */
	Period_100Ms(100); 

	/** Value of velocity period */
	public final int value; 

	/** 
	 * Create a VelocityPeriod of initValue
	 * @param initValue Value of VelocityPeriod
	 */
	VelocityPeriod(int initValue) { 
		this.value = initValue; 
	} 
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, VelocityPeriod> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, VelocityPeriod>();
		for (VelocityPeriod type : VelocityPeriod.values()) {
			_map.put(type.value, type);
		}
    }
	/**
	 * Get velocityPeriod of specified value
	 * @param value value of VelocityPeriod
	 * @return VelocityPeriod of specified value
	 */
	public static VelocityPeriod valueOf(int value) {
		VelocityPeriod retval = _map.get(value);
		if (retval != null)
			return retval;
		return Period_100Ms;
	}
	/**
	 * Get VelocityPeriod of specified value
	 * @param value value of VelocityPeriod
	 * @return VelocityPeriod of specified value
	 */
    public static VelocityPeriod valueOf(double value) {
        return valueOf((int) value); 
	}
	/**
	 * @return String representation of specified VelocityPeriod
	 */
    public String toString() {
        switch(value) {
            case 1 : return "VelocityMeasPeriod.Period_1Ms";
            case 2 : return "VelocityMeasPeriod.Period_2Ms";
            case 5 : return "VelocityMeasPeriod.Period_5Ms";
            case 10 : return "VelocityMeasPeriod.Period_10Ms";
            case 20 : return "VelocityMeasPeriod.Period_20Ms";
            case 25 : return "VelocityMeasPeriod.Period_25Ms";
            case 50 : return "VelocityMeasPeriod.Period_50Ms";
            case 100 : return "VelocityMeasPeriod.Period_100Ms";
            default : return "InvalidValue";
        }
    }
} 
