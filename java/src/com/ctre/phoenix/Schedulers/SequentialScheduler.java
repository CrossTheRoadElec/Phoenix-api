package com.ctre.phoenix.Schedulers;
import java.util.ArrayList;

public class SequentialScheduler implements com.ctre.phoenix.ILoopable
{
	boolean _running = false;
	ArrayList<com.ctre.phoenix.ILoopable> _loops = new ArrayList<com.ctre.phoenix.ILoopable>();
	int _periodMs;
	int _idx;
	boolean _iterated = false;

	public SequentialScheduler(int periodMs)
	{
		_periodMs = periodMs;
	}
	public void Add(com.ctre.phoenix.ILoopable aLoop)
	{
		_loops.add(aLoop);
	}

	public com.ctre.phoenix.ILoopable GetCurrent()
	{
		return null;
	}

	public void RemoveAll()
	{
		_loops.clear();
	}

	public void Start()
	{
		_idx = 0;
		if(_loops.size() > 0)
			_loops.get(0).OnStart();
		
		_running = true;
	}
	public void Stop()
	{
		for (int i = 0; i < _loops.size(); i++)
		{
			_loops.get(i).OnStop();
		}
		_running = false;
	}
	public void Process()
	{
		_iterated = false;
		if (_idx < _loops.size())
		{
			if (_running)
			{
				com.ctre.phoenix.ILoopable loop = _loops.get(_idx);
				loop.OnLoop();
				if (loop.IsDone())
				{
					_iterated = true;
					++_idx;
					if (_idx < _loops.size()) _loops.get(_idx).OnStart();
				}
			}
		}
		else
		{
			_running = false;
		}
	}
	public boolean Iterated()
	{
		return _iterated;
	}
	//--- Loopable ---/
	public void OnStart()
	{
		Start();
	}

	public void OnLoop()
	{
		Process();
	}

	public boolean IsDone()
	{
		/* Have to return something to know if we are done */
		if (_running == false)
			return true;
		else
			return false;
	}

	public void OnStop()
	{
		Stop();
	}
}