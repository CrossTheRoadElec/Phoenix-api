package com.ctre.phoenix.platform.can;

/**
 * Keeps track of cache state
 */
public enum AutocacheState {
	/**
	 * Disabled cache
	 */
	Disabled(0), 
	/**
	 * Enabled cache
	 */
	Enabled(1);

	/**
	 * Get AutocacheState of specified value
	 * @param value Value of autocacheState
	 * @return AutocacheState of specified value
	 */
	public static AutocacheState valueOf(int value) {
		for (AutocacheState frame : values()) {
			if (frame.value == value) {
				return frame;
			}
		}
		return null;
	}

	/**
	 * Value of AutocacheState
	 */
	public final int value;

	/**
	 * Create AutocacheState of initValue
	 * @param initValue Value of AutocacheState
	 */
	AutocacheState(int initValue) {
		this.value = initValue;
	}
}