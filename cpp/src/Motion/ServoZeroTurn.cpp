//#include "ctre/phoenix/Motion/ServoZeroTurn.h"
//#include "HAL/DriverStation.h"
//#include <math.h>
//
//namespace CTRE {
//namespace Phoenix {
//namespace Motion {
//
//ServoZeroTurn::ServoZeroTurn(CTRE::Phoenix::Drive::ISmartDrivetrain *driveTrain,
//		CTRE::Phoenix::Drive::Styles::Smart smartStyle, float targetHeading,
//		float headingTolerance, ServoParameters *Params, float maxOutput) {
//	_driveTrain = driveTrain;
//	_selectedStyle = smartStyle;
//
//	_targetHeading = targetHeading;
//	_headingTolerance = headingTolerance;
//
//	_maxOutput = maxOutput;
//
//	servoParams->P = Params->P;
//	servoParams->I = Params->I;
//	servoParams->D = Params->D;
//}
//ServoZeroTurn::ServoZeroTurn(CTRE::Phoenix::Drive::ISmartDrivetrain *driveTrain,
//		CTRE::Phoenix::Drive::Styles::Smart smartStyle) {
//	_driveTrain = driveTrain;
//	_selectedStyle = smartStyle;
//}
//bool ServoZeroTurn::Set(float targetHeading, float headingTolerance,
//		float maxOutput) {
//	_maxOutput = maxOutput;
//	return ZeroTurn(targetHeading, headingTolerance);
//}
//float ServoZeroTurn::GetEncoderHeading() {
//	return _driveTrain->GetEncoderHeading();
//}
//void ServoZeroTurn::OnStart() {
//	_isDone = false;
//	_isGood = 0;
//	_state = 0;
//}
//void ServoZeroTurn::OnStop() {
//	_driveTrain->Set(CTRE::Phoenix::Drive::Styles::Smart::PercentOutput, 0, 0);
//	_isDone = true;
//}
//bool ServoZeroTurn::IsDone() {
//	return _isDone;
//}
//void ServoZeroTurn::OnLoop() {
//	switch (_state) {
//	case 0:
//		_driveTrain->SetPosition(0.0f);
//		_state = 1;
//		break;
//	case 1:
//		bool running = ZeroTurn(_targetHeading, _headingTolerance);
//
//		if (running == true)
//			_isGood = 0;
//		else if (_isGood < 10)
//			++_isGood;
//		else {
//			_driveTrain->Set(CTRE::Phoenix::Drive::Styles::Smart::PercentOutput, 0, 0);
//			_isDone = true;
//		}
//		break;
//	}
//}
//bool ServoZeroTurn::ZeroTurn(float targetHeading, float headingTolerance) {
//	if (servoParams->P == 0 && servoParams->I == 0 && servoParams->D == 0)
//		HAL_SendError(true, 1, false,
//				"CTR: Servo Zero Turn has no PID values, cannot turn", "", "",
//				true);
//	/* Grab the current heading*/
//	float currentHeading = GetEncoderHeading();
//
//	/* Find the difference between last heading and current heading */
//	_timeElapsed = _myStopwatch->Duration();
//	float headingRate = currentHeading - _previousHeading;
//	_myStopwatch->Start();
//
//	/* Heading PID */
//	float headingError = targetHeading - currentHeading;
//	float X = ((headingError) * servoParams->P)
//			- ((headingRate) * servoParams->D);
//	X = -X;
//	X = fmax(-_maxOutput, fmin(X, _maxOutput));
//
//	/** Set the output of the drivetrain */
//	/** Set the output of the drivetrain */
//	switch (_selectedStyle) {
//	case CTRE::Phoenix::Drive::Styles::Smart::PercentOutput:
//		_driveTrain->Set(CTRE::Phoenix::Drive::Styles::Smart::PercentOutput, 0, X);
//		break;
//	case CTRE::Phoenix::Drive::Styles::Smart::Voltage:
//		_driveTrain->Set(CTRE::Phoenix::Drive::Styles::Smart::Voltage, 0, X);
//		break;
//	case CTRE::Phoenix::Drive::Styles::Smart::VelocityClosedLoop:
//		_driveTrain->Set(CTRE::Phoenix::Drive::Styles::Smart::VelocityClosedLoop, 0, X);
//		break;
//	}
//
//	/** Grab the heading to compare next time */
//	_previousHeading = currentHeading;
//
//	if (fabs(headingError) >= headingTolerance) {
//		_isRunning = true;
//	} else {
//		_isRunning = false;
//	}
//	return _isRunning;
//}
//
//}
//}
//}
