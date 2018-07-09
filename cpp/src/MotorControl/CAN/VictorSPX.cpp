#include "ctre/phoenix/MotorControl/CAN/VictorSPX.h"
#ifndef CTR_EXCLUDE_WPILIB_CLASSES
#include "HAL/HAL.h"
#endif

using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol::can;
/**
 * Constructor
 * @param deviceNumber [0,62]
 */
VictorSPX::VictorSPX(int deviceNumber) :
    BaseMotorController(deviceNumber | 0x01040000) {
#ifndef CTR_EXCLUDE_WPILIB_CLASSES
		HAL_Report(HALUsageReporting::kResourceType_CTRE_future1, deviceNumber + 1);
#endif
	}
