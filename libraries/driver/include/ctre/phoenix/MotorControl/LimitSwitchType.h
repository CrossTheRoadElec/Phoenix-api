#pragma once

namespace ctre {
namespace phoenix {
namespace motorcontrol {

enum LimitSwitchSource {
	LimitSwitchSource_FeedbackConnector = 0, /* default */
	LimitSwitchSource_RemoteTalonSRX = 1,
	LimitSwitchSource_RemoteCANifier = 2,
	LimitSwitchSource_Deactivated = 3,
};

enum RemoteLimitSwitchSource {
	RemoteLimitSwitchSource_RemoteTalonSRX = 1,
	RemoteLimitSwitchSource_RemoteCANifier = 2,
	RemoteLimitSwitchSource_Deactivated = 3,
};

enum LimitSwitchNormal {
	LimitSwitchNormal_NormallyOpen = 0,
	LimitSwitchNormal_NormallyClosed = 1,
	LimitSwitchNormal_Disabled = 2
};

class LimitSwitchRoutines {
public:
	static LimitSwitchSource Promote(
			RemoteLimitSwitchSource limitSwitchSource) {
		return (LimitSwitchSource) limitSwitchSource;
	}
	//Checks if a limit switch is a one of the remote values 
	//(i.e. RemoteTalonSRX or RemoteCANifier)
	static bool IsRemote(LimitSwitchSource limitSwitchSource)
	{
		return limitSwitchSource > 0 && limitSwitchSource < 3;
	}
};
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
