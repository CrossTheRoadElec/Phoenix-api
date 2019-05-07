package com.ctre.phoenix.schedulers;
import java.util.ArrayList;

import com.ctre.phoenix.ILoopable;

/**
 * Scheduler that wil run its ILoopables in concurrency
 */
public class ConcurrentScheduler implements ILoopable {
	ArrayList<ILoopable> _loops = new ArrayList<ILoopable>();
	ArrayList<Boolean> _enabs = new ArrayList<Boolean>();

	/**
	 * Add ILoopable to schedule
	 * @param aLoop ILoopable to add to schedule
	 * @param enable Whether to enable ILoopable
	 */
	public void add(ILoopable aLoop, boolean enable) {
		_loops.add(aLoop);
		_enabs.add(enable);
	}
	/**
	 * Add ILoopable to scheduler
	 * @param aLoop ILoopable to add
	 */
	public void add(ILoopable aLoop) {
		add(aLoop, true);
	}

	/**
	 * Remove all ILoopables from scheduler
	 */
	public void removeAll() {
		_loops.clear();
		_enabs.clear();
	}

	/**
	 * Start an ILoopable
	 * @param toStart ILoopable to start
	 */
	public void start(ILoopable toStart) {
		for (int i = 0; i < _loops.size(); ++i) {
			ILoopable lp = (ILoopable) _loops.get(i);

			if (lp == toStart) {
				_enabs.set(i, true);
				lp.onStart();
				return;
			}
		}

	}

	/**
	 * Stop an ILoopable
	 * @param toStop ILoopable to stop
	 */
	public void stop(ILoopable toStop) {
		for (int i = 0; i < (int) _loops.size(); ++i) {
			ILoopable lp = (ILoopable) _loops.get(i);

			if (lp == toStop) {
				_enabs.set(i, false);
				lp.onStop();
				return;
			}
		}
	}

	//--- Loopable ---/
	/**
	 * Start all ILoopables
	 */
	public void startAll() { // All Loops

		for (ILoopable loop : _loops) {
			loop.onStart();
		}
		for (int i = 0; i < _enabs.size(); ++i) {
			_enabs.set(i,  true);
		}
	}

	/**
	 * Stop all ILoopables
	 */
	public void stopAll() { // All Loops
		for (ILoopable loop : _loops) {
			loop.onStop();
		}
		for (int i = 0; i < _enabs.size(); ++i) {
			_enabs.set(i,  false);
		}
	}

	/**
	 * Process every ILoopable
	 * 
	 * Call this every loop
	 */
	public void process() {
		for (int i = 0; i < (int) _loops.size(); ++i) {
			ILoopable loop = (ILoopable) _loops.get(i);
			boolean en = (boolean) _enabs.get(i);
			if (en) {
				loop.onLoop();
			} else {
				/* Current ILoopable is turned off, don't call onLoop for it */
			}
		}
	}

	/**
	 * Start all ILoopables
	 */
	public void onStart() {
		startAll();
	}

	/**
	 * Process all ILoopables
	 */
	public void onLoop() {
		process();
	}

	/**
	 * Stop all ILoopables
	 */
	public void onStop() {
		stopAll();
	}

	/**
	 * @return false, this is never done
	 */
	public boolean isDone() {
		return false;
	}
}