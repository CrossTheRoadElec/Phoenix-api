#pragma once

#include "ctre/phoenix/Drive/IDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/ILoopable.h"
#include "ServoParameters.h"


namespace CTRE { namespace Motion {

class ServoGoStraightWithImu : public CTRE::ILoopable{
public:
	ServoParameters *servoParameters = new ServoParameters();
	ServoGoStraightWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain, CTRE::Drive::Styles::Basic selectedStyle,
			ServoParameters *parameters, float Y, float targetHeading, float headingTolerance, float maxOutput);
	ServoGoStraightWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain, CTRE::Drive::Styles::Basic selectedStyle);
	bool Set(float Y, float targetHeading, float headingTolerance, float maxOutput);
	float GetImuHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
    CTRE::PigeonImu *_pidgey;
    CTRE::Drive::IDrivetrain *_driveTrain;
    CTRE::Drive::Styles::Basic _selectedStyle;
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
