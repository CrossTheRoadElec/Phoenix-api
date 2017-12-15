//package com.ctre.phoenix.motion;
//
//import com.ctre.phoenix.ErrorCode;
//import com.ctre.phoenix.drive.*;
//
//public class ServoStraightDistance implements com.ctre.phoenix.ILoopable
//{
//	ISmartDrivetrain _driveTrain;
//	Styles.Smart _selectedStyle;
//	
//	private ServoParameters straightServoParams = new ServoParameters();
//	public ServoParameters GetStraightServoParams() { return straightServoParams; }
//	public void SetStraightServoParams(ServoParameters params)
//	{
//		straightServoParams = params;
//		StraightDrive.SetServoParams(params);
//	}
//	
//	private ServoParameters distanceServoParams = new ServoParameters();
//	public ServoParameters GetDistanceServoParams() { return distanceServoParams; }
//	public void SetDistanceServoParams(ServoParameters params)
//	{
//		distanceServoParams = params;
//	}
//	
//	ServoGoStraight StraightDrive;
//	com.ctre.phoenix.time.StopWatch _myStopWatch = new com.ctre.phoenix.time.StopWatch();
//	
//	double _targetDistance;
//    double _targetHeading;
//    double _previousDistance;
//    double _timeElapsed;
//
//    boolean _isRunning = false;
//    boolean _isDone = false;
//    byte _isGood = 0;
//    
//
//    /** Straight servo constuctor that takes a smart drive train */
//    public ServoStraightDistance(ISmartDrivetrain driveTrain, Styles.Smart selectedStyle, ServoParameters turnParams, ServoParameters distanceParams, double targetHeading, double targetDistance)
//    {
//        _driveTrain = driveTrain;
//        _selectedStyle = selectedStyle;
//
//        /* Construct a ServoGoStraight based on sytle selected */
//        if (_selectedStyle == Styles.Smart.Voltage)
//            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.Voltage);
//        else if (_selectedStyle == Styles.Smart.PercentOutput)
//            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.PercentOutput);
//        else if(_selectedStyle == Styles.Smart.VelocityClosedLoop)
//            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.VelocityClosedLoop);
//
//        //================================================//
//        _targetHeading = targetHeading;
//        _targetDistance = targetDistance;
//
//		SetDistanceServoParams(distanceParams);
//		SetStraightServoParams(turnParams);
//		StraightDrive.SetServoParams(turnParams);
//
//        //================================================//
//    }
//
//    /** Straight servo constuctor that takes a smart drive train */
//    public ServoStraightDistance(ISmartDrivetrain driveTrain, Styles.Smart selectedStyle)
//    {
//        _driveTrain = driveTrain;
//        _selectedStyle = selectedStyle;
//
//        /* Construct a ServoGoStraight based on sytle selected */
//        if (_selectedStyle == Styles.Smart.Voltage)
//            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.Voltage);
//        else if (_selectedStyle == Styles.Smart.PercentOutput)
//            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.PercentOutput);
//        else if (_selectedStyle == Styles.Smart.VelocityClosedLoop)
//            StraightDrive = new ServoGoStraight(_driveTrain, Styles.Smart.VelocityClosedLoop);
//    }
//
//    public void set(double targetHeading, double targetDistance)
//    {
//		_targetHeading = targetHeading;
//		_targetDistance = targetDistance;
//    }
//
//    /** Return the heading from the encoders */
//    public double getEncoderHeading()
//    {
//        return _driveTrain.getEncoderHeading();
//    }
//
//    /** Return the encoder distance of the drive train */
//    public double getEncoderDistance()
//    {
//        return _driveTrain.getDistance();
//    }
//
//    private void straightDistance(double targetHeading, double targetDistance)
//    {
//    	if(straightServoParams.P == 0 && straightServoParams.I == 0 && straightServoParams.D == 0)
//    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Straight Distance");
//    	if(distanceServoParams.P == 0 && distanceServoParams.I == 0 && distanceServoParams.D == 0)
//    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Straight Distance");
//        /* Grab current heading and distance*/
//        double currentDistance = getEncoderDistance();
//
//        /* Find the error between the target and current value */
//        double distanceRate = _driveTrain.getVelocity();
//
//        /* Distance PID */
//        double distanceError = targetDistance - currentDistance;
//        double Y = distanceServoParams.PID(distanceError, distanceRate);
//
//        /* StraightDrive moded selected when created within constructor */
//        if (_selectedStyle == Styles.Smart.Voltage)
//        {
//            _driveTrain.configNominalPercentOutputVoltage(+0, -0);
//            _driveTrain.configPeakPercentOutputVoltage(+distanceServoParams.maxOut, -distanceServoParams.maxOut);
//        }
//        StraightDrive.set(Y, targetHeading);
//
//        _previousDistance = currentDistance;
//    }
//
//    /** ILoopable */
//    public void onStart()
//    {
//        _isDone = false;
//        _isGood = 0;
//		StraightDrive.onStart();
//		distanceServoParams.onStart();
//		straightServoParams.onStart();
//    }
//
//    public void onStop()
//    {
//        _driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
//        _isRunning = false;
//        _isDone = true;
//    }
//
//    public boolean isDone()
//    {
//        return _isDone;
//    }
//
//    public void onLoop()
//    {
//		if(!_isDone)
//		{
//			straightDistance(_targetHeading, _targetDistance);
//			StraightDrive.onLoop();
//
//			if (distanceServoParams.isDone() && straightServoParams.isDone())
//			{
//				_driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
//				_isDone = true;
//			}
//		}
//    }
//}