//package com.ctre.phoenix.motion;
//
//import com.ctre.phoenix.ErrorCode;
//import com.ctre.phoenix.drive.*;
//
//public class ServoGoStraight implements com.ctre.phoenix.ILoopable
//{
//	ISmartDrivetrain _driveTrain;
//	Styles.Smart _selectedStyle;
//	com.ctre.phoenix.time.StopWatch _myStopWatch = new com.ctre.phoenix.time.StopWatch();
//	
//	private ServoParameters servoParams = new com.ctre.phoenix.motion.ServoParameters(); 
//	
//	public ServoParameters GetServoParams() { return servoParams; }
//	public void SetServoParams(ServoParameters params)
//	{
//		servoParams = params;
//	}
//	
//	double _y;
//	double _heading;
//	double _previousHeading;
//	double _timeElapsed;
//	
//	boolean _isRunning = false;
//	boolean _isDone = false;
//	
//	public ServoGoStraight(ISmartDrivetrain driveTrain, Styles.Smart style, ServoParameters params, double y, double heading)
//	{
//		_driveTrain = driveTrain;
//		_selectedStyle = style;
//		_y = y;
//		_heading = heading;
//
//		SetServoParams(params);
//	}
//	
//    public ServoGoStraight(ISmartDrivetrain driveTrain, Styles.Smart style)
//    {
//        _driveTrain = driveTrain;
//        _selectedStyle = style;
//    }
//    
//    public void set(double Y , double heading)
//    {
//        _y = Y;
//		_heading = heading;
//    }
//    
//    public double getEncoderHeading()
//    {
//        return _driveTrain.getEncoderHeading();
//    }
//	
//	public void resetIAccum() { servoParams.resetIAccum(); }
//
//    private void goStraight(double Y, double heading)
//    {
//    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
//    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Go Straight");
//    	
//        /* Grab encoder heading */
//        double currentHeading = getEncoderHeading();
//
//        /* Find angular rate from the encoders */
//        _timeElapsed = _myStopWatch.getDuration();
//        double correctionRate = ((currentHeading - _previousHeading) / _timeElapsed);
//        _myStopWatch.start();
//
//        /* Heading PID */
//        double headingError = heading - currentHeading;
//        double X = servoParams.PID(headingError, correctionRate);
//        X = -X;
//
//        /* Select control style based on selected style */
//        switch (_selectedStyle)
//        {
//            case PercentOutput:
//                _driveTrain.set(com.ctre.phoenix.drive.Styles.Smart.PercentOutput, Y, X);
//                break;
//            case Voltage:
//                _driveTrain.configNominalPercentOutputVoltage(+0.0f, -0.0f);
//                _driveTrain.configPeakPercentOutputVoltage(+servoParams.maxOut, -servoParams.maxOut);
//                _driveTrain.set(com.ctre.phoenix.drive.Styles.Smart.Voltage, Y, X);
//                break;
//            case VelocityClosedLoop:
//                _driveTrain.set(com.ctre.phoenix.drive.Styles.Smart.VelocityClosedLoop, Y, X);
//                break;
//        }
//        _previousHeading = currentHeading;
//
//    }
//
//    /** ILoopable */
//    public void onStart()
//    {
//        _isDone = false;
//		servoParams.onStart();
//    }
//
//    public void onStop()
//    {
//        _driveTrain.set(Styles.Smart.PercentOutput, 0, 0);
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
//        goStraight(_y, _heading);
//    }
//}