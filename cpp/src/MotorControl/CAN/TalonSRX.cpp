#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"

using namespace CTRE::MotorControl::CAN;

CTRE::MotorControl::CAN::TalonSRX::TalonSRX(int deviceNumber) :
		BaseMotorController(deviceNumber | 0x02040000) {
}

