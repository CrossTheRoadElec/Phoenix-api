package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CANBusAddressableConfiguration;
import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.SlotConfiguration;

public abstract class BaseMotorControllerConfiguration implements CANBusAddressableConfiguration{
	public double OpenloopRamp;
	public double ClosedloopRamp; 
	public double PeakOutputForward;
	public double PeakOutputReverse;
	public double NominalOutputForward; 
	public double NominalOutputReverse; 
	public double NeutralDeadband;
	public double VoltageCompSaturation; 
	public int VoltageMeasurementFilter;
	public RemoteFeedbackDevice SelectedFeedbackSensorRemote;
	public FeedbackDevice SelectedFeedbackSensor;
	public double SelectedFeedbackCoefficient; //Doesn't this ure a gear ratio type conversion?
	public int RemoteFeedbackFilter;
	public SensorTerm SensorTerm;
	public VelocityMeasPeriod VelocityMeasurementPeriod; 
	public int VelocityMeasurementWindow; 
	//Deal with remote vs local thorny issue 
	public LimitSwitchSource ForwardLimitSwitchSource;
	public LimitSwitchNormal ForwardLimitSwitchNormal;
	public LimitSwitchSource ReverseLimitSwitchSource;
	public LimitSwitchNormal ReverseLimitSwitchNormal;
	//Can a remote encoder be used for soft limits if there is a local encoder? etc? 
	public int ForwardSoftLimitThreshold; 
	public int ReverseSoftLimitThreshold; 
	public bool ForwardSoftLimitEnable; 
	public bool ReverseSoftLimitEnable; 
	public SlotConfiguration Slot_0;
	public SlotConfiguration Slot_1;
	public SlotConfiguration Slot_2;
	public SlotConfiguration Slot_3;
	public bool AuxPIDPolarity; 
	public int MotionCruiseVelocity; 
	public int MotionAcceleration; 
	public int MotionProfileTrajectoryPeriod; 
	public BaseMotorControllerConfiguration(){
		OpenloopRamp = 0.0;
		ClosedloopRamp = 0.0;
		PeakOutputForward = 1.0;
		PeakOutputReverse= -1.0;
		NominalOutputForward = 0.0;
		NominalOutputReverse = 0.0;
		NeutralDeadband = 0.04;
		VoltageCompSaturation = 0.0;
		VoltageMeasurementFilter = 32;
		SelectedFeedbackSensorRemote= -1;//None
		SelectedFeedbackSensor = 0; //Quad
		SelectedFeedbackCoefficient = 1.0; //Doesn't this configure a gear ratio type conversion?
		RemoteFeedbackFilter = 0;
		SensorTerm = 0; //Sum0
		VelocityMeasurementPeriod = 100;
		VelocityMeasurementWindow = 64;
		ForwardLimitSwitchSource = 3; //Deactivated
		ForwardLimitSwitchNormal = 2; //Disabled
		ReverseLimitSwitchSource = 3; //Deactivated
		ReverseLimitSwitchNormal = 2; //Disabled
		//Can a remote encoder be used for soft limits if there is a local encoder? etc? 
		ForwardSoftLimitThreshold = 0.0;
		ReverseSoftLimitThreshold = 0.0; 
		ForwardSoftLimitEnable = false;
		ReverseSoftLimitEnable = false;
		AuxPIDPolarity = false; 
		MotionCruiseVelocity = 0;
		MotionAcceleration = 0;
		MotionProfileTrajectoryPeriod = 0; 
	}		
}
