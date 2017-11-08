#pragma once

#include "ctre/phoenix/core/GadgeteerUartClient.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/ControlMode.h"
#include "ctre/phoenix/MotorControl/Faults.h"
#include "ctre/phoenix/MotorControl/VelocityMeasPeriod.h"
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"

/* forward proto's */
class MotControllerWithBuffer_LowLevel;
class MotController_LowLevel;

namespace CTRE {
namespace MotorControl {
namespace CAN {

class BaseMotorController: public virtual IMotorController {
private:
	ErrorCode _lastError = (ErrorCode)0;
	// _sensColl;

	ControlMode m_controlMode = ControlMode::PercentOutput;
	ControlMode m_sendMode = ControlMode::PercentOutput;

	int _arbId = 0;
	float m_setPoint = 0;
	bool _invert = false;
	int m_profile = 0;

	ErrorCode SetLastError(int error);
	ErrorCode SetLastError(ErrorCode error);
protected:
	//MotController_LowLevel & _ll;
	MotController_LowLevel *_ll; //!< Heap alloced member
	MotController_LowLevel & GetLowLevel();
public:
	BaseMotorController(int arbId);
	int GetDeviceID();
	void Set(ControlMode Mode, float value);
	void Set(ControlMode mode, float demand0, float demand1);
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
	ErrorCode ConfigNeutralDeadband(float percentDeadband,
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
	ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice,
			int timeoutMs);
	//------- sensor status --------- //
	int GetSelectedSensorPosition();
	int GetSelectedSensorVelocity();
	ErrorCode SetSelectedSensorPosition(int sensorPos, int timeoutMs);
	//------ status frame period changes ----------//
	ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
	ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs);
	ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame, int periodMs,
			int timeoutMs);
	ErrorCode GetStatusFramePeriod(StatusFrame frame, int & periodMs,
			int timeoutMs);
	ErrorCode GetStatusFramePeriod(StatusFrameEnhanced frame, int & periodMs,
			int timeoutMs);
	//----- velocity signal conditionaing ------//
	ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs);
	ErrorCode ConfigVelocityMeasurementWindow(int windowSize, int timeoutMs);
	//------ remote limit switch ----------//
	ErrorCode ConfigForwardLimitSwitchSource(RemoteLimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	ErrorCode ConfigReverseLimitSwitchSource(RemoteLimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	void EnableLimitSwitches(bool enable);
	//------ local limit switch ----------//
	ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	//------ soft limit ----------//
	ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit, int timeoutMs);
	ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit, int timeoutMs);
	void EnableSoftLimits(bool enable);
	//------ Current Lim ----------//
	/* not available in base */
	//------ General Close loop ----------//
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
	ErrorCode GetClosedLoopError(int & closedLoopError);
	ErrorCode GetIntegralAccumulator(float & iaccum);
	ErrorCode GetErrorDerivative(float & derror);
	void SelectProfileSlot(int slotIdx);
	//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
	ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms,
			int timeoutMs);
	ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs);
	//------ Motion Profile Buffer ----------//
	void ClearMotionProfileTrajectories();
	int GetMotionProfileTopLevelBufferCount();
	bool IsMotionProfileTopLevelBufferFull();
	void ProcessMotionProfileBuffer();
	void GetMotionProfileStatus(CTRE::Motion::MotionProfileStatus statusToFill);
	//ErrorCode PushMotionProfileTrajectory(const CTRE::Motion::TrajectoryPoint & trajPt);
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
	ErrorCode ConfigSetParameter(ParamEnum param, float value, uint8_t subValue,
			int ordinal, int timeoutMs);
	ErrorCode ConfigGetParameter(ParamEnum param, float & value, int ordinal,
			int timeoutMs);
	//------ Misc. ----------//
	int GetBaseID();
	// ----- Follower ------//
	void Follow(IMotorController & masterToFollow);
	void ValueUpdated();
	//------ RAW Sensor API ----------//
	/**
	 * @retrieve object that can get/set individual RAW sensor values.
	 */
	//SensorCollection & SensorCollection();
};

}
}
}
