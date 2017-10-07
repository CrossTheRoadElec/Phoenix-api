#pragma once

namespace CTRE { namespace MotorControl {

class ControlMode {
public:

	enum SmartControlMode
	{
        kPercentVbus = 0,
        kPosition = 1,
        kSpeed = 2,
        kCurrent = 3,
        kVoltage = 4,
        kFollower = 5,
        kMotionProfile = 6,
        kMotionMagic = 7,
		kDisabled = 15
	};
	enum BasicControlMode
    {
        kPercentVbusBasic = 0,
        kVoltageBasic = 4,
        kFollowerBasic = 5,
    };

	static SmartControlMode Promote(BasicControlMode basicControlMode)
	{
		return (SmartControlMode)basicControlMode;
	}
};
}}
