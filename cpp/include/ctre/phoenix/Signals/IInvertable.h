#pragma once

namespace CTRE{ namespace Signals{

class IInvertable {
public:
	virtual void SetInverted(bool invert) = 0;
	virtual bool GetInverted() const = 0;
};

}}
