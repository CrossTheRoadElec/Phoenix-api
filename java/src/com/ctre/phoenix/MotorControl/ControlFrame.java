package com.ctre.phoenix.MotorControl;

public enum ControlFrame
{
	Control_2_Enable_50m(0x040040),
	Control_3_General(0x040080),
	Control_4_Advanced(0x0400C0),
	Control_6_MotProfAddTrajPoint(0x040140);
	
	public int value;
	ControlFrame(int value)
	{
		this.value = value;
	}
};

// class controlframeroutines{
	// public static controlframeenhanced promote(controlframe controlframe){
		// return (controlframeenhanced)controlframe;
	// }
// }