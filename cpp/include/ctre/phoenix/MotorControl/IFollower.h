#pragma once

namespace CTRE {
namespace MotorControl {

/* forward proto */
class IMotorController;

class IFollower {
public:
	virtual void Follow(IMotorController *masterToFollow) = 0;
	virtual void ValueUpdated()= 0;
};

}
}
