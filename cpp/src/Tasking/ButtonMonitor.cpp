#include "ctre/phoenix/Tasking/ButtonMonitor.h"
#include <GenericHID.h> // WPILIB

#ifndef CTR_EXCLUDE_WPILIB_CLASSES

namespace CTRE {
namespace Phoenix {
namespace Tasking {

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

} // namespace Tasking
} // namespace Phoenix
} // namespace CTRE

#endif // CTR_EXCLUDE_WPILIB_CLASSES
