#pragma once

#include "ctre/Phoenix/LowLevel/Device_LowLevel.h"
#include "ctre/Phoenix/MotorControl/FeedbackDevice.h"
#include "ctre/Phoenix/MotorControl/ControlFrame.h"
#include "ctre/Phoenix/MotorControl/Faults.h"
#include "ctre/Phoenix/MotorControl/StickyFaults.h"
#include "ctre/Phoenix/MotorControl/NeutralMode.h"
#include "ctre/Phoenix/MotorControl/ControlMode.h"
#include "ctre/Phoenix/MotorControl/LimitSwitchType.h"
#include "ctre/Phoenix/MotorControl/StatusFrame.h"
#include "ctre/Phoenix/MotorControl/VelocityMeasPeriod.h"
#include <string>
#include <stdint.h>

/* forward proto's */
enum ErrorCode
: int32_t;
enum ParamEnum
: uint32_t;

namespace CTRE {
namespace MotorControl {
namespace LowLevel {

class MotController_LowLevel: public Device_LowLevel {

protected:
	const uint32_t STATUS_01 = 0x041400;
	const uint32_t STATUS_02 = 0x041440;
	const uint32_t STATUS_03 = 0x041480;
	const uint32_t STATUS_04 = 0x0414C0;
	const uint32_t STATUS_05 = 0x041500;
	const uint32_t STATUS_06 = 0x041540;
	const uint32_t STATUS_07 = 0x041580;
	const uint32_t STATUS_08 = 0x0415C0;
	const uint32_t STATUS_09 = 0x041600;
	const uint32_t STATUS_10 = 0x041640;
	const uint32_t STATUS_11 = 0x041680;
	const uint32_t STATUS_12 = 0x0416C0;
	const uint32_t STATUS_13 = 0x041700;
	const uint32_t STATUS_14 = 0x041740;
	const uint32_t STATUS_15 = 0x041780;

	const uint32_t CONTROL_1 = 0x040000;
	//const uint32_t CONTROL_2 = 0x040040;
	const uint32_t CONTROL_3 = 0x040080;
	const uint32_t CONTROL_5 = 0x040100;
	const uint32_t CONTROL_6 = 0x040140;

	const float FLOAT_TO_FXP_10_22 = (float) 0x400000;
	const float FXP_TO_FLOAT_10_22 = 0.0000002384185791015625f;

	const float FLOAT_TO_FXP_0_8 = (float) 0x100;
	const float FXP_TO_FLOAT_0_8 = 0.00390625f;

	/* Motion Profile Set Output */
	// Motor output is neutral, Motion Profile Executer is not running.
	const int kMotionProf_Disabled = 0;
	// Motor output is updated from Motion Profile Executer, MPE will
	// process the buffered points.
	const int kMotionProf_Enable = 1;
	// Motor output is updated from Motion Profile Executer, MPE will
	// stay processing current trajectory point.
	const int kMotionProf_Hold = 2;

	const int kDefaultControl6PeriodMs = 10;

	void EnableFirmStatusFrame(bool enable);
	ErrorCode SetLastError(ErrorCode errorCode);
	ErrorCode SetLastError(int errorCode);

public:
	MotController_LowLevel(int baseArbId);

	void SetDemand(ControlMode mode, int demand0, int demand1);
	void SelectDemandType(bool enable);
	void SetNeutralMode(NeutralMode neutralMode);
	void SetSensorPhase(bool PhaseSensor);
	void SetInverted(bool invert);

