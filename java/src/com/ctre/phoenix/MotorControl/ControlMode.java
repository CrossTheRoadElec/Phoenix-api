package com.ctre.phoenix.MotorControl;

public class ControlMode
{
	public enum SmartControlMode
	{
		kPercentVbus(0),
		kCurrent(1),
		kSpeed(2),
		kPosition(3),
		kVoltage(4),
		kFollower(5),
		kMotionProfile(6),
		kMotionMagic(7);
		
		public int value;
		SmartControlMode(int value)
		{
			this.value = value;
		}
	};
	
	public enum BasicControlMode
	{
		kPercentVbus(0),
		kVoltage(4),
		kFollower(5);
		
		public int value;
		BasicControlMode(int value)
		{
			this.value = value;
		}
	}
	
	public static SmartControlMode Promote(BasicControlMode basicControlMode)
	{
		return SmartControlMode.values()[basicControlMode.value];
	}
}