#pragma once

namespace CTRE{ namespace Signals{

class IOutputSignal {
public:
	virtual void Set(double value) = 0;
};

}}
