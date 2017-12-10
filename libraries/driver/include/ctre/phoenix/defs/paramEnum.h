#pragma once
#include <stdint.h>

/**
 * Signal enumeration for generic signal access.
 */
enum ParamEnum
	: uint32_t
	{
	eOnBoot_BrakeMode = 31,
	eQuadFilterEn = 91,

    eMotionProfileHasUnderrunErr = 119,

	eStatusFramePeriod = 300,
	eOpenloopRamp = 301,
	eClosedloopRamp = 302,
	eNeutralDeadband = 303,
	//eClosedloopDeadband = 304,
	ePeakPosOutput = 305,
	eNominalPosOutput = 306,
	ePeakNegOutput = 307,
	eNominalNegOutput = 308,

	eProfileParamSlot_P = 310,
	eProfileParamSlot_I = 311,
	eProfileParamSlot_D = 312,
	eProfileParamSlot_F = 313,
	eProfileParamSlot_IZone = 314,
	eProfileParamSlot_AllowableErr = 315,
	eProfileParamSlot_MaxIAccum = 316,

	eClearPositionOnLimitF = 320,
	eClearPositionOnLimitR = 321,
	eClearPositionOnQuadIdx = 322,

	eSampleVelocityPeriod = 325,
	eSampleVelocityWindow = 326,

	eFeedbackSensorType = 330,
	eSelectedSensorPosition = 331,
	eFeedbackNotContinuous = 332,

	eForwardSoftLimitThreshold = 340,
	eReverseSoftLimitThreshold = 341,
	eForwardSoftLimitEnable = 342,
	eReverseSoftLimitEnable = 343,

	eNominalBatteryVoltage = 350,
	eBatteryVoltageFilterSize = 351,

	eContinuousCurrentLimitAmps = 360,
	eContinuousCurrentLimitMs = 361,
	ePeakCurrentLimitAmps = 362,

	eClosedLoopIAccum = 370,

	eCustomParam = 380,

	eStickyFaults = 390,

	eAnalogPosition = 400,
	eQuadraturePosition = 401,
	ePulseWidthPosition = 402,

	eMotMag_Accel = 410,
	eMotMag_VelCruise = 411,

	eLimitSwitchSource = 421, // ordinal (fwd=0,reverse=1), 0-local, 1-RemoteTalon, 2-RemoteCanifer
	eLimitSwitchNormClosedAndDis = 422, // ordinal (fwd=0,reverse=1). 0-Normally Open, 1-Normally Closed, 2- Disabled (web-selectable)
	eLimitSwitchDisableNeutralOnLOS = 423,
	eLimitSwitchRemoteDevID = 424,

	eYawOffset = 160,
	eCompassOffset = 161,
	eBetaGain = 162,
	eReserved163 = 163,
	eGyroNoMotionCal = 164,
	eEnterCalibration = 165,
	eFusedHeadingOffset = 166,
	eStatusFrameRate = 169,
	eAccumZ = 170,
	eTempCompDisable = 171,
	eMotionMeas_tap_threshX = 172,
	eMotionMeas_tap_threshY = 173,
	eMotionMeas_tap_threshZ = 174,
	eMotionMeas_tap_count = 175,
	eMotionMeas_tap_time = 176,
	eMotionMeas_tap_time_multi = 177,
	eMotionMeas_shake_reject_thresh = 178,
	eMotionMeas_shake_reject_time = 179,
	eMotionMeas_shake_reject_timeout = 180,
};