	ErrorCode ConfigOpenLoopRamp(float secondsFromNeutralToFull, int timeoutMs);
	ErrorCode ConfigClosedLoopRamp(float secondsFromNeutralToFull,
			int timeoutMs);
	ErrorCode ConfigPeakOutputForward(float percentOut, int timeoutMs);
	ErrorCode ConfigPeakOutputReverse(float percentOut, int timeoutMs);
	ErrorCode ConfigNominalOutputForward(float percentOut, int timeoutMs);
	ErrorCode ConfigNominalOutputReverse(float percentOut, int timeoutMs);
	ErrorCode ConfigNeutralDeadband(float percentDeadband,
			int timeoutMs);
	ErrorCode ConfigVoltageCompSaturation(float voltage, int timeoutMs);
	ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
			int timeoutMs);
	void EnableVoltageCompensation(bool enable);
	ErrorCode GetBusVoltage(float & param);
	ErrorCode GetMotorOutputPercent(float & param);
	ErrorCode GetOutputCurrent(float & param);
	ErrorCode GetTemperature(float & param);
	ErrorCode ConfigSelectedFeedbackSensor(CTRE::MotorControl::FeedbackDevice feedbackDevice,
			int timeoutMs);
	ErrorCode ConfigRemoteFeedbackFilter(int arbId, int peripheralIdx,
			int reserved, int timeoutMs);
	ErrorCode GetSelectedSensorPosition(int & param);
	ErrorCode GetSelectedSensorVelocity(int & param);
	ErrorCode SetSelectedSensorPosition(int sensorPos, int timeoutMs);
	ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
	ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs);
	ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame, int periodMs,
			int timeoutMs);
	ErrorCode GetStatusFramePeriod(StatusFrame frame, int & periodMs,
			int timeoutMs);
	ErrorCode GetStatusFramePeriod(StatusFrameEnhanced frame, int & periodMs,
			int timeoutMs);
	ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs);
	ErrorCode ConfigVelocityMeasurementWindow(int windowSize, int timeoutMs);
	ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceIDIfApplicable,
			int timeoutMs);
	ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceIDIfApplicable,
			int timeoutMs);
	void EnableLimitSwitches(bool enable);
	ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit, int timeoutMs);
	ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit, int timeoutMs);
	void EnableSoftLimits(bool enable);
	ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs);
	ErrorCode ConfigPeakCurrentDuration(int milliseconds, int timeoutMs);
	ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs);
	void EnableCurrentLimit(bool enable);
	ErrorCode Config_kP(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_kI(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_kD(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_kF(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_IntegralZone(int slotIdx, int izone, int timeoutMs);
	ErrorCode ConfigAllowableClosedloopError(int slotIdx,
			int allowableCloseLoopError, int timeoutMs);
	ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, float iaccum,
			int timeoutMs);
	ErrorCode SetIntegralAccumulator(float iaccum, int timeoutMs);
	ErrorCode GetClosedLoopError(int & error, int pidIdx);
	ErrorCode GetIntegralAccumulator(float & iaccum, int pidIdx);
	ErrorCode GetErrorDerivative(float & derivError, int pidIdx);
	void SelectProfileSlot(int slotIdx);
	ErrorCode SetMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs)/* implemented in child class */;
	ErrorCode GetFaults(Faults & toFill);
	ErrorCode GetStickyFaults(StickyFaults& toFill);
	ErrorCode ClearStickyFaults(int timeoutMs);
	ErrorCode ConfigSetCustomParam(int value, int paramIndex, int timeoutMs);
	ErrorCode ConfigGetCustomParam(int & value, int paramIndex, int timeoutMs);
	ErrorCode GetAnalogInWithOv(int & param);
	ErrorCode GetAnalogInVel(int & param);
	ErrorCode GetQuadraturePosition(int & param);
	ErrorCode GetQuadratureVelocity(int & param);
	ErrorCode GetPulseWidthPosition(int & param);
	ErrorCode GetPulseWidthVelocity(int & param);
	ErrorCode GetPulseWidthRiseToFallUs(int & param);
	ErrorCode GetPulseWidthRiseToRiseUs(int & param);
	ErrorCode GetPinStateQuadA(int & param);
	ErrorCode GetPinStateQuadB(int & param);
	ErrorCode GetPinStateQuadIdx(int & param);
	ErrorCode IsFwdLimitSwitchClosed(int & param);
	ErrorCode IsRevLimitSwitchClosed(int & param);
	ErrorCode GetLastError();

	ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms, int timeoutMs);
	ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec, int timeoutMs);

private:

	void CheckFirm(int minFirm, const char * message);

	uint64_t _cache = 0;
	int32_t _len = 0;
	ErrorCode _lastError = (ErrorCode)0;

};

}
}
}
