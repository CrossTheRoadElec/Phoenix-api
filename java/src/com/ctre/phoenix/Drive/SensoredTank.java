//package com.ctre.phoenix.Drive;
//
//import com.ctre.phoenix.Util;
//import com.ctre.phoenix.Mechanical.*;
//import com.ctre.phoenix.MotorControl.*;
//
//public class SensoredTank implements ISmartDrivetrain
//{
//	SensoredGearbox _left;
//    SensoredGearbox _right;
//
//    /** Encoder heading properties */
//    public double distanceBetweenWheels;
//    public double wheelRadius;
//    float tinyScalor = 1;   /* Not sure if I should make this setable */
//
//    /* Sensored Tank constructor (uses two gearboxes)*/
//    public SensoredTank(SensoredGearbox left, SensoredGearbox right, boolean leftInverted, boolean rightInverted, float wheelRadius, float distanceBetweenWheels)
//    {
//    	if(wheelRadius < 0.01) //Float value, can't use == 0
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
//    public SensoredTank(SmartMotorController m1, SmartMotorController m2, SmartMotorController.FeedbackDevice feedbackDevice,  boolean leftInverted, boolean rightInverted, float wheelRadius, float distanceBetweenWheels)
//    {
//    	if(wheelRadius < 0.01) //Float value, can't use == 0
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
//    public void set(Styles.Smart mode, float forward, float turn)
//    {
//        float l, r;
//        l = forward + turn;
//        r = forward - turn;
//
//        Drive(mode, l, r);
//    }
//    public void set(Styles.Basic basicStyle, float forward, float turn)
//    {
//        set(Styles.Promote(basicStyle), forward, turn);
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
//    public float GetDistance()
//    {
//        float l = _left.GetPosition();
//        float r = _right.GetPosition();
//
//        return (float)((l + r) * wheelRadius * Math.PI);
//    }
//
//    /* Grab the velocity throught the talons' Smart features */
//    public float GetVelocity()
//    {
//        float l = _left.GetVelocity();
//        float r = _right.GetVelocity();
//
//        return (float)(l + r) * (float)wheelRadius * (float)Math.PI;
//    }
//
//    public float GetEncoderHeading()
//    {
//        double l = (float)_left.GetPosition();
//        double r = (float)_right.GetPosition();
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
//        double unitsPerTick = (float)(2 * Math.PI * wheelRadius);
//        double theta = ((r-l) / (distanceBetweenWheels / unitsPerTick) * (180 / Math.PI)) * tinyScalor;
//
//        return (float)theta;
//    }
//
//    /* Reset the encoders on both side of the TankDrivetrain */
//    public void SetPosition(float position)
//    {
//        _left.SetSensor(position);
//        _right.SetSensor(position);
//    }
//
//    /** Sensored Tank drive that takes the mode, left, and right side */
//    private void Drive(Styles.Smart mode, float left, float right)
//    {
//        if(mode == Styles.Smart.Voltage)
//        {
//            _left.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//            _right.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//        }
//        else if (mode == Styles.Smart.PercentOutput)
//        {
//            _left.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//            _right.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//        }
//        else if(mode == Styles.Smart.VelocityClosedLoop)
//        {
//            _left.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//            _right.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//        }
//
//        _left.Set(left);
//        _right.Set(right);
//    }
//
//    public void ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage)
//    {
//        _left.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _right.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void ConfigPeakPercentOutputVoltage(float forwardVoltage, float reverseVoltage)
//    {
//        _left.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _right.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void SetVoltageCompensationRampRate(float rampRate)
//    {
//        _left.SetVoltageCompensationRampRate(rampRate);
//        _right.SetVoltageCompensationRampRate(rampRate);
//    }
//
//    public void SetVoltageRampRate(float rampRate)
//    {
//        _left.SetVoltageRampRate(rampRate);
//        _right.SetVoltageRampRate(rampRate);
//    }
//
//    /* IMotionMagical */
//    public void SetMotionMagicAcceleration(float rotationsPerMinPerSec)
//    {
//        /* RPMPS?? */
//        _left.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//        _right.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//    }
//
//    public void SetMotionMagicCruiseVelocity(float rotationsPerMin)
//    {
//        _left.SetMotionMagicCruiseVelocity(rotationsPerMin);
//        _right.SetMotionMagicCruiseVelocity(rotationsPerMin);
//    }
//}