package com.ctre.phoenix.motorcontrol;

public enum FollowerType {
  FollowerType_PercentOutput(0),
  FollowerType_AuxOutput1(1);

	public int value;
	FollowerType(int value)
	{
		this.value = value;
	}
};
