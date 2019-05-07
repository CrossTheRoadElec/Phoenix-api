package com.ctre.phoenix;

/**
 * Status frames for CANifier
 */
public enum CANifierStatusFrame {
	/**
	 * General status 1
	 */
	Status_1_General(0x041400), 
	/**
	 * General status 2
	 */
	Status_2_General(0x041440), 
	/**
	 * PWM0 input
	 */
	Status_3_PwmInputs0(0x041480), 
	/**
	 * PWM1 input
	 */
	Status_4_PwmInputs1(0x0414C0), 
	/**
	 * PWM2 input
	 */
	Status_5_PwmInputs2(0x041500), 
	/**
	 * PWM3 input
	 */
	Status_6_PwmInputs3(0x041540), 
	/**
	 * Miscelaneous status
	 */
	Status_8_Misc(0x0415C0);

	/**
	 * Get the CANifier Status frame from a specified value  
	 * @param value integer value of CANifier status frame
	 * @return CANifier status frame of specified value
	 */
	public static CANifierStatusFrame valueOf(int value) {
		for (CANifierStatusFrame frame : values()) {
			if (frame.value == value) {
				return frame;
			}
		}
		return null;
	}

	/**
	 * Value of CANifier status frame
	 */
	public final int value;

	/**
	 * Create a CANifierStatusFrame from initValue
	 * @param initValue Value of CANifier Status Frame
	 */
	CANifierStatusFrame(int initValue) {
		this.value = initValue;
	}
}