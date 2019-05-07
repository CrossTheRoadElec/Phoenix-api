package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose the limit switch source for a motor controller
 */
public enum LimitSwitchSource {
	/**
	 * Use a limit switch connected directly
	 * to the motor controller
	 */
	FeedbackConnector(0), 
    /**
     * Use the limit switch connected
     * to a TalonSRX
     */
	RemoteTalonSRX(1), 
    /**
     * Use the limit switch connected
     * to a CANifier 
     */ 
	RemoteCANifier(2), 
    /**
     * Don't use a limit switch
     */
	Deactivated(3);

	/**
	 * Value of LimitSwitchSource
	 */
	public int value;

	/**
	 * Create LimitSwitchSource of specified value
	 * @param value Value of LimitSwitchSource
	 */
	LimitSwitchSource(int value) {
		this.value = value;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, LimitSwitchSource> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, LimitSwitchSource>();
		for (LimitSwitchSource type : LimitSwitchSource.values()) {
			_map.put(type.value, type);
		}
	}
	/**
	 * Get LimitSwitchSource of specified value
	 * @param value Value of LimitSwitchSource
	 * @return LimitSwitchSource of specified value
	 */
	public static LimitSwitchSource valueOf(int value) {
		LimitSwitchSource retval = _map.get(value);
		if (retval != null)
			return retval;
		return FeedbackConnector;
	}
	/**
	 * Get LimitSwitchSource of specified value
	 * @param value Value of LimitSwitchSource
	 * @return LimitSwitchSource of specified value
	 */
    public static LimitSwitchSource valueOf(double value) {
        return valueOf((int) value); 
	}
	/**
	 * @return RemoteLimitSwitchSource of LimitSwitchSource
	 */
	public RemoteLimitSwitchSource getRemote() {
		switch (value) {
			case 1: return RemoteLimitSwitchSource.RemoteTalonSRX;
			case 2: return RemoteLimitSwitchSource.RemoteCANifier;
			default: return RemoteLimitSwitchSource.Deactivated;
		}
	} 
	/**
	 * @return String representation of LimitSwitchSource
	 */
    public String toString() {
        switch(value) {
            case 0 : return "LimitSwitchSource.FeedbackConnector";
            case 1 : return "LimitSwitchSource.RemoteTalonSRX";
            case 2 : return "LimitSwitchSource.RemoteCANifier";
            case 3 : return "LimitSwitchSource.Deactivated";
            default : return "InvalidValue";
        }

    }

};
