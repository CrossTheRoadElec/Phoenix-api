package com.ctre.phoenix.mechanical;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.IMotorController;

public class Linkage {
	IMotorController _motor = null;
	IMotorController[] _follower = { null, null, null };
	int _followerCount = 0;

	public Linkage(IMotorController mc1) {
		_motor = mc1;
		setup();
	}

	public Linkage(IMotorController mc1, IMotorController mc2) {
		_motor = mc1;
		_follower[_followerCount++] = mc2;
		setup();
	}

	public Linkage(IMotorController mc1, IMotorController mc2, IMotorController mc3) {
		_motor = mc1;
		_follower[_followerCount++] = mc2;
		_follower[_followerCount++] = mc3;
		setup();
	}

	public Linkage(IMotorController mc1, IMotorController mc2, IMotorController mc3, IMotorController mc4) {
		_motor = mc1;
		_follower[_followerCount++] = mc2;
		_follower[_followerCount++] = mc3;
		_follower[_followerCount++] = mc4;
		setup();
	}

	private void setup() {
		for (int i = 0; i < _followerCount; i++) {
			_follower[i].follow(_motor);
		}
	}

	public void set(ControlMode mode, double value) {
		_motor.set(mode, value);
		for (int i = 0; i < _followerCount; i++) {
			_follower[i].valueUpdated();
		}
	}
	public void setInverted(boolean... inverts) {
		int i = 0;

		/* leave function if there are not enough inverts */
		if (i >= inverts.length)
			return;

		/* update master and iterate */
		_motor.setInverted(inverts[i++]);

		for (IMotorController follower : _follower) {

			/* leave function if there are not enough inverts */
			if (i >= inverts.length)
				return;

			/* update follower and iterate */
			follower.setInverted(inverts[i++]);
		}
	}

	public ErrorCode configOpenloopRamp(double secondsFromNeutralToFull, int timeoutMs) {
		return _motor.configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
	}

	public ErrorCode configNominalOutputForward(double percentOutput, int timeoutMs) {
		return _motor.configNominalOutputForward(percentOutput, timeoutMs);
	}

	public ErrorCode configNominalOutputReverse(double percentOutput, int timeoutMs) {
		return _motor.configNominalOutputReverse(percentOutput, timeoutMs);
	}

	public ErrorCode configPeakOutputForward(double percentOutput, int timeoutMs) {
		return _motor.configPeakOutputForward(percentOutput, timeoutMs);
	}

	public ErrorCode configPeakOutputReverse(double percentOutput, int timeoutMs) {
		return _motor.configPeakOutputReverse(percentOutput, timeoutMs);
	}

	public void enableVoltageCompensation(boolean enable) {
		_motor.enableVoltageCompensation(enable);
	}

	public IMotorController getMaster() {
		return _motor;
	}
}