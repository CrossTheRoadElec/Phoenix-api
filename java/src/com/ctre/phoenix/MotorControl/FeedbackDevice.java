package com.ctre.phoenix.motorcontrol;

public enum FeedbackDevice {
	None(-1),

	QuadEncoder(0),
	Analog(2),
	Tachometer(4),
	PulseWidthEncodedPosition(8),

	SensorSum(9),
	SensorDifference(10),
	Inertial(11),
	RemoteSensor(12),
	CurrentDrawMilliamperes(14),
	SoftwarEmulatedSensor(15);
	
	public final int value;
	FeedbackDevice(int initValue)
	{
		this.value = initValue;
	}
};