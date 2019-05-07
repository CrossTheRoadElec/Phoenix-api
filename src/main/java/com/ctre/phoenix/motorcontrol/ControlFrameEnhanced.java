package com.ctre.phoenix.motorcontrol;

/**
 * Control Frames for enhanced motor controllers
 */
public enum ControlFrameEnhanced
{
	/**
	 * Control
	 */
	Control_2_Enable_50m(0x040040),
	/**
	 * General Control frame for motor control
	 */
	Control_3_General(0x040080),
	/**
	 * Advanced Control frame for motor control
	 */
	Control_4_Advanced(0x0400C0),
	/**
	 * Control frame to override feedback output
	 */
	Control_5_FeedbackOutputOverride(0x040100),
	/**
	 * Control frame for adding trajectory points from Stream object
	 */
	Control_6_MotProfAddTrajPoint(0x040140);

	/**
	 * Value of enhanced control frame
	 */
	public final int value;
	/**
	 * Create enhanced control frame of initValue
	 * @param initValue Value to create enhanced control frame
	 */
	ControlFrameEnhanced(int initValue)
	{
		this.value = initValue;
	}
};