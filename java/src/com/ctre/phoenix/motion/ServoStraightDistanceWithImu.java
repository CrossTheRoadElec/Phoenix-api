package com.ctre.phoenix.motion;

import com.ctre.phoenix.sensors.PigeonIMU;
import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.drive.*;
import com.ctre.phoenix.time.StopWatch;

public class ServoStraightDistanceWithImu implements com.ctre.phoenix.ILoopable
{
	 PigeonIMU _pidgey;
     ISmartDrivetrain _driveTrain;
     Styles.Smart _selectedStyle;
	 
     private ServoParameters straightServoParameters = new ServoParameters();
	 public ServoParameters GetStraightServoParams() { return straightServoParameters; }
	 public void SetStraightServoParams(ServoParameters params) 
	 {
		straightServoParameters = params;
		StraightDrive.SetServoParams(params);
	 }
	 
     private ServoParameters distanceServoParameters = new ServoParameters();
	 public ServoParameters GetDistanceServoParams() { return distanceServoParameters; }
	 public void SetDistanceServoParams(ServoParameters params) 
	 {
		distanceServoParameters = params;
	 }
	 
	 
     ServoGoStraightWithImuSmart StraightDrive;
     StopWatch _myStopWatch = new StopWatch();

     double _targetDistance;
     double _targetHeading;
     double _previousDistance;
     double _timeElapsed;

     boolean _isRunning = false;
     boolean _isDone = false;
     byte _isGood = 0;

     double [] _ypr = {0,0,0};

     /** Constructor that uses ServoStraightDistanceWithImu as an ILoopable */
     public ServoStraightDistanceWithImu(PigeonIMU pigeonImu, ISmartDrivetrain drivetrain, Styles.Smart selectedStyle, ServoParameters straightParameters, ServoParameters distanceParameters, double targetHeading, double targetDistance)
     {
         _pidgey = pigeonImu;
         _driveTrain = drivetrain;
         _selectedStyle = selectedStyle;

         /* Construct a ServoGoStraightWithImu based on style */
         if (_selectedStyle == Styles.Smart.Voltage)
             StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, Styles.Smart.Voltage);
         else if (_selectedStyle == Styles.Smart.PercentOutput)
             StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, Styles.Smart.PercentOutput);
         else if (_selectedStyle == Styles.Smart.VelocityClosedLoop)
             StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, Styles.Smart.VelocityClosedLoop);

         //============================================================//
         _targetHeading = targetHeading;
         _targetDistance = targetDistance;

         SetDistanceServoParams(distanceParameters);
		 SetStraightServoParams(straightParameters);
		 StraightDrive.SetServoParams(straightParameters);
         //============================================================//
     }

     /** Constructor that uses ServoStraightDistanceWithImu as an ILoopable */
     public ServoStraightDistanceWithImu(PigeonIMU pigeonImu, ISmartDrivetrain drivetrain, Styles.Smart selectedStyle)
     {
         _pidgey = pigeonImu;
         _driveTrain = drivetrain;
         _selectedStyle = selectedStyle;

         /* Construct a ServoGoStraightWithImu based on style */
         if (_selectedStyle == Styles.Smart.Voltage)
             StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, Styles.Smart.Voltage);
         else if (_selectedStyle == Styles.Smart.PercentOutput)
             StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, Styles.Smart.PercentOutput);
         else if (_selectedStyle == Styles.Smart.VelocityClosedLoop)
             StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, Styles.Smart.VelocityClosedLoop);
     }


     /** Sets target heading/distance along with tolerances and updates PID gains */
     public void set(double targetHeading, double targetDistance)
     {
		 _targetHeading = targetHeading;
		 _targetDistance = targetDistance;
     }

     /** Return the heading from the Pigeon */
     public double getImuHeading()
     {
         _pidgey.getYawPitchRoll(_ypr);
         return _ypr[0];
     }

     /** Return the encoder distance from the DriveTrain */
     public double getEncoderDistance()
     {
         return _driveTrain.getDistance();
     }

     /** ServoStraightDistanceWithImu processing */
     private void straightDistance(double targetHeading, double targetDistance)
     {
    	if(straightServoParameters.P == 0 && straightServoParameters.I == 0 && straightServoParameters.D == 0)
    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Straight Distance With Imu");
    	if(distanceServoParameters.P == 0 && distanceServoParameters.I == 0 && distanceServoParameters.D == 0)
    		com.ctre.phoenix.Logger.log(ErrorCode.GainsAreNotSet, "Servo Straight Distance With Imu");
         /* Grab current distance */
         double currentDistance = getEncoderDistance();

         /* Grab the positionRate and elapsed time, must be done anytime we use D gain */
         double positionRate = _driveTrain.getVelocity();

         /* Distance PID */
         double distanceError = targetDistance - currentDistance;
         double Y = distanceServoParameters.PID(distanceError, positionRate);   //We want to PID object here

         /* StraightDrive moded selected when created within constructor */
         if (_selectedStyle == Styles.Smart.Voltage)
         {
             _driveTrain.configNominalPercentOutputVoltage(+0, -0);
             _driveTrain.configPeakPercentOutputVoltage(+distanceServoParameters.maxOut, -distanceServoParameters.maxOut);
         }
         StraightDrive.set(Y, targetHeading);

         _previousDistance = currentDistance;
     }

     /** ILoopable */
     public void onStart()
     {
         _isDone = false;
         _isGood = 0;
		 StraightDrive.onStart();
		distanceServoParameters.onStart();
		straightServoParameters.onStart();
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
		if(!_isDone)
		{
			 straightDistance(_targetHeading, _targetDistance);
			 StraightDrive.onLoop();
			 
			 if (distanceServoParameters.isDone() && straightServoParameters.isDone())
			 {
				 _driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
				 _isDone = true;
			 }
		}
	 }
}