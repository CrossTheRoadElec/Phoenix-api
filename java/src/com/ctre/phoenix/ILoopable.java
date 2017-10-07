package com.ctre.phoenix;

public interface ILoopable
{
	public void OnStart();
	public void OnLoop();
	public boolean IsDone();
	public void OnStop();
}