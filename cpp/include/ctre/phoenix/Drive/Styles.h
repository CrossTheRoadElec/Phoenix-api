#pragma once

namespace ctre {
namespace phoenix {
namespace drive {

class Styles {
public:
	enum Smart {
		Voltage = 0, PercentOutput = 1, VelocityClosedLoop = 2
	};
	enum Basic {
		VoltageBasic = 0, PercentOutputBasic = 1
	};
	static Smart Promote(Basic basicStyle) {
		return (Smart) basicStyle;
	}
};

} // namespace drive
} // namespace phoenix
} // namespace ctre
