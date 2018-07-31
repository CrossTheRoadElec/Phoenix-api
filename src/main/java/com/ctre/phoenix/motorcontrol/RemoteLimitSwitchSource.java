package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum RemoteLimitSwitchSource {
	RemoteTalonSRX(1), RemoteCANifier(2), Deactivated(3);

	public int value;

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
    /** public lookup to convert int to enum */
	public static RemoteLimitSwitchSource valueOf(int value) {
		RemoteLimitSwitchSource retval = _map.get(value);
		if (retval != null)
			return retval;
		return Deactivated;
	}
    public static RemoteLimitSwitchSource valueOf(double value) {
        return valueOf((int) value); 
    }
    public String toString() {
        switch(value) {
            case 1 : return "RemoteLimitSwitchSource.RemoteTalonSRX";
            case 2 : return "RemoteLimitSwitchSource.RemoteCANifier";
            case 3 : return "RemoteLimitSwitchSource.Deactivated";
            default : return "InvalidValue";
        }

    }

};
