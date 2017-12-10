//#include "ctre/phoenix/Motion/ServoStraightDistance.h"
//#include "HAL/DriverStation.h"
//#include <math.h>
//
//namespace ctre {
//namespace phoenix {
//namespace motion {
//
//ServoStraightDistance::ServoStraightDistance(
//		ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
//		ctre::phoenix::drive::Styles::Smart selectedStyle, ServoParameters *turnParams,
//		ServoParameters *distanceParams, float targetHeading,
//		float targetDistance, float headingTolerance, float distanceTolerance,
//		float maxOutput) {
//	_driveTrain = driveTrain;
//	_selectedStyle = selectedStyle;
//
//	/* Construct a ServoGoStraight based on sytle selected */
//	if (_selectedStyle == ctre::Drive::Styles::Smart::Voltage)
//		StraightDrive = new ServoGoStraight(_driveTrain,
//				ctre::Drive::Styles::Smart::Voltage);
//	else if (_selectedStyle == ctre::Drive::Styles::Smart::PercentOutput)
//		StraightDrive = new ServoGoStraight(_driveTrain,
//				ctre::Drive::Styles::Smart::PercentOutput);
//	else if (_selectedStyle == ctre::Drive::Styles::Smart::VelocityClosedLoop)
//		StraightDrive = new ServoGoStraight(_driveTrain,
//				ctre::Drive::Styles::Smart::VelocityClosedLoop);
//
//	//================================================//
//	_targetHeading = targetHeading;
//	_targetDistance = targetDistance;
//	_headingTolerance = headingTolerance;
//	_distanceTolerance = distanceTolerance;
//
//	distanceServoParameters->P = distanceParams->P;
//	distanceServoParameters->I = distanceParams->I;
//	distanceServoParameters->D = distanceParams->D;
//
//	straightServoParameters->P = turnParams->P;
//	straightServoParameters->I = turnParams->I;
//	straightServoParameters->D = turnParams->D;
//
//	StraightDrive->servoParameters->P = turnParams->P;
//	StraightDrive->servoParameters->I = turnParams->I;
//	StraightDrive->servoParameters->D = turnParams->D;
//
//	_maxOutput = maxOutput;
//}
//ServoStraightDistance::ServoStraightDistance(
//		ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
//		ctre::phoenix::drive::Styles::Smart selectedStyle) {
//	_driveTrain = driveTrain;
//	_selectedStyle = selectedStyle;
//
//	/* Construct a ServoGoStraight based on sytle selected */
//	if (_selectedStyle == ctre::Drive::Styles::Smart::Voltage)
//		StraightDrive = new ServoGoStraight(_driveTrain,
//				ctre::Drive::Styles::Smart::Voltage);
//	else if (_selectedStyle == ctre::Drive::Styles::Smart::PercentOutput)
//		StraightDrive = new ServoGoStraight(_driveTrain,
//				ctre::Drive::Styles::Smart::PercentOutput);
//	else if (_selectedStyle == ctre::Drive::Styles::Smart::VelocityClosedLoop)
//		StraightDrive = new ServoGoStraight(_driveTrain,
//				ctre::Drive::Styles::Smart::VelocityClosedLoop);
//}
//bool ServoStraightDistance::Set(float targetHeading, float targetDistance,
//		float headingTolerance, float distanceTolerance, float maxOutput) {
//	StraightDrive->servoParameters->P = straightServoParameters->P;
//	StraightDrive->servoParameters->I = straightServoParameters->I;
//	StraightDrive->servoParameters->D = straightServoParameters->D;
//
//	_maxOutput = maxOutput;
//
//	return StraightDistance(targetHeading, targetDistance, headingTolerance,
//			distanceTolerance);
//}
//float ServoStraightDistance::GetEncoderHeading() {
//	return _driveTrain->GetEncoderHeading();
//}
//float ServoStraightDistance::GetEncoderDistance() {
//	return _driveTrain->GetDistance();
//}
//void ServoStraightDistance::OnStart() {
//	_isDone = false;
//	_isGood = 0;
//	_state = 0;
//}
//void ServoStraightDistance::OnStop() {
//	_driveTrain->Set(ctre::phoenix::drive::Styles::Smart::PercentOutput, 0, 0);
//	_isRunning = false;
//	_isDone = true;
//}
//bool ServoStraightDistance::IsDone() {
//	return _isDone;
//}
//void ServoStraightDistance::OnLoop() {
//	switch (_state) {
//	case 0:
//		_driveTrain->SetPosition(0.0f);
//		_state = 1;
//		break;
//	case 1:
//		bool running = StraightDistance(_targetHeading, _targetDistance,
//				_headingTolerance, _distanceTolerance);
//
//		if (running == true)
//			_isGood = 0;
//		else if (_isGood < 10)
//			++_isGood;
//		else {
//			_driveTrain->Set(ctre::phoenix::drive::Styles::Smart::PercentOutput, 0, 0);
//			_isDone = true;
//		}
//		break;
//	}
//}
//bool ServoStraightDistance::StraightDistance(float targetHeading,
//		float targetDistance, float headingTolerance, float distanceTolerance) {
//	if (straightServoParameters->P == 0 && straightServoParameters->I == 0
//			&& straightServoParameters->D == 0)
//		HAL_SendError(false, 1, false,
//				"CTR: Servo Straight Distance has no straight PID values, cannot go straight",
//				"", "", true);
//	if (distanceServoParameters->P == 0 && distanceServoParameters->I == 0
//			&& distanceServoParameters->D == 0)
//		HAL_SendError(false, 1, false,
//				"CTR: Servo Straight Distance has no distance PID values, cannot go forward",
//				"", "", true);
//	/* Grab current heading and distance*/
//	float currentDistance = GetEncoderDistance();
//
//	/* Find the error between the target and current value */
//	_timeElapsed = _myStopWatch->Duration();
//	float distanceRate =
//			((currentDistance - _previousDistance) / (_timeElapsed));
//	_myStopWatch->Start();
//
//	/* Distance PID */
//	float distanceError = targetDistance - currentDistance;
//	float Y = (distanceError) * distanceServoParameters->P
//			- (distanceRate) * distanceServoParameters->D;
//	Y = fmax(-_maxOutput, fmin(Y, _maxOutput));
//
//	/* StraightDrive moded selected when created within constructor */
//	if (_selectedStyle == ctre::phoenix::drive::Styles::Smart::Voltage) {
//		_driveTrain->ConfigNominalPercentOutputVoltage(+0, -0);
//		_driveTrain->ConfigPeakPercentOutputVoltage(+_maxOutput, -_maxOutput);
//	}
//	bool headingCheck = StraightDrive->Set(Y, targetHeading, headingTolerance,
//			_maxOutput);
//
//	_previousDistance = currentDistance;
//
//	if ((fabs(distanceError) >= distanceTolerance) || (headingCheck == true)) {
//		_isRunning = true;
//	} else {
//		_isRunning = false;
//	}
//	return _isRunning;
//}
//
//}
//} // namespace phoenix
//}
