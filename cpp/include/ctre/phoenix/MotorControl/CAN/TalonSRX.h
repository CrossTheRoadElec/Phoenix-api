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

struct TalonSRXPIDSetConfiguration : BasePIDSetConfiguration {
    FeedbackDevice selectedFeedbackSensor;

    TalonSRXPIDSetConfiguration() :
        selectedFeedbackSensor(QuadEncoder)
    {
    }
};


struct TalonSRXConfiguration : BaseMotorControllerConfiguration{
	TalonSRXPIDSetConfiguration primaryPID;
	TalonSRXPIDSetConfiguration auxilaryPID;
	LimitSwitchSource forwardLimitSwitchSource;
	LimitSwitchSource reverseLimitSwitchSource;

	int peakCurrentLimit; 
    int peakCurrentDuration;
    int continuousCurrentLimit; 
	TalonSRXConfiguration() :
		forwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector),
		reverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector),
		peakCurrentLimit(0),
		peakCurrentDuration(0), 
		continuousCurrentLimit(0)
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

	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);

	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,int periodMs, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrame frame,int periodMs, int timeoutMs = 0);

	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs = 0);
	virtual int GetStatusFramePeriod(StatusFrame frame, int timeoutMs = 0);

	//------ Velocity measurement ----------//
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs = 0);

	//------ limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0);

	//------ Current Limit ----------//
	virtual ctre::phoenix::ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigPeakCurrentDuration(int milliseconds,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs = 0);
	virtual void EnableCurrentLimit(bool enable);
	


	//------ All Configs ----------//

	ctre::phoenix::ErrorCode ConfigurePID(const TalonSRXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50);
	void GetPIDConfigs(TalonSRXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50);
	ctre::phoenix::ErrorCode ConfigAllSettings(const TalonSRXConfiguration &allConfigs, int timeoutMs = 100);
	void GetAllConfigs(TalonSRXConfiguration &allConfigs, int timeoutMs = 100);
	ctre::phoenix::ErrorCode ConfigFactoryDefault(int timeoutMs = 100);

protected:
	LimitSwitchRoutines limitSwitchRoutines;	
	ctre::phoenix::ErrorCode IfRemoteUseRemoteLimitSwitch( bool isForward, 
            LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0);
};// class TalonSRX




} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
