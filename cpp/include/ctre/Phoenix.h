#pragma once
#include "ctre/phoenix/CANifier.h"
#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"
#include "ctre/phoenix/MotorControl/Faults.h"
#include "ctre/phoenix/Sensors/PigeonIMU.h"
#include "ctre/phoenix/Tasking/Schedulers/ConcurrentScheduler.h"
#include "ctre/phoenix/Tasking/ILoopable.h"
#include "ctre/phoenix/Tasking/IProcessable.h"
#include "ctre/phoenix/Tasking/ButtonMonitor.h"
#include "ctre/phoenix/LinearInterpolation.h"
#include "ctre/phoenix/HsvToRgb.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/IMotorControllerEnhanced.h"
#include "ctre/phoenix/Signals/MovingAverage.h"

using namespace CTRE;
using namespace CTRE::MotorControl;
using namespace CTRE::Signals;
using namespace CTRE::MotorControl::CAN;
using namespace CTRE::Tasking;
using namespace CTRE::Tasking::Schedulers;
