#include <gtest/gtest.h>
#include "ConfigHelper.h"
#include "ctre/phoenix/platform/Platform.h"
#include <chrono>
#include <thread>

std::string baseErrString = "Failed due to error from ";

TEST(Error, ConfigSetTimeoutError) {
    int id = 0;
    int timeoutMs = 1;
    
    ctre::phoenix::motorcontrol::can::TalonSRXConfiguration testTalonConfigs;
    ctre::phoenix::motorcontrol::can::VictorSPXConfiguration testVictorConfigs;
    ctre::phoenix::sensors::PigeonIMUConfiguration testPigeonConfigs;
    ctre::phoenix::CANifierConfiguration testCANifierConfigs;
  
    std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> tempVector;
    std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> errorCodes;
 
    tempVector = ConfigAllIndividualTalon( id,  timeoutMs, testTalonConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigAllIndividualVictor( id,  timeoutMs, testVictorConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigAllIndividualPigeon( id,  timeoutMs, testPigeonConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigAllIndividualCANifier( id,  timeoutMs, testCANifierConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigFactoryDefaultTalon( id,  timeoutMs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigFactoryDefaultVictor( id,  timeoutMs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigFactoryDefaultPigeon( id,  timeoutMs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigFactoryDefaultCANifier( id,  timeoutMs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigAllTalon( id,  timeoutMs, testTalonConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigAllVictor( id,  timeoutMs, testVictorConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigAllPigeon( id,  timeoutMs, testPigeonConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    tempVector = ConfigAllCANifier( id,  timeoutMs, testCANifierConfigs);
    errorCodes.insert(errorCodes.end(), tempVector.begin(), tempVector.end());

    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }
}

TEST(Error, GetParamTimeoutError) {

    //While we shouldn't expect different behavior from diff enums, might as well
    std::vector<ctre::phoenix::ParamEnum> allParamEnums = {
    ctre::phoenix::ParamEnum::eOnBoot_BrakeMode,
    ctre::phoenix::ParamEnum::eQuadFilterEn,
    ctre::phoenix::ParamEnum::eQuadIdxPolarity,
    ctre::phoenix::ParamEnum::eMotionProfileHasUnderrunErr,
    ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs,
    ctre::phoenix::ParamEnum::eStatusFramePeriod,
    ctre::phoenix::ParamEnum::eOpenloopRamp,
    ctre::phoenix::ParamEnum::eClosedloopRamp,
    ctre::phoenix::ParamEnum::eNeutralDeadband,
    ctre::phoenix::ParamEnum::ePeakPosOutput,
    ctre::phoenix::ParamEnum::eNominalPosOutput,
    ctre::phoenix::ParamEnum::ePeakNegOutput,
    ctre::phoenix::ParamEnum::eNominalNegOutput,
    ctre::phoenix::ParamEnum::eProfileParamSlot_P,
    ctre::phoenix::ParamEnum::eProfileParamSlot_I,
    ctre::phoenix::ParamEnum::eProfileParamSlot_D,
    ctre::phoenix::ParamEnum::eProfileParamSlot_F,
    ctre::phoenix::ParamEnum::eProfileParamSlot_IZone,
    ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr,
    ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum,
    ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput,
    ctre::phoenix::ParamEnum::eClearPositionOnLimitF,
    ctre::phoenix::ParamEnum::eClearPositionOnLimitR,
    ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx,
    ctre::phoenix::ParamEnum::eSampleVelocityPeriod,
    ctre::phoenix::ParamEnum::eSampleVelocityWindow,
    ctre::phoenix::ParamEnum::eFeedbackSensorType,
    ctre::phoenix::ParamEnum::eSelectedSensorPosition,
    ctre::phoenix::ParamEnum::eFeedbackNotContinuous,
    ctre::phoenix::ParamEnum::eRemoteSensorSource,
    ctre::phoenix::ParamEnum::eRemoteSensorDeviceID,
    ctre::phoenix::ParamEnum::eSensorTerm,
    ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS,
    ctre::phoenix::ParamEnum::ePIDLoopPolarity,
    ctre::phoenix::ParamEnum::ePIDLoopPeriod,
    ctre::phoenix::ParamEnum::eSelectedSensorCoefficient,
    ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold,
    ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold,
    ctre::phoenix::ParamEnum::eForwardSoftLimitEnable,
    ctre::phoenix::ParamEnum::eReverseSoftLimitEnable,
    ctre::phoenix::ParamEnum::eNominalBatteryVoltage,
    ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize,
    ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps,
    ctre::phoenix::ParamEnum::ePeakCurrentLimitMs,
    ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps,
    ctre::phoenix::ParamEnum::eClosedLoopIAccum,
    ctre::phoenix::ParamEnum::eCustomParam,
    ctre::phoenix::ParamEnum::eStickyFaults,
    ctre::phoenix::ParamEnum::eAnalogPosition,
    ctre::phoenix::ParamEnum::eQuadraturePosition,
    ctre::phoenix::ParamEnum::ePulseWidthPosition,
    ctre::phoenix::ParamEnum::eMotMag_Accel,
    ctre::phoenix::ParamEnum::eMotMag_VelCruise,
    ctre::phoenix::ParamEnum::eLimitSwitchSource,
    ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis,
    ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS,
    ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID,
    ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS,
    ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot,
    ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz,
    ctre::phoenix::ParamEnum::eYawOffset,
    ctre::phoenix::ParamEnum::eCompassOffset,
    ctre::phoenix::ParamEnum::eBetaGain,
    ctre::phoenix::ParamEnum::eEnableCompassFusion,
    ctre::phoenix::ParamEnum::eGyroNoMotionCal,
    ctre::phoenix::ParamEnum::eEnterCalibration,
    ctre::phoenix::ParamEnum::eFusedHeadingOffset,
    ctre::phoenix::ParamEnum::eStatusFrameRate,
    ctre::phoenix::ParamEnum::eAccumZ,
    ctre::phoenix::ParamEnum::eTempCompDisable,
    ctre::phoenix::ParamEnum::eMotionMeas_tap_threshX,
    ctre::phoenix::ParamEnum::eMotionMeas_tap_threshY,
    ctre::phoenix::ParamEnum::eMotionMeas_tap_threshZ,
    ctre::phoenix::ParamEnum::eMotionMeas_tap_count,
    ctre::phoenix::ParamEnum::eMotionMeas_tap_time,
    ctre::phoenix::ParamEnum::eMotionMeas_tap_time_multi,
    ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_thresh,
    ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_time,
    ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_timeout,
    ctre::phoenix::ParamEnum::eDefaultConfig
    };
    
    std::vector<std::string> allParamEnumStrings = {
    "ctre::phoenix::ParamEnum::eOnBoot_BrakeMode",
    "ctre::phoenix::ParamEnum::eQuadFilterEn",
    "ctre::phoenix::ParamEnum::eQuadIdxPolarity",
    "ctre::phoenix::ParamEnum::eMotionProfileHasUnderrunErr",
    "ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs",
    "ctre::phoenix::ParamEnum::eStatusFramePeriod",
    "ctre::phoenix::ParamEnum::eOpenloopRamp",
    "ctre::phoenix::ParamEnum::eClosedloopRamp",
    "ctre::phoenix::ParamEnum::eNeutralDeadband",
    "ctre::phoenix::ParamEnum::ePeakPosOutput",
    "ctre::phoenix::ParamEnum::eNominalPosOutput",
    "ctre::phoenix::ParamEnum::ePeakNegOutput",
    "ctre::phoenix::ParamEnum::eNominalNegOutput",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_P",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_I",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_D",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_F",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_IZone",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum",
    "ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput",
    "ctre::phoenix::ParamEnum::eClearPositionOnLimitF",
    "ctre::phoenix::ParamEnum::eClearPositionOnLimitR",
    "ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx",
    "ctre::phoenix::ParamEnum::eSampleVelocityPeriod",
    "ctre::phoenix::ParamEnum::eSampleVelocityWindow",
    "ctre::phoenix::ParamEnum::eFeedbackSensorType",
    "ctre::phoenix::ParamEnum::eSelectedSensorPosition",
    "ctre::phoenix::ParamEnum::eFeedbackNotContinuous",
    "ctre::phoenix::ParamEnum::eRemoteSensorSource",
    "ctre::phoenix::ParamEnum::eRemoteSensorDeviceID",
    "ctre::phoenix::ParamEnum::eSensorTerm",
    "ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS",
    "ctre::phoenix::ParamEnum::ePIDLoopPolarity",
    "ctre::phoenix::ParamEnum::ePIDLoopPeriod",
    "ctre::phoenix::ParamEnum::eSelectedSensorCoefficient",
    "ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold",
    "ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold",
    "ctre::phoenix::ParamEnum::eForwardSoftLimitEnable",
    "ctre::phoenix::ParamEnum::eReverseSoftLimitEnable",
    "ctre::phoenix::ParamEnum::eNominalBatteryVoltage",
    "ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize",
    "ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps",
    "ctre::phoenix::ParamEnum::ePeakCurrentLimitMs",
    "ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps",
    "ctre::phoenix::ParamEnum::eClosedLoopIAccum",
    "ctre::phoenix::ParamEnum::eCustomParam",
    "ctre::phoenix::ParamEnum::eStickyFaults",
    "ctre::phoenix::ParamEnum::eAnalogPosition",
    "ctre::phoenix::ParamEnum::eQuadraturePosition",
    "ctre::phoenix::ParamEnum::ePulseWidthPosition",
    "ctre::phoenix::ParamEnum::eMotMag_Accel",
    "ctre::phoenix::ParamEnum::eMotMag_VelCruise",
    "ctre::phoenix::ParamEnum::eLimitSwitchSource",
    "ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis",
    "ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS",
    "ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID",
    "ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS",
    "ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot",
    "ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz",
    "ctre::phoenix::ParamEnum::eYawOffset",
    "ctre::phoenix::ParamEnum::eCompassOffset",
    "ctre::phoenix::ParamEnum::eBetaGain",
    "ctre::phoenix::ParamEnum::eEnableCompassFusion",
    "ctre::phoenix::ParamEnum::eGyroNoMotionCal",
    "ctre::phoenix::ParamEnum::eEnterCalibration",
    "ctre::phoenix::ParamEnum::eFusedHeadingOffset",
    "ctre::phoenix::ParamEnum::eStatusFrameRate",
    "ctre::phoenix::ParamEnum::eAccumZ",
    "ctre::phoenix::ParamEnum::eTempCompDisable",
    "ctre::phoenix::ParamEnum::eMotionMeas_tap_threshX",
    "ctre::phoenix::ParamEnum::eMotionMeas_tap_threshY",
    "ctre::phoenix::ParamEnum::eMotionMeas_tap_threshZ",
    "ctre::phoenix::ParamEnum::eMotionMeas_tap_count",
    "ctre::phoenix::ParamEnum::eMotionMeas_tap_time",
    "ctre::phoenix::ParamEnum::eMotionMeas_tap_time_multi",
    "ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_thresh",
    "ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_time",
    "ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_timeout",
    "ctre::phoenix::ParamEnum::eDefaultConfig"
    };
   
    std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> errorCodes;
    
    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(0);
    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(0);
    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(0);
    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(0);

    for(size_t i = 0; i < allParamEnums.size(); i++) {    
        testTalon->ConfigGetParameter(allParamEnums[i], 0, 1);    
        errorCodes.push_back(std::make_pair(testTalon->GetLastError(), "testTalon->ConfigGetParameter(" + allParamEnumStrings[i] + ", 0, 1);"));
    }
    for(size_t i = 0; i < allParamEnums.size(); i++) {    
        testVictor->ConfigGetParameter(allParamEnums[i], 0, 1);    
        errorCodes.push_back(std::make_pair(testVictor->GetLastError(), "testVictor->ConfigGetParameter(" + allParamEnumStrings[i] + ", 0, 1);"));
    }
    for(size_t i = 0; i < allParamEnums.size(); i++) {    
        testPigeon->ConfigGetParameter(allParamEnums[i], 0, 1);    
        errorCodes.push_back(std::make_pair(testPigeon->GetLastError(), "testPigeon->ConfigGetParameter(" + allParamEnumStrings[i] + ", 0, 1);"));
    }
    for(size_t i = 0; i < allParamEnums.size(); i++) {    
        testCANifier->ConfigGetParameter(allParamEnums[i], 0, 1);    
        errorCodes.push_back(std::make_pair(testCANifier->GetLastError(), "testCANifier->ConfigGetParameter(" + allParamEnumStrings[i] + ", 0, 1);"));
    }

    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }

}


TEST(DeviceID, Get) {
    for(int i = 0; i < 63; i++) {
        std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(i);
        std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(i);
        std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(i);
        std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(i);

        ASSERT_EQ(testTalon->GetDeviceID(), i) << "Failed at Talon id " << i;
        ASSERT_EQ(testVictor->GetDeviceID(), i) << "Failed at Victor id " << i;
        ASSERT_EQ(testPigeon->GetDeviceNumber(), i) << "Failed at Pigeon id " << i;
        ASSERT_EQ(testCANifier->GetDeviceNumber(), i) << "Failed at CANifier id " << i;
    }
} 

TEST(Simulator, Load) {
    //In windows, this becomes increasingly slower per talon as the number of talons loaded increases (~300 ms for 8 Talons, ~10000 ms for 32 talons, and ~32000 ms for 63 talons).
    //Based on some testing, the time required to copy the file and the time required to get a function pointer expand over time. 
    //No such increasing cost occurs in linux and the load time is generally far lower.
    //This is likely because the while loop in firmware uses as much cpu as it can    


    #if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
    
    for(int i = 0; i < 8; i++) { 
    
    #else

    for(int i = 0; i < 63; i++) { 

    #endif

        ctre::phoenix::platform::SimCreate(ctre::phoenix::platform::DeviceType::TalonSRX, i);  
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
