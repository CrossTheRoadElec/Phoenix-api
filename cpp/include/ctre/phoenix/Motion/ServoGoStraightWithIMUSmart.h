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

class ServoGoStraightWithImuSmart: public ctre::phoenix::tasking::ILoopable {
public:
	ServoParameters *servoParameters = new ServoParameters();
	ServoGoStraightWithImuSmart(ctre::phoenix::sensors::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Smart selectedStyle,
			ServoParameters *straightParameters, float Y, float targetHeading,
			float headingTolerance, float maxOutput);
	ServoGoStraightWithImuSmart(ctre::phoenix::sensors::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::ISmartDrivetrain *driveTrain,
			ctre::phoenix::drive::Styles::Smart selectedStyle);
	bool Set(float Y, float targetHeading, float headingTolerance,
			float maxOutput);
	float GetImuHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
	ctre::phoenix::sensors::PigeonIMU *_pidgey;
	ctre::phoenix::drive::ISmartDrivetrain *_driveTrain;
	ctre::phoenix::drive::Styles::Smart _selectedStyle;
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
