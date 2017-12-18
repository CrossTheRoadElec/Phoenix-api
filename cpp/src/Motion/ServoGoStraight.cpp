//#include "ctre/phoenix/Motion/ServoGoStraight.h"
//#include "HAL/DriverStation.h"
//#include <math.h>
//
//namespace ctre {
//namespace phoenix {
//namespace motion {
//
//ServoGoStraight::ServoGoStraight(
//		ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
//		ctre::phoenix::drive::Styles::Smart selectedStyle,
//		ServoParameters *params, float Y, float targetHeading,
//		float headingTolerance, float maxOutput) {
//	_driveTrain = driveTrain;
//	_selectedStyle = selectedStyle;
//
//	_Y = Y;
//	_targetHeading = targetHeading;
//	_headingTolerance = headingTolerance;
//
//	servoParameters->P = params->P;
//	servoParameters->I = params->I;
//	servoParameters->D = params->D;
//
//	_maxOutput = maxOutput;
//}
//ServoGoStraight::ServoGoStraight(
//		ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
//		ctre::phoenix::drive::Styles::Smart selectedStyle) {
//	_driveTrain = driveTrain;
//	_selectedStyle = selectedStyle;
//}
//bool ServoGoStraight::Set(float Y, float targetHeading, float headingTolerance,
//		float maxOutput) {
//	_maxOutput = maxOutput;
//	return GoStraight(Y, targetHeading, headingTolerance);
//}
//float ServoGoStraight::GetEncoderHeading() {
//	return _driveTrain->GetEncoderHeading();
//}
//void ServoGoStraight::OnStart() {
//	_isDone = false;
//	_state = 0;
//}
//void ServoGoStraight::OnStop() {
//	_driveTrain->Set(ctre::phoenix::drive::Styles::Smart::PercentOutput, 0, 0);
//	_isRunning = false;
//	_isDone = true;
//}
//bool ServoGoStraight::IsDone() {
//	return _isDone;
//}
//void ServoGoStraight::OnLoop() {
//	switch (_state) {
//	case 0:
//		_driveTrain->SetPosition(0.0f);
//		break;
//	case 1:
//		GoStraight(_Y, _targetHeading, _headingTolerance);
//		break;
//	}
//}
//bool ServoGoStraight::GoStraight(float Y, float targetHeading,
//		float headingTolerance) {
//	if (servoParameters->P == 0 && servoParameters->I == 0
//			&& servoParameters->D == 0)
//		HAL_SendError(false, 1, false,
//				"CTR: Servo Go Straight has no PID values, cannot go straight",
//				"", "", true);
//	/* Grab encoder heading */
//	float currentHeading = GetEncoderHeading();
//
//	/* Find angular rate from the encoders */
//	_timeElapsed = _myStopWatch->Duration();
//	float correctionRate = ((currentHeading - _previousHeading) / _timeElapsed);
//	_myStopWatch->Start();
//
//	/* Heading PID */
//	float headingError = targetHeading - currentHeading;
//	float X = (headingError) * servoParameters->P
//			- (correctionRate) * servoParameters->D;
//	X = fmax(-_maxOutput, fmin(X, _maxOutput));
//	X = -X;
//
//	/* Select control mode based on selected style */
//	switch (_selectedStyle) {
//	default:
//	case ctre::phoenix::drive::Styles::Smart::PercentOutput:
//		_driveTrain->Set(ctre::phoenix::drive::Styles::Smart::PercentOutput, Y,
//				X);
//		break;
//	case ctre::phoenix::drive::Styles::Smart::Voltage:
//		_driveTrain->ConfigNominalPercentOutputVoltage(+0.0f, -0.0f);
//		_driveTrain->ConfigPeakPercentOutputVoltage(+_maxOutput, -_maxOutput);
//		_driveTrain->Set(ctre::phoenix::drive::Styles::Smart::Voltage, Y, X);
//		break;
//	case ctre::phoenix::drive::Styles::Smart::VelocityClosedLoop:
//		_driveTrain->Set(
//				ctre::phoenix::drive::Styles::Smart::VelocityClosedLoop, Y, X);
//		break;
//	}
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
