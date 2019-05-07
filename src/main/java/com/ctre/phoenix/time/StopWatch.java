package com.ctre.phoenix.time;

/**
 * Stopwatch to track time in milliseconds
 */
public class StopWatch
{
	private long _t0 = 0;
	private long _t1 = 0;
	
	/**
	 * Start the stopwatch
	 */
	public void start()
	{
		_t0 = System.currentTimeMillis();
	}
	
	/**
	 * @return Current time elapsed since start in s
	 */
	public double getDuration()
	{
		return (double)getDurationMs() / 1000;
	}
	/**
	 * @return Current time elapsed since start in ms
	 */
	public int getDurationMs()
	{
		_t1 = System.currentTimeMillis();
		long retval = _t1 - _t0;
		if(retval < 0)
			retval = 0;
		return (int)retval;
	}
}