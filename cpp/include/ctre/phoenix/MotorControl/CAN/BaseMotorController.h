#pragma once

#include "ctre/phoenix/core/GadgeteerUartClient.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/ControlMode.h"
#include "ctre/phoenix/MotorControl/Faults.h"
#include "ctre/phoenix/MotorControl/StickyFaults.h"
#include "ctre/phoenix/MotorControl/VelocityMeasPeriod.h"
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"
/* WPILIB */
#include "SpeedController.h"

/* forward proto's */
namespace CTRE {
namespace MotorControl {
namespace LowLevel {
class MotControllerWithBuffer_LowLevel;
class MotController_LowLevel;
}
}
}

namespace CTRE {
namespace MotorControl {
namespace CAN {

class BaseMotorController: public virtual IMotorController{
private:
	ErrorCode _lastError = (ErrorCode)0;

	ControlMode m_controlMode = ControlMode::PercentOutput;
	ControlMode m_sendMode = ControlMode::PercentOutput;

	int _arbId = 0;
	float m_setPoint = 0;
	bool _invert = false;
	int m_profile = 0;

	int temp = 0;

	ErrorCode SetLastError(int error);
	ErrorCode SetLastError(ErrorCode error);

	frc::SpeedController * _wpilibSpeedController;
protected:
	void* m_handle;
	void* GetHandle();
public:
	BaseMotorController(int arbId);
	~BaseMotorController();
	int GetDeviceID();
	virtual void Set(float value);
	virtual void Set(ControlMode Mode, float value);
	virtual void Set(ControlMode mode, float demand0, float demand1);
	virtual void NeutralOutput();
	virtual void SetNeutralMode(NeutralMode neutralMode);
	//------ Invert behavior ----------//
	virtual void SetSensorPhase(bool PhaseSensor);
	virtual void SetInverted(bool invert);
	virtual bool GetInverted();
	//----- general output shaping ------------------//
	virtual ErrorCode ConfigOpenloopRamp(float secondsFromNeutralToFull, int timeoutMs);
	virtual ErrorCode ConfigClosedloopRamp(float secondsFromNeutralToFull,
			int timeoutMs);
	virtual ErrorCode ConfigPeakOutputForward(float percentOut, int timeoutMs);
	virtual ErrorCode ConfigPeakOutputReverse(float percentOut, int timeoutMs);
	virtual ErrorCode ConfigNominalOutputForward(float percentOut, int timeoutMs);
	virtual ErrorCode ConfigNominalOutputReverse(float percentOut, int timeoutMs);
	virtual ErrorCode ConfigNeutralDeadband(float percentDeadband,
			int timeoutMs);
	//------ Voltage Compensation ----------//
	virtual ErrorCode ConfigVoltageCompSaturation(float voltage, int timeoutMs);
	virtual ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
			int timeoutMs);
	virtual void EnableVoltageCompensation(bool enable);
	//------ General Status ----------//
	virtual ErrorCode GetBusVoltage(float & param);
	virtual ErrorCode GetMotorOutputPercent(float & param);
	virtual ErrorCode GetMotorOutputVoltage(float & param);
	virtual ErrorCode GetOutputCurrent(float & param);
	virtual ErrorCode GetTemperature(float & param);
	//------ sensor selection ----------//
	virtual ErrorCode ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice,
			int timeoutMs);
	virtual ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice,
			int timeoutMs);
	//------- sensor status --------- //
	virtual int GetSelectedSensorPosition();
	virtual int GetSelectedSensorVelocity();
	virtual ErrorCode SetSelectedSensorPosition(int sensorPos, int timeoutMs);
	//------ status frame period changes ----------//
	virtual ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
	virtual ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs);
	virtual ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame, int periodMs,
			int timeoutMs);
	virtual ErrorCode GetStatusFramePeriod(StatusFrame frame, int & periodMs,
			int timeoutMs);
	virtual ErrorCode GetStatusFramePeriod(StatusFrameEnhanced frame, int & periodMs,
			int timeoutMs);
	//----- velocity signal conditionaing ------//
	virtual ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs);
	virtual ErrorCode ConfigVelocityMeasurementWindow(int windowSize, int timeoutMs);
	//------ remote limit switch ----------//
	virtual ErrorCode ConfigForwardLimitSwitchSource(RemoteLimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	virtual ErrorCode ConfigReverseLimitSwitchSource(RemoteLimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs);
	void EnableLimitSwitches(bool enable);
	//------ local limit switch ----------//
	virtual ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	virtual ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	//------ soft limit ----------//
	virtual ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit, int timeoutMs);
	virtual ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit, int timeoutMs);
	virtual void EnableSoftLimits(bool enable);
	//------ Current Lim ----------//
	/* not available in base */
	//------ General Close loop ----------//
	virtual ErrorCode Config_kP(int slotIdx, float value, int timeoutMs);
	virtual ErrorCode Config_kI(int slotIdx, float value, int timeoutMs);
	virtual ErrorCode Config_kD(int slotIdx, float value, int timeoutMs);
	virtual ErrorCode Config_kF(int slotIdx, float value, int timeoutMs);
	virtual ErrorCode Config_IntegralZone(int slotIdx, int izone, int timeoutMs);
	virtual ErrorCode ConfigAllowableClosedloopError(int slotIdx,
			int allowableCloseLoopError, int timeoutMs);
	virtual ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, float iaccum,
			int timeoutMs);
	virtual ErrorCode SetIntegralAccumulator(float iaccum, int timeoutMs);
	virtual ErrorCode GetClosedLoopError(int & closedLoopError);
	virtual ErrorCode GetIntegralAccumulator(float & iaccum);
	virtual ErrorCode GetErrorDerivative(float & derror);
	virtual void SelectProfileSlot(int slotIdx);
	//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
	virtual ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms,
			int timeoutMs);
	virtual ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs);
	//------ Motion Profile Buffer ----------//
	//virtual void ClearMotionProfileTrajectories();
	//virtual int GetMotionProfileTopLevelBufferCount();
	//virtual bool IsMotionProfileTopLevelBufferFull();
	//virtual void ProcessMotionProfileBuffer();
	//virtual void GetMotionProfileStatus(CTRE::Motion::MotionProfileStatus statusToFill);
	//ErrorCode PushMotionProfileTrajectory(const CTRE::Motion::TrajectoryPoint & trajPt);
