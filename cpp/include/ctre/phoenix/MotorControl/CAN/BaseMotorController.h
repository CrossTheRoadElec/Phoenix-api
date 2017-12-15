#pragma once

#include "ctre/phoenix/ErrorCode.h"
#include "ctre/phoenix/paramEnum.h"
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
namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace lowlevel {
class MotControllerWithBuffer_LowLevel;
class MotController_LowLevel;
}
}
}
}

namespace ctre {
namespace phoenix {
namespace motorcontrol {
class SensorCollection;
}
}
}

namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace can {

class BaseMotorController: public virtual IMotorController {
private:
	ControlMode m_controlMode = ControlMode::PercentOutput;
	ControlMode m_sendMode = ControlMode::PercentOutput;

	int _arbId = 0;
	double m_setPoint = 0;
	bool _invert = false;

	int temp = 0;

	frc::SpeedController * _wpilibSpeedController;

	ctre::phoenix::motorcontrol::SensorCollection * _sensorColl;
protected:
	void* m_handle;
	void* GetHandle();
public:
	BaseMotorController(int arbId);
	~BaseMotorController();
	int GetDeviceID();
	virtual void Set(double value);
	virtual void Set(ControlMode Mode, double value);
	virtual void Set(ControlMode mode, double demand0, double demand1);
	virtual void NeutralOutput();
	virtual void SetNeutralMode(NeutralMode neutralMode);
	void EnableHeadingHold(bool enable);
	void SelectDemandType(bool value);
	//------ Invert behavior ----------//
	virtual void SetSensorPhase(bool PhaseSensor);
	virtual void SetInverted(bool invert);
	virtual bool GetInverted();
	//----- general output shaping ------------------//
	virtual ctre::phoenix::ErrorCode ConfigOpenloopRamp(double secondsFromNeutralToFull,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigClosedloopRamp(double secondsFromNeutralToFull,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigPeakOutputForward(double percentOut, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigPeakOutputReverse(double percentOut, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigNominalOutputForward(double percentOut,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigNominalOutputReverse(double percentOut,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigNeutralDeadband(double percentDeadband,
			int timeoutMs);
	//------ Voltage Compensation ----------//
	virtual ctre::phoenix::ErrorCode ConfigVoltageCompSaturation(double voltage, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
			int timeoutMs);
	virtual void EnableVoltageCompensation(bool enable);
	//------ General Status ----------//
	virtual double GetBusVoltage();
	virtual double GetMotorOutputPercent();
	virtual double GetMotorOutputVoltage();
	virtual double GetOutputCurrent();
	virtual double GetTemperature();
	//------ sensor selection ----------//
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(
			RemoteFeedbackDevice feedbackDevice, int pidIdx, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(
			FeedbackDevice feedbackDevice, int pidIdx, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigRemoteFeedbackFilter(int deviceID,
			RemoteSensorSource remoteSensorSource, int remoteOrdinal,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigSensorTerm(SensorTerm sensorTerm,
			FeedbackDevice feedbackDevice, int timeoutMs);

	//------- sensor status --------- //
	virtual int GetSelectedSensorPosition(int pidIdx);
	virtual int GetSelectedSensorVelocity(int pidIdx);
	virtual ctre::phoenix::ErrorCode SetSelectedSensorPosition(int sensorPos, int pidIdx, int timeoutMs);
	//------ status frame period changes ----------//
	virtual ctre::phoenix::ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,
			int periodMs, int timeoutMs);
	virtual int GetStatusFramePeriod(StatusFrame frame, int timeoutMs);
	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs);
	//----- velocity signal conditionaing ------//
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs);
	//------ remote limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs);
	void EnableLimitSwitches(bool enable);
	//------ local limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs);
	//------ soft limit ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit,
			int timeoutMs);
	virtual void EnableSoftLimits(bool enable);
	//------ Current Lim ----------//
	/* not available in base */
	//------ General Close loop ----------//
	virtual ctre::phoenix::ErrorCode Config_kP(int slotIdx, double value, int timeoutMs);
	virtual ctre::phoenix::ErrorCode Config_kI(int slotIdx, double value, int timeoutMs);
	virtual ctre::phoenix::ErrorCode Config_kD(int slotIdx, double value, int timeoutMs);
	virtual ctre::phoenix::ErrorCode Config_kF(int slotIdx, double value, int timeoutMs);
	virtual ctre::phoenix::ErrorCode Config_IntegralZone(int slotIdx, int izone,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigAllowableClosedloopError(int slotIdx,
			int allowableCloseLoopError, int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, double iaccum,
			int timeoutMs);
	//------ Close loop State ----------//
	virtual ctre::phoenix::ErrorCode SetIntegralAccumulator(double iaccum, int pidIdx,int timeoutMs);
	virtual int GetClosedLoopError(int pidIdx);
	virtual double GetIntegralAccumulator(int pidIdx);
	virtual double GetErrorDerivative(int pidIdx);

	virtual ctre::phoenix::ErrorCode SelectProfileSlot(int slotIdx, int pidIdx);

	virtual int GetClosedLoopTarget(int pidIdx);
	virtual int GetActiveTrajectoryPosition();
	virtual int GetActiveTrajectoryVelocity();
	virtual double GetActiveTrajectoryHeading();

	//------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
	virtual ctre::phoenix::ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms,
			int timeoutMs);
	virtual ctre::phoenix::ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs);
	//------ Motion Profile Buffer ----------//
	virtual void ClearMotionProfileTrajectories();
	virtual int GetMotionProfileTopLevelBufferCount();
	virtual ctre::phoenix::ErrorCode PushMotionProfileTrajectory(
			const ctre::phoenix::motion::TrajectoryPoint & trajPt);
	virtual bool IsMotionProfileTopLevelBufferFull();
	virtual void ProcessMotionProfileBuffer();
	virtual ctre::phoenix::ErrorCode GetMotionProfileStatus(
			ctre::phoenix::motion::MotionProfileStatus & statusToFill);
	virtual ctre::phoenix::ErrorCode ClearMotionProfileHasUnderrun(int timeoutMs);
	virtual ctre::phoenix::ErrorCode ChangeMotionControlFramePeriod(int periodMs);
	//------ error ----------//
	virtual ctre::phoenix::ErrorCode GetLastError();
	//------ Faults ----------//
	virtual ctre::phoenix::ErrorCode GetFaults(Faults & toFill);
	virtual ctre::phoenix::ErrorCode GetStickyFaults(StickyFaults & toFill);
	virtual ctre::phoenix::ErrorCode ClearStickyFaults(int timeoutMs);
	//------ Firmware ----------//
	virtual int GetFirmwareVersion();
	virtual bool HasResetOccured();
	//------ Custom Persistent Params ----------//
	virtual ctre::phoenix::ErrorCode ConfigSetCustomParam(int newValue, int paramIndex,
			int timeoutMs);
	virtual int ConfigGetCustomParam(int paramIndex,
			int timeoutMs);
	//------ Generic Param API, typically not used ----------//
	virtual ctre::phoenix::ErrorCode ConfigSetParameter(ctre::phoenix::ParamEnum param, double value,
			uint8_t subValue, int ordinal, int timeoutMs);
	virtual double ConfigGetParameter(ctre::phoenix::ParamEnum param, int ordinal, int timeoutMs);
	//------ Misc. ----------//
	virtual int GetBaseID();
	// ----- Follower ------//
	virtual void Follow(IMotorController & masterToFollow);
	virtual void ValueUpdated();
	// ----- WPILIB --------//
	virtual frc::SpeedController & GetWPILIB_SpeedController();

	//------ RAW Sensor API ----------//
	/**
	 * @retrieve object that can get/set individual RAW sensor values.
	 */
	ctre::phoenix::motorcontrol::SensorCollection & GetSensorCollection();
};

} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre

