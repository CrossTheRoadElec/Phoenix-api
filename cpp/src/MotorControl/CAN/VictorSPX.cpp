#include "ctre/phoenix/MotorControl/CAN/VictorSPX.h"
#if defined(CTR_INCLUDE_WPILIB_CLASSES) || defined(__FRC_ROBORIO__)
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
#if defined(CTR_INCLUDE_WPILIB_CLASSES) || defined(__FRC_ROBORIO__)
		HAL_Report(HALUsageReporting::kResourceType_CTRE_future1, deviceNumber + 1);
#endif
	}
