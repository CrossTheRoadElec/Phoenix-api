#include "ctre/phoenix/tasking/ButtonMonitor.h"

#if (defined(CTR_INCLUDE_WPILIB_CLASSES) || defined(__FRC_ROBORIO__)) && !defined(CTR_EXCLUDE_WPILIB_CLASSES)
#include <GenericHID.h> // WPILIB

namespace ctre {
namespace phoenix {
namespace tasking {

ButtonMonitor::ButtonMonitor(frc::GenericHID * controller, int buttonIndex,
		IButtonPressEventHandler * ButtonPressEventHandler) {
	_gameCntrlr = controller;
	_btnIdx = buttonIndex;
	_handler = ButtonPressEventHandler;
}
ButtonMonitor::ButtonMonitor(const ButtonMonitor & rhs) {
	_gameCntrlr = rhs._gameCntrlr;
	_btnIdx = rhs._btnIdx;
	_handler = rhs._handler;
}

void ButtonMonitor::Process() {
	bool down = ((frc::GenericHID*)_gameCntrlr)->GetRawButton(_btnIdx);

	if (!_isDown && down)
		_handler->OnButtonPress(_btnIdx, down);

	_isDown = down;
}

void ButtonMonitor::OnStart() {
}
void ButtonMonitor::OnLoop() {
	Process();
}
bool ButtonMonitor::IsDone() {
	return false;
}
void ButtonMonitor::OnStop() {
}

} // namespace tasking
} // namespace phoenix
} // namespace ctre

#endif // CTR_INCLUDE_WPILIB_CLASSES or __FRC_ROBORIO__ and not CTR_EXCLUDE_WPILIB_CLASSES
