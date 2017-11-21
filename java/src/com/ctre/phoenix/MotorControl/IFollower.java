package com.ctre.phoenix.MotorControl;
import com.ctre.phoenix.MotorControl.IMotorController;

public interface IFollower
{
	void Follow(IMotorController masterToFollow);
	void ValueUpdated();
}