package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose the velocity measurement period for a sensor
 */
public enum VelocityMeasPeriod {
	/**
	 * 1ms measurement period
	 */
	Period_1Ms(1),
	/**
	 * 2ms measurement period
	 */
	Period_2Ms(2),
	/**
	 * 5ms measurement period
	 */
	Period_5Ms(5),
	/**
	 * 10ms measurement period
	 */
	Period_10Ms(10),
	/**
	 * 20ms measurement period
	 */
	Period_20Ms(20),
	/**
	 * 25ms measurement period
	 */
	Period_25Ms(25),
	/**
	 * 50ms measurement period
	 */
	Period_50Ms(50),
	/**
	 * 100ms measurement period
	 */
	Period_100Ms(100);

	/**
	 * Value of VelocityMeasurementPeriod
	 */
	public int value;
	/**
	 * Create VelocityMeasurementPeriod of specified value
	 * @param value Value of VelocityMeasurementPeriod
	 */
	VelocityMeasPeriod(int value)
	{
		this.value = value;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, VelocityMeasPeriod> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, VelocityMeasPeriod>();
		for (VelocityMeasPeriod type : VelocityMeasPeriod.values()) {
			_map.put(type.value, type);
		}
	}
	/**
	 * Get VelocityMeasPeriod of specified value
	 * @param value Value of VelocityMeasPeriod
	 * @return VelocityMeasPeriod of specified value
	 */
	public static VelocityMeasPeriod valueOf(int value) {
		VelocityMeasPeriod retval = _map.get(value);
		if (retval != null)
			return retval;
		return Period_100Ms;
	}
	/**
	 * Get VelocityMeasPeriod of specified value
	 * @param value Value of VelocityMeasPeriod
	 * @return VelocityMeasPeriod of specified value
	 */
    public static VelocityMeasPeriod valueOf(double value) {
        return valueOf((int) value); 
	}
	/**
	 * @return String representation of VelocityMeasPeriod
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

};
