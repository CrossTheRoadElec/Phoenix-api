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

//Fix this return data type at some point
ctre::phoenix::ErrorCode VictorSPX::ConfigureSlot(SlotConfiguration &slot, int slotIdx, int timeoutMs) {

    //------ General Close loop ----------//    
    Config_kP(slotIdx, slot.kP, timeoutMs);
    Config_kI(slotIdx, slot.kI, timeoutMs);
    Config_kD(slotIdx, slot.kD, timeoutMs);
    Config_kF(slotIdx, slot.kF, timeoutMs);
    Config_IntegralZone(slotIdx, slot.IntegralZone, timeoutMs);
    ConfigAllowableClosedloopError(slotIdx, slot.AllowableClosedloopError, timeoutMs);
    ConfigMaxIntegralAccumulator(slotIdx, slot.MaxIntegralAccumulator, timeoutMs);
    ConfigClosedLoopPeakOutput(slotIdx, slot.ClosedLoopPeakOutput, timeoutMs);
    ConfigClosedLoopPeriod(slotIdx, slot.ClosedLoopPeriod, timeoutMs);

    return FeatureNotSupported;

}

ctre::phoenix::ErrorCode VictorSPX::ConfigurePID(VictorSPXPIDSetConfiguration &pid, int pidIdx, int timeoutMs) {
    //------ sensor selection ----------//      

    ConfigSelectedFeedbackSensor(pid.SelectedFeedbackSensor, pidIdx, timeoutMs);
    ConfigSelectedFeedbackCoefficient(pid.SelectedFeedbackCoefficient, pidIdx, timeoutMs);
	ConfigRemoteFeedbackFilter( pid.DeviceID,
	pid.remoteSensorSource, pid.RemoteFeedbackFilter,  timeoutMs);
    ConfigSensorTerm(pid.sensorTerm, (FeedbackDevice) pid.SelectedFeedbackSensor, timeoutMs);
    
	return FeatureNotSupported;
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

	//--------Slots---------------//

    ConfigureSlot(allConfigs.Slot_0, 0, timeoutMs);
    ConfigureSlot(allConfigs.Slot_1, 1, timeoutMs);
    ConfigureSlot(allConfigs.Slot_2, 2, timeoutMs);
    ConfigureSlot(allConfigs.Slot_3, 3, timeoutMs);

	//--------PIDs---------------//
	
    ConfigurePID(allConfigs.PrimaryPID, 0, timeoutMs);
    ConfigurePID(allConfigs.AuxilaryPID, 1, timeoutMs);
	
	//---------Auxilary Closed Loop Polarity-------------//
	
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

