package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum SensorTerm {
	Sum0(0),
	Sum1(1),
	Diff0(2),
	Diff1(3);
	
	public int value;
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
    /** public lookup to convert int to enum */
	public static SensorTerm valueOf(int value) {
		SensorTerm retval = _map.get(value);
		if (retval != null)
			return retval;
		return Sum0;
	}
    public static SensorTerm valueOf(double value) {
        return valueOf((int) value); 
    }
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
