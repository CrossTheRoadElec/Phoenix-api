package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum LimitSwitchSource {
	FeedbackConnector(0), RemoteTalonSRX(1), RemoteCANifier(2), Deactivated(3);

	public int value;

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
    /** public lookup to convert int to enum */
	public static LimitSwitchSource valueOf(int value) {
		LimitSwitchSource retval = _map.get(value);
		if (retval != null)
			return retval;
		return FeedbackConnector;
	}
    public static LimitSwitchSource valueOf(double value) {
        return valueOf((int) value); 
    }
	public RemoteLimitSwitchSource getRemote() {
		switch (value) {
			case 1: return RemoteLimitSwitchSource.RemoteTalonSRX;
			case 2: return RemoteLimitSwitchSource.RemoteCANifier;
			default: return RemoteLimitSwitchSource.Deactivated;
		}
	} 
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
