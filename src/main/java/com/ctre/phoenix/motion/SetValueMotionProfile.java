package com.ctre.phoenix.motion;

/**
 * Choose what value to set to the motion profile
 */
public enum SetValueMotionProfile {
	/**
	 * Invalid setting
	 */
	Invalid(-1), 
	/**
	 * Disable motion profile
	 */
	Disable(0), 
	/**
	 * Enable motion profile
	 */
	Enable(1), 
	/**
	 * Hold motion profile
	 * This will keep motor controllers enabled and attempt
	 * to servo to the current position
	 */
	Hold(2);

	/**
	 * Value of SetValueMotionProfile
	 */
	public final int value;

	/**
	 * Create SetValueMotionProfile of initValue
	 * @param initValue Value to create SetValueMotionProfile
	 */
	SetValueMotionProfile(int initValue) {
		this.value = initValue;
	}
	
	/**
	 * Get SetValueMotionProfile from specified value
	 * @param value value to get SetValueMotionProfile
	 * @return SetValueMotionProfile of specified value
	 */
	public static SetValueMotionProfile valueOf(int value) {
		for (SetValueMotionProfile e : SetValueMotionProfile.values()) {
			if (e.value == value) {
				return e;
			}
		}
		return Invalid;
	}
}
