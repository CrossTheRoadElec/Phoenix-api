package com.ctre.phoenix.Motion;

import com.ctre.phoenix.Sensors.PigeonImu;
import com.ctre.phoenix.Drive.*;

public class ServoGoStraightWithImuSmart implements com.ctre.phoenix.ILoopable
{
	PigeonImu _pidgey;
    ISmartDrivetrain _driveTrain;
    Styles.Smart _selectedStyle;
    private ServoParameters servoParams = new ServoParameters();
	
	public ServoParameters GetServoParams() { return servoParams; }
	public void SetServoParams(ServoParameters params)
	{
		servoParams = params;
	}

    float _Y;
    float _targetHeading;

    boolean _isRunning = false;
    boolean _isDone = false;


    /** Constructor that uses ServoGoStraightWithImuSmart as an ILoopable */
    public ServoGoStraightWithImuSmart(PigeonImu pigeonImu, ISmartDrivetrain driveTrain, Styles.Smart selectedStyle, ServoParameters straightParameters, float Y, float targetHeading)
    {
        _pidgey = pigeonImu;
        _driveTrain = driveTrain;
        _selectedStyle = selectedStyle;

        //=====================================//
        _Y = Y;
        _targetHeading = targetHeading;

		SetServoParams(straightParameters);

        //=====================================//
    }

    /** Constructor that uses ServoGoStraightWithImuSmart as an ILoopable */
    public ServoGoStraightWithImuSmart(PigeonImu pigeonImu, ISmartDrivetrain driveTrain, Styles.Smart selectedStyle)
    {
        _pidgey = pigeonImu;
        _driveTrain = driveTrain;
        _selectedStyle = selectedStyle;
    }

    public void Set(float Y, float targetHeading)
    {
		_Y = Y;
		_targetHeading = targetHeading;
    }

    /** Return the heading from the Pigeon*/
    public float GetImuHeading()
    {
        return (float)_pidgey.GetYawPitchRoll()[0];
    }
	
	public void resetIAccum() { servoParams.resetIAccum(); }

    private void GoStraight(float Y, float targetHeading)
    {
    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Go Straight With IMU Smart");
        /* Grab current heading */
        float currentHeading = GetImuHeading();

        /* Grab angular rate from the pigeon */
        float currentAngularRate = (float)_pidgey.GetRawGyro()[2];

        /* Grab Pigeon IMU status */
        boolean angleIsGood = (_pidgey.GetState() == PigeonImu.PigeonState.Ready) ? true : false;

        /* Runs GoStraight if Pigeon IMU is present and in good health, else stop drivetrain */
        if (angleIsGood == true)
        {
            /* Heading PID */
            float headingError = targetHeading - currentHeading;
            float X = servoParams.PID(headingError, currentAngularRate);
            X = -X;

            /* Select control mode based on selected style */
            switch (_selectedStyle)
            {
                case PercentOutput:
                    _driveTrain.set(Styles.Smart.PercentOutput, Y, X);
                    break;
                case Voltage:
                    _driveTrain.ConfigNominalPercentOutputVoltage(+0.0f, -0.0f);
                    _driveTrain.ConfigPeakPercentOutputVoltage(+servoParams.maxOut, -servoParams.maxOut);
                    _driveTrain.set(Styles.Smart.Voltage, Y, X);
                    break;
                case VelocityClosedLoop:
                    /* MotionMagic/ClosedLoop configured by caller in the drivetrain/motorcontroller level */
                    _driveTrain.set(Styles.Smart.VelocityClosedLoop, Y, X);
                    break;
            }

        }
        else if (angleIsGood == false)
        {
            _driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
        }
    }

    /** ILoopable */
    public void OnStart()
    {
        _isDone = false;
		servoParams.OnStart();
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
		GoStraight(_Y, _targetHeading);
    }
}