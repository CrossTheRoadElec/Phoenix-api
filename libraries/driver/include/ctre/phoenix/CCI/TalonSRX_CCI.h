/*
 *  Software License Agreement
 *
 * Copyright (C) Cross The Road Electronics.  All rights
 * reserved.
 * 
 * Cross The Road Electronics (CTRE) licenses to you the right to 
 * use, publish, and distribute copies of CRF (Cross The Road) firmware files (*.crf) and Software
 * API Libraries ONLY when in use with Cross The Road Electronics hardware products.
 * 
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * CROSS THE ROAD ELECTRONICS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
 */
 
 #pragma once
 
 #include "../core/ctre.h"
 #include <map>
namespace TalonSRX_CCI{
  //Map to keep track of handles
  static std::map<void *, bool> talonPresent;
// default control update rate is 10ms.
  static const int kDefaultControlPeriodMs = 10;
  // default enable update rate is 50ms (when using the new control5 frame).
  static const int kDefaultEnablePeriodMs = 50;
  // Default update rate for motion profile control 6.  This only takes effect
  // when calling uses MP functions.
  static const int kDefaultControl6PeriodMs = 10;

  /* mode select enumerations */
  // Demand is 11bit signed duty cycle [-1023,1023].
  static const int kMode_DutyCycle = 0;
  // Position PIDF.
  static const int kMode_PositionCloseLoop = 1;
  // Velocity PIDF.
  static const int kMode_VelocityCloseLoop = 2;
  // Current close loop - not done.
  static const int kMode_CurrentCloseLoop = 3;
  // Voltage Compensation Mode - not done.  Demand is fixed pt target 8.8 volts.
  static const int kMode_VoltCompen = 4;
  // Demand is the 6 bit Device ID of the 'master' TALON SRX.
  static const int kMode_SlaveFollower = 5;
  // Demand is '0' (Disabled), '1' (Enabled), or '2' (Hold).
  static const int kMode_MotionProfile = 6;
  // Zero the output (honors brake/coast) regardless of demand.
  // Might be useful if we need to change modes but can't atomically
  // change all the signals we want in between.
  static const int kMode_NoDrive = 15;
  /* limit switch enumerations */
  static const int kLimitSwitchOverride_UseDefaultsFromFlash = 1;
  static const int kLimitSwitchOverride_DisableFwd_DisableRev = 4;
  static const int kLimitSwitchOverride_DisableFwd_EnableRev = 5;
  static const int kLimitSwitchOverride_EnableFwd_DisableRev = 6;
  static const int kLimitSwitchOverride_EnableFwd_EnableRev = 7;
  /* brake override enumerations */
  static const int kBrakeOverride_UseDefaultsFromFlash = 0;
  static const int kBrakeOverride_OverrideCoast = 1;
  static const int kBrakeOverride_OverrideBrake = 2;
  /* feedback device enumerations */
  static const int kFeedbackDev_DigitalQuadEnc = 0;
  static const int kFeedbackDev_AnalogPot = 2;
  static const int kFeedbackDev_AnalogEncoder = 3;
  static const int kFeedbackDev_CountEveryRisingEdge = 4;
  static const int kFeedbackDev_CountEveryFallingEdge = 5;
  static const int kFeedbackDev_PosIsPulseWidth = 8;
  /* ProfileSlotSelect enumerations*/
  static const int kProfileSlotSelect_Slot0 = 0;
  static const int kProfileSlotSelect_Slot1 = 1;
  /* status frame rate types */
  static const int kStatusFrame_General = 0;
  static const int kStatusFrame_Feedback = 1;
  static const int kStatusFrame_Encoder = 2;
  static const int kStatusFrame_AnalogTempVbat = 3;
  static const int kStatusFrame_PulseWidthMeas = 4;
  static const int kStatusFrame_MotionProfile = 5;
  /* Motion Profile status bits */
  static const int kMotionProfileFlag_ActTraj_IsValid = 0x1;
  static const int kMotionProfileFlag_HasUnderrun = 0x2;
  static const int kMotionProfileFlag_IsUnderrun = 0x4;
  static const int kMotionProfileFlag_ActTraj_IsLast = 0x8;
  static const int kMotionProfileFlag_ActTraj_VelOnly = 0x10;
  /* Motion Profile Set Output */
  // Motor output is neutral, Motion Profile Executer is not running.
  static const int kMotionProf_Disabled = 0;
  // Motor output is updated from Motion Profile Executer, MPE will
  // process the buffered points.
  static const int kMotionProf_Enable = 1;
  // Motor output is updated from Motion Profile Executer, MPE will
  // stay processing current trajectory point.
  static const int kMotionProf_Hold = 2;
  /**
   * Signal enumeration for generic signal access.
   * Although every signal is enumerated, only use this for traffic that must
   * be solicited.
   * Use the auto generated getters/setters at bottom of this header as much as
   * possible.
   */
  enum param_t {
    eProfileParamSlot0_P = 1,
    eProfileParamSlot0_I = 2,
    eProfileParamSlot0_D = 3,
    eProfileParamSlot0_F = 4,
    eProfileParamSlot0_IZone = 5,
    eProfileParamSlot0_CloseLoopRampRate = 6,
    eProfileParamSlot1_P = 11,
    eProfileParamSlot1_I = 12,
    eProfileParamSlot1_D = 13,
    eProfileParamSlot1_F = 14,
    eProfileParamSlot1_IZone = 15,
    eProfileParamSlot1_CloseLoopRampRate = 16,
    eProfileParamSoftLimitForThreshold = 21,
    eProfileParamSoftLimitRevThreshold = 22,
    eProfileParamSoftLimitForEnable = 23,
    eProfileParamSoftLimitRevEnable = 24,
    eOnBoot_BrakeMode = 31,
    eOnBoot_LimitSwitch_Forward_NormallyClosed = 32,
    eOnBoot_LimitSwitch_Reverse_NormallyClosed = 33,
    eOnBoot_LimitSwitch_Forward_Disable = 34,
    eOnBoot_LimitSwitch_Reverse_Disable = 35,
    eFault_OverTemp = 41,
    eFault_UnderVoltage = 42,
    eFault_ForLim = 43,
    eFault_RevLim = 44,
    eFault_HardwareFailure = 45,
    eFault_ForSoftLim = 46,
    eFault_RevSoftLim = 47,
    eStckyFault_OverTemp = 48,
    eStckyFault_UnderVoltage = 49,
    eStckyFault_ForLim = 50,
    eStckyFault_RevLim = 51,
    eStckyFault_ForSoftLim = 52,
    eStckyFault_RevSoftLim = 53,
    eAppliedThrottle = 61,
    eCloseLoopErr = 62,
    eFeedbackDeviceSelect = 63,
    eRevMotDuringCloseLoopEn = 64,
    eModeSelect = 65,
    eProfileSlotSelect = 66,
    eRampThrottle = 67,
    eRevFeedbackSensor = 68,
    eLimitSwitchEn = 69,
    eLimitSwitchClosedFor = 70,
    eLimitSwitchClosedRev = 71,
    eSensorPosition = 73,
    eSensorVelocity = 74,
    eCurrent = 75,
    eBrakeIsEnabled = 76,
    eEncPosition = 77,
    eEncVel = 78,
    eEncIndexRiseEvents = 79,
    eQuadApin = 80,
    eQuadBpin = 81,
    eQuadIdxpin = 82,
    eAnalogInWithOv = 83,
    eAnalogInVel = 84,
    eTemp = 85,
    eBatteryV = 86,
    eResetCount = 87,
    eResetFlags = 88,
    eFirmVers = 89,
    eSettingsChanged = 90,
    eQuadFilterEn = 91,
    ePidIaccum = 93,
    eStatus1FrameRate = 94,  // TALON_Status_1_General_10ms_t
    eStatus2FrameRate = 95,  // TALON_Status_2_Feedback_20ms_t
    eStatus3FrameRate = 96,  // TALON_Status_3_Enc_100ms_t
    eStatus4FrameRate = 97,  // TALON_Status_4_AinTempVbat_100ms_t
    eStatus6FrameRate = 98,  // TALON_Status_6_Eol_t
    eStatus7FrameRate = 99,  // TALON_Status_7_Debug_200ms_t
    eClearPositionOnIdx = 100,
    // reserved,
    // reserved,
    // reserved,
    ePeakPosOutput = 104,
    eNominalPosOutput = 105,
    ePeakNegOutput = 106,
    eNominalNegOutput = 107,
    eQuadIdxPolarity = 108,
    eStatus8FrameRate = 109,  // TALON_Status_8_PulseWid_100ms_t
    eAllowPosOverflow = 110,
    eProfileParamSlot0_AllowableClosedLoopErr = 111,
    eNumberPotTurns = 112,
    eNumberEncoderCPR = 113,
    ePwdPosition = 114,
    eAinPosition = 115,
    eProfileParamVcompRate = 116,
    eProfileParamSlot1_AllowableClosedLoopErr = 117,
    eStatus9FrameRate = 118,  // TALON_Status_9_MotProfBuffer_100ms_t
    eMotionProfileHasUnderrunErr = 119,
    eReserved120 = 120,
    eLegacyControlMode = 121,

