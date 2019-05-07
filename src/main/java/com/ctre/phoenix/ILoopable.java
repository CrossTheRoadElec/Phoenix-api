package com.ctre.phoenix;

/**
 * Interface for loopable objects
 */
public interface ILoopable
{
	/**
	 * Function called when object starts
	 */
	public void onStart();
	/**
	 * Function called every loop
	 */
	public void onLoop();
	/**
	 * @return true if object is done 
	 */
	public boolean isDone();
	/**
	 * Function called when object stops
	 */
	public void onStop();
}