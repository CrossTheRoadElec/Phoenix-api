#pragma once

#include "ctre/phoenix/Drive/IDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ServoParameters.h"

namespace CTRE {
namespace Phoenix {
namespace Motion {

class ServoGoStraightWithImu: public CTRE::Phoenix::Tasking::ILoopable {
public:
	ServoParameters *servoParameters = new ServoParameters();
	ServoGoStraightWithImu(CTRE::PigeonIMU *pigeonImu,
			CTRE::Drive::IDrivetrain *driveTrain,
			CTRE::Drive::Styles::Basic selectedStyle,
			ServoParameters *parameters, float Y, float targetHeading,
			float headingTolerance, float maxOutput);
	ServoGoStraightWithImu(CTRE::PigeonIMU *pigeonImu,
			CTRE::Drive::IDrivetrain *driveTrain,
			CTRE::Drive::Styles::Basic selectedStyle);
	bool Set(float Y, float targetHeading, float headingTolerance,
			float maxOutput);
	float GetImuHeading();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
	CTRE::Phoenix::PigeonIMU *_pidgey;
	CTRE::Phoenix::Drive::IDrivetrain *_driveTrain;
	CTRE::Phoenix::Drive::Styles::Basic _selectedStyle;
	float _Y;
	float _targetHeading;
	float _headingTolerance;
	float _maxOutput;
	bool _isRunning = false;
	bool _isDone = false;
	unsigned char _state = 0;

	bool GoStraight(float Y, float targetHeading, float headingTolerance);
};

} // namespace Motion
} // namespace Phoenix
} // namespace CTRE
