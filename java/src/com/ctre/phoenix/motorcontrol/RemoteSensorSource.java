package com.ctre.phoenix.motorcontrol;

public enum RemoteSensorSource {
	Off(0),
	TalonSRX_SelectedSensor(1),
	Pigeon_Yaw(2),
	Pigeon_Pitch(3),
	Pigeon_Roll(4),
	CANifier_Quadrature(5),
	CANifier_PWMInput0(6),
	CANifier_PWMInput1(7),
	CANifier_PWMInput2(8),
	CANifier_PWMInput3(9);
	
	public int value;
	RemoteSensorSource(int value)
	{
		this.value = value;
	}
};