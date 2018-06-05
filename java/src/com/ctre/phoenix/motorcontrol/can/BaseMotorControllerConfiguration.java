package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CANBusAddressableConfiguration;
import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
//import com.ctre.phoenix.motorcontrol.can.SlotConfiguration;

public abstract class BaseMotorControllerConfiguration extends CANBusAddressableConfiguration{
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
	public BaseMotorControllerConfiguration(){ /*
		this.OpenloopRamp = 0.0;
		this.ClosedloopRamp = 0.0;
		this.PeakOutputForward = 1.0;
		this.PeakOutputReverse= -1.0;
		this.NominalOutputForward = 0.0;
		this.NominalOutputReverse = 0.0;
		this.NeutralDeadband = 0.04;
		this.VoltageCompSaturation = 0.0;
		this.VoltageMeasurementFilter = 32;
		this.SelectedFeedbackSensorRemote= -1;//None
		this.SelectedFeedbackSensor = 0; //Quad
		this.SelectedFeedbackCoefficient = 1.0; //Doesn't this configure a gear ratio type conversion?
		this.RemoteFeedbackFilter = 0;
		this.SensorTerm = 0; //Sum0
		this.VelocityMeasurementPeriod = 100;
		this.VelocityMeasurementWindow = 64;
		this.ForwardLimitSwitchSource = 3; //Deactivated
		this.ForwardLimitSwitchNormal = 2; //Disabled
		this.ReverseLimitSwitchSource = 3; //Deactivated
		this.ReverseLimitSwitchNormal = 2; //Disabled
		//Can a remote encoder be used for soft limits if there is a local encoder? etc? 
		this.ForwardSoftLimitThreshold = 0.0;
		this.ReverseSoftLimitThreshold = 0.0; 
		this.ForwardSoftLimitEnable = false;
		this.ReverseSoftLimitEnable = false;
		this.AuxPIDPolarity = false; 
		this.MotionCruiseVelocity = 0;
		this.MotionAcceleration = 0;
		this.MotionProfileTrajectoryPeriod = 0; 
		*/
	}		
}
