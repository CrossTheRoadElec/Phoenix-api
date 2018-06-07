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
	RemoteFeedbackDevice SelectedFeedbackSensor;

	VictorSPXPIDSetConfiguration() :
		SelectedFeedbackSensor(RemoteFeedbackDevice_None)
	{
	}

};

struct VictorSPXConfiguration : BaseMotorControllerConfiguration {
	VictorSPXPIDSetConfiguration PrimaryPID;	
	VictorSPXPIDSetConfiguration AuxilaryPID;	
	RemoteLimitSwitchSource ForwardLimitSwitchSource;
	RemoteLimitSwitchSource ReverseLimitSwitchSource;

	VictorSPXConfiguration() :
		ForwardLimitSwitchSource(RemoteLimitSwitchSource_Deactivated), 
		ReverseLimitSwitchSource(RemoteLimitSwitchSource_Deactivated)
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
	ctre::phoenix::ErrorCode ConfigureSlot(SlotConfiguration &slot, int slotIdx = 0, int timeoutMs = 50);
	ctre::phoenix::ErrorCode ConfigurePID(VictorSPXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50);
	virtual ctre::phoenix::ErrorCode ConfigAllSettings(VictorSPXConfiguration &allConfigs, int timeoutMs = 50);
	virtual ctre::phoenix::ErrorCode ConfigFactoryDefault(int timeoutMs = 50);

};// class VictorSPX
} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
