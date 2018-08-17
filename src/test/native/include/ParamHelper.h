#pragma once

#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include <string>
#include <utility>
#include <vector>
#include <map>
#include "ConfigHelper.h"
#include <random>

enum ParamUsage {
    OrdinalUsedAsIndex,
    ValueUsedAsIndexAndBinaryORWithArbID,
    NoSubValueOrOrdinalUse
};

double BasicCast (int32_t recieveValue, uint8_t /*recieveSubValue*/);

double SubValueCast (int32_t /*recieveValue*/, uint8_t recieveSubValue);

double DoubleInRange(std::vector<double> minMax);

double IntInRange(std::vector<double> minMax);

struct ParamValues {
    double defaultValue = 0.0;
    
    double sendValue = 0.0;
    
    int32_t recieveValue = 0;
    uint8_t recieveSubValue = 0;
};

struct ParamParameters {
    std::string name = "Default";
    std::map<ctre::phoenix::platform::DeviceType, std::map<int, ParamValues>> ValueSet;
    ParamUsage paramUsage = NoSubValueOrOrdinalUse;

    std::vector<double> generationParams;

    double (*recieveToSend)(int32_t recieveValue, uint8_t recieveSubValue) = BasicCast; 
    double (*generateToSend)(std::vector<double> generationParams) = DoubleInRange;
    
    double equalityInterval = 0;    
};


typedef std::map<ctre::phoenix::ParamEnum, ParamParameters> ParamEnumSet;

void GenerateSendValues(ParamEnumSet &toFill);

void EqualityCheck(ParamEnumSet &toCheck);

//There is some overlap with config set functions

//These below variables should combined contain all enums with no overlap
//Intent is: 
// Talon = generic + sensor + motController + current
// Victor = generic + motController
// CANifier = generic + sensor
// Pigeon = generic + imu

