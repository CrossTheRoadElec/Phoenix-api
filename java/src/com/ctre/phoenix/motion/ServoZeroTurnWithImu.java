package com.ctre.phoenix.motion;
//package com.ctre.phoenix.Motion;
//
//import com.ctre.phoenix.Sensors.PigeonImu;
//import com.ctre.phoenix.Util;
//import com.ctre.phoenix.Drive.*;
//import com.ctre.phoenix.motorcontrol.*;
//import com.ctre.phoenix.Mechanical.*;
//import com.ctre.phoenix.Time.*;
//
//public class ServoZeroTurnWithImu implements com.ctre.phoenix.ILoopable
//{
//	PigeonImu _pidgey;
//    IDrivetrain _IDrivetrain;
//    Styles.Basic _selectedStyle;
//	
//    private ServoParameters servoParams = new ServoParameters();
//	public ServoParameters GetServoParams() { return servoParams; }
//	public void SetServoParams(ServoParameters params)
//	{
//		servoParams = params;
//	}
//
//    double _targetHeading;
//	
//    boolean _isRunning = false;
//    boolean _isDone = false;
//    byte _isGood = 0;
//
//    /** Constructor */
//    public ServoZeroTurnWithImu(PigeonImu pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle, double targetHeading, ServoParameters Params)
//    {
//        _pidgey = pigeonImu;
//        _IDrivetrain = IDrivetrain;
//        _selectedStyle = selectedStyle;
//
//        _targetHeading = targetHeading;
//
//        SetServoParams(Params);
//    }
//
//    public ServoZeroTurnWithImu(PigeonImu pigeonImu, IDrivetrain IDrivetrain, Styles.Basic style)
//    {
//        _pidgey = pigeonImu;
//        _IDrivetrain = IDrivetrain;
//        _selectedStyle = style;
//    }
//
//    public void set(double targetHeading)
//    {
//		_targetHeading = targetHeading;
//    }
//
//    public double getImuHeading()
//    {
//        return (double)_pidgey.getYawPitchRoll()[0];
//    }
//
//    private void ZeroTurn(double targetHeading)
//    {
//    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
//    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Zero Turn IMU");
//        /* Grab the current heading */
//        double currentHeading = GetImuHeading();
//
//        /* Grab angular rate from the pigeon */
//        double currentAngularRate = (double)_pidgey.GetRawGyro()[2];
//
//        /* Grab Pigeon IMU status */
//        boolean angleIsGood = (_pidgey.GetState() == PigeonImu.PigeonState.Ready) ? true : false;
//
//        /* Runs ZeroTurn if Pigeon IMU is present and in good health, else do nothing */
//        if (angleIsGood == true)
//        {
//            /* Heading PID */
//            double headingError = targetHeading - currentHeading;
//            double X = servoParams.PID(headingError, currentAngularRate);
//            X = -X;
//
//
//            /** Set the output of the IDrivetrain */
//            switch (_selectedStyle)
//            {
//                case PercentOutput:
//                    _IDrivetrain.set(Styles.Basic.PercentOutput, 0, X);
//                    break;
//                case Voltage:
//                    _IDrivetrain.set(Styles.Basic.Voltage, 0, X);
//                    break;
//            }
//        }
//    }
//
//    /* ILoopable */
//    public void onStart()
//    {
//        _isDone = false;
//        _isGood = 0;
//		servoParams.onStart();
//    }
//
//    public void onStop()
//    {
//        _IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
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
//			ZeroTurn(_targetHeading);
//
//			if (servoParams.isDone())
//			{
//				_IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
//				_isDone = true;
//			}
//        }
//    }
//}