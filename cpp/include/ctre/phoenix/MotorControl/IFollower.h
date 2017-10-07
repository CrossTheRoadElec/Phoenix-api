#pragma once

namespace CTRE { namespace MotorControl {

class IMotorController;

class IFollower{
public:
	virtual void Follow(IMotorController *masterToFollow) = 0;
};

}}