//	virtual void ClearMotionProfileHasUnderrun(int timeoutMs);
	//------ error ----------//
	virtual ErrorCode GetLastError();
	//------ Faults ----------//
	virtual ErrorCode GetFaults(Faults & toFill);
	virtual ErrorCode GetStickyFaults(StickyFaults & toFill);
	virtual ErrorCode ClearStickyFaults(int timeoutMs);
	//------ Firmware ----------//
	virtual int GetFirmwareVersion();
	virtual bool HasResetOccured();
	//------ Custom Persistent Params ----------//
	virtual ErrorCode ConfigSetCustomParam(int newValue, int paramIndex, int timeoutMs);
	virtual ErrorCode ConfigGetCustomParam(int & readValue, int paramIndex,
			int timeoutMs);
	//------ Generic Param API, typically not used ----------//
	virtual ErrorCode ConfigSetParameter(ParamEnum param, float value, uint8_t subValue,
			int ordinal, int timeoutMs);
	virtual ErrorCode ConfigGetParameter(ParamEnum param, float & value, int ordinal,
			int timeoutMs);
	//------ Misc. ----------//
	virtual int GetBaseID();
	// ----- Follower ------//
	virtual void Follow(IMotorController & masterToFollow);
	virtual void ValueUpdated();
	// ----- WPILIB --------//
	virtual SpeedController & GetWPILIB_SpeedController();

	//------ RAW Sensor API ----------//
	/**
	 * @retrieve object that can get/set individual RAW sensor values.
	 */
	//SensorCollection & SensorCollection();
};

}
}
}
