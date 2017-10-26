#pragma once

#include "ctre/phoenix/MotorControl/ControlMode.h"
#include "ctre/phoenix/MotorControl/ControlFrame.h"
#include "ctre/phoenix/MotorControl/NeutralMode.h"
#include "ctre/phoenix/MotorControl/FeedbackDevice.h"
#include "ctre/phoenix/MotorControl/StatusFrame.h"
#include "ctre/phoenix/MotorControl/LimitSwitchType.h"
#include "ctre/phoenix/MotorControl/Faults.h"
#include "ctre/phoenix/framing/ParamEnum.h"
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"
#include "ctre/phoenix/core/ErrorCode.h"
#include "IFollower.h"

namespace CTRE {
namespace MotorControl {

class IMotorController: public IFollower {
public:
	virtual ~IMotorController() {
	}
	//------ Set output routines. ----------//
	virtual void Set(ControlMode Mode, float demand) = 0;
	virtual void Set(ControlMode Mode, float demand0, float demand1) = 0;
	virtual void NeutralOutput() = 0;
	virtual void SetNeutralMode(NeutralMode neutralMode) = 0;

	//------ Invert behavior ----------//
	virtual void SetSensorPhase(bool PhaseSensor) = 0;
	virtual void SetInverted(bool invert) = 0;
	virtual bool GetInverted() = 0;

	//----- general output shaping ------------------//
	virtual ErrorCode ConfigOpenloopRamp(float secondsFromNeutralToFull,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigClosedloopRamp(float secondsFromNeutralToFull,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigPeakOutputForward(float percentOut,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigPeakOutputReverse(float percentOut,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigNominalOutputForward(float percentOut,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigNominalOutputReverse(float percentOut,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigOpenLoopNeutralDeadband(float percentDeadband,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigClosedLoopNeutralDeadband(float percentDeadband,
			int timeoutMs) = 0;

	//------ Voltage Compensation ----------//
	virtual ErrorCode ConfigVoltageCompSaturation(float voltage,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
			int timeoutMs) = 0;
	virtual void EnableVoltageCompensation(bool enable) = 0;

	//------ General Status ----------//
	virtual ErrorCode GetBusVoltage(float & param) = 0;
	virtual ErrorCode GetMotorOutputPercent(float & param) = 0;
	virtual ErrorCode GetMotorOutputVoltage(float & param) = 0;
	virtual ErrorCode GetOutputCurrent(float & param) = 0;
	virtual ErrorCode GetTemperature(float & param) = 0;

	//------ sensor selection ----------//
	virtual ErrorCode ConfigSelectedFeedbackSensor(
			RemoteFeedbackDevice feedbackDevice, int timeoutMs) = 0;

	//------- sensor status --------- //
	virtual int GetSelectedSensorPosition() = 0;
	virtual int GetSelectedSensorVelocity() = 0;
	virtual ErrorCode SetSelectedSensorPosition(int sensorPos,
			int timeoutMs) = 0;

	//------ status frame period changes ----------//
	virtual ErrorCode SetControlFramePeriod(ControlFrame frame,
			int periodMs) = 0;
	virtual ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs) = 0;
	virtual ErrorCode GetStatusFramePeriod(StatusFrame frame, int & periodMs,
			int timeoutMs) = 0;

	//----- velocity signal conditionaing ------//
	/* not supported */

	//------ remote limit switch ----------//
	virtual ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs) = 0;
	virtual ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs) = 0;
	virtual void EnableLimitSwitches(bool enable) = 0;

	//------ local limit switch ----------//
	/* not supported */

	//------ soft limit ----------//
	virtual ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit,
			int timeoutMs) = 0;

	virtual void EnableSoftLimits(bool enable) = 0;

	//------ Current Lim ----------//
	/* not supported */

	//------ General Close loop ----------//
	virtual ErrorCode Config_kP(int slotIdx, float value, int timeoutMs) = 0;
	virtual ErrorCode Config_kI(int slotIdx, float value, int timeoutMs) = 0;
	virtual ErrorCode Config_kD(int slotIdx, float value, int timeoutMs) = 0;
	virtual ErrorCode Config_kF(int slotIdx, float value, int timeoutMs) = 0;
	virtual ErrorCode Config_IntegralZone(int slotIdx, int izone,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigAllowableClosedloopError(int slotIdx,
			int allowableCloseLoopError, int timeoutMs) = 0;
	virtual ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, float iaccum,
			int timeoutMs) = 0;

	virtual ErrorCode SetIntegralAccumulator(float iaccum, int timeoutMs) = 0;

	virtual ErrorCode GetClosedLoopError(int & error) = 0;
	virtual ErrorCode GetIntegralAccumulator(float & iaccum) = 0;
	virtual ErrorCode GetErrorDerivative(float & derivError) = 0;

	virtual void SelectProfileSlot(int slotIdx) = 0;

	//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
	virtual ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs) = 0;

	//------ Motion Profile Buffer ----------//
//	virtual void ClearMotionProfileTrajectories() = 0;
//	virtual int GetMotionProfileTopLevelBufferCount() = 0;
//	virtual ErrorCode PushMotionProfileTrajectory(
//			CTRE::Motion::TrajectoryPoint trajPt) = 0;
//	virtual bool IsMotionProfileTopLevelBufferFull() = 0;
//	virtual void ProcessMotionProfileBuffer() = 0;
//	virtual void GetMotionProfileStatus(
//			CTRE::Motion::MotionProfileStatus statusToFill) = 0;
//	virtual void ClearMotionProfileHasUnderrun(int timeoutMs) = 0;

//------ error ----------//
	virtual ErrorCode GetLastError() = 0;

	//------ Faults ----------//
	virtual ErrorCode GetFaults(Faults toFill) = 0;
	virtual ErrorCode GetStickyFaults(Faults toFill) = 0;
	virtual ErrorCode ClearStickyFaults() = 0;

	//------ Firmware ----------//
	virtual int GetFirmwareVersion() = 0;
	virtual bool HasResetOccured() = 0;

	//------ Custom Persistent Params ----------//
	virtual ErrorCode ConfigSetCustomParam(int newValue, int paramIndex,
			int timeoutMs) = 0;
	virtual ErrorCode ConfigGetCustomParam(int & readValue, int paramIndex,
			int timeoutMs) = 0;

	//------ Generic Param API, typically not used ----------//
	virtual ErrorCode ConfigSetParameter(ParamEnum param, float value,
			uint8_t subValue, int ordinal, int timeoutMs) = 0;
	virtual ErrorCode ConfigGetParameter(ParamEnum paramEnum, float & value,
			int ordinal, int timeoutMs) = 0;

	//------ Misc. ----------//
	virtual int GetBaseID() = 0;

	// ----- Follower ------//
	/* in parent interface */
};

}
}
