package com.ctre.phoenix.Motion;

import com.ctre.phoenix.Drive.*;

public class ServoStraightDistance implements com.ctre.phoenix.ILoopable
{
	ISmartDrivetrain _driveTrain;
	Styles.Smart _selectedStyle;
	
	private ServoParameters straightServoParams = new ServoParameters();
	public ServoParameters GetStraightServoParams() { return straightServoParams; }
	public void SetStraightServoParams(ServoParameters params)
	{
		straightServoParams = params;
		StraightDrive.SetServoParams(params);
	}
	
	private ServoParameters distanceServoParams = new ServoParameters();
	public ServoParameters GetDistanceServoParams() { return distanceServoParams; }
	public void SetDistanceServoParams(ServoParameters params)
	{
		distanceServoParams = params;
	}
	
	ServoGoStraight StraightDrive;
	com.ctre.phoenix.Time.StopWatch _myStopWatch = new com.ctre.phoenix.Time.StopWatch();
	
	double _targetDistance;
    double _targetHeading;
    double _previousDistance;
    double _timeElapsed;

    boolean _isRunning = false;
    boolean _isDone = false;
    byte _isGood = 0;
    

    /** Straight servo constuctor that takes a smart drive train */
    public ServoStraightDistance(ISmartDrivetrain driveTrain, Styles.Smart selectedStyle, ServoParameters turnParams, ServoParameters distanceParams, double targetHeading, double targetDistance)
    {
        _driveTrain = driveTrain;
        _selectedStyle = selectedStyle;

        /* Construct a ServoGoStraight based on sytle selected */
        if (_selectedStyle == Styles.Smart.Voltage)
            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.Voltage);
        else if (_selectedStyle == Styles.Smart.PercentOutput)
            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.PercentOutput);
        else if(_selectedStyle == Styles.Smart.VelocityClosedLoop)
            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.VelocityClosedLoop);

        //================================================//
        _targetHeading = targetHeading;
        _targetDistance = targetDistance;

		SetDistanceServoParams(distanceParams);
		SetStraightServoParams(turnParams);
		StraightDrive.SetServoParams(turnParams);

        //================================================//
    }

    /** Straight servo constuctor that takes a smart drive train */
    public ServoStraightDistance(ISmartDrivetrain driveTrain, Styles.Smart selectedStyle)
    {
        _driveTrain = driveTrain;
        _selectedStyle = selectedStyle;

        /* Construct a ServoGoStraight based on sytle selected */
        if (_selectedStyle == Styles.Smart.Voltage)
            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.Voltage);
        else if (_selectedStyle == Styles.Smart.PercentOutput)
            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.PercentOutput);
        else if (_selectedStyle == Styles.Smart.VelocityClosedLoop)
            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.VelocityClosedLoop);
    }

    public void Set(double targetHeading, double targetDistance)
    {
		_targetHeading = targetHeading;
		_targetDistance = targetDistance;
    }

    /** Return the heading from the encoders */
    public double GetEncoderHeading()
    {
        return _driveTrain.GetEncoderHeading();
    }

    /** Return the encoder distance of the drive train */
    public double GetEncoderDistance()
    {
        return _driveTrain.GetDistance();
    }

    private void StraightDistance(double targetHeading, double targetDistance)
    {
    	if(straightServoParams.P == 0 && straightServoParams.I == 0 && straightServoParams.D == 0)
    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Straight Distance");
    	if(distanceServoParams.P == 0 && distanceServoParams.I == 0 && distanceServoParams.D == 0)
    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Straight Distance");
        /* Grab current heading and distance*/
        double currentDistance = GetEncoderDistance();

        /* Find the error between the target and current value */
        double distanceRate = _driveTrain.GetVelocity();

        /* Distance PID */
        double distanceError = targetDistance - currentDistance;
        double Y = distanceServoParams.PID(distanceError, distanceRate);

        /* StraightDrive moded selected when created within constructor */
        if (_selectedStyle == Styles.Smart.Voltage)
        {
            _driveTrain.ConfigNominalPercentOutputVoltage(+0, -0);
            _driveTrain.ConfigPeakPercentOutputVoltage(+distanceServoParams.maxOut, -distanceServoParams.maxOut);
        }
        StraightDrive.Set(Y, targetHeading);

        _previousDistance = currentDistance;
    }

    /** ILoopable */
    public void OnStart()
    {
        _isDone = false;
        _isGood = 0;
		StraightDrive.OnStart();
		distanceServoParams.OnStart();
		straightServoParams.OnStart();
    }

    public void OnStop()
    {
        _driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
        _isRunning = false;
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
			StraightDistance(_targetHeading, _targetDistance);
			StraightDrive.OnLoop();

			if (distanceServoParams.IsDone() && straightServoParams.IsDone())
			{
				_driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
				_isDone = true;
			}
		}
    }
}