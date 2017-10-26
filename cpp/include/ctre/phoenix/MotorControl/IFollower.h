#pragma once

namespace CTRE {
namespace MotorControl {

/* forward proto */
class IMotorController;

class IFollower {
public:
	virtual void Follow(CTRE::MotorControl::IMotorController & masterToFollow) = 0;
	virtual void ValueUpdated()= 0;
};

}
}
