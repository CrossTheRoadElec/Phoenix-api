#pragma once

//namespace ctre.Phoenix.MotorControl
//
///**
// * Common Control Modes for all CTRE Motor Controllers.
// **/
//class ControlMode {
//public:
//	enum class Value {
//		PercentOutput = 0,
//		Position = 1,
//		Velocity = 2,
//		Follower = 5,
//		MotionProfile = 6,
//		MotionMagic = 7,
//		MotionMagicArc = 8,
//		TimedPercentOutput = 9,
//		Disabled = 15,
//	};
//	explicit ControlMode(ControlMode::Value value) {
//		_value = value;
//	}
//	operator int  () const {
//		return (int)_value;
//	}
//
//	Value PercentOutput = Value::PercentOutput;
//	Value Position = Value::Position;
//private:
//	Value _value;
//} ;
//extern ControlMode ControlMode;

namespace ctre {
namespace phoenix {
namespace motorcontrol {

enum class ControlMode {
	PercentOutput = 0,
	Position = 1,
	Velocity = 2,
	Current = 3,
	Follower = 5,
	MotionProfile = 6,
	MotionMagic = 7,
	MotionMagicArc = 8,
	TimedPercentOutput = 9,

	Disabled = 15,
};

}
}
}
