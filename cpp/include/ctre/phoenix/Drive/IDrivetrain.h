#pragma once

#include "Styles.h"

namespace ctre {
namespace phoenix {
namespace drive {

class IDrivetrain {
public:
	virtual ~IDrivetrain(){}
	virtual void Set(Styles::Basic mode, float forward, float turn) = 0;
	virtual void SetVoltageRampRate(float rampRate) = 0;
	virtual void ConfigPeakPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage) = 0;
	virtual void ConfigNominalPercentOutputVoltage(float forwardVoltage,
			float reverseVoltage) = 0;
};

} // namespace drive
} // namespace phoenix
} // namespace ctre
