package com.ctre.phoenix.motion;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.drive.*;
import com.ctre.phoenix.sensors.PigeonIMU;

public class ServoGoStraightWithImuSmart implements com.ctre.phoenix.ILoopable
{
	PigeonIMU _pidgey;
    ISmartDrivetrain _driveTrain;
    Styles.Smart _selectedStyle;
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
    
    double [] _ypr = {0,0,0};
    double [] _dps = {0,0,0};


    /** Constructor that uses ServoGoStraightWithImuSmart as an ILoopable */
    public ServoGoStraightWithImuSmart(PigeonIMU pigeonImu, ISmartDrivetrain driveTrain, Styles.Smart selectedStyle, ServoParameters straightParameters, double Y, double targetHeading)
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
    public ServoGoStraightWithImuSmart(PigeonIMU pigeonImu, ISmartDrivetrain driveTrain, Styles.Smart selectedStyle)
    {
        _pidgey = pigeonImu;
        _driveTrain = driveTrain;
        _selectedStyle = selectedStyle;
    }

    public void set(double Y, double targetHeading)
    {
		_Y = Y;
		_targetHeading = targetHeading;
    }

    /** Return the heading from the Pigeon*/
    public double getImuHeading()
    {
        _pidgey.getYawPitchRoll(_ypr);
        return _ypr[0];
    }
	
	public void resetIAccum() { servoParams.resetIAccum(); }

    private void goStraight(double Y, double targetHeading)
    {
    	if(servoParams.P == 0 && servoParams.I == 0 && servoParams.D == 0)
    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Go Straight With IMU Smart");
        /* Grab current heading */
        double currentHeading = getImuHeading();

        /* Grab angular rate from the pigeon */
        _pidgey.getRawGyro(_dps);
        double currentAngularRate = _dps[2];

        /* Grab Pigeon IMU status */
        boolean angleIsGood = (_pidgey.getState() == PigeonIMU.PigeonState.Ready) ? true : false;

        /* Runs goStraight if Pigeon IMU is present and in good health, else stop drivetrain */
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
                    _driveTrain.set(Styles.Smart.PercentOutput, Y, X);
                    break;
                case Voltage:
                    _driveTrain.configNominalPercentOutputVoltage(+0.0f, -0.0f);
                    _driveTrain.configPeakPercentOutputVoltage(+servoParams.maxOut, -servoParams.maxOut);
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
    public void onStart()
    {
        _isDone = false;
		servoParams.onStart();
    }

    public void onStop()
    {
        _driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
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