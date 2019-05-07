package com.ctre.phoenix.motorcontrol;

/**
 * Control Frames for motor controllers
 */
public enum ControlFrame
{
	/**
	 * General Control frame for motor control
	 */
	Control_3_General(0x040080),
	/**
	 * Advanced Control frame for motor control
	 */
	Control_4_Advanced(0x0400C0),
	/**
	 * Control frame for adding trajectory points from Stream object
	 */
	Control_6_MotProfAddTrajPoint(0x040140);

	/**
	 * Value of Control Frame
	 */
	public final int value;

	/**
	 * Create Control frame of initValue
	 * @param initValue Value to create ControlFrame
	 */
	ControlFrame(int initValue)
	{
		this.value = initValue;
	}
};
