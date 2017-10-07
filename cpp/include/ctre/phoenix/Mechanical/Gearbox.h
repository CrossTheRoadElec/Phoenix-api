#pragma once

#include "Linkage.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/IFollower.h"

namespace CTRE{ namespace Mechanical{

class Gearbox : public Linkage{
public:
	Gearbox(CTRE::MotorControl::IMotorController *mc1);
	Gearbox(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2);
	Gearbox(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3);
	Gearbox(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3, CTRE::MotorControl::IFollower *mc4);
};

}}
