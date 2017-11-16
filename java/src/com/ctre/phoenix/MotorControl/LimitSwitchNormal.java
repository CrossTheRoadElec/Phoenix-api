package com.ctre.phoenix.MotorControl;

public enum LimitSwitchNormal {
	NormallyOpen(0), NormallyClosed(1);
	
	public int value;
	LimitSwitchNormal(int value)
	{
		this.value = value;
	}
};