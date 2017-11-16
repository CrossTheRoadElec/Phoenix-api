package com.ctre.phoenix.MotorControl;

public enum NeutralMode {
	/** Use the NeutralMode that is set by the jumper wire on the CAN device */
	EEPROMSetting(0),
	/** Stop the motor's rotation by applying a force. */
	Brake(1),
	/** Do not attempt to stop the motor. Instead allow it to coast to a stop
	 without applying resistance. */
	Coast(2);
	
	public int value;
	NeutralMode(int value)
	{
		this.value = value;
	}
};