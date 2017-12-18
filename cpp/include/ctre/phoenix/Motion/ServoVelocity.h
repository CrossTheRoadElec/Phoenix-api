//#pragma once
//
//#include "ctre/phoenix/Mechanical/SensoredGearbox.h"
//#include "ctre/phoenix/MotorControl/SmartMotorController.h"
//#include "ctre/phoenix/Tasking/ILoopable.h"
//
//namespace ctre { namespace motion {
//
//class ServoVelocity : public ctre::tasking::ILoopable{
//public:
//	ServoVelocity(ctre::motorcontrol::SmartMotorController *motor,
//			ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice, float velocity);
//	ServoVelocity(ctre::Mechanical::SensoredGearbox *gearbox, float velocity);
//	void Set(float targetSpeed, float maxOutput);
//	void OnStart();
//	void OnStop();
//	bool IsDone();
//	void OnLoop();
//
//private:
//	ctre::Mechanical::SensoredGearbox *_gearbox;
//	float _targetVelocity = 0;
//};
//
//}}
