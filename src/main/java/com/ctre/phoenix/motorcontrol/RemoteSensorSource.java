package com.ctre.phoenix.motorcontrol;

import java.util.HashMap;

/**
 * Choose the remote sensor source for a motor controller 
 */
public enum RemoteSensorSource {
	/**
	 * Don't use a sensor
	 */
	Off(0),
	/**
	 * Use a sensor connected to
	 * a TalonSRX and configured on
	 * the TalonSRX
	 */
	TalonSRX_SelectedSensor(1),
	/**
	 * Use a CAN Pigeon's Yaw value
	 */
	Pigeon_Yaw(2),
	/**
	 * Use a CAN Pigeon's Pitch value
	 */
	Pigeon_Pitch(3),
	/**
	 * Use a CAN Pigeon's Roll value
	 */
	Pigeon_Roll(4),
	/**
	 * Use a quadrature sensor
	 * connected to a CANifier
	 */
	CANifier_Quadrature(5),
	/**
	 * Use a PWM sensor connected
	 * to CANifier's PWM0
	 */
	CANifier_PWMInput0(6),
	/**
	 * Use a PWM sensor connected
	 * to CANifier's PWM1
	 */
	CANifier_PWMInput1(7),
	/**
	 * Use a PWM sensor connected
	 * to CANifier's PWM2
	 */
	CANifier_PWMInput2(8),
	/**
	 * Use a PWM sensor connected
	 * to CANifier's PWM3
	 */
	CANifier_PWMInput3(9),
	/**
	 * Use the yaw value of a pigeon
	 * connected to a talon over ribbon cable
	 */
	GadgeteerPigeon_Yaw(10),
	/**
	 * Use the pitch value of a pigeon
	 * connected to a talon over ribbon cable
	 */
	GadgeteerPigeon_Pitch(11),
	/**
	 * Use the roll value of a pigeon
	 * connected to a talon over ribbon cable
	 */
	GadgeteerPigeon_Roll(12);
	
	/**
	 * Value of RemoteSensorSource
	 */
	public int value;
	/**
	 * Create RemoteSensorSource of specified value
	 * @param value Value of RemoteSensorSource
	 */
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
	/**
	 * Get RemoteSensorSource of specified value
	 * @param value Value of RemoteSensorSource
	 * @return RemoteSensorSource of specified value
	 */
	public static RemoteSensorSource valueOf(int value) {
		RemoteSensorSource retval = _map.get(value);
		if (retval != null)
			return retval;
		return Off;
	}
	/**
	 * Get RemoteSensorSource of specified value
	 * @param value Value of RemoteSensorSource
	 * @return RemoteSensorSource of specified value
	 */
    public static RemoteSensorSource valueOf(double value) {
        return valueOf((int) value); 
	}
	/**
	 * @return string representation of RemoteSensorSource
	 */
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
