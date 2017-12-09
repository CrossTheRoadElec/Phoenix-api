package com.ctre.phoenix.MotorControl;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.ParamEnum;

public interface IMotorController
		extends com.ctre.phoenix.Signals.IOutputSignal, com.ctre.phoenix.Signals.IInvertable, IFollower {
	// ------ Set output routines. ----------//
	public void set(ControlMode Mode, double demand);

	public void set(ControlMode Mode, double demand0, double demand1);

	public void neutralOutput();

	public void setNeutralMode(NeutralMode neutralMode);

	// ------ Invert behavior ----------//
	public void setSensorPhase(boolean PhaseSensor);

	public void setInverted(boolean invert);

	public boolean getInverted();

	// ----- general output shaping ------------------//
	public ErrorCode configOpenloopRamp(double secondsFromNeutralToFull, int timeoutMs);

	public ErrorCode configClosedloopRamp(double secondsFromNeutralToFull, int timeoutMs);

	public ErrorCode configPeakOutputForward(double percentOut, int timeoutMs);

	public ErrorCode configPeakOutputReverse(double percentOut, int timeoutMs);

	public ErrorCode configNominalOutputForward(double percentOut, int timeoutMs);

	public ErrorCode configNominalOutputReverse(double percentOut, int timeoutMs);

	public ErrorCode configNeutralDeadband(double percentDeadband, int timeoutMs);

	// ------ Voltage Compensation ----------//
	public ErrorCode configVoltageCompSaturation(double voltage, int timeoutMs);

	public ErrorCode configVoltageMeasurementFilter(int filterWindowSamples, int timeoutMs);

	public void enableVoltageCompensation(boolean enable);

	// ------ General Status ----------//
	public double getBusVoltage() ;

	public double getMotorOutputPercent() ;

	public double getMotorOutputVoltage() ;

	public double getOutputCurrent() ;

	public double getTemperature() ;

	//------ sensor selection ----------//
	public ErrorCode configSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int timeoutMs);

	// ------- sensor status --------- //
	public int getSelectedSensorPosition();

	public int getSelectedSensorVelocity();

	public ErrorCode setSelectedSensorPosition(int sensorPos, int timeoutMs);

	// ------ status frame period changes ----------//
	public ErrorCode setControlFramePeriod(ControlFrame frame, int periodMs);

	public ErrorCode setStatusFramePeriod(StatusFrame frame, int periodMs, int timeoutMs);

	public int getStatusFramePeriod(StatusFrame frame, int timeoutMs);

	//----- velocity signal conditionaing ------//
	/* not supported */

	//------ remote limit switch ----------//
	public ErrorCode configForwardLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs);

	public ErrorCode configReverseLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs);

	public void enableLimitSwitches(boolean enable);

	// ------ local limit switch ----------//
	/* not supported */

	// ------ soft limit ----------//
	public ErrorCode configForwardSoftLimit(int forwardSensorLimit, int timeoutMs);

	public ErrorCode configReverseSoftLimit(int reverseSensorLimit, int timeoutMs);

	public void enableSoftLimits(boolean enable);

	// ------ Current Lim ----------//
	/* not supported */

	// ------ General Close loop ----------//
	public ErrorCode config_kP(int slotIdx, double value, int timeoutMs);

	public ErrorCode config_kI(int slotIdx, double value, int timeoutMs);

	public ErrorCode config_kD(int slotIdx, double value, int timeoutMs);

	public ErrorCode config_kF(int slotIdx, double value, int timeoutMs);

	public ErrorCode config_IntegralZone(int slotIdx, int izone, int timeoutMs);

	public ErrorCode configAllowableClosedloopError(int slotIdx, int allowableCloseLoopError, int timeoutMs);

	public ErrorCode configMaxIntegralAccumulator(int slotIdx, double iaccum, int timeoutMs);

	public ErrorCode setIntegralAccumulator(double iaccum, int timeoutMs);

	public int getClosedLoopError();

	public double getIntegralAccumulator() ;

	public double getErrorDerivative() ;

	public void selectProfileSlot(int slotIdx);

	// ------ Motion Profile Settings used in Motion Magic and Motion Profile
	public ErrorCode configMotionCruiseVelocity(int sensorUnitsPer100ms, int timeoutMs);

	public ErrorCode configMotionAcceleration(int sensorUnitsPer100msPerSec, int timeoutMs);

	// ------ Motion Profile Buffer ----------//
	// public void ClearMotionProfileTrajectories() ;
	// public int getMotionProfileTopLevelBufferCount() ;
	// public ErrorCode PushMotionProfileTrajectory(
	// CTRE::Motion::TrajectoryPoint trajPt) ;
	// public boolean isMotionProfileTopLevelBufferFull() ;
	// public void ProcessMotionProfileBuffer() ;
	// public void GetMotionProfileStatus(
	// CTRE::Motion::MotionProfileStatus statusToFill) ;
	// public void ClearMotionProfileHasUnderrun(int timeoutMs) ;

	// ------ error ----------//
	public ErrorCode getLastError();

	// ------ Faults ----------//
	public ErrorCode getFaults(Faults toFill) ;

	public ErrorCode getStickyFaults(StickyFaults toFill) ;

	public ErrorCode clearStickyFaults(int timeoutMs);

	// ------ Firmware ----------//
	public int getFirmwareVersion();

	public boolean hasResetOccurred();

	// ------ Custom Persistent Params ----------//
	public ErrorCode configSetCustomParam(int newValue, int paramIndex, int timeoutMs);

	public int configGetCustomParam(int paramIndex, int timoutMs);

	//------ Generic Param API, typically not used ----------//
	public ErrorCode configSetParameter(ParamEnum param, double value, int subValue, int ordinal, int timeoutMs);

	public double configGetParameter(ParamEnum paramEnum, int ordinal, int timeoutMs) ;

	//------ Misc. ----------//
	public int getBaseID();
	public int getDeviceID();

	// ----- Follower ------//
	/* in parent interface */
}