#pragma once

#include "ctre/phoenix/Mechanical/Gearbox.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "IDrivetrain.h"

namespace CTRE {
namespace Phoenix {
namespace Drive {

class Mecanum: public IDrivetrain {
public:
	Mecanum(CTRE::MotorControl::IMotorController *m1,
			CTRE::MotorControl::IMotorController *m2,
			CTRE::MotorControl::IMotorController *m3,
			CTRE::MotorControl::IMotorController *m4);
	Mecanum(CTRE::Mechanical::Gearbox *m1, CTRE::Mechanical::Gearbox *m2,
			CTRE::Mechanical::Gearbox *m3, CTRE::Mechanical::Gearbox *m4);
	void Set(Styles::Basic mode, float forward, float turn);
	void Set(Styles::Basic mode, float forward, float strafe, float turn);
	void SetVoltageRampRate(float rampRate);
	void SetVoltageCompensationRampRate(float rampRate);
	void ConfigPeakPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);
	void ConfigNominalPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);
	void Drive(Styles::Basic mode, float forward, float strafe, float turn);

private:
	CTRE::Mechanical::Gearbox *_1;
	CTRE::Mechanical::Gearbox *_2;
	CTRE::Mechanical::Gearbox *_3;
	CTRE::Mechanical::Gearbox *_4;
};

} // namespace Drive
} // namespace Phoenix
} // namespace CTRE
