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

ctre::phoenix::ErrorCode VictorSPX::ConfigurePID(const VictorSPXPIDSetConfiguration &pid, int pidIdx, int timeoutMs) {
    //------ sensor selection ----------//      

	BaseConfigurePID(pid, pidIdx, timeoutMs);
    ConfigSelectedFeedbackSensor(pid.selectedFeedbackSensor, pidIdx, timeoutMs);
	ConfigRemoteFeedbackFilter( pid.remoteSensorDeviceID,
	pid.remoteSensorSource, pidIdx,  timeoutMs);
    ConfigSensorTerm(pid.sensorTerm, (FeedbackDevice) pid.selectedFeedbackSensor, timeoutMs);
    
	return FeatureNotSupported;
}
void VictorSPX::GetPIDConfigs(VictorSPXPIDSetConfiguration &pid, int pidIdx, int timeoutMs)
{
	BaseGetPIDConfigs(pid, pidIdx, timeoutMs);
	pid.selectedFeedbackSensor = (RemoteFeedbackDevice) ConfigGetParameter(eFeedbackSensorType, pidIdx, timeoutMs);

}

ErrorCode VictorSPX::ConfigAllSettings(const VictorSPXConfiguration &allConfigs, int timeoutMs) {
	
	BaseConfigAllSettings(allConfigs, timeoutMs);	
	
	//------ remote limit switch ----------//	
	ConfigForwardLimitSwitchSource(allConfigs.forwardLimitSwitchSource, allConfigs.forwardLimitSwitchNormal, allConfigs.forwardLimitSwitchDeviceID, timeoutMs);
	ConfigReverseLimitSwitchSource(allConfigs.reverseLimitSwitchSource, allConfigs.reverseLimitSwitchNormal, allConfigs.reverseLimitSwitchDeviceID, timeoutMs);
		
	//--------PIDs---------------//
	
    ConfigurePID(allConfigs.primaryPID, 0, timeoutMs);
    ConfigurePID(allConfigs.auxilaryPID, 1, timeoutMs);
	
    return FeatureNotSupported;
}
void VictorSPX::GetAllConfigs(VictorSPXConfiguration &allConfigs, int timeoutMs) {
	
	BaseGetAllConfigs(allConfigs, timeoutMs);
	
	GetPIDConfigs(allConfigs.primaryPID, 0, timeoutMs);
	GetPIDConfigs(allConfigs.auxilaryPID, 1, timeoutMs);

	allConfigs.forwardLimitSwitchSource = (RemoteLimitSwitchSource) ConfigGetParameter(eLimitSwitchSource, 0, timeoutMs);
	allConfigs.reverseLimitSwitchSource = (RemoteLimitSwitchSource) ConfigGetParameter(eLimitSwitchSource, 1, timeoutMs);

}

ErrorCode VictorSPX::ConfigFactoryDefault(int timeoutMs) {
    VictorSPXConfiguration defaults;
    ConfigAllSettings(defaults, timeoutMs);

    return FeatureNotSupported;
}

