package com.ctre.phoenix.mechanical;
//package com.ctre.phoenix.Mechanical;
//
//import com.ctre.phoenix.motorcontrol.*;
//
//public class SensoredGearbox implements com.ctre.phoenix.Signals.IInvertable
//{
//	private double _unitsPerRevolution;
//	private double _scalar;
//	
//	private boolean _isInverted;
//	public SmartMotorController _controller;
//	
//	
//	public SensoredGearbox(double unitsPerRevolution, SmartMotorController mc1, SmartMotorController.FeedbackDevice feedback)
//	{
//		_controller = mc1;
//		_unitsPerRevolution = unitsPerRevolution;
//		_controller.setFeedbackDevice(feedback);
//	}
//	public SensoredGearbox(double unitsPerRevolution, SmartMotorController mc1, IFollower mc2, SmartMotorController.FeedbackDevice feedback)
//	{
//		_controller = mc1;
//		_unitsPerRevolution = unitsPerRevolution;
//		_controller.setFeedbackDevice(feedback);
//		
//		mc2.follow(_controller);
//	}
//	public SensoredGearbox(double unitsPerRevolution, SmartMotorController mc1, IFollower mc2, IFollower mc3, SmartMotorController.FeedbackDevice feedback)
//	{
//		_controller = mc1;
//		_unitsPerRevolution = unitsPerRevolution;
//		_controller.setFeedbackDevice(feedback);
//		
//		mc2.follow(_controller);
//		mc3.follow(_controller);
//	}
//	public SensoredGearbox(double unitsPerRevolution, SmartMotorController mc1, IFollower mc2, IFollower mc3, IFollower mc4, SmartMotorController.FeedbackDevice feedback)
//	{
//		_controller = mc1;
//		_unitsPerRevolution = unitsPerRevolution;
//		_controller.setFeedbackDevice(feedback);
//
//		mc2.follow(_controller);
//		mc3.follow(_controller);
//		mc4.follow(_controller);
//	}
//	
//	 /**
//     * @return The geared output position in rotations.
//     */
//    public double getPosition()
//    {
//        return (double)com.ctre.phoenix.Util.scaleNativeUnitsToRotations(_unitsPerRevolution, (long)_controller.getPosition());
//    }
//    /**
//     * @return The geared output velocity in rotations per minute.
//     */
//    public double getVelocity()
//    {
//        return (double)com.ctre.phoenix.Util.scaleNativeUnitsToRpm(_unitsPerRevolution, (long)_controller.getSpeed());
//    }
//
//    public void SetCurrentLimit(int currentLimitAmps, int timeoutms)
//    {
//        _controller.setCurrentLimit(currentLimitAmps);
//    }
//
//    public void set(double output)
//    {
//        if (_isInverted)
//            output = -output;
//        
//        _controller.set(output);
//    }
//
//    /** Set the control mode of the gearbox */
//    public void SetControlMode(ControlMode.SmartControlMode mode)
//    {
//        _controller.setControlMode(mode);
//    }
//
//    /** Set the limits on the forward and reverse drive */
//    public void SetLimits(double forwardLimit, double reverseLimit)
//    {
//        _controller.setForwardSoftLimit(com.ctre.phoenix.Util.scaleRotationsToNativeUnits(_unitsPerRevolution, forwardLimit));
//        _controller.setReverseSoftLimit(com.ctre.phoenix.Util.scaleRotationsToNativeUnits(_unitsPerRevolution, reverseLimit));
//    }
//    
//    /** Disable limits of the gearbox */
//    public void DisableLimits()
//    {
//        _controller.enableLimitSwitch(false, false);
//    }
//
//    /* IInvertable */
//    public void setInverted(boolean invert)
//    {
//        _isInverted = invert;
//    }
//
//    public boolean getInverted()
//    {
//        return _isInverted;
//    }
//
//    public void InvertSensor(boolean invert)
//    {
//        _controller.reverseSensor(invert);
//    }
//
//    public void SetSensor(double position)
//    {
//        _controller.setPosition(com.ctre.phoenix.Util.scaleRotationsToNativeUnits(_unitsPerRevolution, position));
//    }
//
//    public void ConfigNominalOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _controller.configNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void ConfigPeakOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _controller.configPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void SetVoltageCompensationRampRate(double RampRate)
//    {
//        _controller.setVoltageCompensationRate(RampRate);
//    }
//
//    public void SetVoltageRampRate(double RampRate)
//    {
//        _controller.setVoltageRampRate(RampRate);
//    }
//
//    /* IMotionMagical */
//    /* Motion Magic stuff */
//    public void SetMotionMagicCruiseVelocity(double RPM)
//    {
//        _controller.setMotionMagicCruiseVelocity(com.ctre.phoenix.Util.scaleVelocityToNativeUnits(_unitsPerRevolution, RPM));
//    }
//
//    public void SetMotionMagicAcceleration(double RPM)
//    {
//        _controller.setMotionMagicAcceleration(com.ctre.phoenix.Util.scaleVelocityToNativeUnits(_unitsPerRevolution, RPM));
//    }
//
//    public SmartMotorController GetMaster()
//    {
//        return _controller;
//    }
//}