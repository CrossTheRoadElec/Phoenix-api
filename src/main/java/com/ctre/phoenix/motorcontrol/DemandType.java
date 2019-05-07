package com.ctre.phoenix.motorcontrol;

/**
 * Choose the demand type for the 4 param set
 */
public enum DemandType {
    /**
	 * Ignore the demand value and apply neutral/no-change.
	 */
	Neutral(0),
	/**
	 * When closed-looping, set the target of the aux PID loop to the demand value.
	 *
	 * When following, follow the processed output of the combined 
	 * primary/aux PID output of the master.  The demand value is ignored.
	 * Although it is much cleaner to use the 2-param Follow() in such cases.
	 */
	AuxPID(1), //!< Target value of PID loop 1.  When f
	/**
	 * When closed-looping, add demand arbitrarily to the closed-loop output.
	 */
	ArbitraryFeedForward(2); //!< Simply add to the output

	/**
	 * Value of DemandType
	 */
	public int value;

	/**
	 * Create DemandType of specified value
	 * @param value Value of DemandType
	 */
	DemandType(int value)
	{
		this.value = value;
	}
};
