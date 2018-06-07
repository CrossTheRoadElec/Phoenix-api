package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.can.SlotConfiguration;

public abstract class BaseMotorControllerConfiguration extends CustomParamConfiguration{
	public double OpenloopRamp;
	public double ClosedloopRamp;
	public double PeakOutputForward;
	public double PeakOutputReverse;
	public double NominalOutputForward;
	public double NominalOutputReverse;
	public double NeutralDeadband;
	public double VoltageCompSaturation;
	public int VoltageMeasurementFilter;
	public VelocityMeasPeriod VelocityMeasurementPeriod;
	public int VelocityMeasurementWindow;
    public int ForwardLimitSwitchDeviceID;
    public int ReverseLimitSwitchDeviceID;
	public LimitSwitchNormal ForwardLimitSwitchNormal;
	public LimitSwitchNormal ReverseLimitSwitchNormal;
	public int ForwardSoftLimitThreshold;
	public int ReverseSoftLimitThreshold;
	public boolean ForwardSoftLimitEnable;
	public boolean ReverseSoftLimitEnable;
	public SlotConfiguration Slot_0;
	public SlotConfiguration Slot_1;
	public SlotConfiguration Slot_2;
	public SlotConfiguration Slot_3;
	public boolean AuxPIDPolarity;
	public int MotionCruiseVelocity;
	public int MotionAcceleration;
	public int MotionProfileTrajectoryPeriod;
	public BaseMotorControllerConfiguration() { 
		OpenloopRamp = 0.0;
		ClosedloopRamp = 0.0;
		PeakOutputForward = 1.0;
		PeakOutputReverse = -1.0;
		NominalOutputForward = 0.0;
		NominalOutputReverse = 0.0;
		NeutralDeadband = 0.04;
		VoltageCompSaturation = 0.0;
		VoltageMeasurementFilter = 32;
		VelocityMeasurementPeriod = VelocityMeasPeriod.Period_100Ms;
		VelocityMeasurementWindow = 64;
    	ForwardLimitSwitchDeviceID = 0;
    	ReverseLimitSwitchDeviceID = 0;
		ForwardLimitSwitchNormal = LimitSwitchNormal.NormallyOpen;
		ReverseLimitSwitchNormal = LimitSwitchNormal.NormallyOpen;
		//Can a remote encoder be used for soft limits if there is a local encoder? etc? 
		ForwardSoftLimitThreshold = 0;
		ReverseSoftLimitThreshold = 0;
		ForwardSoftLimitEnable = false;
		ReverseSoftLimitEnable = false;
		AuxPIDPolarity = false;
		MotionCruiseVelocity = 0;
		MotionAcceleration = 0;
		MotionProfileTrajectoryPeriod = 0;

	}		
}
