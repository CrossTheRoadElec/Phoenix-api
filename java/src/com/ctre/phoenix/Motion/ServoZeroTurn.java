package com.ctre.phoenix.Motion;

import com.ctre.phoenix.Util;
import com.ctre.phoenix.Drive.*;
import com.ctre.phoenix.MotorControl.*;
import com.ctre.phoenix.Mechanical.*;
import com.ctre.phoenix.Time.*;

public class ServoZeroTurn implements com.ctre.phoenix.ILoopable
{
	ISmartDrivetrain _driveTrain;
    Styles.Smart _selectedStyle;
	
    private ServoParameters servoParams = new ServoParameters();
	public ServoParameters GetServoParams() { return servoParams; }
	public void SetServoParams(ServoParameters params)
	{
		servoParams = params;
	}
	
    StopWatch _myStopwatch = new StopWatch();

    float _targetHeading;
    float _previousHeading;
    float _timeElapsed;

    boolean _isRunning = false;
    boolean _isDone = false;
    byte _isGood = 0;

    /** Constructor */
    public ServoZeroTurn(ISmartDrivetrain driveTrain, Styles.Smart smartStyle, float targetHeading, ServoParameters Params)
    {
        _driveTrain = driveTrain;
        _selectedStyle = smartStyle;

        _targetHeading = targetHeading;

        SetServoParams(Params);
    }

    public ServoZeroTurn(ISmartDrivetrain driveTrain, Styles.Smart style)
    {
        _driveTrain = driveTrain;
        _selectedStyle = style;
    }

    public void Set(float targetHeading)
    {
		_targetHeading = targetHeading;
    }

    public float GetEncoderHeading()
    {
        return _driveTrain.GetEncoderHeading();
    }

    private void ZeroTurn(float targetHeading)
    {
    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Zero Turn");
        /* Grab the current heading*/
        float currentHeading = GetEncoderHeading();

        /* Find the difference between last heading and current heading */
        _timeElapsed = _myStopwatch.getDuration();
        float headingRate = currentHeading - _previousHeading;
        _myStopwatch.start();

        /* Heading PID */
        float headingError = targetHeading - currentHeading;
        float X = servoParams.PID(headingError, headingRate);
        X = -X;


        /** Set the output of the drivetrain */
        /** Set the output of the drivetrain */
        switch (_selectedStyle)
        {
            case PercentOutput:
                _driveTrain.set(Styles.Smart.PercentOutput, 0, X);
                break;
            case Voltage:
                _driveTrain.set(Styles.Smart.Voltage, 0, X);
                break;
            case VelocityClosedLoop:
                _driveTrain.set(Styles.Smart.VelocityClosedLoop, 0, X);
                break;
        }

        /** Grab the heading to compare next time */
        _previousHeading = currentHeading;
    }

    /** ILoopable */
    public void OnStart()
    {
        _isDone = false;
        _isGood = 0;
		servoParams.OnStart();
    }

    public void OnStop()
    {
        _driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
        _isDone = true;
    }

    public boolean IsDone()
    {
        return _isDone;
    }

    public void OnLoop()
    {
		if(!_isDone)
		{
			ZeroTurn(_targetHeading);

			if (servoParams.IsDone())
			{
				_driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
				_isDone = true;
			}
        }
    }
}