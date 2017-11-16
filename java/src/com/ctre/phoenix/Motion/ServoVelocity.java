//package com.ctre.phoenix.Motion;
//
//import com.ctre.phoenix.Drive.*;
//import com.ctre.phoenix.MotorControl.*;
//import com.ctre.phoenix.MotorControl.ControlMode.SmartControlMode;
//import com.ctre.phoenix.Mechanical.*;
//
//public class ServoVelocity implements com.ctre.phoenix.ILoopable
//{
//
//    SensoredGearbox Gearbox;
//    float _targetVelocity = 0;
//    
//    /* SmartMotorController Constructor */
//    public ServoVelocity(SmartMotorController motor, SmartMotorController.FeedbackDevice feedbackDevice, float velocity)
//    {
//        SensoredGearbox temp1 = new SensoredGearbox(1, motor, feedbackDevice);
//        Gearbox = temp1;
//        _targetVelocity = velocity;
//    }
//    /* SensoredGearbox Constructor */
//    public ServoVelocity(SensoredGearbox gearbox, float velocity)
//    {
//        Gearbox = gearbox;
//        _targetVelocity = velocity;
//    }
//
//    public void OnStart()
//    {
//    }
//
//    public void OnStop()
//    {
//        /* stop the talon */
//        Gearbox.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//        Gearbox.Set(0);
//    }
//    
//    public void Set(float targetSpeed, float maxOut)
//    {
//    	Gearbox.ConfigPeakOutputVoltage(maxOut, -maxOut);
//    	Gearbox.SetControlMode(SmartControlMode.kSpeed);
//    	Gearbox.Set(targetSpeed);
//    }
//
//    public boolean IsDone()
//    {
//        return false;
//    }
//
//    public void OnLoop()
//    {
//        Gearbox.SetControlMode(ControlMode.SmartControlMode	.kSpeed);
//        Gearbox.Set(_targetVelocity);
//    }
//}