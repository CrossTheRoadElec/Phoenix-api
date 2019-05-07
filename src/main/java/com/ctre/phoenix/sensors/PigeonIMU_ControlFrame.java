package com.ctre.phoenix.sensors;

/** Enumerated type for control frame types. */
public enum PigeonIMU_ControlFrame {
	/**
	 * Control
	 */
	Control_1(0x00042800);

	/**
	 * Value of control frame
	 */
	public final int value;

	/**
	 * Create a PigeonIMU_ControlFrame of initValue
	 * @param initValue value of Control Frame
	 */
	PigeonIMU_ControlFrame(int initValue) {
		this.value = initValue;
	}

	/**
	 * Int to enum cast
	 * @param value value of control frame
	 * @return PigeonIMU_ControlFrame of specified value
	 */
	public static PigeonIMU_ControlFrame valueOf(int value) {
		for (PigeonIMU_ControlFrame mode : values()) {
			if (mode.value == value) {
				return mode;
			}
		}
		return null;
	}
}
