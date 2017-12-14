#include "ctre/phoenix/MotorControl/CAN/VictorSPX.h"

using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol::can;

VictorSPX::VictorSPX(int deviceNumber) :
    BaseMotorController(deviceNumber | 0x01040000) {}
