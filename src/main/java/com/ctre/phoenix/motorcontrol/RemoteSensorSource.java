package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

public enum RemoteSensorSource {
	Off(0),
	TalonSRX_SelectedSensor(1),
	Pigeon_Yaw(2),
	Pigeon_Pitch(3),
	Pigeon_Roll(4),
	CANifier_Quadrature(5),
	CANifier_PWMInput0(6),
	CANifier_PWMInput1(7),
	CANifier_PWMInput2(8),
	CANifier_PWMInput3(9),
	GadgeteerPigeon_Yaw(10),
	GadgeteerPigeon_Pitch(11),
	GadgeteerPigeon_Roll(12);

	public int value;
	RemoteSensorSource(int value)
	{
		this.value = value;
	}
    /** Keep singleton map to quickly lookup enum via int */
    private static HashMap<Integer, RemoteSensorSource> _map = null;
	/** static c'tor, prepare the map */
    static {
    	_map = new HashMap<Integer, RemoteSensorSource>();
		for (RemoteSensorSource type : RemoteSensorSource.values()) {
			_map.put(type.value, type);
		}
    }
    /** public lookup to convert int to enum */
	public static RemoteSensorSource valueOf(int value) {
		RemoteSensorSource retval = _map.get(value);
		if (retval != null)
			return retval;
		return Off;
	}
    public static RemoteSensorSource valueOf(double value) {
        return valueOf((int) value); 
    }
    public String toString() {
        switch(value) {
            case 0 : return "RemoteSensorSource.Off";
            case 1 : return "RemoteSensorSource.TalonSRX_SelectedSensor";
            case 2 : return "RemoteSensorSource.Pigeon_Yaw";
            case 3 : return "RemoteSensorSource.Pigeon_Pitch";
            case 4 : return "RemoteSensorSource.Pigeon_Roll";
            case 5 : return "RemoteSensorSource.CANifier_Quadrature";
            case 6 : return "RemoteSensorSource.CANifier_PWMInput0";
            case 7 : return "RemoteSensorSource.CANifier_PWMInput1";
            case 8 : return "RemoteSensorSource.CANifier_PWMInput2";
            case 9 : return "RemoteSensorSource.CANifier_PWMInput3";
            case 10: return "RemoteSensorSource.GadgeteerPigeon_Yaw";
            case 11: return "RemoteSensorSource.GadgeteerPigeon_Pitch";
            case 12: return "RemoteSensorSource.GadgeteerPigeon_Roll";
            default: return "RemoteSensorSource.InvalidValue";
        }
    }

};
