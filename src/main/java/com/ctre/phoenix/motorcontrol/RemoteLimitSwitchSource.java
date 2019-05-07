package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose the remote limit switch source for a motor controller
 */
public enum RemoteLimitSwitchSource {
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
     * Value of RemoteLimitSwitchSource
     */
	public int value;

    /**
     * Create RemoteLimitSwitchSource of specified value
     * @param value Value of RemoteLimitSwitchSource
     */
	RemoteLimitSwitchSource(int value) {
		this.value = value;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, RemoteLimitSwitchSource> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, RemoteLimitSwitchSource>();
		for (RemoteLimitSwitchSource type : RemoteLimitSwitchSource.values()) {
			_map.put(type.value, type);
		}
    }
    /**
     * Get RemoteLimitSwitchSource of specified value
     * @param value Value of RemoteLimitSwitchSource
     * @return RemoteLimitSwitchSource of specified value
     */
	public static RemoteLimitSwitchSource valueOf(int value) {
		RemoteLimitSwitchSource retval = _map.get(value);
		if (retval != null)
			return retval;
		return Deactivated;
	}
    /**
     * Get RemoteLimitSwitchSource of specified value
     * @param value Value of RemoteLimitSwitchSource
     * @return RemoteLimitSwitchSource of specified value
     */
    public static RemoteLimitSwitchSource valueOf(double value) {
        return valueOf((int) value); 
    }
    /**
     * @return String representation of RemoteLimitSwitchSource
     */
    public String toString() {
        switch(value) {
            case 1 : return "RemoteLimitSwitchSource.RemoteTalonSRX";
            case 2 : return "RemoteLimitSwitchSource.RemoteCANifier";
            case 3 : return "RemoteLimitSwitchSource.Deactivated";
            default : return "InvalidValue";
        }

    }

};
