package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.IMotorController;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.ErrorCode;

import edu.wpi.first.wpilibj.hal.HAL;
/**
 * VEX Victor SPX Motor Controller when used on CAN Bus.
 */
public class VictorSPX extends com.ctre.phoenix.motorcontrol.can.BaseMotorController
    implements IMotorController {
	/**
	 * Constructor
	 * 
	 * @param deviceNumber
	 *            [0,62]
	 */
	public VictorSPX(int deviceNumber) {
		super(deviceNumber | 0x01040000);
		HAL.report(65, deviceNumber + 1);
	}

	//Fix this return data type at some point
	public ErrorCode configureSlot(VictorSPXSlotConfiguration slot, int pidIdx, int timeoutMs) {
	
		//------ sensor selection ----------//      
		
		configSelectedFeedbackSensor(slot.SelectedFeedbackSensor, pidIdx, timeoutMs);
		configSelectedFeedbackCoefficient(slot.SelectedFeedbackCoefficient, pidIdx, timeoutMs);
	
	
		configRemoteFeedbackFilter( slot.DeviceID,
		slot.remoteSensorSource, slot.RemoteFeedbackFilter,  timeoutMs);
		configSensorTerm(slot.sensorTerm, slot.SelectedFeedbackSensor.getFeedbackDevice(), timeoutMs); 
		
		
		//------ General Close loop ----------//    
		config_kP(pidIdx, slot.kP, timeoutMs);
		config_kI(pidIdx, slot.kI, timeoutMs);
		config_kD(pidIdx, slot.kD, timeoutMs);
		config_kF(pidIdx, slot.kF, timeoutMs);
		config_IntegralZone(pidIdx, slot.IntegralZone, timeoutMs);
		configAllowableClosedloopError(pidIdx, slot.AllowableClosedloopError, timeoutMs);
		configMaxIntegralAccumulator(pidIdx, slot.MaxIntegralAccumulator, timeoutMs);
		configClosedLoopPeakOutput(pidIdx, slot.ClosedLoopPeakOutput, timeoutMs);
		configClosedLoopPeriod(pidIdx, slot.ClosedLoopPeriod, timeoutMs);
		
		return ErrorCode.FeatureNotSupported;
	
	}
	public ErrorCode configureSlot(VictorSPXSlotConfiguration slot) {
		int pidIdx = 0;
		int timeoutMs = 50;
		return configureSlot(slot, pidIdx, timeoutMs);
	}	
	public ErrorCode configAllSettings(VictorSPXConfiguration allConfigs, int timeoutMs) {
	
		//----- general output shaping ------------------//
		configOpenloopRamp(allConfigs.OpenloopRamp, timeoutMs);
		configClosedloopRamp(allConfigs.ClosedloopRamp, timeoutMs);
		configPeakOutputForward(allConfigs.PeakOutputForward, timeoutMs);
		configPeakOutputReverse(allConfigs.PeakOutputReverse, timeoutMs);
		configNominalOutputForward(allConfigs.NominalOutputForward, timeoutMs);
		configNominalOutputReverse(allConfigs.NominalOutputReverse, timeoutMs);
		configNeutralDeadband(allConfigs.NeutralDeadband, timeoutMs);
		
		//------ Voltage Compensation ----------//
		configVoltageCompSaturation(allConfigs.VoltageCompSaturation, timeoutMs);
		configVoltageMeasurementFilter(allConfigs.VoltageMeasurementFilter, timeoutMs);
		
		//----- velocity signal conditionaing ------//
		configVelocityMeasurementPeriod(allConfigs.VelocityMeasurementPeriod, timeoutMs);
		configVelocityMeasurementWindow(allConfigs.VelocityMeasurementWindow, timeoutMs);
		
		//------ remote limit switch ----------//   
		configForwardLimitSwitchSource(allConfigs.ForwardLimitSwitchSource, allConfigs.ForwardLimitSwitchNormal, allConfigs.ForwardLimitSwitchDeviceID, timeoutMs);
		configReverseLimitSwitchSource(allConfigs.ReverseLimitSwitchSource, allConfigs.ReverseLimitSwitchNormal, allConfigs.ReverseLimitSwitchDeviceID, timeoutMs);
		
		//------ soft limit ----------//
		configForwardSoftLimitThreshold(allConfigs.ForwardSoftLimitThreshold, timeoutMs);
		configReverseSoftLimitThreshold(allConfigs.ReverseSoftLimitThreshold, timeoutMs);
		configForwardSoftLimitEnable(allConfigs.ForwardSoftLimitEnable, timeoutMs);
		configReverseSoftLimitEnable(allConfigs.ReverseSoftLimitEnable, timeoutMs);
		
		//--------Slots---------------//
		
		configureSlot(allConfigs.Slot_0, 0, timeoutMs);
		configureSlot(allConfigs.Slot_1, 1, timeoutMs);
		configureSlot(allConfigs.Slot_2, 2, timeoutMs);
		configureSlot(allConfigs.Slot_3, 3, timeoutMs);
		
		//---------Auxilary Closed Loop Polarity-------------//
		
		configAuxPIDPolarity(allConfigs.AuxPIDPolarity, timeoutMs);
		
		//------ Motion Profile Settings used in Motion Magic  ----------//
		configMotionCruiseVelocity(allConfigs.MotionCruiseVelocity, timeoutMs);
		configMotionAcceleration(allConfigs.MotionAcceleration, timeoutMs);
		
		//------ Motion Profile Buffer ----------//
		configMotionProfileTrajectoryPeriod(allConfigs.MotionProfileTrajectoryPeriod, timeoutMs);
		
		//------ Custom Persistent Params ----------//
		configSetCustomParam(allConfigs.CustomParam_0, 0, timeoutMs);
		configSetCustomParam(allConfigs.CustomParam_0, 1, timeoutMs);
		
		return ErrorCode.FeatureNotSupported;
	}
	public ErrorCode configAllSettings(VictorSPXConfiguration allConfigs) {
		int timeoutMs = 50;
		return configAllSettings(allConfigs, timeoutMs);
	}	
	public ErrorCode configFactoryDefault(int timeoutMs) {
		VictorSPXConfiguration defaults = new VictorSPXConfiguration();
		configAllSettings(defaults, timeoutMs);
		
		return ErrorCode.FeatureNotSupported;
	}
	public ErrorCode configFactoryDefault() {
		int timeoutMs = 50;
		return configFactoryDefault(timeoutMs);
	}
}
