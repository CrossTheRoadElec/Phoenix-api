#pragma once

#include "ctre/phoenix/core/GadgeteerUartClient.h"
#include "IMotorController.h"
#include "ControlMode.h"

namespace CTRE{ namespace MotorControl{ namespace CAN
{

class BaseMotorController : public IMotorController {
public:
	explicit TalonSRX(int deviceNumber);
};

}}}
