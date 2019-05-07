package com.ctre.phoenix;

/**
 * Control Frames for CANifier
 */
public enum CANifierControlFrame {
	/**
	 * CANifier General control
	 */
	Control_1_General(0x040000),
	/**
	 * CANifier PWM outputs 
	 */ 
	Control_2_PwmOutput(0x040040);

	/**
	 * CANifier Control Frame of specified value
	 * @param value Value of CANifier Control Frame
	 * @return CANifier control frame of specified value
	 */
	public static CANifierControlFrame valueOf(int value) {
		for (CANifierControlFrame frame : values()) {
			if (frame.value == value) {
				return frame;
			}
		}
		return null;
	}

	/**
	 * Value of CANifier control frame
	 */
	public final int value;

	/**
	 * Create CANifier control frame of initValue
	 * @param initValue CANifier Control Frame value
	 */
	CANifierControlFrame(int initValue) {
		this.value = initValue;
	}
}
