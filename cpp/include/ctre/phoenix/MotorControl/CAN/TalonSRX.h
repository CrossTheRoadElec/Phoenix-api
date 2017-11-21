#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/MotorControl/IMotorControllerEnhanced.h"

namespace CTRE {
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
	virtual ErrorCode GetStatusFramePeriod(StatusFrameEnhanced frame,
			int & periodMs, int timeoutMs);

	virtual ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs);
	virtual ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs);

	virtual ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	virtual ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);

	virtual ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs);
	virtual ErrorCode ConfigPeakCurrentDuration(int milliseconds,
			int timeoutMs);
	virtual ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs);
	virtual void EnableCurrentLimit(bool enable);

};
// class TalonSRX
}// namespace CAN
} // namespace MotorControl
} // namespace CTRE
