#pragma once

//namespace CTRE.Phoenix.MotorControl
//{
enum LimitSwitchSource {
	Disabled_ = 0,
	FeedbackConnector_ = 1,
	RemoteTalonSRX_ = 2,
	RemoteCANifier_ = 3,
};

enum RemoteLimitSwitchSource {
	Disabled__ = 0, RemoteTalonSRX__ = 2, RemoteCANifier__ = 3,
};

enum LimitSwitchNormal {
	NormallyOpen, NormallyClosed,
};

class IHasRemoteLimitSwitches {
public:
	virtual ~IHasRemoteLimitSwitches() {
	}
	virtual ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID)=0;
	virtual ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID)=0;

	virtual void EnableLimitSwitch(bool forwardEnable, bool reverseEnable)=0;
};

class IHasLimitSwitches {
public:
	virtual ~IHasLimitSwitches() {
	}
	virtual ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose) = 0;
	virtual ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose) = 0;
	virtual void EnableLimitSwitch(bool forwardEnable, bool reverseEnable) = 0;
};

class LimitSwitchRoutines {
public:
	static LimitSwitchSource Promote(
			RemoteLimitSwitchSource limitSwitchSource) {
		return (LimitSwitchSource) limitSwitchSource;
	}
};
//}
