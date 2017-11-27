package com.ctre.phoenix.Motion;

import com.ctre.phoenix.Sensors.PigeonIMU;
import com.ctre.phoenix.Drive.*;
import com.ctre.phoenix.Time.StopWatch;

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
     public void Set(double targetHeading, double targetDistance)
     {
		 _targetHeading = targetHeading;
		 _targetDistance = targetDistance;
     }

     /** Return the heading from the Pigeon */
     public double GetImuHeading()
     {
         return (double)_pidgey.GetYawPitchRoll()[0];
     }

     /** Return the encoder distance from the DriveTrain */
     public double GetEncoderDistance()
     {
         return _driveTrain.GetDistance();
     }

     /** ServoStraightDistanceWithImu processing */
     private void StraightDistance(double targetHeading, double targetDistance)
     {
    	if(straightServoParameters.P == 0 && straightServoParameters.I == 0 && straightServoParameters.D == 0)
    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Straight Distance With Imu");
    	if(distanceServoParameters.P == 0 && distanceServoParameters.I == 0 && distanceServoParameters.D == 0)
    		com.ctre.phoenix.CTRLogger.Log(-503, "Servo Straight Distance With Imu");
         /* Grab current distance */
         double currentDistance = GetEncoderDistance();

         /* Grab the positionRate and elapsed time, must be done anytime we use D gain */
         double positionRate = _driveTrain.GetVelocity();

         /* Distance PID */
         double distanceError = targetDistance - currentDistance;
         double Y = distanceServoParameters.PID(distanceError, positionRate);   //We want to PID object here

         /* StraightDrive moded selected when created within constructor */
         if (_selectedStyle == Styles.Smart.Voltage)
         {
             _driveTrain.ConfigNominalPercentOutputVoltage(+0, -0);
             _driveTrain.ConfigPeakPercentOutputVoltage(+distanceServoParameters.maxOut, -distanceServoParameters.maxOut);
         }
         StraightDrive.Set(Y, targetHeading);

         _previousDistance = currentDistance;
     }

     /** ILoopable */
     public void OnStart()
     {
         _isDone = false;
         _isGood = 0;
		 StraightDrive.OnStart();
		distanceServoParameters.OnStart();
		straightServoParameters.OnStart();
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
		if(!_isDone)
		{
			 StraightDistance(_targetHeading, _targetDistance);
			 StraightDrive.OnLoop();
			 
			 if (distanceServoParameters.IsDone() && straightServoParameters.IsDone())
			 {
				 _driveTrain.set(Styles.Basic.PercentOutput, 0, 0);
				 _isDone = true;
			 }
		}
	 }
}