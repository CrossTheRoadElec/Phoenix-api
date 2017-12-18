#pragma once

#include "ctre/phoenix/Drive/IDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ServoParameters.h"

namespace ctre {
namespace phoenix {
namespace motion {

class ServoGoStraightWithImu: public ctre::phoenix::tasking::ILoopable {
public:
	ServoParameters *servoParameters = new ServoParameters();
	ServoGoStraightWithImu(ctre::phoenix::sensors::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::IDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Basic selectedStyle,
			ServoParameters *parameters, float Y, float targetHeading,
			float headingTolerance, float maxOutput);
	ServoGoStraightWithImu(ctre::phoenix::sensors::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::IDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Basic selectedStyle);
	bool Set(float Y, float targetHeading, float headingTolerance,
			float maxOutput);
	float GetImuHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
	ctre::phoenix::sensors::PigeonIMU *_pidgey;
	ctre::phoenix::drive::IDrivetrain *_driveTrain;
	ctre::phoenix::drive::Styles::Basic _selectedStyle;
	float _Y;
	float _targetHeading;
	float _headingTolerance;
	float _maxOutput;
	bool _isRunning = false;
	bool _isDone = false;
	unsigned char _state = 0;

	bool GoStraight(float Y, float targetHeading, float headingTolerance);
};

} // namespace motion
} // namespace phoenix
} // namespace ctre
