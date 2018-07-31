#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/CustomParamConfiguration.h"
//#include "ctre/phoenix/MotorControl/IMotorController.h"

namespace ctre {
namespace phoenix {
namespace motorcontrol{
namespace can {

/**
 * VEX Victor SPX Motor Configuration settings.
 */
struct VictorSPXPIDSetConfiguration : BasePIDSetConfiguration {
	RemoteFeedbackDevice selectedFeedbackSensor;

	VictorSPXPIDSetConfiguration() :
		selectedFeedbackSensor(RemoteFeedbackDevice_RemoteSensor0) 
        //NOTE: while the factory default value is 0, this value can't
        //be set by the API. Thus, RemoteSensor0 is the default
	{                                                              
	}
    std::string toString(std::string prependString) {

        std::string retstr = prependString + ".selectedFeedbackSensor = " + FeedbackDeviceRoutines::toString(selectedFeedbackSensor) + ";\n";
        retstr += BasePIDSetConfiguration::toString(prependString);
        return retstr;
    }

};

struct VictorSPXConfiguration : BaseMotorControllerConfiguration {
	VictorSPXPIDSetConfiguration primaryPID;	
	VictorSPXPIDSetConfiguration auxilaryPID;	
	RemoteLimitSwitchSource forwardLimitSwitchSource;
	RemoteLimitSwitchSource reverseLimitSwitchSource;
	RemoteFeedbackDevice sum_0;
	RemoteFeedbackDevice sum_1;
	RemoteFeedbackDevice diff_0;
	RemoteFeedbackDevice diff_1;

	VictorSPXConfiguration() :
		forwardLimitSwitchSource(RemoteLimitSwitchSource_Deactivated), 
		reverseLimitSwitchSource(RemoteLimitSwitchSource_Deactivated),
		sum_0 (RemoteFeedbackDevice_RemoteSensor0), 
		sum_1 (RemoteFeedbackDevice_RemoteSensor0), 
		diff_0(RemoteFeedbackDevice_RemoteSensor0),
		diff_1(RemoteFeedbackDevice_RemoteSensor0)
        //NOTE: while the factory default value is 0, this value can't
        //be set by the API. Thus, RemoteSensor0 is the default

	{
	}	
    std::string toString(std::string prependString) {
        std::string retstr = primaryPID.toString(prependString + ".primaryPID");	
	    retstr += auxilaryPID.toString(prependString + ".auxilaryPID");	
	    retstr += prependString + ".forwardLimitSwitchSource = " + LimitSwitchRoutines::toString(forwardLimitSwitchSource) + ";\n";
	    retstr += prependString + ".reverseLimitSwitchSource = " + LimitSwitchRoutines::toString(reverseLimitSwitchSource) + ";\n";
	    retstr += prependString + ".sum_0 = " + FeedbackDeviceRoutines::toString(sum_0) + ";\n";
	    retstr += prependString + ".sum_1 = " + FeedbackDeviceRoutines::toString(sum_1) + ";\n";
	    retstr += prependString + ".diff_0 = " + FeedbackDeviceRoutines::toString(diff_0) + ";\n";
	    retstr += prependString + ".diff_1 = " + FeedbackDeviceRoutines::toString(diff_1) + ";\n";
        retstr += BaseMotorControllerConfiguration::toString(prependString);
        
        return retstr;
    }
};

/**
 * VEX Victor SPX Motor Controller when used on CAN Bus.
 */
class VictorSPX: public virtual ctre::phoenix::motorcontrol::can::BaseMotorController,
                 public virtual ctre::phoenix::motorcontrol::IMotorController {

public:
	VictorSPX(int deviceNumber);
	virtual ~VictorSPX() {
	}
	VictorSPX(VictorSPX const&) = delete;
	VictorSPX& operator=(VictorSPX const&) = delete;
	
	//------ All Configs ----------//
	ctre::phoenix::ErrorCode ConfigurePID(const VictorSPXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50);
	void GetPIDConfigs(VictorSPXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50);
	virtual ctre::phoenix::ErrorCode ConfigAllSettings(const VictorSPXConfiguration &allConfigs, int timeoutMs = 50);
	virtual void GetAllConfigs(VictorSPXConfiguration &allConfigs, int timeoutMs = 50);


};// class VictorSPX
} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
