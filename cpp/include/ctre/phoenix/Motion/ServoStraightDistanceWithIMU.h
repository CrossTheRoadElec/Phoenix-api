#pragma once

#include "ctre/phoenix/Drive/ISmartDriveTrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/ILoopable.h"
#include "ServoGoStraightWithIMUSmart.h"
#include "ServoParameters.h"

namespace CTRE { namespace Motion {

class ServoStraightDistanceWithImu : public CTRE::ILoopable{
public:
	ServoParameters *straightServoParameters = new ServoParameters();
	ServoParameters *distanceServoParameters = new ServoParameters();
	ServoStraightDistanceWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *drivetrain, CTRE::Drive::Styles::Smart selectedStyle, ServoParameters *straightParameters,
			ServoParameters *distanceParameters, float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance, float maxOutput);
	ServoStraightDistanceWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *drivetrain, CTRE::Drive::Styles::Smart selectedStyle);
	bool Set(float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance, float maxOutput);
	float GetImuHeading();
	float GetEncoderDistance();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
    CTRE::PigeonImu *_pidgey;
    CTRE::Drive::ISmartDrivetrain *_driveTrain;
    CTRE::Drive::Styles::Smart _selectedStyle;
    ServoGoStraightWithImuSmart *StraightDrive;
    Stopwatch *_myStopWatch = new Stopwatch();
    float _targetDistance;
    float _targetHeading;
    float _distanceTolerance;
    float _headingTolerance;
    float _previousDistance;
    float _timeElapsed;
    float _maxOutput;
    bool _isRunning = false;
    bool _isDone = false;
    unsigned char _state = 0;
    unsigned char _isGood = 0;

	bool StraightDistance(float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance);
};

}}
