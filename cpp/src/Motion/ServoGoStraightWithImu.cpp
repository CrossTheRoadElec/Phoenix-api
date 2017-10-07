#include "ctre/phoenix/Motion/ServoGoStraightWithIMU.h"
#include "HAL/DriverStation.h"
#include <math.h>

namespace CTRE { namespace Motion {

ServoGoStraightWithImu::ServoGoStraightWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain, CTRE::Drive::Styles::Basic selectedStyle,
		ServoParameters *parameters, float Y, float targetHeading, float headingTolerance, float maxOutput)
{
	_pidgey = pigeonImu;
	_driveTrain = driveTrain;
	_selectedStyle = selectedStyle;
	_Y = Y;
	_targetHeading = targetHeading;
	_headingTolerance = headingTolerance;

	servoParameters->P = parameters->P;
    servoParameters->I = parameters->I;
    servoParameters->D = parameters->D;

	_maxOutput = maxOutput;
}
ServoGoStraightWithImu::ServoGoStraightWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain, CTRE::Drive::Styles::Basic selectedStyle){
	_pidgey = pigeonImu;
	_driveTrain = driveTrain;
	_selectedStyle = selectedStyle;
}
bool ServoGoStraightWithImu::Set(float Y, float targetHeading, float headingTolerance, float maxOutput){
	_maxOutput = maxOutput;
	return GoStraight(Y, targetHeading, headingTolerance);
}
float ServoGoStraightWithImu::GetImuHeading(){
	double YPR[3];
	_pidgey->GetYawPitchRoll(YPR);
	return (float)YPR[0];
}
void ServoGoStraightWithImu::OnStart(){
	_isDone = false;
	_state = 0;
}
void ServoGoStraightWithImu::OnStop(){
	_driveTrain->Set(CTRE::Drive::Styles::Basic::PercentOutputBasic, 0, 0);
	_isRunning = false;
	_isDone = true;
}
bool ServoGoStraightWithImu::IsDone(){
	return _isDone;
}
void ServoGoStraightWithImu::OnLoop(){
	switch(_state)
	{
		case 0:
			_pidgey->SetYaw(0.0f);
			break;
		case 1:
			GoStraight(_Y, _targetHeading, _headingTolerance);
			break;
	}
}
bool ServoGoStraightWithImu::GoStraight(float Y, float targetHeading, float headingTolerance){
	if (servoParameters->P == 0 && servoParameters->I == 0 && servoParameters->D == 0)
		HAL_SendError(false, 1, false, "CTR: Servo Go Straight With Imu has no PID values, cannot go straight", "", "", true);
	/* Grab current heading */
	float currentHeading = GetImuHeading();

	/* Grab angular rate from the pigeon */
	double XYZ_Dps[3];
	_pidgey->GetRawGyro(XYZ_Dps);
	float currentAngularRate = (float)XYZ_Dps[2];

	/* Grab Pigeon IMU status */
	bool angleIsGood = (_pidgey->GetState() == CTRE::PigeonImu::PigeonState::Ready) ? true : false;

	/* Runs GoStraight if Pigeon IMU is present and in good health, else stop drivetrain */
	if (angleIsGood == true)
	{
		/* Heading PID */
		float headingError = targetHeading - currentHeading;
		float X = (headingError) * servoParameters->P - (currentAngularRate) * servoParameters->D;
		X = fmax(-_maxOutput, fmin(X, _maxOutput));
		X = -X;

		/* Select control mode based on selected style */
		switch (_selectedStyle)
		{
			case CTRE::Drive::Styles::Basic::PercentOutputBasic:
				_driveTrain->Set(CTRE::Drive::Styles::Basic::PercentOutputBasic, Y, X);
				break;
			case CTRE::Drive::Styles::Basic::VoltageBasic:
				_driveTrain->ConfigNominalPercentOutputVoltage(+0.0f, -0.0f);
				_driveTrain->ConfigPeakPercentOutputVoltage(+_maxOutput, -_maxOutput);
				_driveTrain->Set(CTRE::Drive::Styles::Basic::VoltageBasic, Y, X);
				break;
		}

		if (fabs(headingError) >= headingTolerance)
		{
			_isRunning = true;
		}
		else
		{
			_isRunning = false;
		}
	}
	else if (angleIsGood == false)
	{
		_driveTrain->Set(CTRE::Drive::Styles::Basic::PercentOutputBasic, 0, 0);
		_isRunning = false;
	}
	return _isRunning;
}


}}
