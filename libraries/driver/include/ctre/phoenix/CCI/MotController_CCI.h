#include "ctre/Phoenix/core/ErrorCode.h"

extern "C"{
	void* c_MotController_Create1(int baseArbId);

	ErrorCode c_MotController_GetDeviceNumber(void *handle, int *deviceNumber);
	void c_MotController_SetDemand(void *handle, int mode, int demand0, int demand1);
	void c_MotController_SetNeutralMode(void *handle, int neutralMode);
	void c_MotController_SetSensorPhase(void *handle, bool PhaseSensor);
	void c_MotController_SetInverted(void *handle, bool invert);
	ErrorCode c_MotController_ConfigOpenLoopRamp(void *handle, double secondsFromNeutralToFull, int timeoutMs);
	ErrorCode c_MotController_ConfigClosedLoopRamp(void *handle, double secondsFromNeutralToFull, int timeoutMs);
	ErrorCode c_MotController_ConfigPeakOutputForward(void *handle, double percentOut, int timeoutMs);
	ErrorCode c_MotController_ConfigPeakOutputReverse(void *handle, double percentOut, int timeoutMs);
	ErrorCode c_MotController_ConfigNominalOutputForward(void *handle, double percentOut, int timeoutMs);
	ErrorCode c_MotController_ConfigNominalOutputReverse(void *handle, double percentOut, int timeoutMs);
	ErrorCode c_MotController_ConfigNeutralDeadband(void *handle, double percentDeadband, int timeoutMs);
	ErrorCode c_MotController_ConfigVoltageCompSaturation(void *handle, double voltage, int timeoutMs);
	ErrorCode c_MotController_ConfigVoltageMeasurementFilter(void *handle, int filterWindowSamples, int timeoutMs);
	void c_MotController_EnableVoltageCompensation(void *handle, bool enable);
	ErrorCode c_MotController_GetBusVoltage(void *handle, double *voltage);
	ErrorCode c_MotController_GetMotorOutputPercent(void *handle, double *percentOutput);
	ErrorCode c_MotController_GetOutputCurrent(void *handle, double *current);
	ErrorCode c_MotController_GetTemperature(void *handle, double *temperature);
	ErrorCode c_MotController_ConfigRemoteFeedbackFilter(void *handle, int arbId, int peripheralIdx, int reserved, int timeoutMs);
	ErrorCode c_MotController_ConfigSelectedFeedbackSensor(void *handle, int feedbackDevice, int timeoutMs);
	ErrorCode c_MotController_GetSelectedSensorPosition(void *handle, int *param);
	ErrorCode c_MotController_GetSelectedSensorVelocity(void *handle, int *param);
	ErrorCode c_MotController_SetSelectedSensorPosition(void *handle, int sensorPos, int timeoutMs);
	ErrorCode c_MotController_SetControlFramePeriod(void *handle, int frame, int periodMs);
	ErrorCode c_MotController_SetStatusFramePeriod(void *handle, int frame, int periodMs, int timeoutMs);
	ErrorCode c_MotController_GetStatusFramePeriod(void *handle, int frame, int *periodMs, int timeoutMs);
	ErrorCode c_MotController_ConfigVelocityMeasurementPeriod(void *handle, int period, int timeoutMs);
	ErrorCode c_MotController_ConfigVelocityMeasurementWindow(void *handle, int windowSize, int timeoutMs);
	ErrorCode c_MotController_ConfigForwardLimitSwitchSource(void *handle, int type, int normalOpenOrClose, int deviceID, int timeoutMs);
	ErrorCode c_MotController_ConfigReverseLimitSwitchSource(void *handle, int type, int normalOpenOrClose, int deviceID, int timeoutMs);
	void c_MotController_EnableLimitSwitches(void *handle, bool enable);
	ErrorCode c_MotController_ConfigForwardSoftLimit(void *handle, int forwardSensorLimit, int timeoutMs);
	ErrorCode c_MotController_ConfigReverseSoftLimit(void *handle, int reverseSensorLimit, int timeoutMs);
	void c_MotController_EnableSoftLimits(void *handle, bool enable);
	ErrorCode c_MotController_Config_kP(void *handle, int slotIdx, double value, int timeoutMs);
	ErrorCode c_MotController_Config_kI(void *handle, int slotIdx, double value, int timeoutMs);
	ErrorCode c_MotController_Config_kD(void *handle, int slotIdx, double value, int timeoutMs);
	ErrorCode c_MotController_Config_kF(void *handle, int slotIdx, double value, int timeoutMs);
	ErrorCode c_MotController_Config_IntegralZone(void *handle, int slotIdx, double izone, int timeoutMs);
	ErrorCode c_MotController_ConfigAllowableClosedloopError(void *handle, int slotIdx, int allowableClosedLoopError, int timeoutMs);
	ErrorCode c_MotController_ConfigMaxIntegralAccumulator(void *handle, int slotIdx, double iaccum, int timeoutMs);
	ErrorCode c_MotController_SetIntegralAccumulator(void *handle, double iaccum, int pidIdx, int timeoutMs);
	ErrorCode c_MotController_GetClosedLoopError(void *handle, int *closedLoopError, int pidIdx);
	ErrorCode c_MotController_GetIntegralAccumulator(void *handle, double *iaccum, int pidIdx);
	ErrorCode c_MotController_GetErrorDerivative(void *handle, double *derror, int pidIdx);
	ErrorCode c_MotController_SelectProfileSlot(void *handle, int slotIdx);
	ErrorCode c_MotController_SelectProfileSlotSpecificPID(void *handle, int slotIdx, int pidIdx);
	ErrorCode c_MotController_GetActiveTrajectoryPosition(void *handle, int *param);
	ErrorCode c_MotController_GetActiveTrajectoryVelocity(void *handle, int *param);
	ErrorCode c_MotController_GetActiveTrajectoryHeading(void *handle, double *param);
	ErrorCode c_MotController_ConfigMotionCruiseVelocity(void *handle, int sensorUnitsPer100ms, int timeoutMs);
	ErrorCode c_MotController_ConfigMotionAcceleration(void *handle, int sensorUnitsPer100msPerSec, int timeoutMs);
	ErrorCode c_MotController_ClearMotionProfileTrajectories(void *handle);
	ErrorCode c_MotController_GetMotionProfileTopLevelBufferCount(void *handle, int * value);
	ErrorCode c_MotController_PushMotionProfileTrajectory(void *handle, double position,
			double velocity, double headingDeg, int profileSlotSelect, bool isLastPoint, bool zeroPos);
	ErrorCode c_MotController_IsMotionProfileTopLevelBufferFull(void *handle, bool * value);
	ErrorCode c_MotController_ProcessMotionProfileBuffer(void *handle);
	ErrorCode c_MotController_GetMotionProfileStatus(void *handle,
			uint32_t *topBufferRem, uint32_t *topBufferCnt, uint32_t *btmBufferCnt,
			bool *hasUnderrun, bool *isUnderrun, bool *activePointValid,
			bool *isLast, int *profileSlotSelect, int *outputEnable);
	ErrorCode c_MotController_ClearMotionProfileHasUnderrun(void *handle,
			int timeoutMs);
	ErrorCode c_MotController_ChangeMotionControlFramePeriod(void *handle,
			int periodMs);
	ErrorCode c_MotController_GetLastError(void *handle);
	ErrorCode c_MotController_GetFirmwareVersion(void *handle, int *);
	ErrorCode c_MotController_HasResetOccurred(void *handle,bool *);
	ErrorCode c_MotController_ConfigSetCustomParam(void *handle, int newValue, int paramIndex, int timeoutMs);
	ErrorCode c_MotController_ConfigGetCustomParam(void *handle, int *readValue, int paramIndex, int timoutMs);
	ErrorCode c_MotController_ConfigSetParameter(void *handle, int param, double value, int subValue, int ordinal, int timeoutMs);
	ErrorCode c_MotController_ConfigGetParameter(void *handle, int param, double *value, int ordinal, int timeoutMs);
	ErrorCode c_MotController_ConfigPeakCurrentLimit(void *handle, int amps, int timeoutMs);
	ErrorCode c_MotController_ConfigPeakCurrentDuration(void *handle, int milliseconds, int timeoutMs);
	ErrorCode c_MotController_ConfigContinuousCurrentLimit(void *handle, int amps, int timeoutMs);
	void c_MotController_EnableCurrentLimit(void *handle, bool enable);
	ErrorCode c_MotController_SetLastError(void *handle, int error);
	ErrorCode c_MotController_GetAnalogIn(void *handle, int * param);
	ErrorCode c_MotController_SetAnalogPosition(void *handle,int newPosition, int timeoutMs);
	ErrorCode c_MotController_GetAnalogInRaw(void *handle, int * param);
	ErrorCode c_MotController_GetAnalogInVel(void *handle, int * param);
	ErrorCode c_MotController_GetQuadraturePosition(void *handle, int * param);
	ErrorCode c_MotController_SetQuadraturePosition(void *handle,int newPosition, int timeoutMs);
	ErrorCode c_MotController_GetQuadratureVelocity(void *handle, int * param);
	ErrorCode c_MotController_GetPulseWidthPosition(void *handle, int * param);
	ErrorCode c_MotController_SetPulseWidthPosition(void *handle,int newPosition, int timeoutMs);
	ErrorCode c_MotController_GetPulseWidthVelocity(void *handle, int * param);
	ErrorCode c_MotController_GetPulseWidthRiseToFallUs(void *handle, int * param);
	ErrorCode c_MotController_GetPulseWidthRiseToRiseUs(void *handle, int * param);
	ErrorCode c_MotController_GetPinStateQuadA(void *handle, int * param);
	ErrorCode c_MotController_GetPinStateQuadB(void *handle, int * param);
	ErrorCode c_MotController_GetPinStateQuadIdx(void *handle, int * param);
	ErrorCode c_MotController_IsFwdLimitSwitchClosed(void *handle, int * param);
	ErrorCode c_MotController_IsRevLimitSwitchClosed(void *handle, int * param);
}
