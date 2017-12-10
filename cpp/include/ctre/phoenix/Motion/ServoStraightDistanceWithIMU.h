#pragma once

#include "ctre/phoenix/Drive/ISmartDriveTrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ServoGoStraightWithIMUSmart.h"
#include "ServoParameters.h"

namespace ctre {
namespace phoenix {
namespace motion {

class ServoStraightDistanceWithImu: public ctre::phoenix::tasking::ILoopable {
public:
	ServoParameters *straightServoParameters = new ServoParameters();
	ServoParameters *distanceServoParameters = new ServoParameters();
	ServoStraightDistanceWithImu(ctre::phoenix::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::ISmartDrivetrain *drivetrain,
			ctre::phoenix::drive::Styles::Smart selectedStyle,
			ServoParameters *straightParameters,
			ServoParameters *distanceParameters, float targetHeading,
			float targetDistance, float headingTolerance,
			float distanceTolerance, float maxOutput);
	ServoStraightDistanceWithImu(ctre::phoenix::PigeonIMU *pigeonImu,
			ctre::phoenix::drive::ISmartDrivetrain *drivetrain,
			ctre::phoenix::drive::Styles::Smart selectedStyle);
	bool Set(float targetHeading, float targetDistance, float headingTolerance,
			float distanceTolerance, float maxOutput);
	float GetImuHeading();
	float GetEncoderDistance();
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
	ctre::phoenix::PigeonIMU *_pidgey;
	ctre::phoenix::drive::ISmartDrivetrain *_driveTrain;
	ctre::phoenix::drive::Styles::Smart _selectedStyle;
	ServoGoStraightWithImuSmart *StraightDrive;
	Stopwatch *_myStopWatch = new Stopwatch();
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

	bool StraightDistance(float targetHeading, float targetDistance,
			float headingTolerance, float distanceTolerance);
};

} // namespace motion
} // namespace phoenix
} // namespace ctre
