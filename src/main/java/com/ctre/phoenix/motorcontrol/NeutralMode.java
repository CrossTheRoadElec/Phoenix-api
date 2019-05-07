package com.ctre.phoenix.motorcontrol;

/**
 * Choose the neutral mode for a motor controller
 */
public enum NeutralMode {
	/** Use the NeutralMode that is set in the MC's persistent storage. */
	EEPROMSetting(0),
	/** When commanded to neutral, motor leads are set to high-impedance, allowing mechanism to coast. */
	Coast(1),
	/** When commanded to neutral, motor leads are commonized electrically to reduce motion. */
	Brake(2);
	
	/**
	 * Value of NeutralMode
	 */
	public int value;
	/**
	 * Create NeutralMode from specified value
	 * @param value Value of NeutralMode
	 */
	NeutralMode(int value)
	{
		this.value = value;
	}
};