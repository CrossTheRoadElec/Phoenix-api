#include "ctre/phoenix/Mechanical/Gearbox.h"

namespace CTRE{ namespace Mechanical{

Gearbox::Gearbox(CTRE::MotorControl::IMotorController *mc1)
: Linkage(mc1) { }
Gearbox::Gearbox(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2)
: Linkage(mc1, mc2) { }
Gearbox::Gearbox(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3)
: Linkage(mc1, mc2, mc3) { }
Gearbox::Gearbox(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3, CTRE::MotorControl::IFollower *mc4)
: Linkage(mc1, mc2, mc3, mc4) { }

}}
