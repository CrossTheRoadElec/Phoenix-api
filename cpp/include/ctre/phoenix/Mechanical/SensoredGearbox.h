//#pragma once
//
//#include "ctre/phoenix/MotorControl/SmartMotorController.h"
//#include "ctre/phoenix/MotorControl/IFollower.h"
//#include "ctre/phoenix/MotorControl/ControlMode.h"
//#include "ctre/phoenix/MotorControl/IMotorController.h"
//
//namespace ctre{ namespace mechanical{
//
//class SensoredGearbox : public ctre::signals::IInvertable {
//public:
//	ctre::motorcontrol::SmartMotorController *master;
//	SensoredGearbox(float gearRatio, ctre::motorcontrol::SmartMotorController *talon, ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice);
//	SensoredGearbox(float gearRatio, ctre::motorcontrol::SmartMotorController *talon, ctre::motorcontrol::IFollower *slave1, ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice);
//	SensoredGearbox(float gearRatio, ctre::motorcontrol::SmartMotorController *talon, ctre::motorcontrol::IFollower *slave1, ctre::motorcontrol::IFollower *slave2, ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice);
//	SensoredGearbox(float gearRatio, ctre::motorcontrol::SmartMotorController *talon, ctre::motorcontrol::IFollower *slave1, ctre::motorcontrol::IFollower *slave2, ctre::motorcontrol::IFollower *slave3, ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice);
//
//	float GetPosition();
//	float GetVelocity();
//	void SetCurrentLimit(unsigned int curentLimitAmps);
//	void Set(float output);
//	void SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode mode);
//	void SetLimits(float forwardLimit, float reverseLimit);
//	void DisableLimits();
//	void SetInverted(bool invert);
//	bool GetInverted() const;
//	void InvertSensor(bool invert);
//	void SetSensor(float position);
//	void ConfigNominalOutputVoltage(float forwardVoltage, float reverseVoltage);
//	void ConfigPeakOutputVoltage(float forwardVoltage, float reverseVoltage);
//	void SetVoltageCompensationRampRate(float rampRate);
//	void SetVoltageRampRate(float rampRate);
//	void SetMotionMagicCruiseVelocity(float RPM);
//	void SetMotionMagicAcceleration(float RPM);
//	ctre::motorcontrol::IMotorController *GetMaster();
//
//private:
//	float _gearRatio;
//	float _scalar;
//	bool _isInverted;
//};
//
//}}
