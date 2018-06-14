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
    ErrorCollection errorCollection;
    
    //------ sensor selection ----------//      

	errorCollection.NewError(BaseConfigurePID(pid, pidIdx, timeoutMs));
    errorCollection.NewError(ConfigSelectedFeedbackSensor(pid.selectedFeedbackSensor, pidIdx, timeoutMs));
        

	return errorCollection._worstError;
}
void VictorSPX::GetPIDConfigs(VictorSPXPIDSetConfiguration &pid, int pidIdx, int timeoutMs)
{
	BaseGetPIDConfigs(pid, pidIdx, timeoutMs);
	pid.selectedFeedbackSensor = (RemoteFeedbackDevice) ConfigGetParameter(eFeedbackSensorType, pidIdx, timeoutMs);

}

ErrorCode VictorSPX::ConfigAllSettings(const VictorSPXConfiguration &allConfigs, int timeoutMs) {
    ErrorCollection errorCollection;
    	
	errorCollection.NewError(BaseConfigAllSettings(allConfigs, timeoutMs));	
	
	//------ remote limit switch ----------//	
	errorCollection.NewError(ConfigForwardLimitSwitchSource(allConfigs.forwardLimitSwitchSource, allConfigs.forwardLimitSwitchNormal, allConfigs.forwardLimitSwitchDeviceID, timeoutMs));
        
	errorCollection.NewError(ConfigReverseLimitSwitchSource(allConfigs.reverseLimitSwitchSource, allConfigs.reverseLimitSwitchNormal, allConfigs.reverseLimitSwitchDeviceID, timeoutMs));
        
		
	//--------PIDs---------------//
	
    errorCollection.NewError(ConfigurePID(allConfigs.primaryPID, 0, timeoutMs));
        
    errorCollection.NewError(ConfigurePID(allConfigs.auxilaryPID, 1, timeoutMs));
        
    errorCollection.NewError(ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, allConfigs.sum_0, timeoutMs));
        
    errorCollection.NewError(ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, allConfigs.sum_1, timeoutMs));
        
    errorCollection.NewError(ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, allConfigs.diff_0, timeoutMs));
        
    errorCollection.NewError(ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, allConfigs.diff_1, timeoutMs));
        
	
    return errorCollection._worstError;
}
void VictorSPX::GetAllConfigs(VictorSPXConfiguration &allConfigs, int timeoutMs) {
	
	BaseGetAllConfigs(allConfigs, timeoutMs);
	
	GetPIDConfigs(allConfigs.primaryPID, 0, timeoutMs);
	GetPIDConfigs(allConfigs.auxilaryPID, 1, timeoutMs);
    allConfigs.sum_0 = (RemoteFeedbackDevice) ConfigGetParameter(eSensorTerm, 0, timeoutMs);
    allConfigs.sum_1 = (RemoteFeedbackDevice) ConfigGetParameter(eSensorTerm, 1, timeoutMs);
    allConfigs.diff_0 = (RemoteFeedbackDevice) ConfigGetParameter(eSensorTerm, 2, timeoutMs);
    allConfigs.diff_1 = (RemoteFeedbackDevice) ConfigGetParameter(eSensorTerm, 3, timeoutMs);

	allConfigs.forwardLimitSwitchSource = (RemoteLimitSwitchSource) ConfigGetParameter(eLimitSwitchSource, 0, timeoutMs);
	allConfigs.reverseLimitSwitchSource = (RemoteLimitSwitchSource) ConfigGetParameter(eLimitSwitchSource, 1, timeoutMs);

}

ErrorCode VictorSPX::ConfigFactoryDefault(int timeoutMs) {
    VictorSPXConfiguration defaults;
    return ConfigAllSettings(defaults, timeoutMs);
}

