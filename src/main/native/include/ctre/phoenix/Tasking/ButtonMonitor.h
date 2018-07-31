#pragma once

#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ctre/phoenix/Tasking/IProcessable.h"
#include <functional>

#if defined(CTR_INCLUDE_WPILIB_CLASSES) || defined(__FRC_ROBORIO__)

/* forward proto's */
namespace frc {
	class GenericHID;
}

namespace ctre {
namespace phoenix {
namespace tasking {

class ButtonMonitor: public IProcessable, public ILoopable {
public:

	class IButtonPressEventHandler {
		public:
			virtual ~IButtonPressEventHandler(){}
			virtual void OnButtonPress(int idx, bool isDown) = 0;
	};

	ButtonMonitor(frc::GenericHID * controller, int buttonIndex, IButtonPressEventHandler * ButtonPressEventHandler);
	ButtonMonitor(const ButtonMonitor & rhs);
	virtual ~ButtonMonitor() {	}

	/* IProcessable */
	virtual void Process();

	/* ILoopable */
	virtual void OnStart();
	virtual void OnLoop();
	virtual bool IsDone();
	virtual void OnStop();

private:
	frc::GenericHID * _gameCntrlr;
	int _btnIdx;
	IButtonPressEventHandler * _handler;
	bool _isDown = false;
};
}
}
}
#endif // CTR_INCLUDE_WPILIB_CLASSES or __FRC_ROBORIO__
