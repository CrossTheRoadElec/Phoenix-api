package com.ctre.phoenix.motorcontrol;

/**
 * The different status frames available to motor controllers
 */
public enum StatusFrame {
	/** 
	 * General Status
	 */
	Status_1_General(0x1400),
	/**
	 * Feedback for selected sensor on primary PID[0].
	 */
	Status_2_Feedback0(0x1440),
	/**
	 * Analog sensor, motor controller 
	 * temperature, and voltage at input leads
	 */
	Status_4_AinTempVbat(0x14C0),
	/**
	 * Miscellaneous signals
	 */
	Status_6_Misc(0x1540),
	/**
	 * Communication status
	 */
	Status_7_CommStatus(0x1580),
	/**
	 * Motion profile buffer status
	 */
	Status_9_MotProfBuffer(0x1600),

	/**
	 * Old name for Status 10
	 * @see #Status_10_Targets Use Status_10_Targets instead.
	 */
	Status_10_MotionMagic(0x1640),
	/**
	 * Correct name for Status 10
	 * @see #Status_10_MotionMagic Functionally equivalent to Status_10_MotionMagic
	 */
	Status_10_Targets(0x1640),

	/**
	 * Feedback for selected sensor on aux PID[1].
	 */
	Status_12_Feedback1(0x16C0),
	/**
	 * Primary PID
	 */
	Status_13_Base_PIDF0(0x1700),
	/**
	 * Auxiliary PID
	 */
	Status_14_Turn_PIDF1(0x1740),
	/**
	 * Firmware & API status information
	 */
	Status_15_FirmwareApiStatus(0x1780),


	/** MotionProfile Targets for Auxiliary PID1. */
	Status_17_Targets1(0x1C00);

	/**
	 * Value of StatusFrame
	 */
	public int value;
	/**
	 * Create StatusFrame of specified value
	 * @param value Value of StatusFrame
	 */
	StatusFrame(int value)
	{
		this.value = value;
	}
};
