#pragma once

namespace CTRE {
namespace Phoenix {
namespace MotorControl {

/* forward proto */
class IMotorController;

class IFollower {
public:
	virtual ~IFollower(){}
	virtual void Follow(CTRE::Phoenix::MotorControl::IMotorController & masterToFollow) = 0;
	virtual void ValueUpdated()= 0;
};

} // namespace MotorControl
} // namespace Phoenix
} // namespace CTRE
