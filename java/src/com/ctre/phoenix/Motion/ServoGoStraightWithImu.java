package com.ctre.phoenix.Motion;

import com.ctre.phoenix.Util;
import com.ctre.phoenix.Drive.*;

public class ServoGoStraightWithImu implements com.ctre.phoenix.ILoopable
{
	com.ctre.phoenix.Sensors.PigeonImu _pidgey;
    IDrivetrain _IDrivetrain;
    Styles.Basic _selectedStyle;
    private ServoParameters servoParams = new ServoParameters();
	
	public ServoParameters GetServoParams() { return servoParams; }
	public void SetServoParams(ServoParameters params)
	{
		servoParams = params;
	}

    double _Y;
    double _targetHeading;

    boolean _isRunning = false;
    boolean _isDone = false;


    /** Go Straight using the IMU */
    public ServoGoStraightWithImu(com.ctre.phoenix.Sensors.PigeonImu pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle, ServoParameters parameters, double Y, double targetHeading, double maxOutput)
    {
        _pidgey = pigeonImu;
        _IDrivetrain = IDrivetrain;
        _selectedStyle = selectedStyle;

        //=====================================//
        _Y = Y;
        _targetHeading = targetHeading;

		SetServoParams(parameters);

        //=====================================//
    }

    /** Go Straight using the IMU */
    public ServoGoStraightWithImu(com.ctre.phoenix.Sensors.PigeonImu pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle)
    {
        _pidgey = pigeonImu;
        _IDrivetrain = IDrivetrain;
        _selectedStyle = selectedStyle;
    }
	
	public void resetIAccum() { servoParams.resetIAccum(); }

    public void Set(double Y, double targetHeading)
    {
		_Y = Y;
		_targetHeading = targetHeading;
    }

    /** Return the heading from the Pigeon*/
    public double GetImuHeading()
    {
        return (double)_pidgey.GetYawPitchRoll()[0];
    }

    private void GoStraight(double Y, double targetHeading)
    {
    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Go Straight With IMU");
        /* Grab current heading */
        double currentHeading = GetImuHeading();

        /* Grab angular rate from the pigeon */
        double currentAngularRate = (double)_pidgey.GetRawGyro()[2];

        /* Grab Pigeon IMU status */
        boolean angleIsGood = (_pidgey.GetState() == com.ctre.phoenix.Sensors.PigeonImu.PigeonState.Ready) ? true : false;

        /* Runs GoStraight if Pigeon IMU is present and in good health, else stop IDrivetrain */
        if (angleIsGood == true)
        {
            /* Heading PID */
            double headingError = targetHeading - currentHeading;
            double X = servoParams.PID(headingError, currentAngularRate);
            X = -X;

            /* Select control mode based on selected style */
            switch (_selectedStyle)
            {
                case PercentOutput:
                    _IDrivetrain.set(Styles.Basic.PercentOutput, Y, X);
                    break;
                case Voltage:
                    _IDrivetrain.ConfigNominalPercentOutputVoltage(+0.0f, -0.0f);
                    _IDrivetrain.ConfigPeakPercentOutputVoltage(+servoParams.maxOut, -servoParams.maxOut);
                    _IDrivetrain.set(Styles.Basic.Voltage, Y, X);
                    break;
            }
        }
        else if (angleIsGood == false)
        {
            _IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
            _isRunning = false;
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
        _IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
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