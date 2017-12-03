#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"

namespace CTRE {
namespace MotorControl {
namespace CAN {

class VictorSPX: public BaseMotorController {
public:

	VictorSPX(int deviceNumber) :
			BaseMotorController(deviceNumber | 0x01040000) {
	}

};

} // namespace CAN
} // namespace MotorControl
} // namespace CTRE

