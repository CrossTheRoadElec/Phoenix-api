package com.ctre.phoenix;
/**
 * Sticky Faults for CANifier (Currently has none)
 */
public class CANifierStickyFaults {
	/**
	 * @return true if any faults are tripped
	 */
	public boolean hasAnyFault() {
		return false;
	}
	/**
	 * @return Current fault list as a bit field
	 */
	public int toBitfield() {
		int retval = 0;
		return retval;
	}
	/**
	 * Updates current fault list with specified bit field of faults
	 * 
	 * @param bits bit field of faults to update with
	 */
	public void update(int bits) {
	}
	public CANifierStickyFaults() {
	}
};
