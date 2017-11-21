package com.ctre.phoenix.MotorControl;

import com.ctre.phoenix.ErrorCode;

public interface IMotorController
		extends com.ctre.phoenix.Signals.IOutputSignal, com.ctre.phoenix.Signals.IInvertable, IFollower {
	// ------ Set output routines. ----------//
	public void Set(ControlMode Mode, double demand);

	public void Set(ControlMode Mode, double demand0, double demand1);

	public void NeutralOutput();

	public void SetNeutralMode(NeutralMode neutralMode);

	// ------ Invert behavior ----------//
	public void SetSensorPhase(boolean PhaseSensor);

	public void SetInverted(boolean invert);

	public boolean GetInverted();

	// ----- general output shaping ------------------//
	public ErrorCode ConfigOpenloopRamp(double secondsFromNeutralToFull, int timeoutMs);

	public ErrorCode ConfigClosedloopRamp(double secondsFromNeutralToFull, int timeoutMs);

	public ErrorCode ConfigPeakOutputForward(double percentOut, int timeoutMs);

	public ErrorCode ConfigPeakOutputReverse(double percentOut, int timeoutMs);

	public ErrorCode ConfigNominalOutputForward(double percentOut, int timeoutMs);

	public ErrorCode ConfigNominalOutputReverse(double percentOut, int timeoutMs);

	public ErrorCode ConfigNeutralDeadband(double percentDeadband, int timeoutMs);

	// ------ Voltage Compensation ----------//
	public ErrorCode ConfigVoltageCompSaturation(double voltage, int timeoutMs);

	public ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples, int timeoutMs);

	public void EnableVoltageCompensation(boolean enable);

	// ------ General Status ----------//
	public double GetBusVoltage() ;

	public double GetMotorOutputPercent() ;

	public double GetMotorOutputVoltage() ;

	public double GetOutputCurrent() ;

	public double GetTemperature() ;

	//------ sensor selection ----------//
	public ErrorCode ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int timeoutMs);

	// ------- sensor status --------- //
	public int GetSelectedSensorPosition();

	public int GetSelectedSensorVelocity();

	public ErrorCode SetSelectedSensorPosition(int sensorPos, int timeoutMs);

	// ------ status frame period changes ----------//
	public ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);

	public ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs, int timeoutMs);

	public int GetStatusFramePeriod(StatusFrame frame, int timeoutMs);

	//----- velocity signal conditionaing ------//
	/* not supported */

	//------ remote limit switch ----------//
	public ErrorCode ConfigForwardLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs);

	public ErrorCode ConfigReverseLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs);

	public void EnableLimitSwitches(boolean enable);

	// ------ local limit switch ----------//
	/* not supported */

	// ------ soft limit ----------//
	public ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit, int timeoutMs);

	public ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit, int timeoutMs);

	public void EnableSoftLimits(boolean enable);

	// ------ Current Lim ----------//
	/* not supported */

	// ------ General Close loop ----------//
	public ErrorCode Config_kP(int slotIdx, double value, int timeoutMs);

	public ErrorCode Config_kI(int slotIdx, double value, int timeoutMs);

	public ErrorCode Config_kD(int slotIdx, double value, int timeoutMs);

	public ErrorCode Config_kF(int slotIdx, double value, int timeoutMs);

	public ErrorCode Config_IntegralZone(int slotIdx, int izone, int timeoutMs);

	public ErrorCode ConfigAllowableClosedloopError(int slotIdx, int allowableCloseLoopError, int timeoutMs);

	public ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, double iaccum, int timeoutMs);

	public ErrorCode SetIntegralAccumulator(double iaccum, int timeoutMs);

	public int GetClosedLoopError();

	public double GetIntegralAccumulator() ;

	public double GetErrorDerivative() ;

	public void SelectProfileSlot(int slotIdx);

	// ------ Motion Profile Settings used in Motion Magic and Motion Profile
	public ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms, int timeoutMs);

	public ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec, int timeoutMs);

	// ------ Motion Profile Buffer ----------//
	// public void ClearMotionProfileTrajectories() ;
	// public int GetMotionProfileTopLevelBufferCount() ;
	// public ErrorCode PushMotionProfileTrajectory(
	// CTRE::Motion::TrajectoryPoint trajPt) ;
	// public boolean IsMotionProfileTopLevelBufferFull() ;
	// public void ProcessMotionProfileBuffer() ;
	// public void GetMotionProfileStatus(
	// CTRE::Motion::MotionProfileStatus statusToFill) ;
	// public void ClearMotionProfileHasUnderrun(int timeoutMs) ;

	// ------ error ----------//
	public ErrorCode GetLastError();

	// ------ Faults ----------//
	public ErrorCode GetFaults(Faults toFill) ;

	public ErrorCode GetStickyFaults(StickyFaults toFill) ;

	public ErrorCode ClearStickyFaults(int timeoutMs);

	// ------ Firmware ----------//
	public int GetFirmwareVersion();

	public boolean HasResetOccurred();

	// ------ Custom Persistent Params ----------//
	public ErrorCode ConfigSetCustomParam(int newValue, int paramIndex, int timeoutMs);

	public int ConfigGetCustomParam(int paramIndex, int timoutMs);

	//------ Generic Param API, typically not used ----------//
	public ErrorCode ConfigSetParameter(ParamEnum param, double value, int subValue, int ordinal, int timeoutMs);

	public double ConfigGetParameter(ParamEnum paramEnum, int ordinal, int timeoutMs) ;

	//------ Misc. ----------//
	public int GetBaseID();
	public int GetDeviceID();

	// ----- Follower ------//
	/* in parent interface */
}