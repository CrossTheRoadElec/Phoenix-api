#pragma once

#include "ctre/phoenix/Drive/ISmartDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/ILoopable.h"
#include "ServoParameters.h"

namespace CTRE { namespace Motion {

class ServoGoStraightWithImuSmart : public CTRE::ILoopable{
public:
	ServoParameters *servoParameters = new ServoParameters();
	ServoGoStraightWithImuSmart(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart selectedStyle,
			ServoParameters *straightParameters, float Y, float targetHeading, float headingTolerance, float maxOutput);
	ServoGoStraightWithImuSmart(CTRE::PigeonImu *pigeonImu, CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart selectedStyle);
	bool Set(float Y, float targetHeading, float headingTolerance, float maxOutput);
	float GetImuHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
    CTRE::PigeonImu *_pidgey;
    CTRE::Drive::ISmartDrivetrain *_driveTrain;
    CTRE::Drive::Styles::Smart _selectedStyle;
    float _Y;
    float _targetHeading;
    float _headingTolerance;
    float _maxOutput;
    bool _isRunning = false;
    bool _isDone = false;
    unsigned char _state = 0;

	bool GoStraight(float Y, float targetHeading, float headingTolerance);
};

}}
