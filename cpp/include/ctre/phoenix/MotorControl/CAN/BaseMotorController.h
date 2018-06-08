#pragma once

#include "ctre/phoenix/ErrorCode.h"
#include "ctre/phoenix/paramEnum.h"
#include "ctre/phoenix/core/GadgeteerUartClient.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/ControlMode.h"
#include "ctre/phoenix/MotorControl/DemandType.h"
#include "ctre/phoenix/MotorControl/Faults.h"
#include "ctre/phoenix/MotorControl/FollowerType.h"
#include "ctre/phoenix/MotorControl/StickyFaults.h"
#include "ctre/phoenix/MotorControl/VelocityMeasPeriod.h"
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"
#include "ctre/phoenix/LowLevel/CANBusAddressable.h"
#include "ctre/phoenix/CustomParamConfiguration.h"
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
struct BasePIDSetConfiguration {

	double selectedFeedbackCoefficient;
	SensorTerm sensorTerm;

	//Remote feedback filter information isn't used unless the device is a remote
	int remoteSensorDeviceID; 
	RemoteSensorSource remoteSensorSource;  
	 
	BasePIDSetConfiguration() :
		selectedFeedbackCoefficient(1.0),
		sensorTerm(SensorTerm::SensorTerm_Sum0), 
        remoteSensorDeviceID(0), 
        remoteSensorSource(RemoteSensorSource::RemoteSensorSource_Off) 	
	{
	}
};// struct BasePIDSetConfiguration

struct SlotConfiguration{

	double kP; 
	double kI; 
	double kD; 
	double kF; 
	int integralZone; 
	int allowableClosedloopError; 
	double maxIntegralAccumulator; 
	double closedLoopPeakOutput;
	int closedLoopPeriod;
		
	SlotConfiguration() : 
		kP(0.0), 
		kI(0.0),
		kD(0.0),
		kF(0.0),
		integralZone(0.0), 
		allowableClosedloopError(0.0), 
		maxIntegralAccumulator(0.0),
		closedLoopPeakOutput(1.0),
		closedLoopPeriod(1)
	{
	}
};// struct BaseSlotConfiguration


struct BaseMotorControllerConfiguration : ctre::phoenix::CustomParamConfiguration {
	double openloopRamp;
	double closedloopRamp; 
	double peakOutputForward;
	double peakOutputReverse;
	double nominalOutputForward; 
	double nominalOutputReverse; 
	double neutralDeadband;
	double voltageCompSaturation; 
	int voltageMeasurementFilter;
	VelocityMeasPeriod velocityMeasurementPeriod; 
	int velocityMeasurementWindow; 
	int forwardLimitSwitchDeviceID; //Limit Switch device id isn't used unless device is a remote
	int reverseLimitSwitchDeviceID;
	LimitSwitchNormal forwardLimitSwitchNormal;
	LimitSwitchNormal reverseLimitSwitchNormal;
	int forwardSoftLimitThreshold; 
	int reverseSoftLimitThreshold; 
	bool forwardSoftLimitEnable; 
	bool reverseSoftLimitEnable; 
	SlotConfiguration slot_0;
	SlotConfiguration slot_1;
	SlotConfiguration slot_2;
	SlotConfiguration slot_3;
	bool auxPIDPolarity; 
	int motionCruiseVelocity; 
	int motionAcceleration; 
	int motionProfileTrajectoryPeriod; 
	BaseMotorControllerConfiguration() :
			openloopRamp(0.0),
			closedloopRamp(0.0),
			peakOutputForward(1.0),
			peakOutputReverse(-1.0),
			nominalOutputForward(0.0),
			nominalOutputReverse(0.0),
			neutralDeadband(0.04),
			voltageCompSaturation(0.0),
			voltageMeasurementFilter(32),
			velocityMeasurementPeriod(Period_100Ms),
			velocityMeasurementWindow(64),
			forwardLimitSwitchDeviceID(0),
			reverseLimitSwitchDeviceID(0),
			forwardLimitSwitchNormal(LimitSwitchNormal_NormallyOpen), 
			reverseLimitSwitchNormal(LimitSwitchNormal_NormallyOpen), 
			//Can a remote encoder be used for soft limits if there is a local encoder? etc? 
			forwardSoftLimitThreshold(0),
			reverseSoftLimitThreshold(0), 
			forwardSoftLimitEnable(false),
			reverseSoftLimitEnable(false),
			auxPIDPolarity(false), 
			motionCruiseVelocity(0),
			motionAcceleration(0),
			motionProfileTrajectoryPeriod(0) 
	{
	}	
};// struct BaseMotorControllerConfiguration

