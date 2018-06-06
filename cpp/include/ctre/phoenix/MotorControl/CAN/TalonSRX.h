#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/MotorControl/IMotorControllerEnhanced.h"
#include "ctre/phoenix/CustomParamConfiguration.h"

namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace can {

/**
 * CTRE Talon SRX Motor Configuration settings.
 */

struct TalonSRXSlotConfiguration : BaseSlotConfiguration {
    FeedbackDevice SelectedFeedbackSensor;

    TalonSRXSlotConfiguration() :
        SelectedFeedbackSensor(QuadEncoder)
    {
    }
};


struct TalonSRXConfiguration : BaseMotorControllerConfiguration{
	TalonSRXSlotConfiguration Slot_0;
	TalonSRXSlotConfiguration Slot_1;
	TalonSRXSlotConfiguration Slot_2;
	TalonSRXSlotConfiguration Slot_3;
	LimitSwitchSource ForwardLimitSwitchSource;
	LimitSwitchSource ReverseLimitSwitchSource;

	int PeakCurrentLimit; 
    int PeakCurrentDuration;
    int ContinuousCurrentLimit; 
	TalonSRXConfiguration() :
		ForwardLimitSwitchSource(LimitSwitchSource_Deactivated),
		ReverseLimitSwitchSource(LimitSwitchSource_Deactivated),
		PeakCurrentLimit(0),
		PeakCurrentDuration(0), 
		ContinuousCurrentLimit(0)
	{
	}
};// struct TalonSRXConfiguration

/**
 * CTRE Talon SRX Motor Controller when used on CAN Bus.
 */

class TalonSRX: public virtual BaseMotorController,
		public virtual IMotorControllerEnhanced {
public:
	TalonSRX(int deviceNumber);
	virtual ~TalonSRX() {
	}
	TalonSRX() = delete;
	TalonSRX(TalonSRX const&) = delete;
	TalonSRX& operator=(TalonSRX const&) = delete;

	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int pidIdx, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int pidIdx, int timeoutMs);

	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,int periodMs, int timeoutMs);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrame frame,int periodMs, int timeoutMs);

	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs);
	virtual int GetStatusFramePeriod(StatusFrame frame, int timeoutMs);

	//------ Velocity measurement ----------//
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs);

	//------ limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);

	//------ Current Limit ----------//
	virtual ctre::phoenix::ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigPeakCurrentDuration(int milliseconds,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs);
	virtual void EnableCurrentLimit(bool enable);
	


	//------ All Configs ----------//

	ctre::phoenix::ErrorCode ConfigureSlot(TalonSRXSlotConfiguration &slot, int pidIdx, int timeoutMs);
	ctre::phoenix::ErrorCode ConfigAllSettings(TalonSRXConfiguration &allConfigs, int timeoutMs);
	ctre::phoenix::ErrorCode ConfigFactoryDefault(int timeoutMs);

protected:
	
	ctre::phoenix::ErrorCode IfRemoteUseRemoteFeedbackFilter(FeedbackDevice feedbackDevice,
			int deviceID, RemoteSensorSource remoteSensorSource, int remoteOrdinal,
            int timeoutMs);

	ctre::phoenix::ErrorCode IfRemoteUseRemoteLimitSwitch( bool isForward, 
            LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
};// class TalonSRX




} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