	eMotMag_Accel = 122,
	eMotMag_VelCruise = 123,
	eStatus10FrameRate=124, // TALON_Status_10_MotMag_100ms_t
	eCurrentLimThreshold=125,

	eBldcStatus1FrameRate=129, //  CYCLONE_BLDC_Status_1_BTC_MEC
	eBldcStatus2FrameRate=130, //  CYCLONE_BLDC_Status_2_SLC
	eBldcStatus3FrameRate=131, //  CYCLONE_BLDC_Status_3_SLD


	eCustomParam0 = 137,
	eCustomParam1 = 138,
	ePersStorageSaving = 139,
	
	eClearPositionOnLimitF = 144,
	eClearPositionOnLimitR = 145,
	eNominalBatteryVoltage = 146,
	eSampleVelocityPeriod = 147,
	eSampleVelocityWindow = 148,
	
	eMotionMeas_YawOffset	=160,
	eMotionMeas_CompassOffset	= 161,
	eMotionMeas_BetaGain =	162,
	eMotionMeas_Reserved163 =	163,
	eMotionMeas_GyroNoMotionCal =	164,
	eMotionMeas_EnterCalibration =	165,
	eMotionMeas_FusedHeadingOffset	= 166,
  };
}
  
extern "C" {
  void *c_TalonSRX_Create3(int deviceNumber, int controlPeriodMs, int enablePeriodMs);
  void *c_TalonSRX_Create2(int deviceNumber, int controlPeriodMs);
  void *c_TalonSRX_Create1(int deviceNumber);
  void c_TalonSRX_Destroy(void *handle);
  void c_TalonSRX_Set(void *handle, double value);
  CTR_Code c_TalonSRX_SetParam(void *handle, int paramEnum, double value);
  CTR_Code c_TalonSRX_RequestParam(void *handle, int paramEnum);
  CTR_Code c_TalonSRX_GetParamResponse(void *handle, int paramEnum, double *value);
  CTR_Code c_TalonSRX_GetParamResponseInt32(void *handle, int paramEnum, int *value);
  CTR_Code c_TalonSRX_SetPgain(void *handle, int slotIdx, double gain);
  CTR_Code c_TalonSRX_SetIgain(void *handle, int slotIdx, double gain);
  CTR_Code c_TalonSRX_SetDgain(void *handle, int slotIdx, double gain);
  CTR_Code c_TalonSRX_SetFgain(void *handle, int slotIdx, double gain);
  CTR_Code c_TalonSRX_SetIzone(void *handle, int slotIdx, int zone);
  CTR_Code c_TalonSRX_SetCloseLoopRampRate(void *handle, int slotIdx, int closeLoopRampRate);
  CTR_Code c_TalonSRX_SetVoltageCompensationRate(void *handle, double voltagePerMs);
  CTR_Code c_TalonSRX_SetSensorPosition(void *handle, int pos);
  CTR_Code c_TalonSRX_SetForwardSoftLimit(void *handle, int forwardLimit);
  CTR_Code c_TalonSRX_SetReverseSoftLimit(void *handle, int reverseLimit);
  CTR_Code c_TalonSRX_SetForwardSoftEnable(void *handle, int enable);
  CTR_Code c_TalonSRX_SetReverseSoftEnable(void *handle, int enable);
  CTR_Code c_TalonSRX_GetPgain(void *handle, int slotIdx, double *gain);
  CTR_Code c_TalonSRX_GetIgain(void *handle, int slotIdx, double *gain);
  CTR_Code c_TalonSRX_GetDgain(void *handle, int slotIdx, double *gain);
  CTR_Code c_TalonSRX_GetFgain(void *handle, int slotIdx, double *gain);
  CTR_Code c_TalonSRX_GetIzone(void *handle, int slotIdx, int *zone);
  CTR_Code c_TalonSRX_GetCloseLoopRampRate(void *handle, int slotIdx, int *closeLoopRampRate);
  CTR_Code c_TalonSRX_GetVoltageCompensationRate(void *handle, double *voltagePerMs);
  CTR_Code c_TalonSRX_GetForwardSoftLimit(void *handle, int *forwardLimit);
  CTR_Code c_TalonSRX_GetReverseSoftLimit(void *handle, int *reverseLimit);
  CTR_Code c_TalonSRX_GetForwardSoftEnable(void *handle, int *enable);
  CTR_Code c_TalonSRX_GetReverseSoftEnable(void *handle, int *enable);
  CTR_Code c_TalonSRX_GetPulseWidthRiseToFallUs(void *handle, int *param);
  CTR_Code c_TalonSRX_IsPulseWidthSensorPresent(void *handle, int *param);
  CTR_Code c_TalonSRX_SetModeSelect2(void *handle, int modeSelect, int demand);
  CTR_Code c_TalonSRX_SetStatusFrameRate(void *handle, int frameEnum, int periodMs);
  CTR_Code c_TalonSRX_ClearStickyFaults(void *handle);
  void c_TalonSRX_ChangeMotionControlFramePeriod(void *handle, int periodMs);
  void c_TalonSRX_ClearMotionProfileTrajectories(void *handle);
  int c_TalonSRX_GetMotionProfileTopLevelBufferCount(void *handle);
  int c_TalonSRX_IsMotionProfileTopLevelBufferFull(void *handle);
  CTR_Code c_TalonSRX_PushMotionProfileTrajectory(void *handle, int targPos, int targVel, int profileSlotSelect, int timeDurMs, int velOnly, int isLastPoint, int zeroPos);
  void c_TalonSRX_ProcessMotionProfileBuffer(void *handle);
  CTR_Code c_TalonSRX_GetMotionProfileStatus(void *handle, int *flags, int *profileSlotSelect, int *targPos, int *targVel, int *topBufferRemaining, int *topBufferCnt, int *btmBufferCnt, int *outputEnable);
  CTR_Code c_TalonSRX_GetFault_OverTemp(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFault_UnderVoltage(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFault_ForLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFault_RevLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFault_HardwareFailure(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFault_ForSoftLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFault_RevSoftLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetStckyFault_OverTemp(void *handle, int *param);
  CTR_Code c_TalonSRX_GetStckyFault_UnderVoltage(void *handle, int *param);
  CTR_Code c_TalonSRX_GetStckyFault_ForLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetStckyFault_RevLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetStckyFault_ForSoftLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetStckyFault_RevSoftLim(void *handle, int *param);
  CTR_Code c_TalonSRX_GetAppliedThrottle(void *handle, int *param);
  CTR_Code c_TalonSRX_GetCloseLoopErr(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFeedbackDeviceSelect(void *handle, int *param);
  CTR_Code c_TalonSRX_GetModeSelect(void *handle, int *param);
  CTR_Code c_TalonSRX_GetLimitSwitchEn(void *handle, int *param);
  CTR_Code c_TalonSRX_GetLimitSwitchClosedFor(void *handle, int *param);
  CTR_Code c_TalonSRX_GetLimitSwitchClosedRev(void *handle, int *param);
  CTR_Code c_TalonSRX_GetSensorPosition(void *handle, int *param);
  CTR_Code c_TalonSRX_GetSensorVelocity(void *handle, int *param);
  CTR_Code c_TalonSRX_GetCurrent(void *handle, double *param);
  CTR_Code c_TalonSRX_GetBrakeIsEnabled(void *handle, int *param);
  CTR_Code c_TalonSRX_GetEncPosition(void *handle, int *param);
  CTR_Code c_TalonSRX_GetEncVel(void *handle, int *param);
  CTR_Code c_TalonSRX_GetEncIndexRiseEvents(void *handle, int *param);
  CTR_Code c_TalonSRX_GetQuadApin(void *handle, int *param);
  CTR_Code c_TalonSRX_GetQuadBpin(void *handle, int *param);
  CTR_Code c_TalonSRX_GetQuadIdxpin(void *handle, int *param);
  CTR_Code c_TalonSRX_GetAnalogInWithOv(void *handle, int *param);
  CTR_Code c_TalonSRX_GetAnalogInVel(void *handle, int *param);
  CTR_Code c_TalonSRX_GetTemp(void *handle, double *param);
  CTR_Code c_TalonSRX_GetBatteryV(void *handle, double *param);
  CTR_Code c_TalonSRX_GetClearPosOnIdx(void *handle, int *param);
  CTR_Code c_TalonSRX_GetClearPosOnLimR(void *handle, int *param);
  CTR_Code c_TalonSRX_GetClearPosOnLimF(void *handle, int *param);
  CTR_Code c_TalonSRX_GetResetCount(void *handle, int *param);
  CTR_Code c_TalonSRX_GetResetFlags(void *handle, int *param);
  CTR_Code c_TalonSRX_GetFirmVers(void *handle, int *param);
  CTR_Code c_TalonSRX_GetPulseWidthPosition(void *handle, int *param);
  CTR_Code c_TalonSRX_GetPulseWidthVelocity(void *handle, int *param);
  CTR_Code c_TalonSRX_GetPulseWidthRiseToRiseUs(void *handle, int *param);
  CTR_Code c_TalonSRX_GetActTraj_IsValid(void *handle, int *param);
  CTR_Code c_TalonSRX_GetActTraj_ProfileSlotSelect(void *handle, int *param);
  CTR_Code c_TalonSRX_GetActTraj_VelOnly(void *handle, int *param);
  CTR_Code c_TalonSRX_GetActTraj_IsLast(void *handle, int *param);
  CTR_Code c_TalonSRX_GetOutputType(void *handle, int *param);
  CTR_Code c_TalonSRX_GetHasUnderrun(void *handle, int *param);
  CTR_Code c_TalonSRX_GetIsUnderrun(void *handle, int *param);
  CTR_Code c_TalonSRX_GetNextID(void *handle, int *param);
  CTR_Code c_TalonSRX_GetBufferIsFull(void *handle, int *param);
  CTR_Code c_TalonSRX_GetCount(void *handle, int *param);
  CTR_Code c_TalonSRX_GetActTraj_Velocity(void *handle, int *param);
  CTR_Code c_TalonSRX_GetActTraj_Position(void *handle, int *param);
  CTR_Code c_TalonSRX_SetDemand(void *handle, int param);
  CTR_Code c_TalonSRX_SetOverrideLimitSwitchEn(void *handle, int param);
  CTR_Code c_TalonSRX_SetFeedbackDeviceSelect(void *handle, int param);
  CTR_Code c_TalonSRX_SetRevMotDuringCloseLoopEn(void *handle, int param);
  CTR_Code c_TalonSRX_SetOverrideBrakeType(void *handle, int param);
  CTR_Code c_TalonSRX_SetModeSelect(void *handle, int param);
  CTR_Code c_TalonSRX_SetProfileSlotSelect(void *handle, int param);
  CTR_Code c_TalonSRX_SetRampThrottle(void *handle, int param);
  CTR_Code c_TalonSRX_SetRevFeedbackSensor(void *handle, int param);
  CTR_Code c_TalonSRX_SetCurrentLimEnable(void *handle, int enable);
  CTR_Code c_TalonSRX_SetDataPortOutputPeriodMs(void *handle, int param);
  CTR_Code c_TalonSRX_SetDataPortOutputEnable(void *handle, int idx, int param);
  CTR_Code c_TalonSRX_SetDataPortOutputOnTimeMs(void *handle, int idx, int param);
  CTR_Code c_TalonSRX_GetMotionMagic_ActiveTrajPosition(void *handle, int *param);
  CTR_Code c_TalonSRX_GetMotionMagic_ActiveTrajVelocity(void *handle, int *param);
  int c_TalonSRX_HasResetOccured(void *handle);
  int c_TalonSRX_GetDeviceNumber(void *handle);
  int c_TalonSRX_GetLastError(void *handle);
  void c_TalonSRX_SetLastError(void *handle, int error);
}