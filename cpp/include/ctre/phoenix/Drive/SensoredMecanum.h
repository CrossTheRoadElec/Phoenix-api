#pragma once

#include "ctre/phoenix/Mechanical/SensoredGearbox.h"
#include "ctre/phoenix/MotorControl/SmartMotorController.h"
#include "Styles.h"
#include "ISmartDrivetrain.h"

namespace CTRE { namespace Drive {

class SensoredMecanum : public ISmartDrivetrain {
public:
	float distanceBetweenWheels;
	unsigned int ticksPerRev;
	float wheelRadius;

	SensoredMecanum(CTRE::MotorControl::SmartMotorController *m1, CTRE::MotorControl::SmartMotorController *m2, CTRE::MotorControl::SmartMotorController *m3, CTRE::MotorControl::SmartMotorController *m4,
			CTRE::MotorControl::SmartMotorController::FeedbackDevice feedbackDevice, bool useLeftFrontSensor, bool useRightFrontSensor, float wheelRadius);
	SensoredMecanum(CTRE::Mechanical::SensoredGearbox *m1, CTRE::Mechanical::SensoredGearbox *m2, CTRE::Mechanical::SensoredGearbox *m3, CTRE::Mechanical::SensoredGearbox *m4, float wheelRadius);
	void Set(Styles::Smart mode, float forward, float turn);
	void Set(Styles::Basic mode, float forward, float turn);
	void Set(Styles::Smart mode, float forward, float strafe, float turn);
	void Set(Styles::Basic mode, float forward, float strafe, float turn);
	void SetCurrentLimit(unsigned int currentLimitAmps);
	float GetDistance();
	float GetVelocity();
	float GetEncoderHeading();
	void SetPosition(float position);
	void Drive(Styles::Smart mode, float forward, float strafe, float turn);
	void ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage);
	void ConfigPeakPercentOtputVoltage(float forwardVoltage, float reverseVoltage);
	void SetVoltageCompensationRampRate(float RampRate);
	void SetVoltageRampRate(float RampRate);
	void SetMotionMagicAcceleration(float rotationsPerMinPerSec);
	void SetMotionMagicCruiseVelocity(float rotationsPerMin);

private:
	CTRE::Mechanical::SensoredGearbox *_1;
	CTRE::Mechanical::SensoredGearbox *_2;
	CTRE::Mechanical::SensoredGearbox *_3;
	CTRE::Mechanical::SensoredGearbox *_4;
	bool _leftSensor;
	bool _rightSensor;
	float tinyScalar = 1;

	float GetLeftPosition();
	float GetRightPosition();
	float GetLeftVelocity();
	float GetRightVelocity();

};

}}
