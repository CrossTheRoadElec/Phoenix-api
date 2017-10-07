#pragma once

#include "Styles.h"

namespace CTRE { namespace Drive{

class IDrivetrain{
public:
	virtual void Set(Styles::Basic mode, float forward, float turn) = 0;
	virtual void SetVoltageRampRate(float rampRate) = 0;
	virtual void ConfigPeakPercentOutputVoltage(float forwardVoltage, float reverseVoltage) = 0;
	virtual void ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage) = 0;
};

}}
