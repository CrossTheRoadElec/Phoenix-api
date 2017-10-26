#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"

namespace CTRE {
namespace MotorControl {
namespace CAN {

class TalonSRX: public BaseMotorController {
public:
	TalonSRX(int deviceNumber);
};

} // namespace CAN
} // namespace MotorControl
} // namespace CTRE
