package com.ctre.phoenix.MotorControl;

public interface IFollower
{
	void follow(Object masterToFollow);
	void valueUpdated();
}