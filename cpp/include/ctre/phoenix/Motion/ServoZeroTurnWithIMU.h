#pragma once

#include "ctre/phoenix/Drive/ISmartDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ServoParameters.h"

namespace ctre {
namespace phoenix {
namespace motion {

class ServoZeroTurnWithImu: public ctre::phoenix::tasking::ILoopable {
public:
	ServoParameters *servoParams = new ServoParameters();
	ServoZeroTurnWithImu(ctre::phoenix::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::IDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Basic selectedStyle, float targetHeading,
			float headingTolerance, ServoParameters *Params, float maxOutput);
	ServoZeroTurnWithImu(ctre::phoenix::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::IDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Basic selectedStyle);
	bool Set(float targetHeading, float headingTolerance, float maxOutput);
	float GetImuHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
	ctre::phoenix::PigeonIMU *_pidgey;
	ctre::phoenix::drive::IDrivetrain *_driveTrain;
	ctre::phoenix::drive::Styles::Basic _selectedStyle;
	float _targetHeading;
	float _headingTolerance;
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

