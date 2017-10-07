#pragma once

#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/IFollower.h"
//#include "ctrlib/MotorControl/ControlMode.h"
#include "ctre/phoenix/Signals/IInvertable.h"
#include "ctre/phoenix/Signals/IOutputSignal.h"

namespace CTRE{ namespace Mechanical{

class Linkage
		: CTRE::Signals::IOutputSignal,
		  CTRE::Signals::IInvertable{
public:
	Linkage(CTRE::MotorControl::IMotorController *mc1);
	Linkage(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2);
	Linkage(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3);
	Linkage(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3, CTRE::MotorControl::IFollower *mc4);
	void Set(double ouput);
	void SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode mode);
	void SetInverted(bool invert);
	bool GetInverted() const;
	void SetVoltageRampRate(float rampRate);
	void SetVoltageCompensationRate(float rampRate);
	void ConfigNominalOutputVoltage(float forwardVoltage, float reverseVoltage);
	void ConfigPeakOutputVoltage(float forwardVoltage, float reverseVoltage);
	CTRE::MotorControl::IMotorController *GetMaster();

private:
	CTRE::MotorControl::IMotorController *_motor = nullptr;
	CTRE::MotorControl::IFollower *_follower[3];
	int _followerCount = 0;
	bool _isInverted = 0;
	void Setup();
};

}}
