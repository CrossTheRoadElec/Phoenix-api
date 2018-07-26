package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum LimitSwitchNormal {
	NormallyOpen(0), NormallyClosed(1), Disabled(2);

	public int value;

	LimitSwitchNormal(int value) {
		this.value = value;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, LimitSwitchNormal> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, LimitSwitchNormal>();
		for (LimitSwitchNormal type : LimitSwitchNormal.values()) {
			_map.put(type.value, type);
		}
    }
    /** public lookup to convert int to enum */
	public static LimitSwitchNormal valueOf(int value) {
		LimitSwitchNormal retval = _map.get(value);
		if (retval != null)
			return retval;
		return NormallyOpen;
	}
    public static LimitSwitchNormal valueOf(double value) {
        return valueOf((int) value); 
    }
    public String toString() {
        switch(value) {
            case 0 : return "LimitSwitchNormal.NormallyOpen";
            case 1 : return "LimitSwitchNormal.NormallyClosed";
            case 2 : return "LimitSwitchNormal.Disabled";
            default : return "InvalidValue";
        }

    }

};
