package com.ctre.phoenix.motorcontrol;

public enum RemoteFeedbackDevice {
	None(-1),

	SensorSum(9),
	SensorDifference(10),
	RemoteSensor0(11),
	RemoteSensor1(12),
	SoftwareEmulatedSensor(15);
	
	public final int value;
	RemoteFeedbackDevice(int initValue)
	{
		this.value = initValue;
	}
	public FeedbackDevice getFeedbackDevice() {
		switch (value) {
			case 9:  return FeedbackDevice.SensorSum;
			case 10: return FeedbackDevice.SensorDifference;
			case 11: return FeedbackDevice.RemoteSensor0;
			case 12: return FeedbackDevice.RemoteSensor1;
			case 15: return FeedbackDevice.SoftwareEmulatedSensor;
			default: return FeedbackDevice.None;
		}
	}
};
