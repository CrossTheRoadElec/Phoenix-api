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
	
	public int value;
	ControlMode(int value)
	{
		this.value = value;
	}
};