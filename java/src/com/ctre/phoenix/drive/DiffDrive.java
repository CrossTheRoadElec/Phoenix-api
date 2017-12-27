package com.ctre.phoenix.drive;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.mechanical.Gearbox;
import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.IMotorController;

public class DiffDrive
{
	Gearbox _left;
	Gearbox _rght;
	
	public DiffDrive(Gearbox left, Gearbox right)
	{
		_left = left;
		_rght = right;
	}
	
	public DiffDrive(IMotorController m1, IMotorController m2)
    {
        /* Create 2 single motor gearboxes */
        Gearbox temp1 = new Gearbox(m1);
        Gearbox temp2 = new Gearbox(m2);
        
        _left = temp1;
        _rght = temp2;
    } 
	
	/** Inherited from IDrivetrain */
    public void set(DriveMode driveMode, double forward, double turn)
    {
        double l, r;
        l = forward + turn;
        r = forward - turn;

        switch (driveMode) {
	        case Voltage:
	            _left.enableVoltageCompensation(true);
	            _rght.enableVoltageCompensation(true);
	            _left.set(ControlMode.PercentOutput, l);
	            _rght.set(ControlMode.PercentOutput, r);
	        	break;
	        case PercentOutput:
	            _left.enableVoltageCompensation(false);
	            _rght.enableVoltageCompensation(false);
	            _left.set(ControlMode.PercentOutput, l);
	            _rght.set(ControlMode.PercentOutput, r);
	        	break;
        }
    }
	public ErrorCode configOpenloopRamp(double secondsFromNeutralToFull, int timeoutMs) {
		ErrorCode e1 = _left.configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
		ErrorCode e2 = _rght.configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
		return ErrorCode.worstOne(e1, e2);
	}  
	public ErrorCode configPeakOutputForward(double percentOutput, int timeoutMs) {
		ErrorCode e1 = _left.configPeakOutputForward(percentOutput, timeoutMs);
		ErrorCode e2 = _rght.configPeakOutputForward(percentOutput, timeoutMs);
		return ErrorCode.worstOne(e1, e2);
	}
	public ErrorCode configPeakOutputReverse(double percentOutput, int timeoutMs) {
		ErrorCode e1 = _left.configPeakOutputReverse(percentOutput, timeoutMs);
		ErrorCode e2 = _rght.configPeakOutputReverse(percentOutput, timeoutMs);
		return ErrorCode.worstOne(e1, e2);
	}
}