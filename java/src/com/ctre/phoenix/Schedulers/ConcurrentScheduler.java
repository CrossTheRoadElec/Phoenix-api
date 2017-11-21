package com.ctre.phoenix.Schedulers;
import java.util.ArrayList;

import com.ctre.phoenix.ILoopable;

public class ConcurrentScheduler implements ILoopable {
	ArrayList<ILoopable> _loops = new ArrayList<ILoopable>();
	ArrayList<Boolean> _enabs = new ArrayList<Boolean>();

	public void Add(ILoopable aLoop, boolean enable) {
		_loops.add(aLoop);
		_enabs.add(enable);
	}
	public void Add(ILoopable aLoop) {
		Add(aLoop, true);
	}

	public void RemoveAll() {
		_loops.clear();
		_enabs.clear();
	}

	public void Start(ILoopable toStart) {
		for (int i = 0; i < _loops.size(); ++i) {
			ILoopable lp = (ILoopable) _loops.get(i);

			if (lp == toStart) {
				_enabs.set(i, true);
				lp.OnStart();
				return;
			}
		}

	}

	public void Stop(ILoopable toStop) {
		for (int i = 0; i < (int) _loops.size(); ++i) {
			ILoopable lp = (ILoopable) _loops.get(i);

			if (lp == toStop) {
				_enabs.set(i, false);
				lp.OnStop();
				return;
			}
		}
	}

	public void StartAll() { // All Loops

		for (ILoopable loop : _loops) {
			loop.OnStart();
		}
		for (int i = 0; i < _enabs.size(); ++i) {
			_enabs.set(i,  true);
		}
	}

	public void StopAll() { // All Loops
		for (ILoopable loop : _loops) {
			loop.OnStop();
		}
		for (int i = 0; i < _enabs.size(); ++i) {
			_enabs.set(i,  false);
		}
	}

	public void Process() {
		for (int i = 0; i < (int) _loops.size(); ++i) {
			ILoopable loop = (ILoopable) _loops.get(i);
			boolean en = (boolean) _enabs.get(i);
			if (en) {
				loop.OnLoop();
			} else {
				/* Current ILoopable is turned off, don't call OnLoop for it */
			}
		}
	}

	/* ILoopable */
	public void OnStart() {
		StartAll();
	}

	public void OnLoop() {
		Process();
	}

	public void OnStop() {
		StopAll();
	}

	public boolean IsDone() {
		return false;
	}
}