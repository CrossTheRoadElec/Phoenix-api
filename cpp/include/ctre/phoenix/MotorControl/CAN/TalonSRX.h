#pragma once

#include "../SmartMotorController.h"

namespace CTRE{ namespace MotorControl{ namespace CAN
{

class TalonSRX : public SmartMotorController {
public:
	explicit TalonSRX(int deviceNumber);
};

}}}
