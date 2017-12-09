#pragma once

#include "ctre/Phoenix/LowLevel/MotController_LowLevel.h"
//#include <string>
//#include <stdint.h>
//
///* forward proto's */
//enum ErrorCode
//: int32_t;
//enum ParamEnum
//: uint32_t;
//
//class MotControllerWithBuffer_LowLevel: public MotController_LowLevel {
//
//private:
//
//    /* Motion Profile status bits */
//    const int kMotionProfileFlag_ActTraj_IsValid = 0x1;
//    const int kMotionProfileFlag_HasUnderrun = 0x2;
//    const int kMotionProfileFlag_IsUnderrun = 0x4;
//    const int kMotionProfileFlag_ActTraj_IsLast = 0x8;
//    const int kMotionProfileFlag_ActTraj_VelOnly = 0x10;
//
//	const int kDefaultControl6PeriodMs = 10;
//
//	void EnableFirmStatusFrame(bool enable);
//	ErrorCode SetLastError(ErrorCode errorCode);
//	ErrorCode SetLastError(int errorCode);
//
//    /** The cache. */
//    uint64_t _cache;
//    /** The length. */
//    uint32_t _len;
//
//
//    //--------------------- Buffering Motion Profile ---------------------------//
//
//    /**
//     * To keep buffers from getting out of control, place a cap on the top level buffer.  Calling
//     * application can stream addition points as they are fed to Talon. Approx memory footprint is
//     * this capacity X 8 bytes.
//     */
//
//    const int kMotionProfileTopBufferCapacity = 512;
//    /** Buffer for mot prof top data. */
//    TrajectoryBuffer _motProfTopBuffer = new TrajectoryBuffer(kMotionProfileTopBufferCapacity);
//    /** Flow control for streaming trajectories. */
//    int32_t _motProfFlowControl = -1;
//
//    /** The mut mot prof. */
//    std::mutex _mutMotProf;    // use this std::unique_lock<std::mutex> lck (_mutMotProf);
//
//    /** Frame Period of the motion profile control6 frame. */
//    uint _control6PeriodMs = kDefaultControl6PeriodMs;
//
//public:
//	MotControllerWithBuffer_LowLevel(int baseArbId);
//
//	  /**
//	   * @return the tx task that transmits Control6 (motion profile control).
//	   *         If it's not scheduled, then schedule it.  This is part
//	   *         of making the lazy-framing that only peforms MotionProf framing
//	   *         when needed to save bandwidth.
//	   */
//	  CtreCanMap::txTask<TALON_Control_6_MotProfAddTrajPoint_t> GetControl6();
//	  /**
//	   * Caller is either pushing a new motion profile point, or is
//	   * calling the Process buffer routine.  In either case check our
//	   * flow control to see if we need to start sending control6.
//	   */
//	  void ReactToMotionProfileCall();
//	  /**
//	   * Update the NextPt signals inside the control frame given the next pt to
//	   * send.
//	   * @param control pointer to the CAN frame payload containing control6.  Only
//	   *                the signals that serialize the next trajectory point are
//	   *                updated from the contents of newPt.
//	   * @param newPt point to the next trajectory that needs to be inserted into
//	   *              Talon RAM.
//	   */
//	  void CopyTrajPtIntoControl(TALON_Control_6_MotProfAddTrajPoint_t *control, const TALON_Control_6_MotProfAddTrajPoint_t *newPt);
//
//	  /**
//	   * @return the tx task that transmits Control7 (feedback output override).
//	   *         If it's not scheduled, then schedule it.  This is part
//	   *         of making the lazy-framing that only peforms output override framing
//	   *         when needed to save bandwidth.
//	   */
//	  CtreCanMap::txTask<TALON_Control_7_FeedbackOutputOverride_t> GetControl7();
//
//
//
//
//
//
//
//
//
//
//
//
//    private UInt64 GetControl6()
//
//    public void ChangeMotionControlFramePeriod(UInt32 periodMs)
//    public void ClearMotionProfileTrajectories()
//    public int GetMotionProfileTopLevelBufferCount()
//    public bool IsMotionProfileTopLevelBufferFull()
//    public ErrorCode PushMotionProfileTrajectory(int targPos,
//                                            int targVel,
//                                            int profileSlotSelect,
//                                            int timeDurMs, int velOnly,
//                                            int isLastPoint,
//                                            int zeroPos)
//    private int MotionProf_IncrementSync(int idx)
//    private void CopyTrajPtIntoControl(ref TALON_Control_6_MotProfAddTrajPoint_t control, TALON_Control_6_MotProfAddTrajPoint_t newPt)
//    private void ReactToMotionProfileCall()
//    public void ProcessMotionProfileBuffer()
//
//public int GetMotionProfileStatus(out UInt32 flags, out UInt32 profileSlotSelect, out Int32 targPos,
//                            out Int32 targVel, out UInt32 topBufferRem, out UInt32 topBufferCnt,
//                            out UInt32 btmBufferCnt, out UInt32 outputEnable)
//
//
//	void SetDemand(ControlMode mode, int demand0, int demand1);
//	void SelectDemandType(bool enable);
//	void SetNeutralMode(NeutralMode neutralMode);
//	void SetSensorPhase(bool PhaseSensor);
//	void SetInverted(bool invert);
//
//	ErrorCode ConfigOpenloopRamp(float secondsFromNeutralToFull, int timeoutMs);
//	ErrorCode ConfigClosedloopRamp(float secondsFromNeutralToFull,
//			int timeoutMs);
//	ErrorCode ConfigPeakOutputForward(float percentOut, int timeoutMs);
//	ErrorCode ConfigPeakOutputReverse(float percentOut, int timeoutMs);
//	ErrorCode ConfigNominalOutputForward(float percentOut, int timeoutMs);
//	ErrorCode ConfigNominalOutputReverse(float percentOut, int timeoutMs);
//	ErrorCode ConfigOpenLoopNeutralDeadband(float percentDeadband,
//			int timeoutMs);
//	ErrorCode ConfigClosedLoopNeutralDeadband(float percentDeadband,
//			int timeoutMs);
//	ErrorCode ConfigVoltageCompSaturation(float voltage, int timeoutMs);
//	ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
//			int timeoutMs);
//	void EnableVoltageCompensation(bool enable);
//	ErrorCode GetBusVoltage(float & param);
//	ErrorCode GetMotorOutputPercent(float & param);
//	ErrorCode GetOutputCurrent(float & param);
//	ErrorCode GetTemperature(float & param);
//	ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice,
//			int timeoutMs);
//	ErrorCode ConfigRemoteFeedbackFilter(int arbId, int peripheralIdx,
//			int reserved, int timeoutMs);
//	ErrorCode GetSelectedSensorPosition(int & param);
//	ErrorCode GetSelectedSensorVelocity(int & param);
//	ErrorCode SetSelectedSensorPosition(int sensorPos, int timeoutMs);
//	ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
//	ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
//			int timeoutMs);
//	ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame, int periodMs,
//			int timeoutMs);
//	ErrorCode GetStatusFramePeriod(StatusFrame frame, int & periodMs,
//			int timeoutMs);
//	ErrorCode GetStatusFramePeriod(StatusFrameEnhanced frame, int & periodMs,
//			int timeoutMs);
//	ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
//			int timeoutMs);
//	ErrorCode ConfigVelocityMeasurementWindow(int windowSize, int timeoutMs);
//	ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
//			LimitSwitchNormal normalOpenOrClose, int deviceIDIfApplicable,
//			int timeoutMs);
//	ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
//			LimitSwitchNormal normalOpenOrClose, int deviceIDIfApplicable,
//			int timeoutMs);
//	void EnableLimitSwitches(bool enable);
//	ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit, int timeoutMs);
//	ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit, int timeoutMs);
//	void EnableSoftLimits(bool enable);
//	ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs);
//	ErrorCode ConfigPeakCurrentDuration(int milliseconds, int timeoutMs);
//	ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs);
//	void EnableCurrentLimit(bool enable);
//	ErrorCode Config_kP(int slotIdx, float value, int timeoutMs);
//	ErrorCode Config_kI(int slotIdx, float value, int timeoutMs);
//	ErrorCode Config_kD(int slotIdx, float value, int timeoutMs);
//	ErrorCode Config_kF(int slotIdx, float value, int timeoutMs);
//	ErrorCode Config_IntegralZone(int slotIdx, int izone, int timeoutMs);
//	ErrorCode ConfigAllowableClosedloopError(int slotIdx,
//			int allowableCloseLoopError, int timeoutMs);
//	ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, float iaccum,
//			int timeoutMs);
//	ErrorCode SetIntegralAccumulator(float iaccum, int timeoutMs);
//	ErrorCode GetClosedLoopError(int & error, int pidIdx);
//	ErrorCode GetIntegralAccumulator(float & iaccum, int pidIdx);
//	ErrorCode GetErrorDerivative(float & derivError, int pidIdx);
//	void SelectProfileSlot(int slotIdx);
//	ErrorCode SetMotionAcceleration(int sensorUnitsPer100msPerSec,
//			int timeoutMs)/* implemented in child class */;
//	ErrorCode GetFaults(Faults & toFill);
//	ErrorCode GetStickyFaults(Faults & toFill);
//	ErrorCode ClearStickyFaults(int timeoutMs);
//	ErrorCode ConfigSetCustomParam(int value, int paramIndex, int timeoutMs);
//	ErrorCode ConfigGetCustomParam(int & value, int paramIndex, int timeoutMs);
//	ErrorCode GetAnalogInWithOv(int & param);
//	ErrorCode GetAnalogInVel(int & param);
//	ErrorCode GetQuadraturePosition(int & param);
//	ErrorCode GetQuadratureVelocity(int & param);
//	ErrorCode GetPulseWidthPosition(int & param);
//	ErrorCode GetPulseWidthVelocity(int & param);
//	ErrorCode GetPulseWidthRiseToFallUs(int & param);
//	ErrorCode GetPulseWidthRiseToRiseUs(int & param);
//	ErrorCode GetPinStateQuadA(int & param);
//	ErrorCode GetPinStateQuadB(int & param);
//	ErrorCode GetPinStateQuadIdx(int & param);
//	ErrorCode IsFwdLimitSwitchClosed(int & param);
//	ErrorCode IsRevLimitSwitchClosed(int & param);
//	void SetClrBit(int bit, int shift, uint baseId);
//	void SetClrSmallVal(int value, int bitTotal, int byteIdx, int bitShift_LE,
//			uint baseId);
//	ErrorCode GetLastError();
//
//	ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms, int timeoutMs);
//	ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec, int timeoutMs);
//
//private:
//
//	void CheckFirm(int minFirm, const char * message);
//
//	uint64_t _cache = 0;
//	int32_t _len = 0;
//	ErrorCode _lastError;
//
//};
