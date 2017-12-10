#pragma once

#include "ctre/phoenix/Mechanical/SensoredGearbox.h"
#include "ctre/phoenix/MotorControl/SmartMotorController.h"
#include "Styles.h"
#include "ISmartDrivetrain.h"

namespace ctre {
namespace phoenix {
namespace drive {

class SensoredTank: public ISmartDrivetrain {
public:
	float distanceBetweenWheels;
	unsigned int ticksPerRev;
	float wheelRadius;

	SensoredTank(ctre::phoenix::mechanical::SensoredGearbox *left,
			ctre::phoenix::mechanical::SensoredGearbox *right, bool leftInverted,
			bool rightInverted, float wheelRadius);
	SensoredTank(ctre::phoenix::motorcontrol::SmartMotorController *left,
			ctre::phoenix::motorcontrol::SmartMotorController *right,
			ctre::phoenix::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice,
			bool leftInverted, bool rightInverted, float wheelRadius);
	void Set(Styles::Smart mode, float forward, float turn);
	void Set(Styles::Basic mode, float forward, float turn);
	void SetCurrentLimit(unsigned int currentAmps);
	float GetDistance();
	float GetVelocity();
	float GetEncoderHeading();
	void SetPosition(float position);
	void ConfigNominalPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);
	void ConfigPeakPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);
	void SetVoltageCompensationRampRate(float rampRate);
	void SetVoltageRampRate(float rampRate);
	void SetMotionMagicAcceleration(float rotationsPerMinPerSec);
	void SetMotionMagicCruiseVelocity(float rotationsPerMin);

private:
	ctre::phoenix::mechanical::SensoredGearbox *_left;
	ctre::phoenix::mechanical::SensoredGearbox *_right;
	float tinyScalor = 1;

	void Drive(Styles::Smart mode, float left, float right);

};

} // namespace drive
} // namespace phoenix
} // namespace ctre
