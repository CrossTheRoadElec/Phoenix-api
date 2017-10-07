#pragma once

#include "IMotorController.h"
#include <vector>

namespace CTRE { namespace MotorControl {

class GroupMotorControllers {
public:
	static void Register(IMotorController *motorController);
	static int MotorControllerCount();
	static IMotorController* Get(int idx);

private:
	static std::vector<IMotorController*> _mcs;
};

}}
