#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/MotorControl/IMotorControllerEnhanced.h"

namespace CTRE {
namespace Phoenix {
namespace MotorControl {
namespace CAN {

class TalonSRX: public virtual BaseMotorController,
		public virtual IMotorControllerEnhanced {
public:
	TalonSRX(int deviceNumber);
	virtual ~TalonSRX() {
	}

	virtual ErrorCode ConfigSelectedFeedbackSensor(
			FeedbackDevice feedbackDevice, int timeoutMs);

	virtual ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,
			int periodMs, int timeoutMs);
	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs);

	//------ Velocity measurement ----------//
	virtual ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs);
	virtual ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs);

	//------ limit switch ----------//
	virtual ErrorCode ConfigForwardLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	virtual ErrorCode ConfigReverseLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	virtual ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	virtual ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);

	//------ Current Limit ----------//
	virtual ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs);
	virtual ErrorCode ConfigPeakCurrentDuration(int milliseconds,
			int timeoutMs);
	virtual ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs);
	virtual void EnableCurrentLimit(bool enable);

};
// class TalonSRX
} // namespace CAN
} // namespace MotorControl
} // namespace Phoenix
} // namespace CTRE
