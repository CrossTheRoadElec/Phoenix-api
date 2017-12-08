#pragma once

namespace CTRE {
namespace Phoenix {
namespace Signals {

class IInvertable {
public:
	virtual ~IInvertable(){}
	virtual void SetInverted(bool invert) = 0;
	virtual bool GetInverted() const = 0;
};

} // namespace  Signals
} // namespace Phoenix
} // namespace CTRE
