#pragma once

#include "ctre/phoenix/MotorControl/SmartMotorController.h"
#include "ctre/phoenix/MotorControl/IFollower.h"
#include "ctre/phoenix/MotorControl/ControlMode.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"

namespace CTRE{ namespace Mechanical{

class SensoredGearbox : public CTRE::Signals::IInvertable {
public:
	CTRE::MotorControl::SmartMotorController *master;
	SensoredGearbox(float gearRatio, CTRE::MotorControl::SmartMotorController *talon, CTRE::MotorControl::SmartMotorController::FeedbackDevice feedbackDevice);
	SensoredGearbox(float gearRatio, CTRE::MotorControl::SmartMotorController *talon, CTRE::MotorControl::IFollower *slave1, CTRE::MotorControl::SmartMotorController::FeedbackDevice feedbackDevice);
	SensoredGearbox(float gearRatio, CTRE::MotorControl::SmartMotorController *talon, CTRE::MotorControl::IFollower *slave1, CTRE::MotorControl::IFollower *slave2, CTRE::MotorControl::SmartMotorController::FeedbackDevice feedbackDevice);
	SensoredGearbox(float gearRatio, CTRE::MotorControl::SmartMotorController *talon, CTRE::MotorControl::IFollower *slave1, CTRE::MotorControl::IFollower *slave2, CTRE::MotorControl::IFollower *slave3, CTRE::MotorControl::SmartMotorController::FeedbackDevice feedbackDevice);

	float GetPosition();
	float GetVelocity();
	void SetCurrentLimit(unsigned int curentLimitAmps);
	void Set(float output);
	void SetControlMode(CTRE::MotorControl::ControlMode::SmartControlMode mode);
	void SetLimits(float forwardLimit, float reverseLimit);
	void DisableLimits();
	void SetInverted(bool invert);
	bool GetInverted() const;
	void InvertSensor(bool invert);
	void SetSensor(float position);
	void ConfigNominalOutputVoltage(float forwardVoltage, float reverseVoltage);
	void ConfigPeakOutputVoltage(float forwardVoltage, float reverseVoltage);
	void SetVoltageCompensationRampRate(float rampRate);
	void SetVoltageRampRate(float rampRate);
	void SetMotionMagicCruiseVelocity(float RPM);
	void SetMotionMagicAcceleration(float RPM);
	CTRE::MotorControl::IMotorController *GetMaster();

private:
	float _gearRatio;
	float _scalar;
	bool _isInverted;
};

}}
