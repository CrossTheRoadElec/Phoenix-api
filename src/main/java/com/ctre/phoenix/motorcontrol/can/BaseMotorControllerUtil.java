package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.CustomParamConfigUtil;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.can.SlotConfiguration;
import com.ctre.phoenix.motorcontrol.can.FilterConfiguration;
import com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration;

/**
 * Util class to help with Base Motor Controller configs
 */
class BaseMotorControllerUtil extends CustomParamConfigUtil {
	private static BaseMotorControllerConfiguration _default = new VictorSPXConfiguration();
	
	static boolean openloopRampDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.openloopRamp == _default.openloopRamp)) || !settings.enableOptimizations; }
	static boolean closedloopRampDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.closedloopRamp == _default.closedloopRamp)) || !settings.enableOptimizations; }
	static boolean peakOutputForwardDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.peakOutputForward == _default.peakOutputForward)) || !settings.enableOptimizations; }
	static boolean peakOutputReverseDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.peakOutputReverse == _default.peakOutputReverse)) || !settings.enableOptimizations; }
	static boolean nominalOutputForwardDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.nominalOutputForward == _default.nominalOutputForward)) || !settings.enableOptimizations; }
	static boolean nominalOutputReverseDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.nominalOutputReverse == _default.nominalOutputReverse)) || !settings.enableOptimizations; }
	static boolean neutralDeadbandDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.neutralDeadband == _default.neutralDeadband)) || !settings.enableOptimizations; }
	static boolean voltageCompSaturationDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.voltageCompSaturation == _default.voltageCompSaturation)) || !settings.enableOptimizations; }
	static boolean voltageMeasurementFilterDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.voltageMeasurementFilter == _default.voltageMeasurementFilter)) || !settings.enableOptimizations; }
	static boolean velocityMeasurementPeriodDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.velocityMeasurementPeriod == _default.velocityMeasurementPeriod)) || !settings.enableOptimizations; }
	static boolean velocityMeasurementWindowDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.velocityMeasurementWindow == _default.velocityMeasurementWindow)) || !settings.enableOptimizations; }
	static boolean forwardSoftLimitThresholdDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.forwardSoftLimitThreshold == _default.forwardSoftLimitThreshold)) || !settings.enableOptimizations; }
	static boolean reverseSoftLimitThresholdDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.reverseSoftLimitThreshold == _default.reverseSoftLimitThreshold)) || !settings.enableOptimizations; }
	static boolean forwardSoftLimitEnableDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.forwardSoftLimitEnable == _default.forwardSoftLimitEnable)) || !settings.enableOptimizations; }
	static boolean reverseSoftLimitEnableDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.reverseSoftLimitEnable == _default.reverseSoftLimitEnable)) || !settings.enableOptimizations; }
	static boolean auxPIDPolarityDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.auxPIDPolarity == _default.auxPIDPolarity)) || !settings.enableOptimizations; }
	static boolean motionCruiseVelocityDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.motionCruiseVelocity == _default.motionCruiseVelocity)) || !settings.enableOptimizations; }
	static boolean motionAccelerationDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.motionAcceleration == _default.motionAcceleration)) || !settings.enableOptimizations; }
	static boolean motionSCurveStrength (BaseMotorControllerConfiguration settings) { return (! (settings.motionCurveStrength == _default.motionCurveStrength)) || !settings.enableOptimizations; }
	static boolean motionProfileTrajectoryPeriodDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.motionProfileTrajectoryPeriod == _default.motionProfileTrajectoryPeriod)) || !settings.enableOptimizations; }
	static boolean feedbackNotContinuousDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.feedbackNotContinuous == _default.feedbackNotContinuous)) || !settings.enableOptimizations; }
	static boolean remoteSensorClosedLoopDisableNeutralOnLOSDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.remoteSensorClosedLoopDisableNeutralOnLOS == _default.remoteSensorClosedLoopDisableNeutralOnLOS)) || !settings.enableOptimizations; }
	static boolean clearPositionOnLimitFDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.clearPositionOnLimitF == _default.clearPositionOnLimitF)) || !settings.enableOptimizations; }
	static boolean clearPositionOnLimitRDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.clearPositionOnLimitR == _default.clearPositionOnLimitR)) || !settings.enableOptimizations; }
	static boolean clearPositionOnQuadIdxDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.clearPositionOnQuadIdx == _default.clearPositionOnQuadIdx)) || !settings.enableOptimizations; }
	static boolean limitSwitchDisableNeutralOnLOSDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.limitSwitchDisableNeutralOnLOS == _default.limitSwitchDisableNeutralOnLOS)) || !settings.enableOptimizations; }
	static boolean softLimitDisableNeutralOnLOSDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.softLimitDisableNeutralOnLOS == _default.softLimitDisableNeutralOnLOS)) || !settings.enableOptimizations; }
	static boolean pulseWidthPeriod_EdgesPerRotDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.pulseWidthPeriod_EdgesPerRot == _default.pulseWidthPeriod_EdgesPerRot)) || !settings.enableOptimizations; }
	static boolean pulseWidthPeriod_FilterWindowSzDifferent (BaseMotorControllerConfiguration settings) { return (!(settings.pulseWidthPeriod_FilterWindowSz == _default.pulseWidthPeriod_FilterWindowSz)) || !settings.enableOptimizations; }
	static boolean trajectoryInterpolationEnableDifferent(BaseMotorControllerConfiguration settings) { return (!(settings.trajectoryInterpolationEnable == _default.trajectoryInterpolationEnable)) || !settings.enableOptimizations; }
}