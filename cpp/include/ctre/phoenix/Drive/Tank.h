#pragma once

#include "ctre/phoenix/Mechanical/Gearbox.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "IDrivetrain.h"
#include "Styles.h"

namespace ctre {
namespace phoenix {
namespace drive {

class Tank: public IDrivetrain {
public:
	Tank(ctre::phoenix::mechanical::Gearbox *left, ctre::Mechanical::Gearbox *right,
			bool leftInvert, bool rightInvert);
	Tank(ctre::phoenix::motorcontrol::IMotorController *left,
			ctre::phoenix::motorcontrol::IMotorController *right, bool leftInvert,
			bool rightInvert);
	void Set(Styles::Basic mode, float forward, float turn);
	void SetVoltageRampRate(float rampRate);
	void SetVoltageCompensationRampRate(float rampRate);
	void ConfigPeakPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);
	void ConfigNominalPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);

private:
	ctre::phoenix::mechanical::Gearbox *_left;
	ctre::phoenix::mechanical::Gearbox *_right;
	void Drive(Styles::Basic mode, float left, float right);
};

} // namespace drive
} // namespace phoenix
} // namespace ctre

