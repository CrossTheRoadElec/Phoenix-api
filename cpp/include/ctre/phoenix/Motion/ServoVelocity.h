#pragma once

#include "ctre/phoenix/Mechanical/SensoredGearbox.h"
#include "ctre/phoenix/MotorControl/SmartMotorController.h"
#include "ctre/phoenix/Tasking/ILoopable.h"

namespace CTRE { namespace Motion {

class ServoVelocity : public CTRE::Tasking::ILoopable{
public:
	ServoVelocity(CTRE::MotorControl::SmartMotorController *motor,
			CTRE::MotorControl::SmartMotorController::FeedbackDevice feedbackDevice, float velocity);
	ServoVelocity(CTRE::Mechanical::SensoredGearbox *gearbox, float velocity);
	void Set(float targetSpeed, float maxOutput);
	void OnStart();
	void OnStop();
	bool IsDone();
	void OnLoop();

private:
	CTRE::Mechanical::SensoredGearbox *_gearbox;
	float _targetVelocity = 0;
};

}}
