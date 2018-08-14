package com.ctre.phoenix.platform;

public enum DeviceType {
    TalonSRX(0),
    VictorSPX(1),
    CANifier(2),
    PigeonIMU(3);

	public int value;
	DeviceType(int value)
	{
		this.value = value;
	}
}
