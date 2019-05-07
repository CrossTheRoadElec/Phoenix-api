package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose the sensor term for a motor controller
 */
public enum SensorTerm {
	/**
	 * Choose Sum0 for a term
	 */
	Sum0(0),
	/**
	 * Choose Sum1 for a term
	 */
	Sum1(1),
	/**
	 * Choose Diff0 for a term
	 */
	Diff0(2),
	/**
	 * Choose Diff1 for a term
	 */
	Diff1(3);
	
	/**
	 * Value of SensorTerm
	 */
	public int value;
	/**
	 * Create SensorTerm of specified value
	 * @param value Value of SensorTerm
	 */
	SensorTerm(int value)
	{
		this.value = value;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, SensorTerm> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, SensorTerm>();
		for (SensorTerm type : SensorTerm.values()) {
			_map.put(type.value, type);
		}
	}
	/**
	 * Get SensorTerm of specified value
	 * @param value Value of SensorTerm
	 * @return SensorTerm of specified value
	 */
	public static SensorTerm valueOf(int value) {
		SensorTerm retval = _map.get(value);
		if (retval != null)
			return retval;
		return Sum0;
	}
	/**
	 * Get SensorTerm of specified value
	 * @param value Value of SensorTerm
	 * @return SensorTerm of specified value
	 */
    public static SensorTerm valueOf(double value) {
        return valueOf((int) value); 
	}
	/**
	 * @return string representation of SensorTerm
	 */
    public String toString() {
        switch(value) {
            case 0 : return "SensorTerm.Sum0";
            case 1 : return "SensorTerm.Sum1";
            case 2 : return "SensorTerm.Diff0";
            case 3 : return "SensorTerm.Diff1";
            default : return "InvalidValue";
        }
    }
};
