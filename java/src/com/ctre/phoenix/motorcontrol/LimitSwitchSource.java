package com.ctre.phoenix.motorcontrol;

public enum LimitSwitchSource {
	Disabled_(0),
	FeedbackConnector_(1),
	RemoteTalonSRX_(2),
	RemoteCANifier_(3);
	
	public int value;
	LimitSwitchSource(int value)
	{
		this.value = value;
	}
};