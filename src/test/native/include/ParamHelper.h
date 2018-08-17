#pragma once

#include "ctre/Phoenix.h"
#include <string>
#include <utility>
#include <vector>
#include <map>
#include "ConfigHelper.h"

struct ParamEnumParameters {
    std::string name = "Default";
    double value = 0;
    uint8_t subValue = 0;
    int ordinal = 0;
    double min = 0;
    double max = 0;
    double equalsResolutionCheck = 0;
};


typedef std::map<ctre::phoenix::ParamEnum, ParamEnumParameters> ParamEnumString;

//There is some overlap with config set functions

//These below variables should combined contain all enums with no overlap
//Intent is: 
// Talon = generic + sensor + motController + current
// Victor = generic + motController
// CANifier = generic + sensor
// Pigeon = generic + imu

const static ParamEnumString genericParamEnumStrings {
{ctre::phoenix::ParamEnum::eStatusFramePeriod, {"ctre::phoenix::ParamEnum::eStatusFramePeriod", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eCustomParam, {"ctre::phoenix::ParamEnum::eCustomParam", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eStickyFaults, {"ctre::phoenix::ParamEnum::eStickyFaults", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eDefaultConfig, {"ctre::phoenix::ParamEnum::eDefaultConfig", 0.0, 0, 0, 0, 1, 0.5}}
};

const static ParamEnumString sensorParamEnumStrings {
{ctre::phoenix::ParamEnum::eQuadFilterEn, {"ctre::phoenix::ParamEnum::eQuadFilterEn", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eQuadIdxPolarity, {"ctre::phoenix::ParamEnum::eQuadIdxPolarity", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eClearPositionOnLimitF, {"ctre::phoenix::ParamEnum::eClearPositionOnLimitF", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eClearPositionOnLimitR, {"ctre::phoenix::ParamEnum::eClearPositionOnLimitR", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx, {"ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eSampleVelocityPeriod, {"ctre::phoenix::ParamEnum::eSampleVelocityPeriod", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eSampleVelocityWindow, {"ctre::phoenix::ParamEnum::eSampleVelocityWindow", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eFeedbackNotContinuous, {"ctre::phoenix::ParamEnum::eFeedbackNotContinuous", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eAnalogPosition, {"ctre::phoenix::ParamEnum::eAnalogPosition", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eQuadraturePosition, {"ctre::phoenix::ParamEnum::eQuadraturePosition", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePulseWidthPosition, {"ctre::phoenix::ParamEnum::ePulseWidthPosition", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis, {"ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot, {"ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz, {"ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz", 0.0, 0, 0, 0, 1, 0.5}}
};

const static ParamEnumString imuParamEnumStrings {
{ctre::phoenix::ParamEnum::eYawOffset, {"ctre::phoenix::ParamEnum::eYawOffset", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eCompassOffset, {"ctre::phoenix::ParamEnum::eCompassOffset", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eBetaGain, {"ctre::phoenix::ParamEnum::eBetaGain", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eEnableCompassFusion, {"ctre::phoenix::ParamEnum::eEnableCompassFusion", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eGyroNoMotionCal, {"ctre::phoenix::ParamEnum::eGyroNoMotionCal", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eEnterCalibration, {"ctre::phoenix::ParamEnum::eEnterCalibration", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eFusedHeadingOffset, {"ctre::phoenix::ParamEnum::eFusedHeadingOffset", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eAccumZ, {"ctre::phoenix::ParamEnum::eAccumZ", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eTempCompDisable, {"ctre::phoenix::ParamEnum::eTempCompDisable", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_threshX, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_threshX", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_threshY, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_threshY", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_threshZ, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_threshZ", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_count, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_count", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_time, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_time", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_time_multi, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_time_multi", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_thresh, {"ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_thresh", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_time, {"ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_time", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_timeout, {"ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_timeout", 0.0, 0, 0, 0, 1, 0.5}}
};

const static ParamEnumString motControllerParamEnumStrings {
{ctre::phoenix::ParamEnum::eOnBoot_BrakeMode, {"ctre::phoenix::ParamEnum::eOnBoot_BrakeMode", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionProfileHasUnderrunErr, {"ctre::phoenix::ParamEnum::eMotionProfileHasUnderrunErr", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs, {"ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eSelectedSensorPosition, {"ctre::phoenix::ParamEnum::eSelectedSensorPosition", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eOpenloopRamp, {"ctre::phoenix::ParamEnum::eOpenloopRamp", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eClosedloopRamp, {"ctre::phoenix::ParamEnum::eClosedloopRamp", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eNeutralDeadband, {"ctre::phoenix::ParamEnum::eNeutralDeadband", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePeakPosOutput, {"ctre::phoenix::ParamEnum::ePeakPosOutput", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eNominalPosOutput, {"ctre::phoenix::ParamEnum::eNominalPosOutput", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePeakNegOutput, {"ctre::phoenix::ParamEnum::ePeakNegOutput", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eNominalNegOutput, {"ctre::phoenix::ParamEnum::eNominalNegOutput", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_P, {"ctre::phoenix::ParamEnum::eProfileParamSlot_P", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_I, {"ctre::phoenix::ParamEnum::eProfileParamSlot_I", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_D, {"ctre::phoenix::ParamEnum::eProfileParamSlot_D", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_F, {"ctre::phoenix::ParamEnum::eProfileParamSlot_F", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_IZone, {"ctre::phoenix::ParamEnum::eProfileParamSlot_IZone", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr, {"ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum, {"ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput, {"ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eFeedbackSensorType, {"ctre::phoenix::ParamEnum::eFeedbackSensorType", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eRemoteSensorSource, {"ctre::phoenix::ParamEnum::eRemoteSensorSource", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eRemoteSensorDeviceID, {"ctre::phoenix::ParamEnum::eRemoteSensorDeviceID", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eSensorTerm, {"ctre::phoenix::ParamEnum::eSensorTerm", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS, {"ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePIDLoopPolarity, {"ctre::phoenix::ParamEnum::ePIDLoopPolarity", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePIDLoopPeriod, {"ctre::phoenix::ParamEnum::ePIDLoopPeriod", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eSelectedSensorCoefficient, {"ctre::phoenix::ParamEnum::eSelectedSensorCoefficient", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold, {"ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold, {"ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eForwardSoftLimitEnable, {"ctre::phoenix::ParamEnum::eForwardSoftLimitEnable", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eReverseSoftLimitEnable, {"ctre::phoenix::ParamEnum::eReverseSoftLimitEnable", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eNominalBatteryVoltage, {"ctre::phoenix::ParamEnum::eNominalBatteryVoltage", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize, {"ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eClosedLoopIAccum, {"ctre::phoenix::ParamEnum::eClosedLoopIAccum", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotMag_Accel, {"ctre::phoenix::ParamEnum::eMotMag_Accel", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eMotMag_VelCruise, {"ctre::phoenix::ParamEnum::eMotMag_VelCruise", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchSource, {"ctre::phoenix::ParamEnum::eLimitSwitchSource", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS, {"ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID, {"ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS, {"ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS", 0.0, 0, 0, 0, 1, 0.5}}
};

const static ParamEnumString currentParamEnumStrings {
{ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps, {"ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePeakCurrentLimitMs, {"ctre::phoenix::ParamEnum::ePeakCurrentLimitMs", 0.0, 0, 0, 0, 1, 0.5}},
{ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps, {"ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps", 0.0, 0, 0, 0, 1, 0.5}}
};

void GetAllParamsTalon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes);

void GetAllParamsVictor(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes);

void GetAllParamsPigeon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes);

void GetAllParamsCANifier(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes);


void SetAllParamsTalon(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes);

void SetAllParamsVictor(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes);

void SetAllParamsPigeon(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes);

void SetAllParamsCANifier(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes);
