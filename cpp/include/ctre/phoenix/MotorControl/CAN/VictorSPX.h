#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"

namespace CTRE {
namespace Phoenix {
namespace MotorControl{
namespace CAN {

class VictorSPX: public virtual CTRE::Phoenix::MotorControl::CAN::BaseMotorController,
                 public virtual CTRE::Phoenix::MotorControl::IMotorController {

public:
  VictorSPX(int deviceNumber);
  virtual ~VictorSPX() {}
}; //class VictorSPX

} //namespace CAN
} //namespace MotorControl
} //namespace Phoenix
} //namespace CTRE