const static ParamEnumSet genericParamEnumSets {
{ctre::phoenix::ParamEnum::eStatusFramePeriod, {"ctre::phoenix::ParamEnum::eStatusFramePeriod", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0x1400, {0.0, 0.0, 0, 0}}}}}, ValueUsedAsIndexAndBinaryORWithArbID, {1, 255}, SubValueCast, IntInRange, 0}},
{ctre::phoenix::ParamEnum::eCustomParam, {"ctre::phoenix::ParamEnum::eCustomParam", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eStickyFaults, {"ctre::phoenix::ParamEnum::eStickyFaults", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eDefaultConfig, {"ctre::phoenix::ParamEnum::eDefaultConfig", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}}
};

const static ParamEnumSet sensorParamEnumSets {
{ctre::phoenix::ParamEnum::eQuadFilterEn, {"ctre::phoenix::ParamEnum::eQuadFilterEn", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eQuadIdxPolarity, {"ctre::phoenix::ParamEnum::eQuadIdxPolarity", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eClearPositionOnLimitF, {"ctre::phoenix::ParamEnum::eClearPositionOnLimitF", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eClearPositionOnLimitR, {"ctre::phoenix::ParamEnum::eClearPositionOnLimitR", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx, {"ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eSampleVelocityPeriod, {"ctre::phoenix::ParamEnum::eSampleVelocityPeriod", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eSampleVelocityWindow, {"ctre::phoenix::ParamEnum::eSampleVelocityWindow", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eFeedbackNotContinuous, {"ctre::phoenix::ParamEnum::eFeedbackNotContinuous", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eAnalogPosition, {"ctre::phoenix::ParamEnum::eAnalogPosition", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eQuadraturePosition, {"ctre::phoenix::ParamEnum::eQuadraturePosition", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePulseWidthPosition, {"ctre::phoenix::ParamEnum::ePulseWidthPosition", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis, {"ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot, {"ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz, {"ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}}
};

const static ParamEnumSet imuParamEnumSets {
{ctre::phoenix::ParamEnum::eYawOffset, {"ctre::phoenix::ParamEnum::eYawOffset", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eCompassOffset, {"ctre::phoenix::ParamEnum::eCompassOffset", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eBetaGain, {"ctre::phoenix::ParamEnum::eBetaGain", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eEnableCompassFusion, {"ctre::phoenix::ParamEnum::eEnableCompassFusion", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eGyroNoMotionCal, {"ctre::phoenix::ParamEnum::eGyroNoMotionCal", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eEnterCalibration, {"ctre::phoenix::ParamEnum::eEnterCalibration", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eFusedHeadingOffset, {"ctre::phoenix::ParamEnum::eFusedHeadingOffset", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eAccumZ, {"ctre::phoenix::ParamEnum::eAccumZ", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eTempCompDisable, {"ctre::phoenix::ParamEnum::eTempCompDisable", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_threshX, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_threshX", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_threshY, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_threshY", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_threshZ, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_threshZ", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_count, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_count", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_time, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_time", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_tap_time_multi, {"ctre::phoenix::ParamEnum::eMotionMeas_tap_time_multi", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_thresh, {"ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_thresh", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_time, {"ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_time", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_timeout, {"ctre::phoenix::ParamEnum::eMotionMeas_shake_reject_timeout", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}}
};

const static ParamEnumSet motControllerParamEnumSets {
{ctre::phoenix::ParamEnum::eOnBoot_BrakeMode, {"ctre::phoenix::ParamEnum::eOnBoot_BrakeMode", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionProfileHasUnderrunErr, {"ctre::phoenix::ParamEnum::eMotionProfileHasUnderrunErr", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs, {"ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eSelectedSensorPosition, {"ctre::phoenix::ParamEnum::eSelectedSensorPosition", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eOpenloopRamp, {"ctre::phoenix::ParamEnum::eOpenloopRamp", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eClosedloopRamp, {"ctre::phoenix::ParamEnum::eClosedloopRamp", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eNeutralDeadband, {"ctre::phoenix::ParamEnum::eNeutralDeadband", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePeakPosOutput, {"ctre::phoenix::ParamEnum::ePeakPosOutput", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eNominalPosOutput, {"ctre::phoenix::ParamEnum::eNominalPosOutput", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePeakNegOutput, {"ctre::phoenix::ParamEnum::ePeakNegOutput", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eNominalNegOutput, {"ctre::phoenix::ParamEnum::eNominalNegOutput", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_P, {"ctre::phoenix::ParamEnum::eProfileParamSlot_P", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_I, {"ctre::phoenix::ParamEnum::eProfileParamSlot_I", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_D, {"ctre::phoenix::ParamEnum::eProfileParamSlot_D", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_F, {"ctre::phoenix::ParamEnum::eProfileParamSlot_F", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_IZone, {"ctre::phoenix::ParamEnum::eProfileParamSlot_IZone", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr, {"ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum, {"ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput, {"ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eFeedbackSensorType, {"ctre::phoenix::ParamEnum::eFeedbackSensorType", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eRemoteSensorSource, {"ctre::phoenix::ParamEnum::eRemoteSensorSource", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eRemoteSensorDeviceID, {"ctre::phoenix::ParamEnum::eRemoteSensorDeviceID", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eSensorTerm, {"ctre::phoenix::ParamEnum::eSensorTerm", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS, {"ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePIDLoopPolarity, {"ctre::phoenix::ParamEnum::ePIDLoopPolarity", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePIDLoopPeriod, {"ctre::phoenix::ParamEnum::ePIDLoopPeriod", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eSelectedSensorCoefficient, {"ctre::phoenix::ParamEnum::eSelectedSensorCoefficient", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold, {"ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold, {"ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eForwardSoftLimitEnable, {"ctre::phoenix::ParamEnum::eForwardSoftLimitEnable", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eReverseSoftLimitEnable, {"ctre::phoenix::ParamEnum::eReverseSoftLimitEnable", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eNominalBatteryVoltage, {"ctre::phoenix::ParamEnum::eNominalBatteryVoltage", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize, {"ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eClosedLoopIAccum, {"ctre::phoenix::ParamEnum::eClosedLoopIAccum", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotMag_Accel, {"ctre::phoenix::ParamEnum::eMotMag_Accel", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eMotMag_VelCruise, {"ctre::phoenix::ParamEnum::eMotMag_VelCruise", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchSource, {"ctre::phoenix::ParamEnum::eLimitSwitchSource", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS, {"ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID, {"ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS, {"ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}}
};

const static ParamEnumSet currentParamEnumSets {
{ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps, {"ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePeakCurrentLimitMs, {"ctre::phoenix::ParamEnum::ePeakCurrentLimitMs", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}},
{ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps, {"ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps", {{ctre::phoenix::platform::DeviceType::TalonSRXType, {{0, {0.0, 0.0, 0, 0}}}}}, NoSubValueOrOrdinalUse, {0.0, 1.0}, BasicCast, DoubleInRange, 0.5}}
};

void GetAllParams(std::map<ctre::phoenix::platform::DeviceType, int> &idMap, int timeoutMs, ParamEnumSet &paramsToGet, ErrorCodeString &errorCodes);

void SetAllParams(std::map<ctre::phoenix::platform::DeviceType, int> &idMap, int timeoutMs, const ParamEnumSet &paramsToSet, ErrorCodeString &errorCodes);
