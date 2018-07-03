package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum VelocityMeasPeriod {
	Period_1Ms(1),
	Period_2Ms(2),
	Period_5Ms(5),
	Period_10Ms(10),
	Period_20Ms(20),
	Period_25Ms(25),
	Period_50Ms(50),
	Period_100Ms(100);
	
	public int value;
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
    /** public lookup to convert int to enum */
	public static VelocityMeasPeriod valueOf(int value) {
		VelocityMeasPeriod retval = _map.get(value);
		if (retval != null)
			return retval;
		return Period_100Ms;
	}
    public static VelocityMeasPeriod valueOf(double value) {
        return valueOf((int) value); 
    }
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
