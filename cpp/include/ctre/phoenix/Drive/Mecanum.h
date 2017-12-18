#pragma once

#include "ctre/phoenix/Mechanical/Gearbox.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "IDrivetrain.h"

namespace ctre {
namespace phoenix {
namespace drive {

class Mecanum: public IDrivetrain {
public:
	Mecanum(ctre::phoenix::motorcontrol::IMotorController *m1,
			ctre::phoenix::motorcontrol::IMotorController *m2,
			ctre::phoenix::motorcontrol::IMotorController *m3,
			ctre::phoenix::motorcontrol::IMotorController *m4);
	Mecanum(ctre::phoenix::mechanical::Gearbox *m1, ctre::Mechanical::Gearbox *m2,
			ctre::phoenix::mechanical::Gearbox *m3, ctre::Mechanical::Gearbox *m4);
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
	ctre::Mechanical::Gearbox *_1;
	ctre::Mechanical::Gearbox *_2;
	ctre::Mechanical::Gearbox *_3;
	ctre::Mechanical::Gearbox *_4;
};

} // namespace drive
} // namespace phoenix
} // namespace ctre
