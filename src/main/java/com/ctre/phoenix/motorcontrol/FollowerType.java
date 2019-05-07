package com.ctre.phoenix.motorcontrol;

/**
 * Choose the type of follower
 */
public enum FollowerType {
	/**
	 * Follow the percentOutput the master is using
	 */
	PercentOutput(0),
	/**
	 * Follow the auxiliary output the master is
	 * calculating. Used for 2-axis control.
	 * This typically means apply PID0 - PID1 from master.
	 */
	AuxOutput1(1);

    /** Value of follower type */
	public int value;
	/**
	 * Create a FollowerType of specified value
	 * @param value Value of FollowerType
	 */
	FollowerType(int value)
	{
		this.value = value;
	}
};
