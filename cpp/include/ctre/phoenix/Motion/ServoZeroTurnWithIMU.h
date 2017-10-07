#pragma once

#include "ctre/phoenix/Drive/ISmartDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/ILoopable.h"
#include "ServoParameters.h"

namespace CTRE { namespace Motion {

class ServoZeroTurnWithImu : public CTRE::ILoopable{
public:
	ServoParameters *servoParams = new ServoParameters();
	ServoZeroTurnWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain,
			CTRE::Drive::Styles::Basic selectedStyle, float targetHeading, float headingTolerance,
			ServoParameters *Params, float maxOutput);
	ServoZeroTurnWithImu(CTRE::PigeonImu *pigeonImu, CTRE::Drive::IDrivetrain *driveTrain, CTRE::Drive::Styles::Basic selectedStyle);
	bool Set(float targetHeading, float headingTolerance, float maxOutput);
	float GetImuHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
    CTRE::PigeonImu *_pidgey;
    CTRE::Drive::IDrivetrain *_driveTrain;
    CTRE::Drive::Styles::Basic _selectedStyle;
    float _targetHeading;
    float _headingTolerance;
    float _maxOutput;
    bool _isRunning = false;
    bool _isDone = false;
    unsigned char _isGood = 0;
    unsigned char _state = 0;

	bool ZeroTurn(float targetHeading, float headingTolerance);
};

}}
