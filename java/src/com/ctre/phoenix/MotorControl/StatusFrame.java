package com.ctre.phoenix.MotorControl;

public enum StatusFrame {
	Status_1_General_(0x1400),
	Status_2_Feedback_(0x1440),
	Status_4_AinTempVbat_(0x14C0),
	Status_6_Misc_(0x1540),
	Status_7_CommStatus_(0x1580),
	Status_9_MotProfBuffer_(0x1600),
	Status_10_MotionMagic_(0x1640),
	Status_12_RobotPose_(0x16C0),
	Status_13_Base_PIDF1_(0x1700),
	Status_14_Turn_PIDF2_(0x1740),
	Status_15_FirmwareApiStatus_(0x1780);
	
	public int value;
	StatusFrame(int value)
	{
		this.value = value;
	}
};