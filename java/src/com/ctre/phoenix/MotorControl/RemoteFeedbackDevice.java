package com.ctre.phoenix.MotorControl;

import com.ctre.phoenix.MotorControl.FeedbackDevice;
import com.ctre.phoenix.ErrorCode;

public class RemoteFeedbackDevice {
	
	public FeedbackDevice _type;
	
	public int _peripheralIndex;
	public int _reserved;
	public int _arbId;
	
	public RemoteFeedbackDevice(int baseId, FeedbackDevice type)
	{
		_type = type;
		_peripheralIndex = 0;
		_reserved = 2;
		_arbId = baseId;
	}
	
	ErrorCode SetPosition(double position, int timeoutMs)
	{
		return ErrorCode.FeatureNotSupported;
	}
}