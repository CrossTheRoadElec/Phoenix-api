//package com.ctre.phoenix.motion;
//
//import com.ctre.phoenix.ErrorCode;
//import com.ctre.phoenix.drive.*;
//
//public class ServoGoStraightWithImu implements com.ctre.phoenix.ILoopable
//{
//	com.ctre.phoenix.sensors.PigeonIMU _pidgey;
//    IDrivetrain _IDrivetrain;
//    Styles.Basic _selectedStyle;
//    private ServoParameters servoParams = new ServoParameters();
//	
//	public ServoParameters GetServoParams() { return servoParams; }
//	public void SetServoParams(ServoParameters params)
//	{
//		servoParams = params;
//	}
//
//    double _Y;
//    double _targetHeading;
//
//    boolean _isRunning = false;
//    boolean _isDone = false;
//    
//    double [] _ypr = {0,0,0};
//    double [] _dps = {0,0,0};
//
//    /** Go Straight using the IMU */
//    public ServoGoStraightWithImu(com.ctre.phoenix.sensors.PigeonIMU pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle, ServoParameters parameters, double Y, double targetHeading, double maxOutput)
//    {
//        _pidgey = pigeonImu;
//        _IDrivetrain = IDrivetrain;
//        _selectedStyle = selectedStyle;
//
//        //=====================================//
//        _Y = Y;
//        _targetHeading = targetHeading;
//
//		SetServoParams(parameters);
//
//        //=====================================//
//    }
//
//    /** Go Straight using the IMU */
//    public ServoGoStraightWithImu(com.ctre.phoenix.sensors.PigeonIMU pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle)
//    {
//        _pidgey = pigeonImu;
//        _IDrivetrain = IDrivetrain;
//        _selectedStyle = selectedStyle;
//    }
//	
//	public void resetIAccum() { servoParams.resetIAccum(); }
//
//    public void set(double Y, double targetHeading)
//    {
//		_Y = Y;
//		_targetHeading = targetHeading;
//    }
//    
//    /** Return the heading from the Pigeon*/
//    public double getImuHeading()
//    {
//        _pidgey.getYawPitchRoll(_ypr);
//        return _ypr[0];
//    }
//    
//    private void goStraight(double Y, double targetHeading)
//    {
//    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
//    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Go Straight With IMU");
//        /* Grab current heading */
//        double currentHeading = getImuHeading();
//
//        /* Grab angular rate from the pigeon */
//        _pidgey.getRawGyro(_dps);
//        double currentAngularRate = _dps[2];
//
//        /* Grab Pigeon IMU status */
//        boolean angleIsGood = (_pidgey.getState() == com.ctre.phoenix.sensors.PigeonIMU.PigeonState.Ready) ? true : false;
//
//        /* Runs goStraight if Pigeon IMU is present and in good health, else stop IDrivetrain */
//        if (angleIsGood == true)
//        {
//            /* Heading PID */
//            double headingError = targetHeading - currentHeading;
//            double X = servoParams.PID(headingError, currentAngularRate);
//            X = -X;
//
//            /* Select control mode based on selected style */
//            switch (_selectedStyle)
//            {
//                case PercentOutput:
//                    _IDrivetrain.set(Styles.Basic.PercentOutput, Y, X);
//                    break;
//                case Voltage:
//                    _IDrivetrain.configNominalPercentOutputVoltage(+0.0f, -0.0f);
//                    _IDrivetrain.configPeakPercentOutputVoltage(+servoParams.maxOut, -servoParams.maxOut);
//                    _IDrivetrain.set(Styles.Basic.Voltage, Y, X);
//                    break;
//            }
//        }
//        else if (angleIsGood == false)
//        {
//            _IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
//            _isRunning = false;
//        }
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
//        _IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
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
//        goStraight(_Y, _targetHeading);
//    }
//}