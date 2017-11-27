#include "ctre/phoenix/Motion/ServoZeroTurnWithIMU.h"
#include "HAL/DriverStation.h"
#include <math.h>

namespace CTRE { namespace Motion {

ServoZeroTurnWithImu::ServoZeroTurnWithImu(CTRE::PigeonIMU *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain,
		CTRE::Drive::Styles::Basic selectedStyle, float targetHeading, float headingTolerance,
		ServoParameters *Params, float maxOutput)
{
    _pidgey = pigeonImu;
    _driveTrain = driveTrain;
    _selectedStyle = selectedStyle;

    _targetHeading = targetHeading;
    _headingTolerance = headingTolerance;

    _maxOutput = maxOutput;

    servoParams->P = Params->P;
    servoParams->I = Params->I;
    servoParams->D = Params->D;
}
ServoZeroTurnWithImu::ServoZeroTurnWithImu(CTRE::PigeonIMU *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain, CTRE::Drive::Styles::Basic selectedStyle){
    _selectedStyle = selectedStyle;
    _pidgey = pigeonImu;
    _driveTrain = driveTrain;
}
bool ServoZeroTurnWithImu::Set(float targetHeading, float headingTolerance, float maxOutput){
    _maxOutput = maxOutput;
    return ZeroTurn(targetHeading, headingTolerance);
}
float ServoZeroTurnWithImu::GetImuHeading(){
    double YPR[3];
    _pidgey->GetYawPitchRoll(YPR);
    return (float)YPR[0];
}
void ServoZeroTurnWithImu::OnStart(){
    _isDone = false;
    _isGood = 0;
    _state = 0;
}
void ServoZeroTurnWithImu::OnStop(){
    _driveTrain->Set(CTRE::Drive::Styles::Basic::PercentOutputBasic, 0, 0);
    _isDone = true;
}
bool ServoZeroTurnWithImu::IsDone(){
    return _isDone;
}
void ServoZeroTurnWithImu::OnLoop(){
    switch (_state)
    {
        case 0:
            _pidgey->SetYaw(0.0f);
            _state = 1;
            break;
        case 1:
            bool running = ZeroTurn(_targetHeading, _headingTolerance);

            if (running == true)
                _isGood = 0;
            else if (_isGood < 10)
                ++_isGood;
            else
            {
                _driveTrain->Set(CTRE::Drive::Styles::Basic::PercentOutputBasic, 0, 0);
                _isDone = true;
            }
            break;
    }
}
bool ServoZeroTurnWithImu::ZeroTurn(float targetHeading, float headingTolerance){
    if (servoParams->P == 0 && servoParams->I == 0 && servoParams->D == 0)
    	HAL_SendError(false, 1, false, "CTR: Servo Zero Turn With Imu has no PID values, cannot turn", "", "", true);
    /* Grab the current heading */
    float currentHeading = GetImuHeading();

    /* Grab angular rate from the pigeon */
    double XYZ_Dps[3];
    _pidgey->GetRawGyro(XYZ_Dps);
    float currentAngularRate = (float)XYZ_Dps[2];

    /* Grab Pigeon IMU status */
    bool angleIsGood = (_pidgey->GetState() == CTRE::PigeonIMU::PigeonState::Ready) ? true : false;

    /* Runs ZeroTurn if Pigeon IMU is present and in good health, else do nothing */
    if (angleIsGood == true)
    {
        /* Heading PID */
        float headingError = targetHeading - currentHeading;
        float X = (headingError) * servoParams->P - (currentAngularRate) * servoParams->D;
        X = -X;
        X = fmax(-_maxOutput, fmin(X, _maxOutput));


        /** Set the output of the drivetrain */
        switch (_selectedStyle)
        {
            case CTRE::Drive::Styles::Basic::PercentOutputBasic:
                _driveTrain->Set(CTRE::Drive::Styles::Basic::PercentOutputBasic, 0, X);
                break;
            case CTRE::Drive::Styles::Basic::VoltageBasic:
                _driveTrain->Set(CTRE::Drive::Styles::Basic::VoltageBasic, 0, X);
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
