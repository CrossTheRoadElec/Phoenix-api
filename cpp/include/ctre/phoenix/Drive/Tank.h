#pragma once

#include "ctre/phoenix/Mechanical/Gearbox.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "IDrivetrain.h"
#include "Styles.h"

namespace CTRE {
namespace Phoenix {
namespace Drive {

class Tank: public IDrivetrain {
public:
	Tank(CTRE::Mechanical::Gearbox *left, CTRE::Mechanical::Gearbox *right,
			bool leftInvert, bool rightInvert);
	Tank(CTRE::MotorControl::IMotorController *left,
			CTRE::MotorControl::IMotorController *right, bool leftInvert,
			bool rightInvert);
	void Set(Styles::Basic mode, float forward, float turn);
	void SetVoltageRampRate(float rampRate);
	void SetVoltageCompensationRampRate(float rampRate);
	void ConfigPeakPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);
	void ConfigNominalPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage);

private:
	CTRE::Mechanical::Gearbox *_left;
	CTRE::Mechanical::Gearbox *_right;
	void Drive(Styles::Basic mode, float left, float right);
};

} // namespace Drive
} // namespace Phoenix
} // namespace CTRE

