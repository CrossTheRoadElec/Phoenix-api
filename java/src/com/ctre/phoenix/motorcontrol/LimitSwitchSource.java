package com.ctre.phoenix.motorcontrol;

public enum LimitSwitchSource {
	FeedbackConnector(0), RemoteTalonSRX(1), RemoteCANifier(2), Deactivated(3);

	public int value;

	LimitSwitchSource(int value) {
		this.value = value;
	}
	public RemoteLimitSwitchSource getRemote() {
		switch (value) {
			case 1: return RemoteLimitSwitchSource.RemoteTalonSRX;
			case 2: return RemoteLimitSwitchSource.RemoteCANifier;
			default: return RemoteLimitSwitchSource.Deactivated;
		}
	} 
};
