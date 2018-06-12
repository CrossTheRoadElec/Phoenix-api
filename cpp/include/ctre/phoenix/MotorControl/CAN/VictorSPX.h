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
		selectedFeedbackSensor(RemoteFeedbackDevice_None) //Check with victor
	{
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
		forwardLimitSwitchSource(RemoteLimitSwitchSource_Deactivated), //Check with victor
		reverseLimitSwitchSource(RemoteLimitSwitchSource_Deactivated),
		sum_0 (RemoteFeedbackDevice_None),
		sum_1 (RemoteFeedbackDevice_None),
		diff_0(RemoteFeedbackDevice_None),
		diff_1(RemoteFeedbackDevice_None)

	{
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
	virtual ctre::phoenix::ErrorCode ConfigAllSettings(const VictorSPXConfiguration &allConfigs, int timeoutMs = 100);
	virtual void GetAllConfigs(VictorSPXConfiguration &allConfigs, int timeoutMs = 100);
	virtual ctre::phoenix::ErrorCode ConfigFactoryDefault(int timeoutMs = 100);


};// class VictorSPX
} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
