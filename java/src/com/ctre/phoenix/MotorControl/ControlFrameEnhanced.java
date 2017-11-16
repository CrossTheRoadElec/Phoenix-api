package com.ctre.phoenix.MotorControl;

public enum ControlFrameEnhanced
{
	Control_2_Enable_50m_(0x040040),
	Control_3_General_(0x040080),
	Control_4_Advanced_(0x0400C0),
	Control_5_FeedbackOutputOverride_(0x040100),
	Control_6_MotProfAddTrajPoint(0x040140);
	
	public int value;
	ControlFrameEnhanced(int value)
	{
		this.value = value;
	}
};