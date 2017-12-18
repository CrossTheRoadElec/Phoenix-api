//#pragma once
//
//#include "ctre/phoenix/Mechanical/SensoredGearbox.h"
//#include "ctre/phoenix/MotorControl/SmartMotorController.h"
//#include "Styles.h"
//#include "ISmartDrivetrain.h"
//
//namespace ctre { namespace drive {
//
//class SensoredMecanum : public ISmartDrivetrain {
//public:
//	float distanceBetweenWheels;
//	unsigned int ticksPerRev;
//	float wheelRadius;
//
//	SensoredMecanum(ctre::motorcontrol::SmartMotorController *m1, ctre::motorcontrol::SmartMotorController *m2, ctre::motorcontrol::SmartMotorController *m3, ctre::motorcontrol::SmartMotorController *m4,
//			ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice, bool useLeftFrontSensor, bool useRightFrontSensor, float wheelRadius);
//	SensoredMecanum(ctre::Mechanical::SensoredGearbox *m1, ctre::Mechanical::SensoredGearbox *m2, ctre::Mechanical::SensoredGearbox *m3, ctre::Mechanical::SensoredGearbox *m4, float wheelRadius);
//	void Set(Styles::Smart mode, float forward, float turn);
//	void Set(Styles::Basic mode, float forward, float turn);
//	void Set(Styles::Smart mode, float forward, float strafe, float turn);
//	void Set(Styles::Basic mode, float forward, float strafe, float turn);
//	void SetCurrentLimit(unsigned int currentLimitAmps);
//	float GetDistance();
//	float GetVelocity();
//	float GetEncoderHeading();
//	void SetPosition(float position);
//	void Drive(Styles::Smart mode, float forward, float strafe, float turn);
//	void ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage);
//	void ConfigPeakPercentOtputVoltage(float forwardVoltage, float reverseVoltage);
//	void SetVoltageCompensationRampRate(float RampRate);
//	void SetVoltageRampRate(float RampRate);
//	void SetMotionMagicAcceleration(float rotationsPerMinPerSec);
//	void SetMotionMagicCruiseVelocity(float rotationsPerMin);
//
//private:
//	ctre::Mechanical::SensoredGearbox *_1;
//	ctre::Mechanical::SensoredGearbox *_2;
//	ctre::Mechanical::SensoredGearbox *_3;
//	ctre::Mechanical::SensoredGearbox *_4;
//	bool _leftSensor;
//	bool _rightSensor;
//	float tinyScalar = 1;
//
//	float GetLeftPosition();
//	float GetRightPosition();
//	float GetLeftVelocity();
//	float GetRightVelocity();
//
//};
//
//}}
