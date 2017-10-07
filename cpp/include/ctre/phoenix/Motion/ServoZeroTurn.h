#pragma once

#include "ctre/phoenix/Drive/ISmartDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/ILoopable.h"
#include "ServoParameters.h"

namespace CTRE { namespace Motion {

class ServoZeroTurn : public CTRE::ILoopable{
public:
    ServoParameters *servoParams = new ServoParameters();
	ServoZeroTurn(CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart smartStyle,
			float targetHeading, float headingTolerance, ServoParameters *Params, float maxOutput);
	ServoZeroTurn(CTRE::Drive::ISmartDrivetrain *driveTrain, CTRE::Drive::Styles::Smart smartStyle);
	bool Set(float targetHeading, float headingTolerance, float maxOutput);
	float GetEncoderHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
    CTRE::Drive::ISmartDrivetrain *_driveTrain;
    CTRE::Drive::Styles::Smart _selectedStyle;
    CTRE::Stopwatch *_myStopwatch = new Stopwatch();
    float _targetHeading;
    float _headingTolerance;
    float _previousHeading;
    float _timeElapsed;
    float _maxOutput;
    bool _isRunning = false;
    bool _isDone = false;
    unsigned char _isGood = 0;
    unsigned char _state = 0;

	bool ZeroTurn(float targetHeading, float headingTolerance);
};

}}
