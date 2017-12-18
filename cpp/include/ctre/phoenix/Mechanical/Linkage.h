//#pragma once
//
//#include "ctre/phoenix/MotorControl/IMotorController.h"
//#include "ctre/phoenix/MotorControl/IFollower.h"
////#include "ctrlib/MotorControl/ControlMode.h"
//#include "ctre/phoenix/Signals/IInvertable.h"
//#include "ctre/phoenix/Signals/IOutputSignal.h"
//
//namespace ctre{ namespace mechanical{
//
//class Linkage
//		: ctre::signals::IOutputSignal,
//		  ctre::signals::IInvertable{
//public:
//	Linkage(ctre::phoenix::motorcontrol::IMotorController *mc1);
//	Linkage(ctre::phoenix::motorcontrol::IMotorController *mc1, ctre::motorcontrol::IFollower *mc2);
//	Linkage(ctre::phoenix::motorcontrol::IMotorController *mc1, ctre::motorcontrol::IFollower *mc2, ctre::motorcontrol::IFollower *mc3);
//	Linkage(ctre::phoenix::motorcontrol::IMotorController *mc1, ctre::motorcontrol::IFollower *mc2, ctre::motorcontrol::IFollower *mc3, ctre::motorcontrol::IFollower *mc4);
//	void Set(double ouput);
//	void SetControlMode(ctre::motorcontrol::ControlMode::BasicControlMode mode);
//	void SetInverted(bool invert);
//	bool GetInverted() const;
//	void SetVoltageRampRate(float rampRate);
//	void SetVoltageCompensationRate(float rampRate);
//	void ConfigNominalOutputVoltage(float forwardVoltage, float reverseVoltage);
//	void ConfigPeakOutputVoltage(float forwardVoltage, float reverseVoltage);
//	ctre::motorcontrol::IMotorController *GetMaster();
//
//private:
//	ctre::motorcontrol::IMotorController *_motor = nullptr;
//	ctre::motorcontrol::IFollower *_follower[3];
//	int _followerCount = 0;
//	bool _isInverted = 0;
//	void Setup();
//};
//
//}}
