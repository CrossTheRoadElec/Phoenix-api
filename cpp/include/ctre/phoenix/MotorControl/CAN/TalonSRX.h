#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"

namespace CTRE {
namespace MotorControl {
namespace CAN {

class TalonSRX: public BaseMotorController {
public:
	TalonSRX(int deviceNumber);

	ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs);
	ErrorCode ConfigPeakCurrentDuration(int milliseconds, int timeoutMs);
	ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs);
	void EnableCurrentLimit(bool enable);

};

} // namespace CAN
} // namespace MotorControl
} // namespace CTRE
