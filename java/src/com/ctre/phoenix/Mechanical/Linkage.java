package com.ctre.phoenix.mechanical;
//package com.ctre.phoenix.Mechanical;
//
//import com.ctre.phoenix.motorcontrol.*;
//
//public class Linkage implements com.ctre.phoenix.Signals.IOutputSignal, com.ctre.phoenix.Signals.IInvertable
//{
//	IMotorController _motor = null;
//	IFollower[] _follower = {null, null, null};
//	int _followerCount = 0;
//	boolean _isInverted = false;
//	
//	public Linkage(IMotorController mc1)
//	{
//		_motor = mc1;
//		Setup();
//	}
//	public Linkage(IMotorController mc1, IMotorController mc2)
//	{
//		_motor = mc1;
//		_follower[_followerCount++] = mc2;
//		Setup();
//	}
//	public Linkage(IMotorController mc1, IMotorController mc2, IMotorController mc3)
//	{
//		_motor = mc1;
//		_follower[_followerCount++] = mc2;
//		_follower[_followerCount++] = mc3;
//		Setup();
//	}
//	public Linkage(IMotorController mc1, IMotorController mc2, IMotorController mc3, IMotorController mc4)
//	{
//		_motor = mc1;
//		_follower[_followerCount++] = mc2;
//		_follower[_followerCount++] = mc3;
//		_follower[_followerCount++] = mc4;
//		Setup();
//	}
//	
//	private void setup()
//	{
//		for(int i = 0; i < _followerCount; i++)
//		{
//			_follower[i].follow(_motor);
//		}
//	}
//	
//	public void set(double value)
//	{
//		if(_isInverted)
//			value = -value;
//		_motor.set(value);
//		for(int i = 0; i < _followerCount; i++)
//		{
//			_follower[i].valueUpdated();
//		}
//	}
//	
//	public void SetControlMode(ControlMode mode)
//	{
//		_motor.setControlMode(mode);
//	}
//	
//	public void setInverted(boolean inverted)
//	{
//		_isInverted = inverted;
//	}
//	
//	public boolean getInverted()
//	{
//		return _isInverted;
//	}
//	
//	public void SetVoltageRampRate(double rampRate)
//    {
//        _motor.setVoltageRampRate(rampRate);
//    }
//
//    public void SetVoltageCompensationRampRate(double rampRate)
//    {
//        _motor.setVoltageRampRate(rampRate);
//    }
//
//    public void ConfigNominalOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _motor.configNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public void ConfigPeakOutputVoltage(double forwardVoltage, double reverseVoltage)
//    {
//        _motor.configPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    }
//
//    public IMotorController getMaster()
//    {
//        return _motor;
//    }
//}