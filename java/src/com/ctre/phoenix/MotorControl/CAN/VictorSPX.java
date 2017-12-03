package com.ctre.phoenix.MotorControl.CAN;

public class VictorSPX extends com.ctre.phoenix.MotorControl.CAN.BaseMotorController {

	public VictorSPX(int deviceNumber) {
		super(deviceNumber | 0x01040000);
	}

}
