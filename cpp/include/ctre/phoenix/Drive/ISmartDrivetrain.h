#pragma once

#include "Styles.h"
#include "IDrivetrain.h"

namespace CTRE {
namespace Phoenix {
namespace Drive {

class ISmartDrivetrain: public IDrivetrain {
public:
	virtual ~ISmartDrivetrain(){}
	virtual void Set(Styles::Smart mode, float forward, float reverse) = 0;
	virtual void SetCurrentLimit(unsigned int currentLimitAmps) = 0;
	virtual float GetDistance() = 0;
	virtual float GetVelocity() = 0;
	virtual float GetEncoderHeading() = 0;
	virtual void SetPosition(float position) = 0;
};

} // namespace Drive
} // namespace Phoenix
} // namespace CTRE
