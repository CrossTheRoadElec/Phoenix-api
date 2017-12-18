#pragma once

#include "ctre/phoenix/Drive/ISmartDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ServoParameters.h"

namespace ctre {
namespace phoenix {
namespace motion {

class ServoZeroTurn: public ctre::phoenix::tasking::ILoopable {
public:
	ServoParameters *servoParams = new ServoParameters();
	ServoZeroTurn(ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Smart smartStyle, float targetHeading,
			float headingTolerance, ServoParameters *Params, float maxOutput);
	ServoZeroTurn(ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Smart smartStyle);
	bool Set(float targetHeading, float headingTolerance, float maxOutput);
	float GetEncoderHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
	ctre::phoenix::drive::ISmartDrivetrain *_driveTrain;
	ctre::phoenix::drive::Styles::Smart _selectedStyle;
	ctre::phoenix::Stopwatch *_myStopwatch = new Stopwatch();
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

} // namespace motion
} // namespace phoenix
} // namespace ctre
