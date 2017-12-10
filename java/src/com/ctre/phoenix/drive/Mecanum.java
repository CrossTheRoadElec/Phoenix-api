package com.ctre.phoenix.drive;
//package com.ctre.phoenix.Drive;
//
//import com.ctre.phoenix.Mechanical.*;
//import com.ctre.phoenix.motorcontrol.*;
//import com.ctre.phoenix.Drive.Styles;
//
//public class Mecanum implements IDrivetrain
//{
//	Gearbox _1;
//	Gearbox _2;
//	Gearbox _3;
//	Gearbox _4;
//	
//	public Mecanum(IMotorController m1, IMotorController m2, IMotorController m3, IMotorController m4)
//	{
//		GroupMotorControllers.Register(m1);
//		
//		Gearbox temp1 = new Gearbox(m1);
//		Gearbox temp2 = new Gearbox(m2);
//		Gearbox temp3 = new Gearbox(m3);
//		Gearbox temp4 = new Gearbox(m4);
//		
//		_1 = temp1;
//		_2 = temp2;
//		_3 = temp3;
//		_4 = temp4;
//	}
//	
//	public void set(Styles.Basic mode, double forward, double turn)
//	{
//		Drive(mode, forward, 0, turn);
//	}
//	
//	public void set(Styles.Basic mode, double forward, double strafe, double turn)
//	{
//		Drive(mode, forward, strafe, turn);
//	}
//	
//	public void SetVoltageRampRate(double rampRate)
//    {
//        _1.SetVoltageRampRate(rampRate);
//        _2.SetVoltageRampRate(rampRate);
//        _3.SetVoltageRampRate(rampRate);
//        _4.SetVoltageRampRate(rampRate);
//    }
//
//    public void SetVoltageCompensationRampRate(double rampRate)
//    {
//        _1.SetVoltageCompensationRampRate(rampRate);
//        _2.SetVoltageCompensationRampRate(rampRate);
//        _3.SetVoltageCompensationRampRate(rampRate);
//        _4.SetVoltageCompensationRampRate(rampRate);
//    }
//
//    public void ConfigPeakPercentOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _1.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _2.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _3.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//        _4.ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void ConfigNominalPercentOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _1.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _2.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _3.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//        _4.ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    } 
//    
//    private void Drive(Styles.Basic mode, double forward, double strafe, double turn)
//    {
//        double leftFrnt_throt = (forward + strafe + turn); // left front moves positive for forward, strafe-right, turn-right
//        double leftRear_throt = (forward - strafe + turn); // left rear moves positive for forward, strafe-left, turn-right
//        double rghtFrnt_throt = (forward - strafe - turn); // right front moves positive for forward, strafe-left, turn-left
//        double rghtRear_throt = (forward + strafe - turn); // right rear moves positive for forward, strafe-right, turn-left
//
//        /* Set control mode */
//        if(mode == Styles.Basic.PercentOutput)
//        {
//            _1.SetControlMode(ControlMode.BasicControlMode.kPercentVbus);
//            _2.SetControlMode(ControlMode.BasicControlMode.kPercentVbus);
//            _3.SetControlMode(ControlMode.BasicControlMode.kPercentVbus);
//            _4.SetControlMode(ControlMode.BasicControlMode.kPercentVbus);
//        }
//        else if(mode == Styles.Basic.Voltage)
//        {
//            _1.SetControlMode(ControlMode.BasicControlMode.kVoltage);
//            _2.SetControlMode(ControlMode.BasicControlMode.kVoltage);
//            _3.SetControlMode(ControlMode.BasicControlMode.kVoltage);
//            _4.SetControlMode(ControlMode.BasicControlMode.kVoltage);
//        }
//
//        /* Set motors */
//        _1.set(leftFrnt_throt);
//        _2.set(leftRear_throt);
//        _3.set(rghtFrnt_throt);
//        _4.set(rghtRear_throt);
//    }
//}