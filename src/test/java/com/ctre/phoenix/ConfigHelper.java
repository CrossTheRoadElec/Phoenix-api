package com.ctre.phoenix;

import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.ctre.phoenix.motorcontrol.can.VictorSPX;
import com.ctre.phoenix.sensors.PigeonIMU;
import com.ctre.phoenix.CANifier;

import com.ctre.phoenix.motorcontrol.can.TalonSRXConfiguration;
import com.ctre.phoenix.motorcontrol.can.VictorSPXConfiguration;
import com.ctre.phoenix.sensors.PigeonIMUConfiguration;
import com.ctre.phoenix.CANifierConfiguration;

import com.ctre.phoenix.ErrorCodeString;

import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.RemoteLimitSwitchSource;
import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.RemoteSensorSource;
import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.VelocityPeriod;

import java.util.List;

public class ConfigHelper {
    public static void ConfigAllIndividualTalon(int id, int timeoutMs, TalonSRXConfiguration testTalonConfigs, List<ErrorCodeString> errorCodes) {
    
        TalonSRX testTalon = new TalonSRX(id);
        
        errorCodes.add(new ErrorCodeString(testTalon.configOpenloopRamp(testTalonConfigs.openloopRamp, timeoutMs),
            "testTalon.configOpenloopRamp(testTalonConfigs.openloopRamp, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedloopRamp(testTalonConfigs.closedloopRamp, timeoutMs),
            "testTalon.configClosedloopRamp(testTalonConfigs.closedloopRamp, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configPeakOutputForward(testTalonConfigs.peakOutputForward, timeoutMs),
            "testTalon.configPeakOutputForward(testTalonConfigs.peakOutputForward, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configPeakOutputReverse(testTalonConfigs.peakOutputReverse, timeoutMs),
            "testTalon.configPeakOutputReverse(testTalonConfigs.peakOutputReverse, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configNominalOutputForward(testTalonConfigs.nominalOutputForward, timeoutMs),
            "testTalon.configNominalOutputForward(testTalonConfigs.nominalOutputForward, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configNominalOutputReverse(testTalonConfigs.nominalOutputReverse, timeoutMs),
            "testTalon.configNominalOutputReverse(testTalonConfigs.nominalOutputReverse, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configNeutralDeadband(testTalonConfigs.neutralDeadband, timeoutMs),
            "testTalon.configNeutralDeadband(testTalonConfigs.neutralDeadband, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configVoltageCompSaturation(testTalonConfigs.voltageCompSaturation, timeoutMs),
            "testTalon.configVoltageCompSaturation(testTalonConfigs.voltageCompSaturation, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configVoltageMeasurementFilter(testTalonConfigs.voltageMeasurementFilter, timeoutMs),
            "testTalon.configVoltageMeasurementFilter(testTalonConfigs.voltageMeasurementFilter, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configVelocityMeasurementPeriod(testTalonConfigs.velocityMeasurementPeriod, timeoutMs),
            "testTalon.configVelocityMeasurementPeriod(testTalonConfigs.velocityMeasurementPeriod, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configVelocityMeasurementWindow(testTalonConfigs.velocityMeasurementWindow, timeoutMs),
            "testTalon.configVelocityMeasurementWindow(testTalonConfigs.velocityMeasurementWindow, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configForwardSoftLimitThreshold(testTalonConfigs.forwardSoftLimitThreshold, timeoutMs),
            "testTalon.configForwardSoftLimitThreshold(testTalonConfigs.forwardSoftLimitThreshold, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configReverseSoftLimitThreshold(testTalonConfigs.reverseSoftLimitThreshold, timeoutMs),
            "testTalon.configReverseSoftLimitThreshold(testTalonConfigs.reverseSoftLimitThreshold, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configForwardSoftLimitEnable(testTalonConfigs.forwardSoftLimitEnable, timeoutMs),
            "testTalon.configForwardSoftLimitEnable(testTalonConfigs.forwardSoftLimitEnable, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configReverseSoftLimitEnable(testTalonConfigs.reverseSoftLimitEnable, timeoutMs),
            "testTalon.configReverseSoftLimitEnable(testTalonConfigs.reverseSoftLimitEnable, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configAuxPIDPolarity(testTalonConfigs.auxPIDPolarity, timeoutMs),
            "testTalon.configAuxPIDPolarity(testTalonConfigs.auxPIDPolarity, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configMotionCruiseVelocity(testTalonConfigs.motionCruiseVelocity, timeoutMs),
            "testTalon.configMotionCruiseVelocity(testTalonConfigs.motionCruiseVelocity, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configMotionAcceleration(testTalonConfigs.motionAcceleration, timeoutMs),
            "testTalon.configMotionAcceleration(testTalonConfigs.motionAcceleration, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configMotionProfileTrajectoryPeriod(testTalonConfigs.motionProfileTrajectoryPeriod, timeoutMs),
            "testTalon.configMotionProfileTrajectoryPeriod(testTalonConfigs.motionProfileTrajectoryPeriod, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configFeedbackNotContinuous(testTalonConfigs.feedbackNotContinuous, timeoutMs),
            "testTalon.configFeedbackNotContinuous(testTalonConfigs.feedbackNotContinuous, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configRemoteSensorClosedLoopDisableNeutralOnLOS(testTalonConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs),
            "testTalon.configRemoteSensorClosedLoopDisableNeutralOnLOS(testTalonConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClearPositionOnLimitF(testTalonConfigs.clearPositionOnLimitF, timeoutMs),
            "testTalon.configClearPositionOnLimitF(testTalonConfigs.clearPositionOnLimitF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClearPositionOnLimitR(testTalonConfigs.clearPositionOnLimitR, timeoutMs),
            "testTalon.configClearPositionOnLimitR(testTalonConfigs.clearPositionOnLimitR, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClearPositionOnQuadIdx(testTalonConfigs.clearPositionOnQuadIdx, timeoutMs),
            "testTalon.configClearPositionOnQuadIdx(testTalonConfigs.clearPositionOnQuadIdx, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configLimitSwitchDisableNeutralOnLOS(testTalonConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs),
            "testTalon.configLimitSwitchDisableNeutralOnLOS(testTalonConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configSoftLimitDisableNeutralOnLOS(testTalonConfigs.softLimitDisableNeutralOnLOS, timeoutMs),
            "testTalon.configSoftLimitDisableNeutralOnLOS(testTalonConfigs.softLimitDisableNeutralOnLOS, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configPulseWidthPeriod_EdgesPerRot(testTalonConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs),
            "testTalon.configPulseWidthPeriod_EdgesPerRot(testTalonConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configPulseWidthPeriod_FilterWindowSz(testTalonConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs),
            "testTalon.configPulseWidthPeriod_FilterWindowSz(testTalonConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs)"));
   
        errorCodes.add(new ErrorCodeString(testTalon.configRemoteFeedbackFilter(testTalonConfigs.remoteFilter0.remoteSensorDeviceID, testTalonConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs),
            "testTalon.configRemoteFeedbackFilter(testTalonConfigs.remoteFilter0.remoteSensorDeviceID, testTalonConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configRemoteFeedbackFilter(testTalonConfigs.remoteFilter1.remoteSensorDeviceID, testTalonConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs),
            "testTalon.configRemoteFeedbackFilter(testTalonConfigs.remoteFilter1.remoteSensorDeviceID, testTalonConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testTalon.config_kP(0, testTalonConfigs.slot0.kP, timeoutMs),
            "testTalon.config_kP(0, testTalonConfigs.slot0.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kI(0, testTalonConfigs.slot0.kI, timeoutMs),
            "testTalon.config_kI(0, testTalonConfigs.slot0.kI, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kD(0, testTalonConfigs.slot0.kD, timeoutMs),
            "testTalon.config_kD(0, testTalonConfigs.slot0.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kF(0, testTalonConfigs.slot0.kF, timeoutMs),
            "testTalon.config_kF(0, testTalonConfigs.slot0.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_IntegralZone(0, testTalonConfigs.slot0.integralZone, timeoutMs),
            "testTalon.config_IntegralZone(0, testTalonConfigs.slot0.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configAllowableClosedloopError(0, testTalonConfigs.slot0.allowableClosedloopError, timeoutMs),
            "testTalon.configAllowableClosedloopError(0, testTalonConfigs.slot0.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configMaxIntegralAccumulator(0, testTalonConfigs.slot0.maxIntegralAccumulator, timeoutMs),
            "testTalon.configMaxIntegralAccumulator(0, testTalonConfigs.slot0.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeakOutput(0, testTalonConfigs.slot0.closedLoopPeakOutput, timeoutMs),
            "testTalon.configClosedLoopPeakOutput(0, testTalonConfigs.slot0.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeriod(0, testTalonConfigs.slot0.closedLoopPeriod, timeoutMs),
            "testTalon.configClosedLoopPeriod(0, testTalonConfigs.slot0.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testTalon.config_kP(1, testTalonConfigs.slot1.kP, timeoutMs),
            "testTalon.config_kP(1, testTalonConfigs.slot1.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kI(1, testTalonConfigs.slot1.kI, timeoutMs),
            "testTalon.config_kI(1, testTalonConfigs.slot1.kI, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kD(1, testTalonConfigs.slot1.kD, timeoutMs),
            "testTalon.config_kD(1, testTalonConfigs.slot1.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kF(1, testTalonConfigs.slot1.kF, timeoutMs),
            "testTalon.config_kF(1, testTalonConfigs.slot1.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_IntegralZone(1, testTalonConfigs.slot1.integralZone, timeoutMs),
            "testTalon.config_IntegralZone(1, testTalonConfigs.slot1.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configAllowableClosedloopError(1, testTalonConfigs.slot1.allowableClosedloopError, timeoutMs),
            "testTalon.configAllowableClosedloopError(1, testTalonConfigs.slot1.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configMaxIntegralAccumulator(1, testTalonConfigs.slot1.maxIntegralAccumulator, timeoutMs),
            "testTalon.configMaxIntegralAccumulator(1, testTalonConfigs.slot1.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeakOutput(1, testTalonConfigs.slot1.closedLoopPeakOutput, timeoutMs),
            "testTalon.configClosedLoopPeakOutput(1, testTalonConfigs.slot1.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeriod(1, testTalonConfigs.slot1.closedLoopPeriod, timeoutMs),
            "testTalon.configClosedLoopPeriod(1, testTalonConfigs.slot1.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testTalon.config_kP(2, testTalonConfigs.slot2.kP, timeoutMs),
            "testTalon.config_kP(2, testTalonConfigs.slot2.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kI(2, testTalonConfigs.slot2.kI, timeoutMs),
            "testTalon.config_kI(2, testTalonConfigs.slot2.kI, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kD(2, testTalonConfigs.slot2.kD, timeoutMs),
            "testTalon.config_kD(2, testTalonConfigs.slot2.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kF(2, testTalonConfigs.slot2.kF, timeoutMs),
            "testTalon.config_kF(2, testTalonConfigs.slot2.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_IntegralZone(2, testTalonConfigs.slot2.integralZone, timeoutMs),
            "testTalon.config_IntegralZone(2, testTalonConfigs.slot2.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configAllowableClosedloopError(2, testTalonConfigs.slot2.allowableClosedloopError, timeoutMs),
            "testTalon.configAllowableClosedloopError(2, testTalonConfigs.slot2.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configMaxIntegralAccumulator(2, testTalonConfigs.slot2.maxIntegralAccumulator, timeoutMs),
            "testTalon.configMaxIntegralAccumulator(2, testTalonConfigs.slot2.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeakOutput(2, testTalonConfigs.slot2.closedLoopPeakOutput, timeoutMs),
            "testTalon.configClosedLoopPeakOutput(2, testTalonConfigs.slot2.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeriod(2, testTalonConfigs.slot2.closedLoopPeriod, timeoutMs),
            "testTalon.configClosedLoopPeriod(2, testTalonConfigs.slot2.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testTalon.config_kP(3, testTalonConfigs.slot3.kP, timeoutMs),
            "testTalon.config_kP(3, testTalonConfigs.slot3.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kI(3, testTalonConfigs.slot3.kI, timeoutMs),
            "testTalon.config_kI(3, testTalonConfigs.slot3.kI, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kD(3, testTalonConfigs.slot3.kD, timeoutMs),
            "testTalon.config_kD(3, testTalonConfigs.slot3.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_kF(3, testTalonConfigs.slot3.kF, timeoutMs),
            "testTalon.config_kF(3, testTalonConfigs.slot3.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.config_IntegralZone(3, testTalonConfigs.slot3.integralZone, timeoutMs),
            "testTalon.config_IntegralZone(3, testTalonConfigs.slot3.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configAllowableClosedloopError(3, testTalonConfigs.slot3.allowableClosedloopError, timeoutMs),
            "testTalon.configAllowableClosedloopError(3, testTalonConfigs.slot3.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configMaxIntegralAccumulator(3, testTalonConfigs.slot3.maxIntegralAccumulator, timeoutMs),
            "testTalon.configMaxIntegralAccumulator(3, testTalonConfigs.slot3.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeakOutput(3, testTalonConfigs.slot3.closedLoopPeakOutput, timeoutMs),
            "testTalon.configClosedLoopPeakOutput(3, testTalonConfigs.slot3.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configClosedLoopPeriod(3, testTalonConfigs.slot3.closedLoopPeriod, timeoutMs),
            "testTalon.configClosedLoopPeriod(3, testTalonConfigs.slot3.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testTalon.configSelectedFeedbackCoefficient(testTalonConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs),
            "testTalon.configSelectedFeedbackCoefficient(testTalonConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configSelectedFeedbackSensor(testTalonConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs),
            "testTalon.configSelectedFeedbackSensor(testTalonConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configSelectedFeedbackCoefficient(testTalonConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs),
            "testTalon.configSelectedFeedbackCoefficient(testTalonConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configSelectedFeedbackSensor(testTalonConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs),
            "testTalon.configSelectedFeedbackSensor(testTalonConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testTalon.configSensorTerm(SensorTerm.Sum0, testTalonConfigs.sum0Term, timeoutMs),
            "testTalon.configSensorTerm(SensorTerm.Sum0, testTalonConfigs.sum0Term, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configSensorTerm(SensorTerm.Sum1, testTalonConfigs.sum1Term, timeoutMs),
            "testTalon.configSensorTerm(SensorTerm.Sum1, testTalonConfigs.sum1Term, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configSensorTerm(SensorTerm.Diff0, testTalonConfigs.diff0Term, timeoutMs),
            "testTalon.configSensorTerm(SensorTerm.Diff0, testTalonConfigs.diff0Term, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configSensorTerm(SensorTerm.Diff1, testTalonConfigs.diff1Term, timeoutMs),
            "testTalon.configSensorTerm(SensorTerm.Diff1, testTalonConfigs.diff1Term, timeoutMs)"));
        
        //Unique to just Talon
        errorCodes.add(new ErrorCodeString(testTalon.configForwardLimitSwitchSource(testTalonConfigs.forwardLimitSwitchSource, testTalonConfigs.forwardLimitSwitchNormal, timeoutMs),
            "testTalon.configForwardLimitSwitchSource(testTalonConfigs.forwardLimitSwitchSource, testTalonConfigs.forwardLimitSwitchNormal, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configReverseLimitSwitchSource(testTalonConfigs.reverseLimitSwitchSource, testTalonConfigs.reverseLimitSwitchNormal, timeoutMs),
            "testTalon.configReverseLimitSwitchSource(testTalonConfigs.reverseLimitSwitchSource, testTalonConfigs.reverseLimitSwitchNormal, timeoutMs)"));
        
        errorCodes.add(new ErrorCodeString(testTalon.configPeakCurrentLimit(testTalonConfigs.peakCurrentLimit, timeoutMs),
            "testTalon.configPeakCurrentLimit(testTalonConfigs.peakCurrentLimit, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configPeakCurrentDuration(testTalonConfigs.peakCurrentDuration, timeoutMs),
            "testTalon.configPeakCurrentDuration(testTalonConfigs.peakCurrentDuration, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testTalon.configContinuousCurrentLimit(testTalonConfigs.continuousCurrentLimit, timeoutMs),
            "testTalon.configContinuousCurrentLimit(testTalonConfigs.continuousCurrentLimit, timeoutMs)"));
    }
    public static void ConfigAllIndividualVictor(int id, int timeoutMs, VictorSPXConfiguration testVictorConfigs, List<ErrorCodeString> errorCodes) {
    
        VictorSPX testVictor = new VictorSPX(id);
        
        errorCodes.add(new ErrorCodeString(testVictor.configOpenloopRamp(testVictorConfigs.openloopRamp, timeoutMs),
            "testVictor.configOpenloopRamp(testVictorConfigs.openloopRamp, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedloopRamp(testVictorConfigs.closedloopRamp, timeoutMs),
            "testVictor.configClosedloopRamp(testVictorConfigs.closedloopRamp, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configPeakOutputForward(testVictorConfigs.peakOutputForward, timeoutMs),
            "testVictor.configPeakOutputForward(testVictorConfigs.peakOutputForward, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configPeakOutputReverse(testVictorConfigs.peakOutputReverse, timeoutMs),
            "testVictor.configPeakOutputReverse(testVictorConfigs.peakOutputReverse, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configNominalOutputForward(testVictorConfigs.nominalOutputForward, timeoutMs),
            "testVictor.configNominalOutputForward(testVictorConfigs.nominalOutputForward, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configNominalOutputReverse(testVictorConfigs.nominalOutputReverse, timeoutMs),
            "testVictor.configNominalOutputReverse(testVictorConfigs.nominalOutputReverse, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configNeutralDeadband(testVictorConfigs.neutralDeadband, timeoutMs),
            "testVictor.configNeutralDeadband(testVictorConfigs.neutralDeadband, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configVoltageCompSaturation(testVictorConfigs.voltageCompSaturation, timeoutMs),
            "testVictor.configVoltageCompSaturation(testVictorConfigs.voltageCompSaturation, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configVoltageMeasurementFilter(testVictorConfigs.voltageMeasurementFilter, timeoutMs),
            "testVictor.configVoltageMeasurementFilter(testVictorConfigs.voltageMeasurementFilter, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configVelocityMeasurementPeriod(testVictorConfigs.velocityMeasurementPeriod, timeoutMs),
            "testVictor.configVelocityMeasurementPeriod(testVictorConfigs.velocityMeasurementPeriod, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configVelocityMeasurementWindow(testVictorConfigs.velocityMeasurementWindow, timeoutMs),
            "testVictor.configVelocityMeasurementWindow(testVictorConfigs.velocityMeasurementWindow, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configForwardSoftLimitThreshold(testVictorConfigs.forwardSoftLimitThreshold, timeoutMs),
            "testVictor.configForwardSoftLimitThreshold(testVictorConfigs.forwardSoftLimitThreshold, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configReverseSoftLimitThreshold(testVictorConfigs.reverseSoftLimitThreshold, timeoutMs),
            "testVictor.configReverseSoftLimitThreshold(testVictorConfigs.reverseSoftLimitThreshold, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configForwardSoftLimitEnable(testVictorConfigs.forwardSoftLimitEnable, timeoutMs),
            "testVictor.configForwardSoftLimitEnable(testVictorConfigs.forwardSoftLimitEnable, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configReverseSoftLimitEnable(testVictorConfigs.reverseSoftLimitEnable, timeoutMs),
            "testVictor.configReverseSoftLimitEnable(testVictorConfigs.reverseSoftLimitEnable, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configAuxPIDPolarity(testVictorConfigs.auxPIDPolarity, timeoutMs),
            "testVictor.configAuxPIDPolarity(testVictorConfigs.auxPIDPolarity, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configMotionCruiseVelocity(testVictorConfigs.motionCruiseVelocity, timeoutMs),
            "testVictor.configMotionCruiseVelocity(testVictorConfigs.motionCruiseVelocity, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configMotionAcceleration(testVictorConfigs.motionAcceleration, timeoutMs),
            "testVictor.configMotionAcceleration(testVictorConfigs.motionAcceleration, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configMotionProfileTrajectoryPeriod(testVictorConfigs.motionProfileTrajectoryPeriod, timeoutMs),
            "testVictor.configMotionProfileTrajectoryPeriod(testVictorConfigs.motionProfileTrajectoryPeriod, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configFeedbackNotContinuous(testVictorConfigs.feedbackNotContinuous, timeoutMs),
            "testVictor.configFeedbackNotContinuous(testVictorConfigs.feedbackNotContinuous, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configRemoteSensorClosedLoopDisableNeutralOnLOS(testVictorConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs),
            "testVictor.configRemoteSensorClosedLoopDisableNeutralOnLOS(testVictorConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClearPositionOnLimitF(testVictorConfigs.clearPositionOnLimitF, timeoutMs),
            "testVictor.configClearPositionOnLimitF(testVictorConfigs.clearPositionOnLimitF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClearPositionOnLimitR(testVictorConfigs.clearPositionOnLimitR, timeoutMs),
            "testVictor.configClearPositionOnLimitR(testVictorConfigs.clearPositionOnLimitR, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClearPositionOnQuadIdx(testVictorConfigs.clearPositionOnQuadIdx, timeoutMs),
            "testVictor.configClearPositionOnQuadIdx(testVictorConfigs.clearPositionOnQuadIdx, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configLimitSwitchDisableNeutralOnLOS(testVictorConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs),
            "testVictor.configLimitSwitchDisableNeutralOnLOS(testVictorConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configSoftLimitDisableNeutralOnLOS(testVictorConfigs.softLimitDisableNeutralOnLOS, timeoutMs),
            "testVictor.configSoftLimitDisableNeutralOnLOS(testVictorConfigs.softLimitDisableNeutralOnLOS, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configPulseWidthPeriod_EdgesPerRot(testVictorConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs),
            "testVictor.configPulseWidthPeriod_EdgesPerRot(testVictorConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configPulseWidthPeriod_FilterWindowSz(testVictorConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs),
            "testVictor.configPulseWidthPeriod_FilterWindowSz(testVictorConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs)"));
   
        errorCodes.add(new ErrorCodeString(testVictor.configRemoteFeedbackFilter(testVictorConfigs.remoteFilter0.remoteSensorDeviceID, testVictorConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs),
            "testVictor.configRemoteFeedbackFilter(testVictorConfigs.remoteFilter0.remoteSensorDeviceID, testVictorConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configRemoteFeedbackFilter(testVictorConfigs.remoteFilter1.remoteSensorDeviceID, testVictorConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs),
            "testVictor.configRemoteFeedbackFilter(testVictorConfigs.remoteFilter1.remoteSensorDeviceID, testVictorConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testVictor.config_kP(0, testVictorConfigs.slot0.kP, timeoutMs),
            "testVictor.config_kP(0, testVictorConfigs.slot0.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kI(0, testVictorConfigs.slot0.kI, timeoutMs),
            "testVictor.config_kI(0, testVictorConfigs.slot0.kI, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kD(0, testVictorConfigs.slot0.kD, timeoutMs),
            "testVictor.config_kD(0, testVictorConfigs.slot0.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kF(0, testVictorConfigs.slot0.kF, timeoutMs),
            "testVictor.config_kF(0, testVictorConfigs.slot0.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_IntegralZone(0, testVictorConfigs.slot0.integralZone, timeoutMs),
            "testVictor.config_IntegralZone(0, testVictorConfigs.slot0.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configAllowableClosedloopError(0, testVictorConfigs.slot0.allowableClosedloopError, timeoutMs),
            "testVictor.configAllowableClosedloopError(0, testVictorConfigs.slot0.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configMaxIntegralAccumulator(0, testVictorConfigs.slot0.maxIntegralAccumulator, timeoutMs),
            "testVictor.configMaxIntegralAccumulator(0, testVictorConfigs.slot0.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeakOutput(0, testVictorConfigs.slot0.closedLoopPeakOutput, timeoutMs),
            "testVictor.configClosedLoopPeakOutput(0, testVictorConfigs.slot0.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeriod(0, testVictorConfigs.slot0.closedLoopPeriod, timeoutMs),
            "testVictor.configClosedLoopPeriod(0, testVictorConfigs.slot0.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testVictor.config_kP(1, testVictorConfigs.slot1.kP, timeoutMs),
            "testVictor.config_kP(1, testVictorConfigs.slot1.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kI(1, testVictorConfigs.slot1.kI, timeoutMs),
            "testVictor.config_kI(1, testVictorConfigs.slot1.kI, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kD(1, testVictorConfigs.slot1.kD, timeoutMs),
            "testVictor.config_kD(1, testVictorConfigs.slot1.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kF(1, testVictorConfigs.slot1.kF, timeoutMs),
            "testVictor.config_kF(1, testVictorConfigs.slot1.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_IntegralZone(1, testVictorConfigs.slot1.integralZone, timeoutMs),
            "testVictor.config_IntegralZone(1, testVictorConfigs.slot1.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configAllowableClosedloopError(1, testVictorConfigs.slot1.allowableClosedloopError, timeoutMs),
            "testVictor.configAllowableClosedloopError(1, testVictorConfigs.slot1.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configMaxIntegralAccumulator(1, testVictorConfigs.slot1.maxIntegralAccumulator, timeoutMs),
            "testVictor.configMaxIntegralAccumulator(1, testVictorConfigs.slot1.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeakOutput(1, testVictorConfigs.slot1.closedLoopPeakOutput, timeoutMs),
            "testVictor.configClosedLoopPeakOutput(1, testVictorConfigs.slot1.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeriod(1, testVictorConfigs.slot1.closedLoopPeriod, timeoutMs),
            "testVictor.configClosedLoopPeriod(1, testVictorConfigs.slot1.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testVictor.config_kP(2, testVictorConfigs.slot2.kP, timeoutMs),
            "testVictor.config_kP(2, testVictorConfigs.slot2.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kD(2, testVictorConfigs.slot2.kD, timeoutMs),
            "testVictor.config_kD(2, testVictorConfigs.slot2.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kF(2, testVictorConfigs.slot2.kF, timeoutMs),
            "testVictor.config_kF(2, testVictorConfigs.slot2.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_IntegralZone(2, testVictorConfigs.slot2.integralZone, timeoutMs),
            "testVictor.config_IntegralZone(2, testVictorConfigs.slot2.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configAllowableClosedloopError(2, testVictorConfigs.slot2.allowableClosedloopError, timeoutMs),
            "testVictor.configAllowableClosedloopError(2, testVictorConfigs.slot2.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configMaxIntegralAccumulator(2, testVictorConfigs.slot2.maxIntegralAccumulator, timeoutMs),
            "testVictor.configMaxIntegralAccumulator(2, testVictorConfigs.slot2.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeakOutput(2, testVictorConfigs.slot2.closedLoopPeakOutput, timeoutMs),
            "testVictor.configClosedLoopPeakOutput(2, testVictorConfigs.slot2.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeriod(2, testVictorConfigs.slot2.closedLoopPeriod, timeoutMs),
            "testVictor.configClosedLoopPeriod(2, testVictorConfigs.slot2.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testVictor.config_kP(3, testVictorConfigs.slot3.kP, timeoutMs),
            "testVictor.config_kP(3, testVictorConfigs.slot3.kP, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kI(3, testVictorConfigs.slot3.kI, timeoutMs),
            "testVictor.config_kI(3, testVictorConfigs.slot3.kI, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kD(3, testVictorConfigs.slot3.kD, timeoutMs),
            "testVictor.config_kD(3, testVictorConfigs.slot3.kD, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_kF(3, testVictorConfigs.slot3.kF, timeoutMs),
            "testVictor.config_kF(3, testVictorConfigs.slot3.kF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.config_IntegralZone(3, testVictorConfigs.slot3.integralZone, timeoutMs),
            "testVictor.config_IntegralZone(3, testVictorConfigs.slot3.integralZone, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configAllowableClosedloopError(3, testVictorConfigs.slot3.allowableClosedloopError, timeoutMs),
            "testVictor.configAllowableClosedloopError(3, testVictorConfigs.slot3.allowableClosedloopError, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configMaxIntegralAccumulator(3, testVictorConfigs.slot3.maxIntegralAccumulator, timeoutMs),
            "testVictor.configMaxIntegralAccumulator(3, testVictorConfigs.slot3.maxIntegralAccumulator, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeakOutput(3, testVictorConfigs.slot3.closedLoopPeakOutput, timeoutMs),
            "testVictor.configClosedLoopPeakOutput(3, testVictorConfigs.slot3.closedLoopPeakOutput, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configClosedLoopPeriod(3, testVictorConfigs.slot3.closedLoopPeriod, timeoutMs),
            "testVictor.configClosedLoopPeriod(3, testVictorConfigs.slot3.closedLoopPeriod, timeoutMs)"));

        errorCodes.add(new ErrorCodeString(testVictor.configSelectedFeedbackCoefficient(testVictorConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs),
            "testVictor.configSelectedFeedbackCoefficient(testVictorConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configSelectedFeedbackSensor(testVictorConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs),
            "testVictor.configSelectedFeedbackSensor(testVictorConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configSelectedFeedbackCoefficient(testVictorConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs),
            "testVictor.configSelectedFeedbackCoefficient(testVictorConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configSelectedFeedbackSensor(testVictorConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs),
            "testVictor.configSelectedFeedbackSensor(testVictorConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs)"));
        
        errorCodes.add(new ErrorCodeString(testVictor.configSensorTerm(SensorTerm.Sum0, testVictorConfigs.sum0Term, timeoutMs),
            "testVictor.configSensorTerm(SensorTerm.Sum0, testVictorConfigs.sum0Term, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configSensorTerm(SensorTerm.Sum1, testVictorConfigs.sum1Term, timeoutMs),
            "testVictor.configSensorTerm(SensorTerm.Sum1, testVictorConfigs.sum1Term, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configSensorTerm(SensorTerm.Diff0, testVictorConfigs.diff0Term, timeoutMs),
            "testVictor.configSensorTerm(SensorTerm.Diff0, testVictorConfigs.diff0Term, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configSensorTerm(SensorTerm.Diff1, testVictorConfigs.diff1Term, timeoutMs),
            "testVictor.configSensorTerm(SensorTerm.Diff1, testVictorConfigs.diff1Term, timeoutMs)"));
        
        //Unique to just Victor    
        errorCodes.add(new ErrorCodeString(testVictor.configForwardLimitSwitchSource(testVictorConfigs.forwardLimitSwitchSource, testVictorConfigs.forwardLimitSwitchNormal, testVictorConfigs.forwardLimitSwitchDeviceID, timeoutMs),
            "testVictor.configForwardLimitSwitchSource(testVictorConfigs.forwardLimitSwitchSource, testVictorConfigs.forwardLimitSwitchNormal, testVictorConfigs.forwardLimitSwitchDeviceID, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testVictor.configReverseLimitSwitchSource(testVictorConfigs.reverseLimitSwitchSource, testVictorConfigs.reverseLimitSwitchNormal, testVictorConfigs.reverseLimitSwitchDeviceID, timeoutMs),
            "testVictor.configReverseLimitSwitchSource(testVictorConfigs.reverseLimitSwitchSource, testVictorConfigs.reverseLimitSwitchNormal, testVictorConfigs.reverseLimitSwitchDeviceID, timeoutMs)"));
    
    }
    public static void ConfigAllIndividualPigeon(int id, int timeoutMs, PigeonIMUConfiguration testPigeonConfigs, List<ErrorCodeString> errorCodes) {
        
        PigeonIMU testPigeon = new PigeonIMU(id);
        
        errorCodes.add(new ErrorCodeString(testPigeon.configSetCustomParam(testPigeonConfigs.customParam0, 0, timeoutMs),
            "testPigeon.configSetCustomParam(testPigeonConfigs.customParam0, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testPigeon.configSetCustomParam(testPigeonConfigs.customParam1, 1, timeoutMs),
            "testPigeon.configSetCustomParam(testPigeonConfigs.customParam1, 1, timeoutMs)"));
    }
    public static void ConfigAllIndividualCANifier(int id, int timeoutMs, CANifierConfiguration testCANifierConfigs, List<ErrorCodeString> errorCodes) {
        
        CANifier testCANifier = new CANifier(id);
        
        errorCodes.add(new ErrorCodeString(testCANifier.configVelocityMeasurementPeriod(testCANifierConfigs.velocityMeasurementPeriod, timeoutMs),
            "testCANifier.configVelocityMeasurementPeriod(testCANifierConfigs.velocityMeasurementPeriod, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testCANifier.configVelocityMeasurementWindow(testCANifierConfigs.velocityMeasurementWindow, timeoutMs),
            "testCANifier.configVelocityMeasurementWindow(testCANifierConfigs.velocityMeasurementWindow, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testCANifier.configClearPositionOnLimitF(testCANifierConfigs.clearPositionOnLimitF, timeoutMs),
            "testCANifier.configClearPositionOnLimitF(testCANifierConfigs.clearPositionOnLimitF, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testCANifier.configClearPositionOnLimitR(testCANifierConfigs.clearPositionOnLimitR, timeoutMs),
            "testCANifier.configClearPositionOnLimitR(testCANifierConfigs.clearPositionOnLimitR, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testCANifier.configClearPositionOnQuadIdx(testCANifierConfigs.clearPositionOnQuadIdx, timeoutMs),
            "testCANifier.configClearPositionOnQuadIdx(testCANifierConfigs.clearPositionOnQuadIdx, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testCANifier.configSetCustomParam(testCANifierConfigs.customParam0, 0, timeoutMs),
            "testCANifier.configSetCustomParam(testCANifierConfigs.customParam0, 0, timeoutMs)"));
        errorCodes.add(new ErrorCodeString(testCANifier.configSetCustomParam(testCANifierConfigs.customParam1, 1, timeoutMs),
            "testCANifier.configSetCustomParam(testCANifierConfigs.customParam1, 1, timeoutMs)"));

    }
    public static void ConfigFactoryDefaultTalon(int id, int timeoutMs, List<ErrorCodeString> errorCodes) {
    
        TalonSRX testTalon = new TalonSRX(id);
        
        errorCodes.add(new ErrorCodeString(testTalon.configFactoryDefault(timeoutMs),
            "testTalon.configFactoryDefault(timeoutMs)"));
    }
    public static void ConfigFactoryDefaultVictor(int id, int timeoutMs, List<ErrorCodeString> errorCodes) {
    
        VictorSPX testVictor = new VictorSPX(id);
        
        errorCodes.add(new ErrorCodeString(testVictor.configFactoryDefault(timeoutMs),
            "testVictor.configFactoryDefault(timeoutMs)"));
    }
    public static void ConfigFactoryDefaultPigeon(int id, int timeoutMs, List<ErrorCodeString> errorCodes) {
        
        PigeonIMU testPigeon = new PigeonIMU(id);
        
        errorCodes.add(new ErrorCodeString(testPigeon.configFactoryDefault(timeoutMs),
            "testPigeon.configFactoryDefault(timeoutMs)"));
    }
    public static void ConfigFactoryDefaultCANifier(int id, int timeoutMs, List<ErrorCodeString> errorCodes) {
    
        CANifier testCANifier = new CANifier(id);
        
        errorCodes.add(new ErrorCodeString(testCANifier.configFactoryDefault(timeoutMs),
            "testCANifier.configFactoryDefault(timeoutMs)"));
    }
    public static void ConfigAllTalon(int id, int timeoutMs, TalonSRXConfiguration testTalonConfigs, List<ErrorCodeString> errorCodes) {
    
        TalonSRX testTalon = new TalonSRX(id);
        
        errorCodes.add(new ErrorCodeString(testTalon.configAllSettings(testTalonConfigs, timeoutMs),
            "testTalon.configAllSettings(testTalonConfigs, timeoutMs)"));
    }
    public static void ConfigAllVictor(int id, int timeoutMs, VictorSPXConfiguration testVictorConfigs, List<ErrorCodeString> errorCodes) {
    
        VictorSPX testVictor = new VictorSPX(id);
        
        errorCodes.add(new ErrorCodeString(testVictor.configAllSettings(testVictorConfigs, timeoutMs),
            "testVictor.configAllSettings(testVictorConfigs, timeoutMs)"));
    }
    public static void ConfigAllPigeon(int id, int timeoutMs, PigeonIMUConfiguration testPigeonConfigs, List<ErrorCodeString> errorCodes) {
        
        PigeonIMU testPigeon = new PigeonIMU(id);
        
        errorCodes.add(new ErrorCodeString(testPigeon.configAllSettings(testPigeonConfigs, timeoutMs),
            "testVictor.configAllSettings(testVictorConfigs, timeoutMs)"));
    }
    public static void ConfigAllCANifier(int id, int timeoutMs, CANifierConfiguration testCANifierConfigs, List<ErrorCodeString> errorCodes) {
    
        CANifier testCANifier = new CANifier(id);
        
        errorCodes.add(new ErrorCodeString(testCANifier.configAllSettings(testCANifierConfigs, timeoutMs),
            "testCANifier.configAllSettings(testCANifierConfigs, timeoutMs)"));
    }
}
