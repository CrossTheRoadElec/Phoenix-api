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
//    double _targetVelocity = 0;
//    
//    /* SmartMotorController Constructor */
//    public ServoVelocity(SmartMotorController motor, SmartMotorController.FeedbackDevice feedbackDevice, double velocity)
//    {
//        SensoredGearbox temp1 = new SensoredGearbox(1, motor, feedbackDevice);
//        Gearbox = temp1;
//        _targetVelocity = velocity;
//    }
//    /* SensoredGearbox Constructor */
//    public ServoVelocity(SensoredGearbox gearbox, double velocity)
//    {
//        Gearbox = gearbox;
//        _targetVelocity = velocity;
//    }
//
//    public void onStart()
//    {
//    }
//
//    public void onStop()
//    {
//        /* stop the talon */
//        Gearbox.SetControlMode(ControlMode.SmartControlMode.kPercentVbus);
//        Gearbox.Set(0);
//    }
//    
//    public void set(double targetSpeed, double maxOut)
//    {
//    	Gearbox.ConfigPeakOutputVoltage(maxOut, -maxOut);
//    	Gearbox.SetControlMode(SmartControlMode.kSpeed);
//    	Gearbox.Set(targetSpeed);
//    }
//
//    public boolean isDone()
//    {
//        return false;
//    }
//
//    public void onLoop()
//    {
//        Gearbox.SetControlMode(ControlMode.SmartControlMode	.kSpeed);
//        Gearbox.Set(_targetVelocity);
//    }
//}