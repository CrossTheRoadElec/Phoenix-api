//package com.ctre.phoenix.drive;
//
//import com.ctre.phoenix.Util;
//import com.ctre.phoenix.mechanical.*;
//import com.ctre.phoenix.motorcontrol.*;
//
//public class SensoredTank
//{
//	SensoredGearbox _left;
//    SensoredGearbox _right;
//
//    /** Encoder heading properties */
//    public double distanceBetweenWheels;
//    public double wheelRadius;
//    double tinyScalor = 1;   /* Not sure if I should make this setable */
//
//    /* Sensored Tank constructor (uses two gearboxes)*/
//    public SensoredTank(SensoredGearbox left, SensoredGearbox right, boolean leftInverted, boolean rightInverted, double wheelRadius, double distanceBetweenWheels)
//    {
//    	if(wheelRadius < 0.01) //double value, can't use == 0
//    		com.ctre.phoenix.CTRLogger.Log(-500, "ServoStraightDistanceWithImu");
//    	
//        GroupMotorControllers.Register(left.GetMaster());
//        _left = left;
//        _right = right;
//
//        _left.setInverted(leftInverted);
//        _right.setInverted(rightInverted);
//        this.wheelRadius = wheelRadius;
//		this.distanceBetweenWheels = distanceBetweenWheels;
//    }
//
//    public SensoredTank(SmartMotorController m1, SmartMotorController m2, SmartMotorController.FeedbackDevice feedbackDevice,  boolean leftInverted, boolean rightInverted, double wheelRadius, double distanceBetweenWheels)
//    {
//    	if(wheelRadius < 0.01) //double value, can't use == 0
//    		com.ctre.phoenix.CTRLogger.Log(-500, "ServoStraightDistanceWithImu");
//    	
//        GroupMotorControllers.Register(m1);
//
//        /* Create 2 single motor gearboxes */
//        SensoredGearbox temp1 = new SensoredGearbox(1, m1, feedbackDevice);
//        SensoredGearbox temp2 = new SensoredGearbox(1, m2, feedbackDevice);
//
//        _left = temp1;
//        _right = temp2;
//
//        _left.setInverted(leftInverted);
//        _right.setInverted(rightInverted);
//        
//        this.wheelRadius = wheelRadius;
//		this.distanceBetweenWheels = distanceBetweenWheels;
//    }
//    
//    /** Part of IDrivetrain; Takes control mode, forward output and turn output */
//    public void set(DriveMode.Smart mode, double forward, double turn)
//    {
//        double l, r;
//        l = forward + turn;
//        r = forward - turn;
//
//        Drive(mode, l, r);
//    }
//    public void set(DriveMode.Basic basicStyle, double forward, double turn)
//    {
//        set(DriveMode.Promote(basicStyle), forward, turn);
//    }
//    
//
//    /* Set the currentlimit with Amps and a timeout */
//    public void SetCurrentLimit(int currentAmps, int timeoutMs)
//    {
//        _left.SetCurrentLimit(currentAmps, timeoutMs);
//        _right.SetCurrentLimit(currentAmps, timeoutMs);
//    }
//
//    /* Grab the position throught the talons' Smart features */
//    public double getDistance()
//    {
//        double l = _left.GetPosition();
//        double r = _right.GetPosition();
//
//        return (double)((l + r) * wheelRadius * Math.PI);
//    }
//
//    /* Grab the velocity throught the talons' Smart features */
//    public double getVelocity()
//    {
//        double l = _left.GetVelocity();
//        double r = _right.GetVelocity();
//
//        return (double)(l + r) * (double)wheelRadius * (double)Math.PI;
//    }
//
//    public double getEncoderHeading()
//    {
//        double l = (double)_left.GetPosition();
//        double r = (double)_right.GetPosition();
//        
//        if(wheelRadius < 0.01)
//        {
//    		com.ctre.phoenix.CTRLogger.Log(-500, "ServoStraightDistanceWithImu");
//        	return 0;
//        }
//        
//        if(distanceBetweenWheels < 0.01)
//        {
//    		com.ctre.phoenix.CTRLogger.Log(-503, "ServoStraightDistanceWithImu");
//        	return 0;
//        }
//        
//        double unitsPerTick = (double)(2 * Math.PI * wheelRadius);
//        double theta = ((r-l) / (distanceBetweenWheels / unitsPerTick) * (180 / Math.PI)) * tinyScalor;
//
//        return (double)theta;
//    }
//
//    /* Reset the encoders on both side of the TankDrivetrain */
//    public void SetPosition(double position)
//    {
//        _left.SetSensor(position);
//        _right.SetSensor(position);
//    }
//
//    /** Sensored Tank drive that takes the mode, left, and right side */
//    private void Drive(DriveMode.Smart mode, double left, double right)
//    {
//        if(mode == DriveControlMode.DriveMode.Voltage)
//        {
//            _left.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//            _right.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//        }
//        else if (mode == DriveControlMode.DriveMode.PercentOutput)
//        {
//            _left.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//            _right.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//        }
//        else if(mode == DriveControlMode.DriveMode.VelocityClosedLoop)
//        {
//            _left.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//            _right.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//        }
//
//        _left.Set(left);
//        _right.Set(right);
//    }
//
//    public void ConfigNominalPercentOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _left.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _right.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void ConfigPeakPercentOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _left.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _right.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void SetVoltageCompensationRampRate(double rampRate)
//    {
//        _left.SetVoltageCompensationRampRate(rampRate);
//        _right.SetVoltageCompensationRampRate(rampRate);
//    }
//
//    public void SetVoltageRampRate(double rampRate)
//    {
//        _left.SetVoltageRampRate(rampRate);
//        _right.SetVoltageRampRate(rampRate);
//    }
//
//    /* IMotionMagical */
//    public void SetMotionMagicAcceleration(double rotationsPerMinPerSec)
//    {
//        /* RPMPS?? */
//        _left.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//        _right.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//    }
//
//    public void SetMotionMagicCruiseVelocity(double rotationsPerMin)
//    {
//        _left.SetMotionMagicCruiseVelocity(rotationsPerMin);
//        _right.SetMotionMagicCruiseVelocity(rotationsPerMin);
//    }
//}