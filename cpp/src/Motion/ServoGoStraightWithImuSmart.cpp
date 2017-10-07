#include "ctre/phoenix/Motion/ServoGoStraightWithImuSmart.h"
#include "HAL/DriverStation.h"
#include <math.h>


namespace CTRE { namespace Motion {

ServoGoStraightWithImuSmart::ServoGoStraightWithImuSmart(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart selectedStyle,
		ServoParameters *straightParameters, float Y, float targetHeading, float headingTolerance, float maxOutput)
{
    _pidgey = pigeonImu;
    _driveTrain = driveTrain;
    _selectedStyle = selectedStyle;

    //=====================================//
    _Y = Y;
    _targetHeading = targetHeading;
    _headingTolerance = headingTolerance;

    servoParameters->P = straightParameters->P;
    servoParameters->I = straightParameters->I;
    servoParameters->D = straightParameters->D;

    _maxOutput = maxOutput;
}
ServoGoStraightWithImuSmart::ServoGoStraightWithImuSmart(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart selectedStyle){
    _pidgey = pigeonImu;
    _driveTrain = driveTrain;
    _selectedStyle = selectedStyle;
}
bool ServoGoStraightWithImuSmart::Set(float Y, float targetHeading, float headingTolerance, float maxOutput){
	_maxOutput = maxOutput;
	return GoStraight(Y, targetHeading, headingTolerance);
}
float ServoGoStraightWithImuSmart::GetImuHeading(){
	double YPR[3];
	_pidgey->GetYawPitchRoll(YPR);
	return (float)YPR[0];
}
void ServoGoStraightWithImuSmart::OnStart(){
	_isDone = false;
	_state = 0;
}
void ServoGoStraightWithImuSmart::OnStop(){
    _driveTrain->Set(CTRE::Drive::Styles::Smart::PercentOutput, 0, 0);
    _isRunning = false;
    _isDone = true;
}
bool ServoGoStraightWithImuSmart::IsDone(){
    return _isDone;
}
void ServoGoStraightWithImuSmart::OnLoop(){
    switch (_state)
    {
        case 0:
            _pidgey->SetYaw(0.0f);
            break;
        case 1:
            GoStraight(_Y, _targetHeading, _headingTolerance);
            break;
    }
}
bool ServoGoStraightWithImuSmart::GoStraight(float Y, float targetHeading, float headingTolerance){
	if (servoParameters->P == 0 && servoParameters->I == 0 && servoParameters->D == 0)
		HAL_SendError(false, 1, false, "CTR: Servo Go Straight With Imu Smart has no PID values, cannot go straight", "", "", true);
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
		X = -X;
		X = fmax(-_maxOutput, fmin(X, _maxOutput));

		/* Select control mode based on selected style */
		switch (_selectedStyle)
		{
			case CTRE::Drive::Styles::Smart::PercentOutput:
				_driveTrain->Set(CTRE::Drive::Styles::Smart::PercentOutput, Y, X);
				break;
			case CTRE::Drive::Styles::Smart::Voltage:
				_driveTrain->ConfigNominalPercentOutputVoltage(+0.0f, -0.0f);
				_driveTrain->ConfigPeakPercentOutputVoltage(+_maxOutput, -_maxOutput);
				_driveTrain->Set(CTRE::Drive::Styles::Smart::Voltage, Y, X);
				break;
			case CTRE::Drive::Styles::Smart::VelocityClosedLoop:
				/* MotionMagic/ClosedLoop configured by caller in the drivetrain/motorcontroller level */
				_driveTrain->Set(CTRE::Drive::Styles::Smart::VelocityClosedLoop, Y, X);
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
		_driveTrain->Set(CTRE::Drive::Styles::Smart::PercentOutput, 0, 0);
		_isRunning = false;
	}
	return _isRunning;
}


}}
