#pragma once

#include "ctre/phoenix/Drive/ISmartDriveTrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ServoGoStraight.h"
#include "ServoParameters.h"

namespace CTRE { namespace Motion {

class ServoStraightDistance : public CTRE::Tasking::ILoopable{
public:
	ServoParameters *straightServoParameters = new ServoParameters();
	ServoParameters *distanceServoParameters = new ServoParameters();

	ServoStraightDistance(CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart selectedStyle, ServoParameters *turnParams,
			ServoParameters *distanceParams, float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance, float maxOutput);
	ServoStraightDistance(CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart selectedStyle);
	bool Set(float targetHeading, float targetDistance, float headingTolerance, float distanceTolerance, float maxOutput);
	float GetEncoderHeading();
	float GetEncoderDistance();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
    CTRE::Drive::ISmartDrivetrain *_driveTrain;
    CTRE::Drive::Styles::Smart _selectedStyle;
    ServoGoStraight *StraightDrive;
    CTRE::Stopwatch *_myStopWatch = new Stopwatch();
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
