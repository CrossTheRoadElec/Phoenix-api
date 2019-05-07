package com.ctre.phoenix.platform;

/**
 * Devices available to Sim
 */
public enum DeviceType {
	/**
	 * TalonSRX
	 */
	TalonSRX(0),
	/**
	 * VictorSPX
	 */
	VictorSPX(1),
	/**
	 * CANifier
	 */
	CANifier(2),
	/**
	 * Pigeon
	 */
    PigeonIMU(3);

	/**
	 * Value of DeviceType
	 */
	public int value;
	/**
	 * Create DeviceType of specified value
	 * @param value Value of DeviceType
	 */
	DeviceType(int value)
	{
		this.value = value;
	}
}
