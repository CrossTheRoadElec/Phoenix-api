package com.ctre.phoenix.MotorControl;

public enum RemoteLimitSwitchSource {
	Disabled__(0), RemoteTalonSRX__(2), RemoteCANifier__(3);
	
	public int value;
	RemoteLimitSwitchSource(int value)
	{
		this.value = value;
	}
};