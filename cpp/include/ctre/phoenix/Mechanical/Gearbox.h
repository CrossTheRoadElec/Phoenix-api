#pragma once

#include "Linkage.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/IFollower.h"

namespace ctre {
namespace phoenix {
namespace mechanical {

class Gearbox: public Linkage {
public:
	Gearbox(ctre::phoenix::motorcontrol::IMotorController *mc1);
	Gearbox(ctre::phoenix::motorcontrol::IMotorController *mc1,
			ctre::phoenix::motorcontrol::IFollower *mc2);
	Gearbox(ctre::phoenix::motorcontrol::IMotorController *mc1,
			ctre::phoenix::motorcontrol::IFollower *mc2,
			ctre::phoenix::motorcontrol::IFollower *mc3);
	Gearbox(ctre::phoenix::motorcontrol::IMotorController *mc1,
			ctre::phoenix::motorcontrol::IFollower *mc2,
			ctre::phoenix::motorcontrol::IFollower *mc3,
			ctre::phoenix::motorcontrol::IFollower *mc4);
};

} // namespace mechanical
} // namespace phoenix
} // namespace ctre
