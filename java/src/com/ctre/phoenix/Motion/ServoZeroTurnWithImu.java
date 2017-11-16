//package com.ctre.phoenix.Motion;
//
//import com.ctre.phoenix.Sensors.PigeonImu;
//import com.ctre.phoenix.Util;
//import com.ctre.phoenix.Drive.*;
//import com.ctre.phoenix.MotorControl.*;
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
//    float _targetHeading;
//	
//    boolean _isRunning = false;
//    boolean _isDone = false;
//    byte _isGood = 0;
//
//    /** Constructor */
//    public ServoZeroTurnWithImu(PigeonImu pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle, float targetHeading, ServoParameters Params)
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
//    public void Set(float targetHeading)
//    {
//		_targetHeading = targetHeading;
//    }
//
//    public float GetImuHeading()
//    {
//        return (float)_pidgey.GetYawPitchRoll()[0];
//    }
//
//    private void ZeroTurn(float targetHeading)
//    {
//    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
//    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Zero Turn IMU");
//        /* Grab the current heading */
//        float currentHeading = GetImuHeading();
//
//        /* Grab angular rate from the pigeon */
//        float currentAngularRate = (float)_pidgey.GetRawGyro()[2];
//
//        /* Grab Pigeon IMU status */
//        boolean angleIsGood = (_pidgey.GetState() == PigeonImu.PigeonState.Ready) ? true : false;
//
//        /* Runs ZeroTurn if Pigeon IMU is present and in good health, else do nothing */
//        if (angleIsGood == true)
//        {
//            /* Heading PID */
//            float headingError = targetHeading - currentHeading;
//            float X = servoParams.PID(headingError, currentAngularRate);
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
//    public void OnStart()
//    {
//        _isDone = false;
//        _isGood = 0;
//		servoParams.OnStart();
//    }
//
//    public void OnStop()
//    {
//        _IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
//        _isDone = true;
//    }
//
//    public boolean IsDone()
//    {
//        return _isDone;
//    }
//
//    public void OnLoop()
//    {
//		if(!_isDone)
//		{
//			ZeroTurn(_targetHeading);
//
//			if (servoParams.IsDone())
//			{
//				_IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
//				_isDone = true;
//			}
//        }
//    }
//}