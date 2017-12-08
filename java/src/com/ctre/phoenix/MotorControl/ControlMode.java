package com.ctre.phoenix.MotorControl;

public enum ControlMode
{
	PercentOutput(0),
	Position(1),
	Velocity(2),
	Current(3),
	Follower(5),
	MotionProfile(6),
	MotionMagic(7),
	MotionMagicArc(8),
	TimedPercentOutput(9),
	
	Disabled(15);
	
	public final int value;
	ControlMode(int initValue)
	{
		this.value = initValue;
	}
};