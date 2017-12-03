package com.ctre.phoenix.Motion;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.Drive.*;

public class ServoGoStraightWithImu implements com.ctre.phoenix.ILoopable
{
	com.ctre.phoenix.Sensors.PigeonIMU _pidgey;
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
    public ServoGoStraightWithImu(com.ctre.phoenix.Sensors.PigeonIMU pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle, ServoParameters parameters, double Y, double targetHeading, double maxOutput)
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
    public ServoGoStraightWithImu(com.ctre.phoenix.Sensors.PigeonIMU pigeonImu, IDrivetrain IDrivetrain, Styles.Basic selectedStyle)
    {
        _pidgey = pigeonImu;
        _IDrivetrain = IDrivetrain;
        _selectedStyle = selectedStyle;
    }
	
	public void resetIAccum() { servoParams.resetIAccum(); }

    public void set(double Y, double targetHeading)
    {
		_Y = Y;
		_targetHeading = targetHeading;
    }

    /** Return the heading from the Pigeon*/
    public double getImuHeading()
    {
        return (double)_pidgey.getYawPitchRoll()[0];
    }

    private void goStraight(double Y, double targetHeading)
    {
    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Go Straight With IMU");
        /* Grab current heading */
        double currentHeading = getImuHeading();

        /* Grab angular rate from the pigeon */
        double currentAngularRate = (double)_pidgey.getRawGyro()[2];

        /* Grab Pigeon IMU status */
        boolean angleIsGood = (_pidgey.getState() == com.ctre.phoenix.Sensors.PigeonIMU.PigeonState.Ready) ? true : false;

        /* Runs goStraight if Pigeon IMU is present and in good health, else stop IDrivetrain */
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
                    _IDrivetrain.configNominalPercentOutputVoltage(+0.0f, -0.0f);
                    _IDrivetrain.configPeakPercentOutputVoltage(+servoParams.maxOut, -servoParams.maxOut);
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
    public void onStart()
    {
        _isDone = false;
		servoParams.onStart();
    }

    public void onStop()
    {
        _IDrivetrain.set(Styles.Basic.PercentOutput, 0, 0);
        _isRunning = false;
        _isDone = true;
    }

    public boolean isDone()
    {
        return _isDone;
    }

    public void onLoop()
    {
        goStraight(_Y, _targetHeading);
    }
}