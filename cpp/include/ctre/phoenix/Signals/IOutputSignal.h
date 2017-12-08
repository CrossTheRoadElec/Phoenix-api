#pragma once

namespace CTRE {
namespace Phoenix {
namespace Signals {

class IOutputSignal {
public:
	virtual ~IOutputSignal(){}
	virtual void Set(double value) = 0;
};

} // namespace  Signals
} // namespace Phoenix
} // namespace CTRE
