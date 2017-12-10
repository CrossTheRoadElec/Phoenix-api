#pragma once

#include "ctre/phoenix/Drive/ISmartDrivetrain.h"
#include "ctre/phoenix/Drive/Styles.h"
#include "ctre/phoenix/Stopwatch.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ServoParameters.h"

namespace ctre {
namespace phoenix {
namespace motion {

enum SetValueMotionProfile {
	Disable = 0, Enable = 1, Hold = 2,
};

} // namespace motion
} // namespace phoenix
} // namespace ctre
