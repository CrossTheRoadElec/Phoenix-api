package com.ctre.phoenix.motorcontrol;

public enum DemandType {
  /**
	 * Ignore the demand value and apply neutral/no-change.
	 */
	DemandType_Neutral(0),
	/**
	 * When closed-looping, set the target of the aux PID loop to the demand value.
	 *
	 * When following, follow the processed output of the combined
	 * primary/aux PID output.  The demand value is ignored.
	 */
	DemandType_AuxPID(1), //!< Target value of PID loop 1.  When f
	/**
	 * When closed-looping, add this arbitrarily to the closed-loop output.
	 */
	DemandType_ArbitraryFeedForward(2); //!< Simply add to the output

	public int value;
	DemandType(int value)
	{
		this.value = value;
	}
};
