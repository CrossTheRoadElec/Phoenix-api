package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose whether the limit switch is normally
 * open or normally closed
 */
public enum LimitSwitchNormal {
    /**
     * Limit Switch is tripped when
     * the circuit is closed
     */
    NormallyOpen(0),
    /**
     * Limit Switch is tripped when
     * the circuit is open 
     */ 
    NormallyClosed(1),
    /**
     * Limit switch is disabled 
     */ 
    Disabled(2);

    /**
     * Value of LimitSwitch Setting
     */
	public int value;

    /**
     * Create LimitSwitchNormal of specified value
     * @param value Value of LimitSwitchNormal
     */
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
    /**
     * Get LimitSwitchNormal of specified value
     * @param value Value of LimitSwitchNormal
     * @return LimitSwitchNormal of specified value
     */
	public static LimitSwitchNormal valueOf(int value) {
		LimitSwitchNormal retval = _map.get(value);
		if (retval != null)
			return retval;
		return NormallyOpen;
    }
    /**
     * Get LimitSwitchNormal of specified value
     * @param value Value of LimitSwitchNormal
     * @return LimitSwitchNormal of specified value
     */
    public static LimitSwitchNormal valueOf(double value) {
        return valueOf((int) value); 
    }
    /**
     * @return String representation of LimitSwitchNormal setting
     */
    public String toString() {
        switch(value) {
            case 0 : return "LimitSwitchNormal.NormallyOpen";
            case 1 : return "LimitSwitchNormal.NormallyClosed";
            case 2 : return "LimitSwitchNormal.Disabled";
            default : return "InvalidValue";
        }

    }

};
