#include "ctre/phoenix/MotorControl/CAN/VictorSPX.h"

using namespace CTRE::Phoenix::MotorControl::CAN;

VictorSPX::VictorSPX(int deviceNumber) :
    BaseMotorController(deviceNumber | 0x01040000) {}
