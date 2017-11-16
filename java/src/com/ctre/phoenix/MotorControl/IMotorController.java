package com.ctre.phoenix.MotorControl;

public interface IMotorController extends com.ctre.phoenix.Signals.IOutputSignal, com.ctre.phoenix.Signals.IInvertable, IFollower
{
	public int getDeviceID();
	//public void setControlMode(com.ctre.phoenix.MotorControl.ControlMode mode);
	//public void setVoltageRampRate(double rampRate);
	//public void setVoltageCompensationRate(double rampRate);
	//public void configPeakOutputVoltage(double forwardVoltage, double reverseVoltage);
	//public void configNominalOutputVoltage(double forwardVoltage, double reverseVoltage);
}