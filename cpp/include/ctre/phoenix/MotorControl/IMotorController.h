#pragma once

#include "NeutralMode.h"
#include "ControlMode.h"
#include "IFollower.h"

namespace CTRE {
namespace MotorControl {

class IMotorController: public IFollower {
public:
	~IMotorController() {
	}
	//------ Set output routines. ----------//
	void Set(ControlMode Mode, float demand);
	void Set(ControlMode Mode, float demand0, float demand1);
	void NeutralOutput();
	void SetNeutralMode(NeutralMode neutralMode);

	//------ Invert behavior ----------//
	void SetSensorPhase(bool PhaseSensor);
	void SetInverted(bool invert);
	bool GetInverted();

	//----- general output shaping ------------------//
	ErrorCode ConfigOpenloopRamp(float secondsFromNeutralToFull, int timeoutMs);
	ErrorCode ConfigClosedloopRamp(float secondsFromNeutralToFull,
			int timeoutMs);
	ErrorCode ConfigPeakOutputForward(float percentOut, int timeoutMs);
	ErrorCode ConfigPeakOutputReverse(float percentOut, int timeoutMs);
	ErrorCode ConfigNominalOutputForward(float percentOut, int timeoutMs);
	ErrorCode ConfigNominalOutputReverse(float percentOut, int timeoutMs);
	ErrorCode ConfigOpenLoopNeutralDeadband(float percentDeadband,
			int timeoutMs);
	ErrorCode ConfigClosedLoopNeutralDeadband(float percentDeadband,
			int timeoutMs);

	//------ Voltage Compensation ----------//
	ErrorCode ConfigVoltageCompSaturation(float voltage, int timeoutMs);
	ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
			int timeoutMs);
	void EnableVoltageCompensation(bool enable);

	//------ General Status ----------//
	ErrorCode GetBusVoltage(float & param);
	ErrorCode GetMotorOutputPercent(float & param);
	ErrorCode GetMotorOutputVoltage(float & param);
	ErrorCode GetOutputCurrent(float & param);
	ErrorCode GetTemperature(float & param);

	//------ sensor selection ----------//
	ErrorCode ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice,
			int timeoutMs);

	//------- sensor status --------- //
	int GetSelectedSensorPosition();
	int GetSelectedSensorVelocity();
	ErrorCode SetSelectedSensorPosition(int sensorPos, int timeoutMs);

	//------ status frame period changes ----------//
	ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
	ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs);
	ErrorCode GetStatusFramePeriod(StatusFrame frame, int & periodMs,
			int timeoutMs);

	//----- velocity signal conditionaing ------//
	/* not supported */

	//------ remote limit switch ----------//
	ErrorCode ConfigForwardLimitSwitchSource(RemoteLimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	ErrorCode ConfigReverseLimitSwitchSource(RemoteLimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	void EnableLimitSwitches(bool enable);

	//------ local limit switch ----------//
	/* not supported */

	//------ soft limit ----------//
	ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit, int timeoutMs);
	ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit, int timeoutMs);

	void EnableSoftLimits(bool enable);

	//------ Current Lim ----------//
	/* not supported */

	//------ General Close loop ----------//
	ErrorCode Config_kP(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_kI(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_kD(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_kF(int slotIdx, float value, int timeoutMs);
	ErrorCode Config_IntegralZone(int slotIdx, int izone, int timeoutMs);
	ErrorCode ConfigAllowableClosedloopError(int slotIdx,
			int allowableCloseLoopError, int timeoutMs);
	ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, float iaccum,
			timeoutMs);

	ErrorCode SetIntegralAccumulator(float iaccum = 0, int timeoutMs);

	ErrorCode GetClosedLoopError(int & error);
	ErrorCode GetIntegralAccumulator(float & iaccum);
	ErrorCode GetErrorDerivative(float & derivError);

	void SelectProfileSlot(int slotIdx);

	//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
	ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms,
			int timeoutMs);
	ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs);

	//------ Motion Profile Buffer ----------//
	void ClearMotionProfileTrajectories();
	int GetMotionProfileTopLevelBufferCount();
	ErrorCode PushMotionProfileTrajectory(Motion::TrajectoryPoint trajPt);
	bool IsMotionProfileTopLevelBufferFull();
	void ProcessMotionProfileBuffer();
	void GetMotionProfileStatus(Motion::MotionProfileStatus statusToFill);
	void ClearMotionProfileHasUnderrun(int timeoutMs);

	//------ error ----------//
	ErrorCode GetLastError();

	//------ Faults ----------//
	ErrorCode GetFaults(Faults toFill);
	ErrorCode GetStickyFaults(Faults toFill);
	ErrorCode ClearStickyFaults();

	//------ Firmware ----------//
	int GetFirmwareVersion();
	bool HasResetOccured();

	//------ Custom Persistent Params ----------//
	ErrorCode ConfigSetCustomParam(int newValue, int paramIndex, int timeoutMs);
	ErrorCode ConfigGetCustomParam(int & readValue, int paramIndex,
			int timeoutMs);

	//------ Generic Param API, typically not used ----------//
	ErrorCode ConfigSetParameter(ParamEnum param, float value, byte subValue,
			int ordinal, int timeoutMs);
	ErrorCode ConfigGetParameter(ParamEnum paramEnum, float & value,
			int ordinal, int timeoutMs);

	//------ Misc. ----------//
	int GetBaseID();

	// ----- Follower ------//
	/* in parent interface */
};

}
}
