#include "ctre/phoenix/Motion/ServoStraightDistanceWithIMU.h"
#include "HAL/DriverStation.h"
#include <math.h>

namespace CTRE { namespace Motion {

ServoStraightDistanceWithImu::ServoStraightDistanceWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *drivetrain, CTRE::Drive::Styles::Smart selectedStyle, ServoParameters *straightParameters,
		ServoParameters *distanceParameters, float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance, float maxOutput)
{
    _pidgey = pigeonImu;
    _driveTrain = drivetrain;
    _selectedStyle = selectedStyle;

    /* Construct a ServoGoStraightWithImu based on style */
    if (_selectedStyle == CTRE::Drive::Styles::Smart::Voltage)
        StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, CTRE::Drive::Styles::Smart::Voltage);
    else if (_selectedStyle == CTRE::Drive::Styles::Smart::PercentOutput)
        StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, CTRE::Drive::Styles::Smart::PercentOutput);
    else if (_selectedStyle == CTRE::Drive::Styles::Smart::VelocityClosedLoop)
        StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, CTRE::Drive::Styles::Smart::VelocityClosedLoop);

    //============================================================//
    _targetHeading = targetHeading;
    _targetDistance = targetDistance;
    _headingTolerance = headingTolerance;
    _distanceTolerance = distanceTolerance;

    distanceServoParameters->P = distanceParameters->P;
    distanceServoParameters->I = distanceParameters->I;
    distanceServoParameters->D = distanceParameters->D;

    straightServoParameters->P = straightParameters->P;
    straightServoParameters->I = straightParameters->I;
    straightServoParameters->D = straightParameters->D;

    StraightDrive->servoParameters->P = straightParameters->P;
    StraightDrive->servoParameters->I = straightParameters->I;
    StraightDrive->servoParameters->D = straightParameters->D;

    _maxOutput = maxOutput;
}
ServoStraightDistanceWithImu::ServoStraightDistanceWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *drivetrain, CTRE::Drive::Styles::Smart selectedStyle){
    _pidgey = pigeonImu;
    _driveTrain = drivetrain;
    _selectedStyle = selectedStyle;

    /* Construct a ServoGoStraightWithImu based on style */
    if (_selectedStyle == CTRE::Drive::Styles::Smart::Voltage)
        StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, CTRE::Drive::Styles::Smart::Voltage);
    else if (_selectedStyle == CTRE::Drive::Styles::Smart::PercentOutput)
        StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, CTRE::Drive::Styles::Smart::PercentOutput);
    else if (_selectedStyle == CTRE::Drive::Styles::Smart::VelocityClosedLoop)
        StraightDrive = new ServoGoStraightWithImuSmart(_pidgey, _driveTrain, CTRE::Drive::Styles::Smart::VelocityClosedLoop);
}
bool ServoStraightDistanceWithImu::Set(float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance, float maxOutput){
	StraightDrive->servoParameters->P = straightServoParameters->P;
	StraightDrive->servoParameters->I = straightServoParameters->I;
	StraightDrive->servoParameters->D = straightServoParameters->D;

    _maxOutput = maxOutput;

    return StraightDistance(targetHeading, targetDistance, headingTolerance, distanceTolerance);
}
float ServoStraightDistanceWithImu::GetImuHeading(){
    double YPR[3];
    _pidgey->GetYawPitchRoll(YPR);
    return (float)YPR[0];
}
float ServoStraightDistanceWithImu::GetEncoderDistance(){
    return _driveTrain->GetDistance();
}
void ServoStraightDistanceWithImu::OnStart(){
    _isDone = false;
    _isGood = 0;
    _state = 0;
}
void ServoStraightDistanceWithImu::OnStop(){
    _driveTrain->Set(CTRE::Drive::Styles::Smart::PercentOutput, 0, 0);
    _isRunning = false;
    _isDone = true;
}
bool ServoStraightDistanceWithImu::IsDone(){
    return _isDone;
}
void ServoStraightDistanceWithImu::OnLoop(){
    switch (_state)
    {
        case 0: /* Init */
            _driveTrain->SetPosition(0.0f);
            _pidgey->SetYaw(0.0f);
            _state = 1;
            break;
        case 1: /* Process */
            bool running = StraightDistance(_targetHeading, _targetDistance, _headingTolerance, _distanceTolerance);

            if (running == true)
                _isGood = 0;
            else if (_isGood < 10)
                ++_isGood;
            else
            {
                _driveTrain->Set(CTRE::Drive::Styles::Smart::PercentOutput, 0, 0);
                _isDone = true;
            }
            break;
    }
}
bool ServoStraightDistanceWithImu::StraightDistance(float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance){
    if (straightServoParameters->P == 0 && straightServoParameters->I == 0 && straightServoParameters->D == 0)
    	HAL_SendError(false, 1, false, "CTR: Servo Straight Distance With Imu has no straight PID values, cannot go straight", "", "", true);
    if (distanceServoParameters->P == 0 && distanceServoParameters->I == 0 && distanceServoParameters->D == 0)
    	HAL_SendError(false, 1, false, "CTR: Servo Straight Distance With Imuhas no distance PID values, cannot go forward", "", "", true);
    /* Grab current distance */
    float currentDistance = GetEncoderDistance();

    /* Grab the positionRate and elapsed time, must be done anytime we use D gain */
    _timeElapsed = (_myStopWatch->Duration());
    float positionRate = ((currentDistance - _previousDistance) / (_timeElapsed));
    _myStopWatch->Start();

    /* Distance PID */
    float distanceError = targetDistance - currentDistance;
    float Y = (distanceError) * distanceServoParameters->P - (positionRate) * distanceServoParameters->D;   //We want to PID object here
    Y = fmax(-_maxOutput, fmin(Y, _maxOutput));

    /* StraightDrive moded selected when created within constructor */
    if (_selectedStyle == CTRE::Drive::Styles::Smart::Voltage)
    {
        _driveTrain->ConfigNominalPercentOutputVoltage(+0, -0);
        _driveTrain->ConfigPeakPercentOutputVoltage(+_maxOutput, -_maxOutput);
    }
    bool headingCheck = StraightDrive->Set(Y, targetHeading, headingTolerance, _maxOutput);

    _previousDistance = currentDistance;

    if ((fabs(distanceError) >= distanceTolerance) || (headingCheck == true))
    {
        _isRunning = true;
    }
    else
    {
        _isRunning = false;
    }
    return _isRunning;
}


}}
