#include "ctre/phoenix/MotorControl/CAN/VictorSPX.h"
#include "HAL/HAL.h"

using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol::can;
/**
 * Constructor
 * @param deviceNumber [0,62]
 */
VictorSPX::VictorSPX(int deviceNumber) :
    BaseMotorController(deviceNumber | 0x01040000) {
		HAL_Report(HALUsageReporting::kResourceType_CTRE_future1, deviceNumber + 1);
	}

ErrorCode VictorSPX::ConfigAllSettings(VictorSPXConfiguration &allConfigs, int timeoutMs) {
	
	//----- general output shaping ------------------//
	ConfigOpenloopRamp(allConfigs.OpenloopRamp, timeoutMs);
	ConfigClosedloopRamp(allConfigs.ClosedloopRamp, timeoutMs);
	ConfigPeakOutputForward(allConfigs.PeakOutputForward, timeoutMs);
	ConfigPeakOutputReverse(allConfigs.PeakOutputReverse, timeoutMs);
	ConfigNominalOutputForward(allConfigs.NominalOutputForward, timeoutMs);
	ConfigNominalOutputReverse(allConfigs.NominalOutputReverse, timeoutMs);
	ConfigNeutralDeadband(allConfigs.NeutralDeadband, timeoutMs);

	//------ Voltage Compensation ----------//
	ConfigVoltageCompSaturation(allConfigs.VoltageCompSaturation, timeoutMs);
	ConfigVoltageMeasurementFilter(allConfigs.VoltageMeasurementFilter, timeoutMs);
	
	//------ sensor selection ----------//
		
		//-------Slot_0-----------//
	ConfigSelectedFeedbackSensor(allConfigs.Slot_0.SelectedFeedbackSensor, 0, timeoutMs);
	ConfigSelectedFeedbackCoefficient(allConfigs.Slot_0.SelectedFeedbackCoefficient, 0, timeoutMs);
	ConfigRemoteFeedbackFilter( allConfigs.Slot_0.DeviceID,
	allConfigs.Slot_0.remoteSensorSource, allConfigs.Slot_0.RemoteFeedbackFilter,  timeoutMs);
	ConfigSensorTerm(allConfigs.Slot_0.sensorTerm, (FeedbackDevice) allConfigs.Slot_0.SelectedFeedbackSensor, timeoutMs);
	
		//-------Slot_1-----------//
	ConfigSelectedFeedbackSensor(allConfigs.Slot_1.SelectedFeedbackSensor, 1, timeoutMs);
	ConfigSelectedFeedbackCoefficient(allConfigs.Slot_1.SelectedFeedbackCoefficient, 1, timeoutMs);
	ConfigRemoteFeedbackFilter( allConfigs.Slot_1.DeviceID,
	allConfigs.Slot_1.remoteSensorSource, allConfigs.Slot_1.RemoteFeedbackFilter,  timeoutMs);
	ConfigSensorTerm(allConfigs.Slot_1.sensorTerm, (FeedbackDevice) allConfigs.Slot_1.SelectedFeedbackSensor, timeoutMs);
	
		//-------Slot_2-----------//
	ConfigSelectedFeedbackSensor(allConfigs.Slot_2.SelectedFeedbackSensor, 2, timeoutMs);
	ConfigSelectedFeedbackCoefficient(allConfigs.Slot_2.SelectedFeedbackCoefficient, 2, timeoutMs);
	ConfigRemoteFeedbackFilter( allConfigs.Slot_2.DeviceID,
	allConfigs.Slot_2.remoteSensorSource, allConfigs.Slot_2.RemoteFeedbackFilter,  timeoutMs);
	ConfigSensorTerm(allConfigs.Slot_2.sensorTerm, (FeedbackDevice) allConfigs.Slot_2.SelectedFeedbackSensor, timeoutMs);
	
		//-------Slot_3-----------//
	ConfigSelectedFeedbackSensor(allConfigs.Slot_3.SelectedFeedbackSensor, 3, timeoutMs);
	ConfigSelectedFeedbackCoefficient(allConfigs.Slot_3.SelectedFeedbackCoefficient, 3, timeoutMs);
	ConfigRemoteFeedbackFilter(allConfigs.Slot_3.DeviceID, allConfigs.Slot_3.remoteSensorSource, allConfigs.Slot_3.RemoteFeedbackFilter,  timeoutMs);
	ConfigSensorTerm(allConfigs.Slot_3.sensorTerm, (FeedbackDevice) allConfigs.Slot_3.SelectedFeedbackSensor, timeoutMs);

    //----- velocity signal conditionaing ------//
	ConfigVelocityMeasurementPeriod(allConfigs.VelocityMeasurementPeriod, timeoutMs);
	ConfigVelocityMeasurementWindow(allConfigs.VelocityMeasurementWindow, timeoutMs);
    
	//------ remote limit switch ----------//	
	ConfigForwardLimitSwitchSource(allConfigs.ForwardLimitSwitchSource, allConfigs.ForwardLimitSwitchNormal, allConfigs.ForwardLimitSwitchDeviceID, timeoutMs);
	ConfigReverseLimitSwitchSource(allConfigs.ReverseLimitSwitchSource, allConfigs.ReverseLimitSwitchNormal, allConfigs.ReverseLimitSwitchDeviceID, timeoutMs);
		
	//------ soft limit ----------//
	ConfigForwardSoftLimitThreshold(allConfigs.ForwardSoftLimitThreshold, timeoutMs);
	ConfigReverseSoftLimitThreshold(allConfigs.ReverseSoftLimitThreshold, timeoutMs);
	ConfigForwardSoftLimitEnable(allConfigs.ForwardSoftLimitEnable, timeoutMs);
	ConfigReverseSoftLimitEnable(allConfigs.ReverseSoftLimitEnable, timeoutMs);

	//------ General Close loop ----------//	

		//-------Slot_0-----------//
	Config_kP(0, allConfigs.Slot_0.kP, timeoutMs);
	Config_kI(0, allConfigs.Slot_0.kI, timeoutMs);
	Config_kD(0, allConfigs.Slot_0.kD, timeoutMs);
	Config_kF(0, allConfigs.Slot_0.kF, timeoutMs);
	Config_IntegralZone(0, allConfigs.Slot_0.IntegralZone, timeoutMs);
	ConfigAllowableClosedloopError(0, allConfigs.Slot_0.AllowableClosedloopError, timeoutMs);
	ConfigMaxIntegralAccumulator(0, allConfigs.Slot_0.MaxIntegralAccumulator, timeoutMs);
	ConfigClosedLoopPeakOutput(0, allConfigs.Slot_0.ClosedLoopPeakOutput, timeoutMs);
	ConfigClosedLoopPeriod(0, allConfigs.Slot_0.ClosedLoopPeriod, timeoutMs);
	
		//-------Slot_1-----------//
	Config_kP(1, allConfigs.Slot_1.kP, timeoutMs);
	Config_kI(1, allConfigs.Slot_1.kI, timeoutMs);
	Config_kD(1, allConfigs.Slot_1.kD, timeoutMs);
	Config_kF(1, allConfigs.Slot_1.kF, timeoutMs);
	Config_IntegralZone(1, allConfigs.Slot_1.IntegralZone, timeoutMs);
	ConfigAllowableClosedloopError(1, allConfigs.Slot_1.AllowableClosedloopError, timeoutMs);
	ConfigMaxIntegralAccumulator(1, allConfigs.Slot_1.MaxIntegralAccumulator, timeoutMs);
	ConfigClosedLoopPeakOutput(1, allConfigs.Slot_1.ClosedLoopPeakOutput, timeoutMs);
	ConfigClosedLoopPeriod(1, allConfigs.Slot_1.ClosedLoopPeriod, timeoutMs);
	
		//-------Slot_2-----------//
	Config_kP(2, allConfigs.Slot_2.kP, timeoutMs);
	Config_kI(2, allConfigs.Slot_2.kI, timeoutMs);
	Config_kD(2, allConfigs.Slot_2.kD, timeoutMs);
	Config_kF(2, allConfigs.Slot_2.kF, timeoutMs);
	Config_IntegralZone(2, allConfigs.Slot_2.IntegralZone, timeoutMs);
	ConfigAllowableClosedloopError(2, allConfigs.Slot_2.AllowableClosedloopError, timeoutMs);
	ConfigMaxIntegralAccumulator(2, allConfigs.Slot_2.MaxIntegralAccumulator, timeoutMs);
	ConfigClosedLoopPeakOutput(2, allConfigs.Slot_2.ClosedLoopPeakOutput, timeoutMs);
	ConfigClosedLoopPeriod(2, allConfigs.Slot_2.ClosedLoopPeriod, timeoutMs);
	
		//-------Slot_3-----------//
	Config_kP(3, allConfigs.Slot_3.kP, timeoutMs);
	Config_kI(3, allConfigs.Slot_3.kI, timeoutMs);
	Config_kD(3, allConfigs.Slot_3.kD, timeoutMs);
	Config_kF(3, allConfigs.Slot_3.kF, timeoutMs);
	Config_IntegralZone(3, allConfigs.Slot_3.IntegralZone, timeoutMs);
	ConfigAllowableClosedloopError(3, allConfigs.Slot_3.AllowableClosedloopError, timeoutMs);
	ConfigMaxIntegralAccumulator(3, allConfigs.Slot_3.MaxIntegralAccumulator, timeoutMs);
	ConfigClosedLoopPeakOutput(3, allConfigs.Slot_3.ClosedLoopPeakOutput, timeoutMs);
	ConfigClosedLoopPeriod(3, allConfigs.Slot_3.ClosedLoopPeriod, timeoutMs);
	
	ConfigAuxPIDPolarity(allConfigs.AuxPIDPolarity, timeoutMs);

	//------ Motion Profile Settings used in Motion Magic  ----------//
	ConfigMotionCruiseVelocity(allConfigs.MotionCruiseVelocity, timeoutMs);
	ConfigMotionAcceleration(allConfigs.MotionAcceleration, timeoutMs);
	
    //------ Motion Profile Buffer ----------//
	ConfigMotionProfileTrajectoryPeriod(allConfigs.MotionProfileTrajectoryPeriod, timeoutMs);

	//------ Custom Persistent Params ----------//
    ConfigSetCustomParam(allConfigs.CustomParam_0, 0, timeoutMs);
    ConfigSetCustomParam(allConfigs.CustomParam_0, 1, timeoutMs);

    return FeatureNotSupported;
}

ErrorCode VictorSPX::ConfigFactoryDefault(int timeoutMs) {
    VictorSPXConfiguration defaults;
    ConfigAllSettings(defaults, timeoutMs);

    return FeatureNotSupported;
}

