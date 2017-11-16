//package com.ctre.phoenix.Drive;
//
//import com.ctre.phoenix.MotorControl.*;
//import com.ctre.phoenix.Mechanical.*;
//
//public class SensoredMecanum implements ISmartDrivetrain
//{
//	SensoredGearbox _1;
//    SensoredGearbox _2;
//    SensoredGearbox _3;
//    SensoredGearbox _4;
//
//    boolean _leftSensor;
//    boolean _rightSensor;
//
//    /** Encoder heading properties */
//    public float distanceBetweenWheels;
//    public float wheelRadius;
//    float tinyScalor = 1;   /* Not sure if I should make this setable */
//
//    /** Constructor that takes 4 SmartMotorcontrollers with a sensor on each side. Also, ask for FeedbackDevice and whether front sensor is used or back sensor is used */
//    public SensoredMecanum(SmartMotorController m1, SmartMotorController m2, SmartMotorController m3, SmartMotorController m4, SmartMotorController.FeedbackDevice feedbackDevice, boolean useLeftFrontSensor, boolean useRightFrontSensor, float wheelRadius, float distanceBetweenWheels)
//    {
//    	if(wheelRadius < 0.01) //Float value, can't use == 0
//    		com.ctre.phoenix.CTRLogger.Log(-500, "Sensored Mecanum");
//    	
//        GroupMotorControllers.Register(m1);
//
//        /* Create 4 sensored gearboxes */
//        SensoredGearbox temp1 = new SensoredGearbox(1, m1, feedbackDevice);
//        SensoredGearbox temp2 = new SensoredGearbox(1, m2, feedbackDevice);
//        SensoredGearbox temp3 = new SensoredGearbox(1, m3, feedbackDevice);
//        SensoredGearbox temp4 = new SensoredGearbox(1, m4, feedbackDevice);
//
//        /* Use front or back sensors */
//        _leftSensor = useLeftFrontSensor;
//        _rightSensor = useRightFrontSensor;
//
//        _1 = temp1;
//        _2 = temp2;
//        _3 = temp3;
//        _4 = temp4;
//        this.wheelRadius = wheelRadius;
//		this.distanceBetweenWheels = distanceBetweenWheels;
//    }
//
//    /** Constructor that takes 4 SensoredGearboxes */
//    public SensoredMecanum(SensoredGearbox m1, SensoredGearbox m2, SensoredGearbox m3, SensoredGearbox m4, float wheelRadius, float distanceBetweenWheels)
//    {
//    	if(wheelRadius < 0.01) //Float value, can't use == 0
//    		com.ctre.phoenix.CTRLogger.Log(-500, "Sensored Mecanum");
//    	
//        GroupMotorControllers.Register(m1.GetMaster());
//
//        _1 = m1;
//        _2 = m2;
//        _3 = m3;
//        _4 = m4;
//
//        /* just use the front sensors */
//        _leftSensor = true;
//        _rightSensor = true;
//        
//        this.wheelRadius = wheelRadius;
//		this.distanceBetweenWheels = distanceBetweenWheels;
//    }
//
//    /**
//     * Part of IDrivetrain
//     * Uses forward and turn (Arcade drive)
//     * 
//     * @param   forward     Y direction of robot
//     * @param   turn        twist of the robot
//     */
//    public void set(Styles.Smart mode, float forward, float turn)
//    {
//        Drive(mode, forward, 0, turn);
//    }
//    public void set(Styles.Basic basicStyle, float forward, float turn)
//    {
//        set(Styles.Promote(basicStyle), forward, turn);
//    }
//
//    /**
//     * Uses forward, strafe, and turn (Mecanum drive)
//     * 
//     * @param   forward     Y direction of robot
//     * @param   strafe      X direction of robot
//     * @param   turn        twist of the robot (arch)
//     */
//    public void set(Styles.Smart mode, float forward, float strafe, float turn)
//    {
//        Drive(mode, forward, strafe, turn);
//    }
//    public void set(Styles.Basic basicStyle, float forward, float strafe, float turn)
//    {
//        set(Styles.Promote(basicStyle), forward, turn);
//    }
//
//    /** Set the current limit on all 4 motors/gearboxes */
//    public void SetCurrentLimit(int currentLimitAmps, int timeoutMs)
//    {
//        _1.SetCurrentLimit(currentLimitAmps, timeoutMs);
//        _2.SetCurrentLimit(currentLimitAmps, timeoutMs);
//        _3.SetCurrentLimit(currentLimitAmps, timeoutMs);
//        _4.SetCurrentLimit(currentLimitAmps, timeoutMs);
//    }
//
//    /** Grab the distance from the left and right encoder */
//    public float GetDistance()
//    { 
//        float l = GetLeftPosition();
//        float r = GetRightPosition();
//
//        return (l + r) * 0.5f;
//    }
//
//    /** Grab the velocity from the left and right encoder */
//    public float GetVelocity()
//    {
//        float l = GetLeftVelocity();
//        float r = GetRightVelocity();
//
//        return (l + r) * 0.5f;
//    }
//
//    public float GetEncoderHeading()
//    {
//        float l = GetLeftPosition();
//        float r = GetRightPosition();
//        
//        if(wheelRadius < 0.01)
//        {
//    		com.ctre.phoenix.CTRLogger.Log(-500, "Sensored Mecanum");
//        	return 0;
//        }
//        
//        if(distanceBetweenWheels < 0.01)
//        {
//    		com.ctre.phoenix.CTRLogger.Log(-502, "Sensored Mecanum");
//        	return 0;
//        }
//        float unitsPerTick = (float)(2 * Math.PI * wheelRadius);
//        float theta = ((r - l) / (distanceBetweenWheels / unitsPerTick) * (float)(180 / Math.PI)) * tinyScalor;
//
//        return theta;
//    }
//
//    public void SetPosition(float position)
//    {
//        _1.SetSensor(position);
//        _2.SetSensor(position);
//        _3.SetSensor(position);
//        _4.SetSensor(position);
//    }
//
//    private void Drive(Styles.Smart mode, float forward, float strafe, float turn)
//    {
//        float leftFrnt_throt = (forward + strafe + turn); // left front moves positive for forward, strafe-right, turn-right
//        float leftRear_throt = (forward - strafe + turn); // left rear moves positive for forward, strafe-left, turn-right
//        float rghtFrnt_throt = (forward - strafe - turn); // right front moves positive for forward, strafe-left, turn-left
//        float rghtRear_throt = (forward + strafe - turn); // right rear moves positive for forward, strafe-right, turn-left
//
//        if (mode == Styles.Smart.Voltage)
//        {
//            _1.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//            _2.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//            _3.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//            _4.SetControlMode(ControlMode.SmartControlMode.kVoltage);
//        }
//        else if (mode == Styles.Smart.PercentOutput)
//        {
//            _1.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//            _2.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//            _3.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//            _4.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//        }
//        else if(mode == Styles.Smart.VelocityClosedLoop)
//        {
//            _1.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//            _2.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//            _3.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//            _4.SetControlMode(ControlMode.SmartControlMode.kSpeed);
//        }
//
//        _1.Set(leftFrnt_throt);
//        _2.Set(leftRear_throt);
//        _3.Set(rghtFrnt_throt);
//        _4.Set(rghtRear_throt);
//    }
//
//    /** Right and left postion */
//    private float GetLeftPosition()
//    {
//        if (_leftSensor)
//            return _1.GetPosition();
//        else
//            return _2.GetPosition();
//    }
//    private float GetRightPosition()
//    {
//        if (_rightSensor)
//            return _4.GetPosition();
//        else
//            return _3.GetPosition();
//    }
//
//    /** Right and left velocity */
//    private float GetLeftVelocity()
//    {
//        if (_leftSensor)
//            return _1.GetVelocity();
//        else
//            return _2.GetVelocity();
//    }
//    private float GetRightVelocity()
//    {
//        if (_rightSensor)
//            return _4.GetVelocity();
//        else
//            return _3.GetVelocity();
//    }
//
//    public void ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage)
//    {
//        _1.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _2.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _3.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _4.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void ConfigPeakPercentOutputVoltage(float forwardVoltage, float reverseVoltage)
//    {
//        _1.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _2.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _3.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _4.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void SetVoltageCompensationRampRate(float RampRate)
//    {
//        _1.SetVoltageCompensationRampRate(RampRate);
//        _2.SetVoltageCompensationRampRate(RampRate);
//        _3.SetVoltageCompensationRampRate(RampRate);
//        _4.SetVoltageCompensationRampRate(RampRate);
//    }
//
//    public void SetVoltageRampRate(float RampRate)
//    {
//        _1.SetVoltageRampRate(RampRate);
//        _2.SetVoltageRampRate(RampRate);
//        _3.SetVoltageRampRate(RampRate);
//        _4.SetVoltageRampRate(RampRate);
//    }
//
//    /* IMotionMagical */
//    public void SetMotionMagicAcceleration(float rotationsPerMinPerSec)
//    {
//        _1.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//        _2.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//        _3.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//        _4.SetMotionMagicAcceleration(rotationsPerMinPerSec);
//    }
//
//    public void SetMotionMagicCruiseVelocity(float rotationsPerMin)
//    {
//        _1.SetMotionMagicCruiseVelocity(rotationsPerMin);
//        _2.SetMotionMagicCruiseVelocity(rotationsPerMin);
//        _3.SetMotionMagicCruiseVelocity(rotationsPerMin);
//        _4.SetMotionMagicCruiseVelocity(rotationsPerMin);
//    }
//}