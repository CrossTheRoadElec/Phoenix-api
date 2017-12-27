package com.ctre.phoenix.drive;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.mechanical.Gearbox;
import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.IMotorController;

public class MecanumDrive {
	Gearbox _1;
	Gearbox _2;
	Gearbox _3;
	Gearbox _4;

	public MecanumDrive(IMotorController m1, IMotorController m2, IMotorController m3, IMotorController m4) {
		Gearbox temp1 = new Gearbox(m1);
		Gearbox temp2 = new Gearbox(m2);
		Gearbox temp3 = new Gearbox(m3);
		Gearbox temp4 = new Gearbox(m4);

		_1 = temp1;
		_2 = temp2;
		_3 = temp3;
		_4 = temp4;
	}

	public void set(DriveMode driveMode, double forward, double turn) {
		Drive(driveMode, forward, turn, 0);
	}

	public void set(DriveMode driveMode, double forward, double turn, double strafe) {
		Drive(driveMode, forward, turn, strafe);
	}

	public ErrorCode configOpenloopRamp(double secondsFromNeutralToFull, int timeoutMs) {
		ErrorCode e1 = _1.configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
		ErrorCode e2 = _2.configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
		ErrorCode e3 = _3.configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
		ErrorCode e4 = _4.configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
		return ErrorCode.worstOne(e1, e2, e3, e4);
	}

	public ErrorCode configPeakOutputForward(double percentOutput, int timeoutMs) {
		ErrorCode e1 = _1.configPeakOutputForward(percentOutput, timeoutMs);
		ErrorCode e2 = _2.configPeakOutputForward(percentOutput, timeoutMs);
		ErrorCode e3 = _3.configPeakOutputForward(percentOutput, timeoutMs);
		ErrorCode e4 = _4.configPeakOutputForward(percentOutput, timeoutMs);
		return ErrorCode.worstOne(e1, e2, e3, e4);
	}

	public ErrorCode configPeakOutputReverse(double percentOutput, int timeoutMs) {
		ErrorCode e1 = _1.configPeakOutputReverse(percentOutput, timeoutMs);
		ErrorCode e2 = _2.configPeakOutputReverse(percentOutput, timeoutMs);
		ErrorCode e3 = _3.configPeakOutputReverse(percentOutput, timeoutMs);
		ErrorCode e4 = _4.configPeakOutputReverse(percentOutput, timeoutMs);
		return ErrorCode.worstOne(e1, e2, e3, e4);
	}

	private void Drive(DriveMode driveMode, double forward, double turn, double strafe)
    {
        double leftFrnt_throt = (forward + strafe + turn); // left front moves positive for forward, strafe-right, turn-right
        double leftRear_throt = (forward - strafe + turn); // left rear moves positive for forward, strafe-left, turn-right
        double rghtFrnt_throt = (forward - strafe - turn); // right front moves positive for forward, strafe-left, turn-left
        double rghtRear_throt = (forward + strafe - turn); // right rear moves positive for forward, strafe-right, turn-left

		/* Set control mode */
		switch (driveMode) {
			case PercentOutput:
				_1.enableVoltageCompensation(false);
				_2.enableVoltageCompensation(false);
				_3.enableVoltageCompensation(false);
				_4.enableVoltageCompensation(false);
				break;
			case Voltage:
				_1.enableVoltageCompensation(true);
				_2.enableVoltageCompensation(true);
				_3.enableVoltageCompensation(true);
				_4.enableVoltageCompensation(true);
				break;
		}
		_1.set(ControlMode.PercentOutput, leftFrnt_throt);
		_2.set(ControlMode.PercentOutput, leftRear_throt);
		_3.set(ControlMode.PercentOutput, rghtFrnt_throt);
		_4.set(ControlMode.PercentOutput, rghtRear_throt);
	}
}