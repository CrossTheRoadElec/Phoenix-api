#pragma once
#include "ctre/phoenix/CANifier.h"
#include "ctre/phoenix/ErrorCode.h"
#include "ctre/phoenix/paramEnum.h"
#include "ctre/phoenix/HsvToRgb.h"
#include "ctre/phoenix/LinearInterpolation.h"
#include "ctre/phoenix/motion/MotionProfileStatus.h"
#include "ctre/phoenix/motion/TrajectoryPoint.h"
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
#include "ctre/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h"
#include "ctre/phoenix/motorcontrol/DemandType.h"
#include "ctre/phoenix/motorcontrol/Faults.h"
#include "ctre/phoenix/motorcontrol/FollowerType.h"
#include "ctre/phoenix/motorcontrol/SensorCollection.h"
#include "ctre/phoenix/motorcontrol/IMotorController.h"
#include "ctre/phoenix/motorcontrol/IMotorControllerEnhanced.h"
#include "ctre/phoenix/sensors/PigeonIMU.h"
#include "ctre/phoenix/signals/MovingAverage.h"
#include "ctre/phoenix/tasking/Schedulers/ConcurrentScheduler.h"
#include "ctre/phoenix/tasking/ILoopable.h"
#include "ctre/phoenix/tasking/IProcessable.h"
#include "ctre/phoenix/tasking/ButtonMonitor.h"
#include "ctre/phoenix/Utilities.h"

using namespace ctre;
using namespace ctre::phoenix;
using namespace ctre::phoenix::motion;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::sensors;
using namespace ctre::phoenix::signals;
using namespace ctre::phoenix::tasking;
using namespace ctre::phoenix::tasking::schedulers;
