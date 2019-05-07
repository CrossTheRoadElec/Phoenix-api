package com.ctre.phoenix.schedulers;
import java.util.ArrayList;

/**
 * Scheduler that will run its ILoopables in sequence
 */
public class SequentialScheduler implements com.ctre.phoenix.ILoopable
{
	boolean _running = false;
	ArrayList<com.ctre.phoenix.ILoopable> _loops = new ArrayList<com.ctre.phoenix.ILoopable>();
	int _periodMs;
	int _idx;
	boolean _iterated = false;

	/**
	 * Constructor for SequentialScheduler
	 * @param periodMs Not used, pass 0
	 */
	public SequentialScheduler(int periodMs)
	{
		_periodMs = periodMs;
	}
	/**
	 * Add ILoopable to scheduler
	 * @param aLoop ILoopable to add
	 */
	public void add(com.ctre.phoenix.ILoopable aLoop)
	{
		_loops.add(aLoop);
	}

	/**
	 * Get the currently running ILoopable
	 * @return null, not implemented
	 */
	public com.ctre.phoenix.ILoopable getCurrent()
	{
		return null;
	}

	/**
	 * Remove all ILoopables
	 */
	public void removeAll()
	{
		_loops.clear();
	}

	/**
	 * Start next ILoopable
	 */
	public void start()
	{
		_idx = 0;
		if(_loops.size() > 0)
			_loops.get(0).onStart();
		
		_running = true;
	}
	/**
	 * Stop every ILoopable
	 */
	public void stop()
	{
		for (int i = 0; i < _loops.size(); i++)
		{
			_loops.get(i).onStop();
		}
		_running = false;
	}
	/**
	 * Process the currently active ILoopable
	 * 
	 * Call this every loop
	 */
	public void process()
	{
		_iterated = false;
		if (_idx < _loops.size())
		{
			if (_running)
			{
				com.ctre.phoenix.ILoopable loop = _loops.get(_idx);
				loop.onLoop();
				if (loop.isDone())
				{
					_iterated = true;
					++_idx;
					if (_idx < _loops.size()) _loops.get(_idx).onStart();
				}
			}
		}
		else
		{
			_running = false;
		}
	}
	/**
	 * @return true if we've just iterated to the next ILoopable
	 */
	public boolean iterated()
	{
		return _iterated;
	}
	//--- Loopable ---/
	/**
	 * Start next ILoopable
	 */
	public void onStart()
	{
		start();
	}

	/**
	 * Process currently active ILoopable
	 */
	public void onLoop()
	{
		process();
	}

	/**
	 * @return true when no longer running
	 */
	public boolean isDone()
	{
		/* Have to return something to know if we are done */
		if (_running == false)
			return true;
		else
			return false;
	}

	/**
	 * Stop all ILoopables
	 */
	public void onStop()
	{
		stop();
	}
}