/**
 * Base motor controller features for all CTRE CAN motor controllers.
 */
class BaseMotorController: public virtual IMotorController {
private:
	ControlMode m_controlMode = ControlMode::PercentOutput;
	ControlMode m_sendMode = ControlMode::PercentOutput;

	int _arbId = 0;
	double m_setPoint = 0;
	bool _invert = false;

	ctre::phoenix::motorcontrol::SensorCollection * _sensorColl;
protected:
	void* m_handle;
	void* GetHandle();
	virtual ctre::phoenix::ErrorCode BaseConfigAllSettings(const BaseMotorControllerConfiguration &allConfigs, int timeoutMs);
	virtual void BaseGetAllConfigs(BaseMotorControllerConfiguration &allConfigs, int timeoutMs);
	virtual ctre::phoenix::ErrorCode BaseConfigurePID(const BasePIDSetConfiguration &pid, int pidIdx, int timeoutMs);
	virtual void BaseGetPIDConfigs(BasePIDSetConfiguration &pid, int pidIdx, int timeoutMs);
public:
	BaseMotorController(int arbId);
	~BaseMotorController();
	BaseMotorController() = delete;
	BaseMotorController(BaseMotorController const&) = delete;
	BaseMotorController& operator=(BaseMotorController const&) = delete;
	int GetDeviceID();
	virtual void Set(ControlMode Mode, double value);
	virtual void Set(ControlMode mode, double demand0, double demand1);
	virtual void Set(ControlMode mode, double demand0, DemandType demand1Type, double demand1);
	virtual void NeutralOutput();
	virtual void SetNeutralMode(NeutralMode neutralMode);
	void EnableHeadingHold(bool enable);
	void SelectDemandType(bool value);
	//------ Invert behavior ----------//
	virtual void SetSensorPhase(bool PhaseSensor);
	virtual void SetInverted(bool invert);
	virtual bool GetInverted() const;
	//----- general output shaping ------------------//
	virtual ctre::phoenix::ErrorCode ConfigOpenloopRamp(double secondsFromNeutralToFull,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedloopRamp(double secondsFromNeutralToFull,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigPeakOutputForward(double percentOut, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigPeakOutputReverse(double percentOut, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigNominalOutputForward(double percentOut,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigNominalOutputReverse(double percentOut,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigNeutralDeadband(double percentDeadband,
			int timeoutMs = 0);
	//------ Voltage Compensation ----------//
	virtual ctre::phoenix::ErrorCode ConfigVoltageCompSaturation(double voltage, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
			int timeoutMs = 0);
	virtual void EnableVoltageCompensation(bool enable);
	//------ General Status ----------//
	virtual double GetBusVoltage();
	virtual double GetMotorOutputPercent();
	virtual double GetMotorOutputVoltage();
	virtual double GetOutputCurrent();
	virtual double GetTemperature();
	//------ sensor selection ----------//
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(
			RemoteFeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(
			FeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackCoefficient(
			double coefficient, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigRemoteFeedbackFilter(int deviceID,
			RemoteSensorSource remoteSensorSource, int remoteOrdinal,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSensorTerm(SensorTerm sensorTerm,
			FeedbackDevice feedbackDevice, int timeoutMs = 0);

	//------- sensor status --------- //
	virtual int GetSelectedSensorPosition(int pidIdx = 0);
	virtual int GetSelectedSensorVelocity(int pidIdx = 0);
	virtual ctre::phoenix::ErrorCode SetSelectedSensorPosition(int sensorPos, int pidIdx = 0, int timeoutMs = 50);
	//------ status frame period changes ----------//
	virtual ctre::phoenix::ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,
			int periodMs, int timeoutMs = 0);
	virtual int GetStatusFramePeriod(StatusFrame frame, int timeoutMs = 0);
	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs = 0);
	//----- velocity signal conditionaing ------//
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs = 0);
	//------ remote limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs = 0);
	void OverrideLimitSwitchesEnable(bool enable);
	//------ local limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	//------ soft limit ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardSoftLimitThreshold(int forwardSensorLimit,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseSoftLimitThreshold(int reverseSensorLimit,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigForwardSoftLimitEnable(bool enable,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseSoftLimitEnable(bool enable,
			int timeoutMs = 0);		
	virtual void OverrideSoftLimitsEnable(bool enable);
	//------ Current Lim ----------//
	/* not available in base */
	//------ General Close loop ----------//
	virtual ctre::phoenix::ErrorCode Config_kP(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kI(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kD(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kF(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_IntegralZone(int slotIdx, int izone,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigAllowableClosedloopError(int slotIdx,
			int allowableCloseLoopError, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, double iaccum,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedLoopPeakOutput(int slotIdx, double percentOut, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedLoopPeriod(int slotIdx, int loopTimeMs, int timeoutMs = 0);
	
	//Overloads for defaults:
	
	virtual ctre::phoenix::ErrorCode Config_kP(double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kI(double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kD(double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kF(double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_IntegralZone(int izone,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigAllowableClosedloopError(int allowableCloseLoopError, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigMaxIntegralAccumulator(double iaccum,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedLoopPeakOutput(double percentOut, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedLoopPeriod(int loopTimeMs, int timeoutMs = 0);






	virtual ctre::phoenix::ErrorCode ConfigAuxPIDPolarity(bool invert, int timeoutMs = 0);

	//------ Close loop State ----------//
	virtual ctre::phoenix::ErrorCode SetIntegralAccumulator(double iaccum, int pidIdx = 0,int timeoutMs = 0);
	virtual int GetClosedLoopError(int pidIdx = 0);
	virtual double GetIntegralAccumulator(int pidIdx = 0);
	virtual double GetErrorDerivative(int pidIdx = 0);

	virtual ctre::phoenix::ErrorCode SelectProfileSlot(int slotIdx, int pidIdx);

	virtual int GetClosedLoopTarget(int pidIdx = 0);
	virtual int GetActiveTrajectoryPosition();
	virtual int GetActiveTrajectoryVelocity();
	virtual double GetActiveTrajectoryHeading();

	//------ Motion Profile Settings used in Motion Magic  ----------//
	virtual ctre::phoenix::ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs = 0);
	//------ Motion Profile Buffer ----------//
	virtual ErrorCode ClearMotionProfileTrajectories();
	virtual int GetMotionProfileTopLevelBufferCount();
	virtual ctre::phoenix::ErrorCode PushMotionProfileTrajectory(
			const ctre::phoenix::motion::TrajectoryPoint & trajPt);
	virtual bool IsMotionProfileTopLevelBufferFull();
	virtual void ProcessMotionProfileBuffer();
	virtual ctre::phoenix::ErrorCode GetMotionProfileStatus(
			ctre::phoenix::motion::MotionProfileStatus & statusToFill);
	virtual ctre::phoenix::ErrorCode ClearMotionProfileHasUnderrun(int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ChangeMotionControlFramePeriod(int periodMs);
	virtual ctre::phoenix::ErrorCode ConfigMotionProfileTrajectoryPeriod(int baseTrajDurationMs, int timeoutMs = 0);
	//------ error ----------//
	virtual ctre::phoenix::ErrorCode GetLastError();
	//------ Faults ----------//
	virtual ctre::phoenix::ErrorCode GetFaults(Faults & toFill);
	virtual ctre::phoenix::ErrorCode GetStickyFaults(StickyFaults & toFill);
	virtual ctre::phoenix::ErrorCode ClearStickyFaults(int timeoutMs = 0);
	//------ Firmware ----------//
	virtual int GetFirmwareVersion();
	virtual bool HasResetOccurred();
	//------ Custom Persistent Params ----------//
	virtual ctre::phoenix::ErrorCode ConfigSetCustomParam(int newValue, int paramIndex,
			int timeoutMs = 0);
	virtual int ConfigGetCustomParam(int paramIndex,
			int timeoutMs = 0);
	//------ Generic Param API, typically not used ----------//
	virtual ctre::phoenix::ErrorCode ConfigSetParameter(ctre::phoenix::ParamEnum param, double value,
			uint8_t subValue, int ordinal, int timeoutMs = 0);
	virtual double ConfigGetParameter(ctre::phoenix::ParamEnum param, int ordinal, int timeoutMs = 0);
	//------ Misc. ----------//
	virtual int GetBaseID();
	virtual ControlMode GetControlMode();
	// ----- Follower ------//
	void Follow(IMotorController & masterToFollow, ctre::phoenix::motorcontrol::FollowerType followerType);
	virtual void Follow(IMotorController & masterToFollow);
	virtual void ValueUpdated();

	//------ RAW Sensor API ----------//
	/**
	 * @retrieve object that can get/set individual RAW sensor values.
	 */
	ctre::phoenix::motorcontrol::SensorCollection & GetSensorCollection();
	//-------Config All----------//
	ctre::phoenix::ErrorCode ConfigureSlot(const SlotConfiguration &slot, int slotIdx = 0, int timeoutMs = 50);	
	void GetSlotConfigs(SlotConfiguration &slot, int slotIdx = 0, int timeoutMs = 50);	
	
};// class BaseMotorController
} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
