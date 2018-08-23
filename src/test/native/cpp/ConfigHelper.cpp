#include "ConfigHelper.h"
#include <memory>
#include <gtest/gtest.h>

void ConfigAllIndividualTalon(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);

    errorCodes.push_back(std::make_pair(testTalon->ConfigOpenloopRamp(testTalonConfigs.openloopRamp, timeoutMs),
        "testTalon->ConfigOpenloopRamp(testTalonConfigs.openloopRamp, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedloopRamp(testTalonConfigs.closedloopRamp, timeoutMs),
        "testTalon->ConfigClosedloopRamp(testTalonConfigs.closedloopRamp, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigPeakOutputForward(testTalonConfigs.peakOutputForward, timeoutMs),
        "testTalon->ConfigPeakOutputForward(testTalonConfigs.peakOutputForward, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigPeakOutputReverse(testTalonConfigs.peakOutputReverse, timeoutMs),
        "testTalon->ConfigPeakOutputReverse(testTalonConfigs.peakOutputReverse, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigNominalOutputForward(testTalonConfigs.nominalOutputForward, timeoutMs),
        "testTalon->ConfigNominalOutputForward(testTalonConfigs.nominalOutputForward, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigNominalOutputReverse(testTalonConfigs.nominalOutputReverse, timeoutMs),
        "testTalon->ConfigNominalOutputReverse(testTalonConfigs.nominalOutputReverse, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigNeutralDeadband(testTalonConfigs.neutralDeadband, timeoutMs),
        "testTalon->ConfigNeutralDeadband(testTalonConfigs.neutralDeadband, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigVoltageCompSaturation(testTalonConfigs.voltageCompSaturation, timeoutMs),
        "testTalon->ConfigVoltageCompSaturation(testTalonConfigs.voltageCompSaturation, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigVoltageMeasurementFilter(testTalonConfigs.voltageMeasurementFilter, timeoutMs),
        "testTalon->ConfigVoltageMeasurementFilter(testTalonConfigs.voltageMeasurementFilter, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigVelocityMeasurementPeriod(testTalonConfigs.velocityMeasurementPeriod, timeoutMs),
        "testTalon->ConfigVelocityMeasurementPeriod(testTalonConfigs.velocityMeasurementPeriod, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigVelocityMeasurementWindow(testTalonConfigs.velocityMeasurementWindow, timeoutMs),
        "testTalon->ConfigVelocityMeasurementWindow(testTalonConfigs.velocityMeasurementWindow, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigForwardSoftLimitThreshold(testTalonConfigs.forwardSoftLimitThreshold, timeoutMs),
        "testTalon->ConfigForwardSoftLimitThreshold(testTalonConfigs.forwardSoftLimitThreshold, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigReverseSoftLimitThreshold(testTalonConfigs.reverseSoftLimitThreshold, timeoutMs),
        "testTalon->ConfigReverseSoftLimitThreshold(testTalonConfigs.reverseSoftLimitThreshold, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigForwardSoftLimitEnable(testTalonConfigs.forwardSoftLimitEnable, timeoutMs),
        "testTalon->ConfigForwardSoftLimitEnable(testTalonConfigs.forwardSoftLimitEnable, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigReverseSoftLimitEnable(testTalonConfigs.reverseSoftLimitEnable, timeoutMs),
        "testTalon->ConfigReverseSoftLimitEnable(testTalonConfigs.reverseSoftLimitEnable, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigAuxPIDPolarity(testTalonConfigs.auxPIDPolarity, timeoutMs),
        "testTalon->ConfigAuxPIDPolarity(testTalonConfigs.auxPIDPolarity, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigMotionCruiseVelocity(testTalonConfigs.motionCruiseVelocity, timeoutMs),
        "testTalon->ConfigMotionCruiseVelocity(testTalonConfigs.motionCruiseVelocity, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigMotionAcceleration(testTalonConfigs.motionAcceleration, timeoutMs),
        "testTalon->ConfigMotionAcceleration(testTalonConfigs.motionAcceleration, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigMotionProfileTrajectoryPeriod(testTalonConfigs.motionProfileTrajectoryPeriod, timeoutMs),
        "testTalon->ConfigMotionProfileTrajectoryPeriod(testTalonConfigs.motionProfileTrajectoryPeriod, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigFeedbackNotContinuous(testTalonConfigs.feedbackNotContinuous, timeoutMs),
        "testTalon->ConfigFeedbackNotContinuous(testTalonConfigs.feedbackNotContinuous, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(testTalonConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs),
        "testTalon->ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(testTalonConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClearPositionOnLimitF(testTalonConfigs.clearPositionOnLimitF, timeoutMs),
        "testTalon->ConfigClearPositionOnLimitF(testTalonConfigs.clearPositionOnLimitF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClearPositionOnLimitR(testTalonConfigs.clearPositionOnLimitR, timeoutMs),
        "testTalon->ConfigClearPositionOnLimitR(testTalonConfigs.clearPositionOnLimitR, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClearPositionOnQuadIdx(testTalonConfigs.clearPositionOnQuadIdx, timeoutMs),
        "testTalon->ConfigClearPositionOnQuadIdx(testTalonConfigs.clearPositionOnQuadIdx, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigLimitSwitchDisableNeutralOnLOS(testTalonConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs),
        "testTalon->ConfigLimitSwitchDisableNeutralOnLOS(testTalonConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigSoftLimitDisableNeutralOnLOS(testTalonConfigs.softLimitDisableNeutralOnLOS, timeoutMs),
        "testTalon->ConfigSoftLimitDisableNeutralOnLOS(testTalonConfigs.softLimitDisableNeutralOnLOS, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigPulseWidthPeriod_EdgesPerRot(testTalonConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs),
        "testTalon->ConfigPulseWidthPeriod_EdgesPerRot(testTalonConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigPulseWidthPeriod_FilterWindowSz(testTalonConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs),
        "testTalon->ConfigPulseWidthPeriod_FilterWindowSz(testTalonConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs)"));
   
    errorCodes.push_back(std::make_pair(testTalon->ConfigRemoteFeedbackFilter(testTalonConfigs.remoteFilter0.remoteSensorDeviceID, testTalonConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs),
        "testTalon->ConfigRemoteFeedbackFilter(testTalonConfigs.remoteFilter0.remoteSensorDeviceID, testTalonConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigRemoteFeedbackFilter(testTalonConfigs.remoteFilter1.remoteSensorDeviceID, testTalonConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs),
        "testTalon->ConfigRemoteFeedbackFilter(testTalonConfigs.remoteFilter1.remoteSensorDeviceID, testTalonConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testTalon->Config_kP(0, testTalonConfigs.slot0.kP, timeoutMs),
        "testTalon->Config_kP(0, testTalonConfigs.slot0.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kI(0, testTalonConfigs.slot0.kI, timeoutMs),
        "testTalon->Config_kI(0, testTalonConfigs.slot0.kI, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kD(0, testTalonConfigs.slot0.kD, timeoutMs),
        "testTalon->Config_kD(0, testTalonConfigs.slot0.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kF(0, testTalonConfigs.slot0.kF, timeoutMs),
        "testTalon->Config_kF(0, testTalonConfigs.slot0.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_IntegralZone(0, testTalonConfigs.slot0.integralZone, timeoutMs),
        "testTalon->Config_IntegralZone(0, testTalonConfigs.slot0.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigAllowableClosedloopError(0, testTalonConfigs.slot0.allowableClosedloopError, timeoutMs),
        "testTalon->ConfigAllowableClosedloopError(0, testTalonConfigs.slot0.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigMaxIntegralAccumulator(0, testTalonConfigs.slot0.maxIntegralAccumulator, timeoutMs),
        "testTalon->ConfigMaxIntegralAccumulator(0, testTalonConfigs.slot0.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeakOutput(0, testTalonConfigs.slot0.closedLoopPeakOutput, timeoutMs),
        "testTalon->ConfigClosedLoopPeakOutput(0, testTalonConfigs.slot0.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeriod(0, testTalonConfigs.slot0.closedLoopPeriod, timeoutMs),
        "testTalon->ConfigClosedLoopPeriod(0, testTalonConfigs.slot0.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testTalon->Config_kP(1, testTalonConfigs.slot1.kP, timeoutMs),
        "testTalon->Config_kP(1, testTalonConfigs.slot1.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kI(1, testTalonConfigs.slot1.kI, timeoutMs),
        "testTalon->Config_kI(1, testTalonConfigs.slot1.kI, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kD(1, testTalonConfigs.slot1.kD, timeoutMs),
        "testTalon->Config_kD(1, testTalonConfigs.slot1.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kF(1, testTalonConfigs.slot1.kF, timeoutMs),
        "testTalon->Config_kF(1, testTalonConfigs.slot1.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_IntegralZone(1, testTalonConfigs.slot1.integralZone, timeoutMs),
        "testTalon->Config_IntegralZone(1, testTalonConfigs.slot1.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigAllowableClosedloopError(1, testTalonConfigs.slot1.allowableClosedloopError, timeoutMs),
        "testTalon->ConfigAllowableClosedloopError(1, testTalonConfigs.slot1.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigMaxIntegralAccumulator(1, testTalonConfigs.slot1.maxIntegralAccumulator, timeoutMs),
        "testTalon->ConfigMaxIntegralAccumulator(1, testTalonConfigs.slot1.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeakOutput(1, testTalonConfigs.slot1.closedLoopPeakOutput, timeoutMs),
        "testTalon->ConfigClosedLoopPeakOutput(1, testTalonConfigs.slot1.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeriod(1, testTalonConfigs.slot1.closedLoopPeriod, timeoutMs),
        "testTalon->ConfigClosedLoopPeriod(1, testTalonConfigs.slot1.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testTalon->Config_kP(2, testTalonConfigs.slot2.kP, timeoutMs),
        "testTalon->Config_kP(2, testTalonConfigs.slot2.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kI(2, testTalonConfigs.slot2.kI, timeoutMs),
        "testTalon->Config_kI(2, testTalonConfigs.slot2.kI, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kD(2, testTalonConfigs.slot2.kD, timeoutMs),
        "testTalon->Config_kD(2, testTalonConfigs.slot2.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kF(2, testTalonConfigs.slot2.kF, timeoutMs),
        "testTalon->Config_kF(2, testTalonConfigs.slot2.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_IntegralZone(2, testTalonConfigs.slot2.integralZone, timeoutMs),
        "testTalon->Config_IntegralZone(2, testTalonConfigs.slot2.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigAllowableClosedloopError(2, testTalonConfigs.slot2.allowableClosedloopError, timeoutMs),
        "testTalon->ConfigAllowableClosedloopError(2, testTalonConfigs.slot2.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigMaxIntegralAccumulator(2, testTalonConfigs.slot2.maxIntegralAccumulator, timeoutMs),
        "testTalon->ConfigMaxIntegralAccumulator(2, testTalonConfigs.slot2.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeakOutput(2, testTalonConfigs.slot2.closedLoopPeakOutput, timeoutMs),
        "testTalon->ConfigClosedLoopPeakOutput(2, testTalonConfigs.slot2.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeriod(2, testTalonConfigs.slot2.closedLoopPeriod, timeoutMs),
        "testTalon->ConfigClosedLoopPeriod(2, testTalonConfigs.slot2.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testTalon->Config_kP(3, testTalonConfigs.slot3.kP, timeoutMs),
        "testTalon->Config_kP(3, testTalonConfigs.slot3.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kI(3, testTalonConfigs.slot3.kI, timeoutMs),
        "testTalon->Config_kI(3, testTalonConfigs.slot3.kI, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kD(3, testTalonConfigs.slot3.kD, timeoutMs),
        "testTalon->Config_kD(3, testTalonConfigs.slot3.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_kF(3, testTalonConfigs.slot3.kF, timeoutMs),
        "testTalon->Config_kF(3, testTalonConfigs.slot3.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->Config_IntegralZone(3, testTalonConfigs.slot3.integralZone, timeoutMs),
        "testTalon->Config_IntegralZone(3, testTalonConfigs.slot3.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigAllowableClosedloopError(3, testTalonConfigs.slot3.allowableClosedloopError, timeoutMs),
        "testTalon->ConfigAllowableClosedloopError(3, testTalonConfigs.slot3.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigMaxIntegralAccumulator(3, testTalonConfigs.slot3.maxIntegralAccumulator, timeoutMs),
        "testTalon->ConfigMaxIntegralAccumulator(3, testTalonConfigs.slot3.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeakOutput(3, testTalonConfigs.slot3.closedLoopPeakOutput, timeoutMs),
        "testTalon->ConfigClosedLoopPeakOutput(3, testTalonConfigs.slot3.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigClosedLoopPeriod(3, testTalonConfigs.slot3.closedLoopPeriod, timeoutMs),
        "testTalon->ConfigClosedLoopPeriod(3, testTalonConfigs.slot3.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testTalon->ConfigSelectedFeedbackCoefficient(testTalonConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs),
        "testTalon->ConfigSelectedFeedbackCoefficient(testTalonConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigSelectedFeedbackSensor(testTalonConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs),
        "testTalon->ConfigSelectedFeedbackSensor(testTalonConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigSelectedFeedbackCoefficient(testTalonConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs),
        "testTalon->ConfigSelectedFeedbackCoefficient(testTalonConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigSelectedFeedbackSensor(testTalonConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs),
        "testTalon->ConfigSelectedFeedbackSensor(testTalonConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, testTalonConfigs.sum0Term, timeoutMs),
        "testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, testTalonConfigs.sum0Term, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, testTalonConfigs.sum1Term, timeoutMs),
        "testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, testTalonConfigs.sum1Term, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, testTalonConfigs.diff0Term, timeoutMs),
        "testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, testTalonConfigs.diff0Term, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, testTalonConfigs.diff1Term, timeoutMs),
        "testTalon->ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, testTalonConfigs.diff1Term, timeoutMs)"));
    
    //Unique to just Talon
    errorCodes.push_back(std::make_pair(testTalon->ConfigForwardLimitSwitchSource(testTalonConfigs.forwardLimitSwitchSource, testTalonConfigs.forwardLimitSwitchNormal, timeoutMs),
        "testTalon->ConfigForwardLimitSwitchSource(testTalonConfigs.forwardLimitSwitchSource, testTalonConfigs.forwardLimitSwitchNormal, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigReverseLimitSwitchSource(testTalonConfigs.reverseLimitSwitchSource, testTalonConfigs.reverseLimitSwitchNormal, timeoutMs),
        "testTalon->ConfigReverseLimitSwitchSource(testTalonConfigs.reverseLimitSwitchSource, testTalonConfigs.reverseLimitSwitchNormal, timeoutMs)"));
    
    errorCodes.push_back(std::make_pair(testTalon->ConfigPeakCurrentLimit(testTalonConfigs.peakCurrentLimit, timeoutMs),
        "testTalon->ConfigPeakCurrentLimit(testTalonConfigs.peakCurrentLimit, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigPeakCurrentDuration(testTalonConfigs.peakCurrentDuration, timeoutMs),
        "testTalon->ConfigPeakCurrentDuration(testTalonConfigs.peakCurrentDuration, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testTalon->ConfigContinuousCurrentLimit(testTalonConfigs.continuousCurrentLimit, timeoutMs),
        "testTalon->ConfigContinuousCurrentLimit(testTalonConfigs.continuousCurrentLimit, timeoutMs)"));

}

void ConfigAllIndividualVictor(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes) {
    
    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);

    errorCodes.push_back(std::make_pair(testVictor->ConfigOpenloopRamp(testVictorConfigs.openloopRamp, timeoutMs),
        "testVictor->ConfigOpenloopRamp(testVictorConfigs.openloopRamp, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedloopRamp(testVictorConfigs.closedloopRamp, timeoutMs),
        "testVictor->ConfigClosedloopRamp(testVictorConfigs.closedloopRamp, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigPeakOutputForward(testVictorConfigs.peakOutputForward, timeoutMs),
        "testVictor->ConfigPeakOutputForward(testVictorConfigs.peakOutputForward, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigPeakOutputReverse(testVictorConfigs.peakOutputReverse, timeoutMs),
        "testVictor->ConfigPeakOutputReverse(testVictorConfigs.peakOutputReverse, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigNominalOutputForward(testVictorConfigs.nominalOutputForward, timeoutMs),
        "testVictor->ConfigNominalOutputForward(testVictorConfigs.nominalOutputForward, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigNominalOutputReverse(testVictorConfigs.nominalOutputReverse, timeoutMs),
        "testVictor->ConfigNominalOutputReverse(testVictorConfigs.nominalOutputReverse, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigNeutralDeadband(testVictorConfigs.neutralDeadband, timeoutMs),
        "testVictor->ConfigNeutralDeadband(testVictorConfigs.neutralDeadband, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigVoltageCompSaturation(testVictorConfigs.voltageCompSaturation, timeoutMs),
        "testVictor->ConfigVoltageCompSaturation(testVictorConfigs.voltageCompSaturation, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigVoltageMeasurementFilter(testVictorConfigs.voltageMeasurementFilter, timeoutMs),
        "testVictor->ConfigVoltageMeasurementFilter(testVictorConfigs.voltageMeasurementFilter, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigVelocityMeasurementPeriod(testVictorConfigs.velocityMeasurementPeriod, timeoutMs),
        "testVictor->ConfigVelocityMeasurementPeriod(testVictorConfigs.velocityMeasurementPeriod, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigVelocityMeasurementWindow(testVictorConfigs.velocityMeasurementWindow, timeoutMs),
        "testVictor->ConfigVelocityMeasurementWindow(testVictorConfigs.velocityMeasurementWindow, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigForwardSoftLimitThreshold(testVictorConfigs.forwardSoftLimitThreshold, timeoutMs),
        "testVictor->ConfigForwardSoftLimitThreshold(testVictorConfigs.forwardSoftLimitThreshold, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigReverseSoftLimitThreshold(testVictorConfigs.reverseSoftLimitThreshold, timeoutMs),
        "testVictor->ConfigReverseSoftLimitThreshold(testVictorConfigs.reverseSoftLimitThreshold, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigForwardSoftLimitEnable(testVictorConfigs.forwardSoftLimitEnable, timeoutMs),
        "testVictor->ConfigForwardSoftLimitEnable(testVictorConfigs.forwardSoftLimitEnable, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigReverseSoftLimitEnable(testVictorConfigs.reverseSoftLimitEnable, timeoutMs),
        "testVictor->ConfigReverseSoftLimitEnable(testVictorConfigs.reverseSoftLimitEnable, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigAuxPIDPolarity(testVictorConfigs.auxPIDPolarity, timeoutMs),
        "testVictor->ConfigAuxPIDPolarity(testVictorConfigs.auxPIDPolarity, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigMotionCruiseVelocity(testVictorConfigs.motionCruiseVelocity, timeoutMs),
        "testVictor->ConfigMotionCruiseVelocity(testVictorConfigs.motionCruiseVelocity, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigMotionAcceleration(testVictorConfigs.motionAcceleration, timeoutMs),
        "testVictor->ConfigMotionAcceleration(testVictorConfigs.motionAcceleration, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigMotionProfileTrajectoryPeriod(testVictorConfigs.motionProfileTrajectoryPeriod, timeoutMs),
        "testVictor->ConfigMotionProfileTrajectoryPeriod(testVictorConfigs.motionProfileTrajectoryPeriod, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigFeedbackNotContinuous(testVictorConfigs.feedbackNotContinuous, timeoutMs),
        "testVictor->ConfigFeedbackNotContinuous(testVictorConfigs.feedbackNotContinuous, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(testVictorConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs),
        "testVictor->ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(testVictorConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClearPositionOnLimitF(testVictorConfigs.clearPositionOnLimitF, timeoutMs),
        "testVictor->ConfigClearPositionOnLimitF(testVictorConfigs.clearPositionOnLimitF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClearPositionOnLimitR(testVictorConfigs.clearPositionOnLimitR, timeoutMs),
        "testVictor->ConfigClearPositionOnLimitR(testVictorConfigs.clearPositionOnLimitR, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClearPositionOnQuadIdx(testVictorConfigs.clearPositionOnQuadIdx, timeoutMs),
        "testVictor->ConfigClearPositionOnQuadIdx(testVictorConfigs.clearPositionOnQuadIdx, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigLimitSwitchDisableNeutralOnLOS(testVictorConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs),
        "testVictor->ConfigLimitSwitchDisableNeutralOnLOS(testVictorConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigSoftLimitDisableNeutralOnLOS(testVictorConfigs.softLimitDisableNeutralOnLOS, timeoutMs),
        "testVictor->ConfigSoftLimitDisableNeutralOnLOS(testVictorConfigs.softLimitDisableNeutralOnLOS, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigPulseWidthPeriod_EdgesPerRot(testVictorConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs),
        "testVictor->ConfigPulseWidthPeriod_EdgesPerRot(testVictorConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigPulseWidthPeriod_FilterWindowSz(testVictorConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs),
        "testVictor->ConfigPulseWidthPeriod_FilterWindowSz(testVictorConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs)"));
   
    errorCodes.push_back(std::make_pair(testVictor->ConfigRemoteFeedbackFilter(testVictorConfigs.remoteFilter0.remoteSensorDeviceID, testVictorConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs),
        "testVictor->ConfigRemoteFeedbackFilter(testVictorConfigs.remoteFilter0.remoteSensorDeviceID, testVictorConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigRemoteFeedbackFilter(testVictorConfigs.remoteFilter1.remoteSensorDeviceID, testVictorConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs),
        "testVictor->ConfigRemoteFeedbackFilter(testVictorConfigs.remoteFilter1.remoteSensorDeviceID, testVictorConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testVictor->Config_kP(0, testVictorConfigs.slot0.kP, timeoutMs),
        "testVictor->Config_kP(0, testVictorConfigs.slot0.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kI(0, testVictorConfigs.slot0.kI, timeoutMs),
        "testVictor->Config_kI(0, testVictorConfigs.slot0.kI, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kD(0, testVictorConfigs.slot0.kD, timeoutMs),
        "testVictor->Config_kD(0, testVictorConfigs.slot0.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kF(0, testVictorConfigs.slot0.kF, timeoutMs),
        "testVictor->Config_kF(0, testVictorConfigs.slot0.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_IntegralZone(0, testVictorConfigs.slot0.integralZone, timeoutMs),
        "testVictor->Config_IntegralZone(0, testVictorConfigs.slot0.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigAllowableClosedloopError(0, testVictorConfigs.slot0.allowableClosedloopError, timeoutMs),
        "testVictor->ConfigAllowableClosedloopError(0, testVictorConfigs.slot0.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigMaxIntegralAccumulator(0, testVictorConfigs.slot0.maxIntegralAccumulator, timeoutMs),
        "testVictor->ConfigMaxIntegralAccumulator(0, testVictorConfigs.slot0.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeakOutput(0, testVictorConfigs.slot0.closedLoopPeakOutput, timeoutMs),
        "testVictor->ConfigClosedLoopPeakOutput(0, testVictorConfigs.slot0.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeriod(0, testVictorConfigs.slot0.closedLoopPeriod, timeoutMs),
        "testVictor->ConfigClosedLoopPeriod(0, testVictorConfigs.slot0.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testVictor->Config_kP(1, testVictorConfigs.slot1.kP, timeoutMs),
        "testVictor->Config_kP(1, testVictorConfigs.slot1.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kI(1, testVictorConfigs.slot1.kI, timeoutMs),
        "testVictor->Config_kI(1, testVictorConfigs.slot1.kI, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kD(1, testVictorConfigs.slot1.kD, timeoutMs),
        "testVictor->Config_kD(1, testVictorConfigs.slot1.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kF(1, testVictorConfigs.slot1.kF, timeoutMs),
        "testVictor->Config_kF(1, testVictorConfigs.slot1.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_IntegralZone(1, testVictorConfigs.slot1.integralZone, timeoutMs),
        "testVictor->Config_IntegralZone(1, testVictorConfigs.slot1.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigAllowableClosedloopError(1, testVictorConfigs.slot1.allowableClosedloopError, timeoutMs),
        "testVictor->ConfigAllowableClosedloopError(1, testVictorConfigs.slot1.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigMaxIntegralAccumulator(1, testVictorConfigs.slot1.maxIntegralAccumulator, timeoutMs),
        "testVictor->ConfigMaxIntegralAccumulator(1, testVictorConfigs.slot1.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeakOutput(1, testVictorConfigs.slot1.closedLoopPeakOutput, timeoutMs),
        "testVictor->ConfigClosedLoopPeakOutput(1, testVictorConfigs.slot1.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeriod(1, testVictorConfigs.slot1.closedLoopPeriod, timeoutMs),
        "testVictor->ConfigClosedLoopPeriod(1, testVictorConfigs.slot1.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testVictor->Config_kP(2, testVictorConfigs.slot2.kP, timeoutMs),
        "testVictor->Config_kP(2, testVictorConfigs.slot2.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kD(2, testVictorConfigs.slot2.kD, timeoutMs),
        "testVictor->Config_kD(2, testVictorConfigs.slot2.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kF(2, testVictorConfigs.slot2.kF, timeoutMs),
        "testVictor->Config_kF(2, testVictorConfigs.slot2.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_IntegralZone(2, testVictorConfigs.slot2.integralZone, timeoutMs),
        "testVictor->Config_IntegralZone(2, testVictorConfigs.slot2.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigAllowableClosedloopError(2, testVictorConfigs.slot2.allowableClosedloopError, timeoutMs),
        "testVictor->ConfigAllowableClosedloopError(2, testVictorConfigs.slot2.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigMaxIntegralAccumulator(2, testVictorConfigs.slot2.maxIntegralAccumulator, timeoutMs),
        "testVictor->ConfigMaxIntegralAccumulator(2, testVictorConfigs.slot2.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeakOutput(2, testVictorConfigs.slot2.closedLoopPeakOutput, timeoutMs),
        "testVictor->ConfigClosedLoopPeakOutput(2, testVictorConfigs.slot2.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeriod(2, testVictorConfigs.slot2.closedLoopPeriod, timeoutMs),
        "testVictor->ConfigClosedLoopPeriod(2, testVictorConfigs.slot2.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testVictor->Config_kP(3, testVictorConfigs.slot3.kP, timeoutMs),
        "testVictor->Config_kP(3, testVictorConfigs.slot3.kP, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kI(3, testVictorConfigs.slot3.kI, timeoutMs),
        "testVictor->Config_kI(3, testVictorConfigs.slot3.kI, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kD(3, testVictorConfigs.slot3.kD, timeoutMs),
        "testVictor->Config_kD(3, testVictorConfigs.slot3.kD, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_kF(3, testVictorConfigs.slot3.kF, timeoutMs),
        "testVictor->Config_kF(3, testVictorConfigs.slot3.kF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->Config_IntegralZone(3, testVictorConfigs.slot3.integralZone, timeoutMs),
        "testVictor->Config_IntegralZone(3, testVictorConfigs.slot3.integralZone, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigAllowableClosedloopError(3, testVictorConfigs.slot3.allowableClosedloopError, timeoutMs),
        "testVictor->ConfigAllowableClosedloopError(3, testVictorConfigs.slot3.allowableClosedloopError, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigMaxIntegralAccumulator(3, testVictorConfigs.slot3.maxIntegralAccumulator, timeoutMs),
        "testVictor->ConfigMaxIntegralAccumulator(3, testVictorConfigs.slot3.maxIntegralAccumulator, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeakOutput(3, testVictorConfigs.slot3.closedLoopPeakOutput, timeoutMs),
        "testVictor->ConfigClosedLoopPeakOutput(3, testVictorConfigs.slot3.closedLoopPeakOutput, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigClosedLoopPeriod(3, testVictorConfigs.slot3.closedLoopPeriod, timeoutMs),
        "testVictor->ConfigClosedLoopPeriod(3, testVictorConfigs.slot3.closedLoopPeriod, timeoutMs)"));

    errorCodes.push_back(std::make_pair(testVictor->ConfigSelectedFeedbackCoefficient(testVictorConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs),
        "testVictor->ConfigSelectedFeedbackCoefficient(testVictorConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigSelectedFeedbackSensor(testVictorConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs),
        "testVictor->ConfigSelectedFeedbackSensor(testVictorConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigSelectedFeedbackCoefficient(testVictorConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs),
        "testVictor->ConfigSelectedFeedbackCoefficient(testVictorConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigSelectedFeedbackSensor(testVictorConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs),
        "testVictor->ConfigSelectedFeedbackSensor(testVictorConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs)"));
    
    errorCodes.push_back(std::make_pair(testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, testVictorConfigs.sum0Term, timeoutMs),
        "testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, testVictorConfigs.sum0Term, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, testVictorConfigs.sum1Term, timeoutMs),
        "testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, testVictorConfigs.sum1Term, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, testVictorConfigs.diff0Term, timeoutMs),
        "testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, testVictorConfigs.diff0Term, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, testVictorConfigs.diff1Term, timeoutMs),
        "testVictor->ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, testVictorConfigs.diff1Term, timeoutMs)"));
    
    //Unique to just Victor    
    errorCodes.push_back(std::make_pair(testVictor->ConfigForwardLimitSwitchSource(testVictorConfigs.forwardLimitSwitchSource, testVictorConfigs.forwardLimitSwitchNormal, testVictorConfigs.forwardLimitSwitchDeviceID, timeoutMs),
        "testVictor->ConfigForwardLimitSwitchSource(testVictorConfigs.forwardLimitSwitchSource, testVictorConfigs.forwardLimitSwitchNormal, testVictorConfigs.forwardLimitSwitchDeviceID, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testVictor->ConfigReverseLimitSwitchSource(testVictorConfigs.reverseLimitSwitchSource, testVictorConfigs.reverseLimitSwitchNormal, testVictorConfigs.reverseLimitSwitchDeviceID, timeoutMs),
        "testVictor->ConfigReverseLimitSwitchSource(testVictorConfigs.reverseLimitSwitchSource, testVictorConfigs.reverseLimitSwitchNormal, testVictorConfigs.reverseLimitSwitchDeviceID, timeoutMs)"));

    
}

void ConfigAllIndividualPigeon(int id, int timeoutMs, const ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes) {
    
    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);

    errorCodes.push_back(std::make_pair(testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam0, 0, timeoutMs),
        "testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam0, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam1, 1, timeoutMs),
        "testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam1, 1, timeoutMs)"));

    
}

void ConfigAllIndividualCANifier(int id, int timeoutMs, const ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes) {
    
    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    
    errorCodes.push_back(std::make_pair(testCANifier->ConfigVelocityMeasurementPeriod(testCANifierConfigs.velocityMeasurementPeriod, timeoutMs),
        "testCANifier->ConfigVelocityMeasurementPeriod(testCANifierConfigs.velocityMeasurementPeriod, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testCANifier->ConfigVelocityMeasurementWindow(testCANifierConfigs.velocityMeasurementWindow, timeoutMs),
        "testCANifier->ConfigVelocityMeasurementWindow(testCANifierConfigs.velocityMeasurementWindow, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testCANifier->ConfigClearPositionOnLimitF(testCANifierConfigs.clearPositionOnLimitF, timeoutMs),
        "testCANifier->ConfigClearPositionOnLimitF(testCANifierConfigs.clearPositionOnLimitF, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testCANifier->ConfigClearPositionOnLimitR(testCANifierConfigs.clearPositionOnLimitR, timeoutMs),
        "testCANifier->ConfigClearPositionOnLimitR(testCANifierConfigs.clearPositionOnLimitR, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testCANifier->ConfigClearPositionOnQuadIdx(testCANifierConfigs.clearPositionOnQuadIdx, timeoutMs),
        "testCANifier->ConfigClearPositionOnQuadIdx(testCANifierConfigs.clearPositionOnQuadIdx, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testCANifier->ConfigSetCustomParam(testCANifierConfigs.customParam0, 0, timeoutMs),
        "testCANifier->ConfigSetCustomParam(testCANifierConfigs.customParam0, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testCANifier->ConfigSetCustomParam(testCANifierConfigs.customParam1, 1, timeoutMs),
        "testCANifier->ConfigSetCustomParam(testCANifierConfigs.customParam1, 1, timeoutMs)"));
    
    
}

void ConfigFactoryDefaultTalon(int id, int timeoutMs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);
    
    errorCodes.push_back(std::make_pair(testTalon->ConfigFactoryDefault(timeoutMs),
        "testTalon->ConfigFactoryDefault(timeoutMs)"));

    
}

void ConfigFactoryDefaultVictor(int id, int timeoutMs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
    
    errorCodes.push_back(std::make_pair(testVictor->ConfigFactoryDefault(timeoutMs),
        "testVictor->ConfigFactoryDefault(timeoutMs)"));

    
}

void ConfigFactoryDefaultPigeon(int id, int timeoutMs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
    
    errorCodes.push_back(std::make_pair(testPigeon->ConfigFactoryDefault(timeoutMs),
        "testPigeon->ConfigFactoryDefault(timeoutMs)"));

    
}

void ConfigFactoryDefaultCANifier(int id, int timeoutMs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    
    errorCodes.push_back(std::make_pair(testCANifier->ConfigFactoryDefault(timeoutMs),
        "testCANifier->ConfigFactoryDefault(timeoutMs)"));

    
}

void ConfigAllTalon(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);
    
    errorCodes.push_back(std::make_pair(testTalon->ConfigAllSettings(testTalonConfigs, timeoutMs),
        "testTalon->ConfigAllSettings(testTalonConfigs, timeoutMs)"));
    
    
}

void ConfigAllVictor(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
    
    errorCodes.push_back(std::make_pair(testVictor->ConfigAllSettings(testVictorConfigs, timeoutMs),
        "testVictor->ConfigAllSettings(testVictorConfigs, timeoutMs)"));

    
}

void ConfigAllPigeon(int id, int timeoutMs, const ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
    
    errorCodes.push_back(std::make_pair(testPigeon->ConfigAllSettings(testPigeonConfigs, timeoutMs),
        "testPigeon->ConfigAllSettings(testPigeonConfigs, timeoutMs)"));

    
}

void ConfigAllCANifier(int id, int timeoutMs, const ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    
    errorCodes.push_back(std::make_pair(testCANifier->ConfigAllSettings(testCANifierConfigs, timeoutMs),
        "testCANifier->ConfigAllSettings(testCANifierConfigs, timeoutMs)"));
    
}

void GetAllConfigsTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);

    testTalon->GetAllConfigs(testTalonConfigs, timeoutMs);    

    errorCodes.push_back(std::make_pair(testTalon->GetLastError(),
        "testTalon->GetAllConfigs(testTalonConfigs, timeoutMs)"));
    
    
}

void GetAllConfigsVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
    
    testVictor->GetAllConfigs(testVictorConfigs, timeoutMs);    

    errorCodes.push_back(std::make_pair(testVictor->GetLastError(),
        "testVictor->GetAllConfigs(testVictorConfigs, timeoutMs)"));
    
}

void GetAllConfigsPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
    
    testPigeon->GetAllConfigs(testPigeonConfigs, timeoutMs);    

    errorCodes.push_back(std::make_pair(testPigeon->GetLastError(),
        "testPigeon->GetAllConfigs(testPigeonConfigs, timeoutMs)"));
    
}

void GetAllConfigsCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    
    testCANifier->GetAllConfigs(testCANifierConfigs, timeoutMs);    

    errorCodes.push_back(std::make_pair(testCANifier->GetLastError(),
        "testCANifier->GetAllConfigs(testCANifierConfigs, timeoutMs)"));
    
}
void GenerateCustomParamSendValues(ctre::phoenix::CustomParamConfiguration &configs, std::default_random_engine &engine) {
    auto iterCustomParam = genericParamEnumSets.find(ctre::phoenix::ParamEnum::eCustomParam);

    configs.customParam0 = static_cast<int>((*iterCustomParam->second.generateToSend)(iterCustomParam->second.generationParams, engine));
    configs.customParam1 = static_cast<int>((*iterCustomParam->second.generateToSend)(iterCustomParam->second.generationParams, engine));
}

void GenerateCANifierSendValues(ctre::phoenix::CANifierConfiguration &configs, std::default_random_engine &engine) {
    GenerateCustomParamSendValues(configs, engine);
    
    auto iterSampleVelocityPeriod = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityPeriod);

    configs.velocityMeasurementPeriod = static_cast<ctre::phoenix::CANifierVelocityMeasPeriod>((*iterSampleVelocityPeriod->second.generateToSend)(iterSampleVelocityPeriod->second.generationParams, engine));

    auto iterSampleVelocityWindow = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityWindow);

    configs.velocityMeasurementWindow  = static_cast<int>((*iterSampleVelocityWindow->second.generateToSend)(iterSampleVelocityWindow->second.generationParams, engine));

    auto iterClearPositionOnLimitF = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitF);
    
    configs.clearPositionOnLimitF = static_cast<bool>((*iterClearPositionOnLimitF->second.generateToSend)(iterClearPositionOnLimitF->second.generationParams, engine));
    
    auto iterClearPositionOnLimitR = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitR);

    configs.clearPositionOnLimitR = static_cast<bool>((*iterClearPositionOnLimitR->second.generateToSend)(iterClearPositionOnLimitR->second.generationParams, engine));

    auto iterClearPositionOnQuadIdx = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx);

    configs.clearPositionOnQuadIdx = static_cast<bool>((*iterClearPositionOnQuadIdx->second.generateToSend)(iterClearPositionOnQuadIdx->second.generationParams, engine));
}
void GeneratePigeonSendValues(ctre::phoenix::sensors::PigeonIMUConfiguration &configs, std::default_random_engine &engine) {
    GenerateCustomParamSendValues(configs, engine);
}
void GenerateSlotSendValues(ctre::phoenix::motorcontrol::can::SlotConfiguration &configs, std::default_random_engine &engine) {

    auto iterProfileParamSlot_P = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_P);

    configs.kP = (*iterProfileParamSlot_P->second.generateToSend)(iterProfileParamSlot_P->second.generationParams, engine);
 
    auto iterProfileParamSlot_I = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_I);

    configs.kI = (*iterProfileParamSlot_I->second.generateToSend)(iterProfileParamSlot_I->second.generationParams, engine);
 
    auto iterProfileParamSlot_D = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_D);

    configs.kD = (*iterProfileParamSlot_D->second.generateToSend)(iterProfileParamSlot_D->second.generationParams, engine);
 
    auto iterProfileParamSlot_F = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_F);

    configs.kF = (*iterProfileParamSlot_F->second.generateToSend)(iterProfileParamSlot_F->second.generationParams, engine);
 
    auto iterProfileParamSlot_IZone = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_IZone);

    configs.integralZone = static_cast<int>((*iterProfileParamSlot_IZone->second.generateToSend)(iterProfileParamSlot_IZone->second.generationParams, engine));
 
    auto iterProfileParamSlot_AllowableErr = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr);

    configs.allowableClosedloopError = static_cast<int>((*iterProfileParamSlot_AllowableErr->second.generateToSend)(iterProfileParamSlot_AllowableErr->second.generationParams, engine));
 
    auto iterProfileParamSlot_MaxIAccum = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum);

    configs.maxIntegralAccumulator = static_cast<int>((*iterProfileParamSlot_MaxIAccum->second.generateToSend)(iterProfileParamSlot_MaxIAccum->second.generationParams, engine));
 
    auto iterProfileParamSlot_PeakOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput);

    configs.closedLoopPeakOutput = (*iterProfileParamSlot_PeakOutput->second.generateToSend)(iterProfileParamSlot_PeakOutput->second.generationParams, engine);
 
    auto iterPIDLoopPeriod = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePIDLoopPeriod);

    configs.closedLoopPeriod = static_cast<int>((*iterPIDLoopPeriod->second.generateToSend)(iterPIDLoopPeriod->second.generationParams, engine));
}
void GenerateFilterSendValues(ctre::phoenix::motorcontrol::can::FilterConfiguration &configs, std::default_random_engine &engine) {

    auto iterRemoteSensorDeviceID = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eRemoteSensorDeviceID);

    configs.remoteSensorDeviceID = static_cast<int>((*iterRemoteSensorDeviceID->second.generateToSend)(iterRemoteSensorDeviceID->second.generationParams, engine));
 
    auto iterRemoteSensorSource = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eRemoteSensorSource);

    configs.remoteSensorSource = static_cast<ctre::phoenix::motorcontrol::RemoteSensorSource>((*iterRemoteSensorSource->second.generateToSend)(iterRemoteSensorSource->second.generationParams, engine));
}
void GenerateBasePIDSendValues(ctre::phoenix::motorcontrol::can::BasePIDSetConfiguration &configs, std::default_random_engine &engine) {

    auto iterSelectedSensorCoefficient = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eSelectedSensorCoefficient);

    configs.selectedFeedbackCoefficient = (*iterSelectedSensorCoefficient->second.generateToSend)(iterSelectedSensorCoefficient->second.generationParams, engine);
}
void GenerateBaseMotControllerSendValues(ctre::phoenix::motorcontrol::can::BaseMotorControllerConfiguration &configs, std::default_random_engine &engine) {

    GenerateCustomParamSendValues(configs, engine);
    GenerateSlotSendValues(configs.slot0, engine);
    GenerateSlotSendValues(configs.slot1, engine);
    GenerateSlotSendValues(configs.slot2, engine);
    GenerateSlotSendValues(configs.slot3, engine);
    GenerateFilterSendValues(configs.remoteFilter0, engine);
    GenerateFilterSendValues(configs.remoteFilter1, engine);

    auto iterOpenloopRamp = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eOpenloopRamp);

    configs.openloopRamp = RampConversion((*iterOpenloopRamp->second.generateToSend)(iterOpenloopRamp->second.generationParams, engine));
 
    auto iterClosedloopRamp = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eClosedloopRamp);

    configs.closedloopRamp = RampConversion((*iterClosedloopRamp->second.generateToSend)(iterClosedloopRamp->second.generationParams, engine));
 
    auto iterPeakPosOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakPosOutput);

    configs.peakOutputForward = Div_1023((*iterPeakPosOutput->second.generateToSend)(iterPeakPosOutput->second.generationParams, engine));
 
    auto iterPeakNegOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakNegOutput);

    configs.peakOutputReverse = Div_1023((*iterPeakNegOutput->second.generateToSend)(iterPeakNegOutput->second.generationParams, engine));
 
    auto iterNominalPosOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNominalPosOutput);

    configs.nominalOutputForward = Div_1023((*iterNominalPosOutput->second.generateToSend)(iterNominalPosOutput->second.generationParams, engine));
 
    auto iterNominalNegOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNominalNegOutput);

    configs.nominalOutputReverse = Div_1023((*iterNominalNegOutput->second.generateToSend)(iterNominalNegOutput->second.generationParams, engine));
 
    auto iterNeutralDeadband = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNeutralDeadband);

    configs.neutralDeadband = Div_1023((*iterNeutralDeadband->second.generateToSend)(iterNeutralDeadband->second.generationParams, engine));
 
    auto iterNominalBatteryVoltage = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNominalBatteryVoltage);

    configs.voltageCompSaturation = (*iterNominalBatteryVoltage->second.generateToSend)(iterNominalBatteryVoltage->second.generationParams, engine);
 
    auto iterBatteryVoltageFilterSize = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize);

    configs.voltageMeasurementFilter = static_cast<int>((*iterBatteryVoltageFilterSize->second.generateToSend)(iterBatteryVoltageFilterSize->second.generationParams, engine));
 
    auto iterSampleVelocityPeriod = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityPeriod);

    configs.velocityMeasurementPeriod = static_cast<ctre::phoenix::motorcontrol::VelocityMeasPeriod>((*iterSampleVelocityPeriod->second.generateToSend)(iterSampleVelocityPeriod->second.generationParams, engine));
 
    auto iterSampleVelocityWindow = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityWindow);

    configs.velocityMeasurementWindow = static_cast<int>((*iterSampleVelocityWindow->second.generateToSend)(iterSampleVelocityWindow->second.generationParams, engine));
 
    auto iterForwardSoftLimitThreshold = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold);

    configs.forwardSoftLimitThreshold = static_cast<int>((*iterForwardSoftLimitThreshold->second.generateToSend)(iterForwardSoftLimitThreshold->second.generationParams, engine));
 
    auto iterReverseSoftLimitThreshold = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold);

    configs.reverseSoftLimitThreshold = static_cast<int>((*iterReverseSoftLimitThreshold->second.generateToSend)(iterReverseSoftLimitThreshold->second.generationParams, engine));
 
    auto iterForwardSoftLimitEnable = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eForwardSoftLimitEnable);

    configs.forwardSoftLimitEnable = static_cast<int>((*iterForwardSoftLimitEnable->second.generateToSend)(iterForwardSoftLimitEnable->second.generationParams, engine));
 
    auto iterReverseSoftLimitEnable = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eReverseSoftLimitEnable);

    configs.reverseSoftLimitEnable = static_cast<int>((*iterReverseSoftLimitEnable->second.generateToSend)(iterReverseSoftLimitEnable->second.generationParams, engine));
 
    auto iterPIDLoopPolarity = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePIDLoopPolarity);

    configs.auxPIDPolarity = static_cast<bool>((*iterPIDLoopPolarity->second.generateToSend)(iterPIDLoopPolarity->second.generationParams, engine));
 
    auto iterMotMag_VelCruise = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eMotMag_VelCruise);

    configs.motionCruiseVelocity = static_cast<int>((*iterMotMag_VelCruise->second.generateToSend)(iterMotMag_VelCruise->second.generationParams, engine));
 
    auto iterMotMag_Accel = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eMotMag_Accel);

    configs.motionAcceleration = static_cast<int>((*iterMotMag_Accel->second.generateToSend)(iterMotMag_Accel->second.generationParams, engine));
 
    auto iterMotionProfileTrajectoryPointDurationMs = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs);

    configs.motionProfileTrajectoryPeriod = static_cast<int>((*iterMotionProfileTrajectoryPointDurationMs->second.generateToSend)(iterMotionProfileTrajectoryPointDurationMs->second.generationParams, engine));
 
    auto iterFeedbackNotContinuous = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackNotContinuous);

    configs.feedbackNotContinuous = static_cast<bool>((*iterFeedbackNotContinuous->second.generateToSend)(iterFeedbackNotContinuous->second.generationParams, engine));
 
    auto itereRemoteSensorClosedLoopDisableNeutralOnLOS = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS);

    configs.remoteSensorClosedLoopDisableNeutralOnLOS = static_cast<bool>((*itereRemoteSensorClosedLoopDisableNeutralOnLOS->second.generateToSend)(itereRemoteSensorClosedLoopDisableNeutralOnLOS->second.generationParams, engine));
 
    auto iterClearPositionOnLimitF = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitF);

    configs.clearPositionOnLimitF = static_cast<bool>((*iterClearPositionOnLimitF->second.generateToSend)(iterClearPositionOnLimitF->second.generationParams, engine));
 
    auto iterClearPositionOnLimitR = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitR);

    configs.clearPositionOnLimitR = static_cast<bool>((*iterClearPositionOnLimitR->second.generateToSend)(iterClearPositionOnLimitR->second.generationParams, engine));
 
    auto iterClearPositionOnQuadIdx = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx);

    configs.clearPositionOnQuadIdx = static_cast<bool>((*iterClearPositionOnQuadIdx->second.generateToSend)(iterClearPositionOnQuadIdx->second.generationParams, engine));
 
    auto iterLimitSwitchDisableNeutralOnLOS = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS);

    configs.limitSwitchDisableNeutralOnLOS = static_cast<bool>((*iterLimitSwitchDisableNeutralOnLOS->second.generateToSend)(iterLimitSwitchDisableNeutralOnLOS->second.generationParams, engine));
 
    auto iterSoftLimitDisableNeutralOnLOS = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS);

    configs.softLimitDisableNeutralOnLOS = static_cast<bool>((*iterSoftLimitDisableNeutralOnLOS->second.generateToSend)(iterSoftLimitDisableNeutralOnLOS->second.generationParams, engine));
 
    auto iterPulseWidthPeriod_EdgesPerRot = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot);

    configs.pulseWidthPeriod_EdgesPerRot = static_cast<int>((*iterPulseWidthPeriod_EdgesPerRot->second.generateToSend)(iterPulseWidthPeriod_EdgesPerRot->second.generationParams, engine));
 
    auto iterPulseWidthPeriod_FilterWindowSz = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz);

    configs.pulseWidthPeriod_FilterWindowSz = static_cast<int>((*iterPulseWidthPeriod_FilterWindowSz->second.generateToSend)(iterPulseWidthPeriod_FilterWindowSz->second.generationParams, engine));
 
}

void GenerateTalonPIDSendValues(ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration &configs, std::default_random_engine &engine) {
    GenerateBasePIDSendValues(configs, engine);
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    configs.selectedFeedbackSensor = static_cast<ctre::phoenix::motorcontrol::FeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine)); 
}

void GenerateVictorPIDSendValues(ctre::phoenix::motorcontrol::can::VictorSPXPIDSetConfiguration &configs, std::default_random_engine &engine) {
    GenerateBasePIDSendValues(configs, engine);
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    std::vector<double> onlyVictorVals = {0, 9, 10, 11, 12};
    configs.selectedFeedbackSensor = static_cast<ctre::phoenix::motorcontrol::RemoteFeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(onlyVictorVals, engine)); 
}
void GenerateTalonSendValues(ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &configs, std::default_random_engine &engine) {
    GenerateBaseMotControllerSendValues(configs, engine);
    GenerateTalonPIDSendValues(configs.primaryPID, engine);
    GenerateTalonPIDSendValues(configs.auxilaryPID, engine);

    auto iterLimitSwitchSource = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchSource);

    configs.forwardLimitSwitchSource = static_cast<ctre::phoenix::motorcontrol::LimitSwitchSource>((*iterLimitSwitchSource->second.generateToSend)(iterLimitSwitchSource->second.generationParams, engine));
 
    configs.reverseLimitSwitchSource = static_cast<ctre::phoenix::motorcontrol::LimitSwitchSource>((*iterLimitSwitchSource->second.generateToSend)(iterLimitSwitchSource->second.generationParams, engine));
 
    auto iterLimitSwitchRemoteDevID = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID);

    configs.forwardLimitSwitchDeviceID = static_cast<int>((*iterLimitSwitchRemoteDevID->second.generateToSend)(iterLimitSwitchRemoteDevID->second.generationParams, engine));
 
    configs.reverseLimitSwitchDeviceID = static_cast<int>((*iterLimitSwitchRemoteDevID->second.generateToSend)(iterLimitSwitchRemoteDevID->second.generationParams, engine));
 
    auto iterLimitSwitchNormClosedAndDis = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis);

    configs.forwardLimitSwitchNormal = static_cast<ctre::phoenix::motorcontrol::LimitSwitchNormal>((*iterLimitSwitchNormClosedAndDis->second.generateToSend)(iterLimitSwitchNormClosedAndDis->second.generationParams, engine));
 
    configs.reverseLimitSwitchNormal = static_cast<ctre::phoenix::motorcontrol::LimitSwitchNormal>((*iterLimitSwitchNormClosedAndDis->second.generateToSend)(iterLimitSwitchNormClosedAndDis->second.generationParams, engine));
 
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    configs.sum0Term = static_cast<ctre::phoenix::motorcontrol::FeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));
 
    configs.sum1Term = static_cast<ctre::phoenix::motorcontrol::FeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));
 
    configs.diff0Term = static_cast<ctre::phoenix::motorcontrol::FeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));
 
    configs.diff1Term = static_cast<ctre::phoenix::motorcontrol::FeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));
 
    auto iterePeakCurrentLimitAmps = currentParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps);

    configs.peakCurrentLimit = static_cast<int>((*iterePeakCurrentLimitAmps->second.generateToSend)(iterePeakCurrentLimitAmps->second.generationParams, engine));
 
    auto iterPeakCurrentLimitMs = currentParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakCurrentLimitMs);

    configs.peakCurrentDuration = static_cast<int>((*iterPeakCurrentLimitMs->second.generateToSend)(iterPeakCurrentLimitMs->second.generationParams, engine));
 
    auto iterContinuousCurrentLimitAmps = currentParamEnumSets.find(ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps);

    configs.continuousCurrentLimit = static_cast<int>((*iterContinuousCurrentLimitAmps->second.generateToSend)(iterContinuousCurrentLimitAmps->second.generationParams, engine));
 
}
void GenerateVictorSendValues(ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &configs, std::default_random_engine &engine) {
    GenerateBaseMotControllerSendValues(configs, engine);
    GenerateVictorPIDSendValues(configs.primaryPID, engine);
    GenerateVictorPIDSendValues(configs.auxilaryPID, engine);

    auto iterLimitSwitchSource = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchSource);

    configs.forwardLimitSwitchSource = static_cast<ctre::phoenix::motorcontrol::RemoteLimitSwitchSource>((*iterLimitSwitchSource->second.generateToSend)(iterLimitSwitchSource->second.generationParams, engine));

    configs.reverseLimitSwitchSource = static_cast<ctre::phoenix::motorcontrol::RemoteLimitSwitchSource>((*iterLimitSwitchSource->second.generateToSend)(iterLimitSwitchSource->second.generationParams, engine));
 
    auto iterLimitSwitchRemoteDevID = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID);

    configs.forwardLimitSwitchDeviceID = static_cast<int>((*iterLimitSwitchRemoteDevID->second.generateToSend)(iterLimitSwitchRemoteDevID->second.generationParams, engine));

    configs.reverseLimitSwitchDeviceID = static_cast<int>((*iterLimitSwitchRemoteDevID->second.generateToSend)(iterLimitSwitchRemoteDevID->second.generationParams, engine));
 
    auto iterLimitSwitchNormClosedAndDis = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis);

    configs.forwardLimitSwitchNormal = static_cast<ctre::phoenix::motorcontrol::LimitSwitchNormal>((*iterLimitSwitchNormClosedAndDis->second.generateToSend)(iterLimitSwitchNormClosedAndDis->second.generationParams, engine));

    configs.reverseLimitSwitchNormal = static_cast<ctre::phoenix::motorcontrol::LimitSwitchNormal>((*iterLimitSwitchNormClosedAndDis->second.generateToSend)(iterLimitSwitchNormClosedAndDis->second.generationParams, engine));
 
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    configs.sum0Term = static_cast<ctre::phoenix::motorcontrol::RemoteFeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));

    configs.sum1Term = static_cast<ctre::phoenix::motorcontrol::RemoteFeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));
 
    configs.diff0Term = static_cast<ctre::phoenix::motorcontrol::RemoteFeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));

    configs.diff1Term = static_cast<ctre::phoenix::motorcontrol::RemoteFeedbackDevice>((*iterFeedbackSensorType->second.generateToSend)(iterFeedbackSensorType->second.generationParams, engine));
 
}

void EqualityCheckCustomParam(const ctre::phoenix::CustomParamConfiguration &configs1, const ctre::phoenix::CustomParamConfiguration &configs2) {

    auto iterCustomParam = genericParamEnumSets.find(ctre::phoenix::ParamEnum::eCustomParam);

    ASSERT_NEAR(configs1.customParam0, configs2.customParam0, iterCustomParam->second.equalityInterval);
    ASSERT_NEAR(configs1.customParam1, configs2.customParam1, iterCustomParam->second.equalityInterval);

}
void EqualityCheckCANifier(const ctre::phoenix::CANifierConfiguration &configs1, const ctre::phoenix::CANifierConfiguration &configs2) {

    EqualityCheckCustomParam(configs1, configs2);
    
    auto iterSampleVelocityPeriod = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityPeriod);

    ASSERT_NEAR(configs1.velocityMeasurementPeriod, configs2.velocityMeasurementPeriod, iterSampleVelocityPeriod->second.equalityInterval);

    auto iterSampleVelocityWindow = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityWindow);

    ASSERT_NEAR(configs1.velocityMeasurementWindow, configs2.velocityMeasurementWindow, iterSampleVelocityWindow->second.equalityInterval);

    auto iterClearPositionOnLimitF = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitF);
    
    ASSERT_NEAR(configs1.clearPositionOnLimitF, configs2.clearPositionOnLimitF, iterClearPositionOnLimitF->second.equalityInterval);
    
    auto iterClearPositionOnLimitR = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitR);

    ASSERT_NEAR(configs1.clearPositionOnLimitR, configs2.clearPositionOnLimitR, iterClearPositionOnLimitR->second.equalityInterval);

    auto iterClearPositionOnQuadIdx = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx);

    ASSERT_NEAR(configs1.clearPositionOnQuadIdx, configs2.clearPositionOnQuadIdx, iterClearPositionOnQuadIdx->second.equalityInterval);

}
void EqualityCheckPigeon(const ctre::phoenix::sensors::PigeonIMUConfiguration &configs1, const ctre::phoenix::sensors::PigeonIMUConfiguration &configs2) {

    EqualityCheckCustomParam(configs1, configs2);

}
void EqualityCheckSlot(const ctre::phoenix::motorcontrol::can::SlotConfiguration &configs1, const ctre::phoenix::motorcontrol::can::SlotConfiguration &configs2) {

    auto iterProfileParamSlot_P = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_P);

    ASSERT_NEAR(configs1.kP, configs2.kP, iterProfileParamSlot_P->second.equalityInterval);
 
    auto iterProfileParamSlot_I = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_I);

    ASSERT_NEAR(configs1.kI, configs2.kI, iterProfileParamSlot_I->second.equalityInterval);
 
    auto iterProfileParamSlot_D = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_D);

    ASSERT_NEAR(configs1.kD, configs2.kD, iterProfileParamSlot_D->second.equalityInterval);
 
    auto iterProfileParamSlot_F = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_F);

    ASSERT_NEAR(configs1.kF, configs2.kF, iterProfileParamSlot_F->second.equalityInterval);
 
    auto iterProfileParamSlot_IZone = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_IZone);

    ASSERT_NEAR(configs1.integralZone, configs2.integralZone, iterProfileParamSlot_IZone->second.equalityInterval);
 
    auto iterProfileParamSlot_AllowableErr = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_AllowableErr);

    ASSERT_NEAR(configs1.allowableClosedloopError, configs2.allowableClosedloopError, iterProfileParamSlot_AllowableErr->second.equalityInterval);
 
    auto iterProfileParamSlot_MaxIAccum = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_MaxIAccum);

    ASSERT_NEAR(configs1.maxIntegralAccumulator, configs2.maxIntegralAccumulator, iterProfileParamSlot_MaxIAccum->second.equalityInterval);
 
    auto iterProfileParamSlot_PeakOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eProfileParamSlot_PeakOutput);

    ASSERT_NEAR(configs1.closedLoopPeakOutput, configs2.closedLoopPeakOutput, iterProfileParamSlot_PeakOutput->second.equalityInterval);
 
    auto iterPIDLoopPeriod = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePIDLoopPeriod);

    ASSERT_NEAR(configs1.closedLoopPeriod, configs2.closedLoopPeriod, iterPIDLoopPeriod->second.equalityInterval);

}
void EqualityCheckFilter(const ctre::phoenix::motorcontrol::can::FilterConfiguration &configs1, const ctre::phoenix::motorcontrol::can::FilterConfiguration &configs2) {

    auto iterRemoteSensorDeviceID = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eRemoteSensorDeviceID);

    ASSERT_NEAR(configs1.remoteSensorDeviceID, configs2.remoteSensorDeviceID, iterRemoteSensorDeviceID->second.equalityInterval);
 
    auto iterRemoteSensorSource = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eRemoteSensorSource);

    ASSERT_NEAR((int) configs1.remoteSensorSource, (int) configs2.remoteSensorSource, iterRemoteSensorSource->second.equalityInterval);

}
void EqualityCheckBasePID(const ctre::phoenix::motorcontrol::can::BasePIDSetConfiguration &configs1, const ctre::phoenix::motorcontrol::can::BasePIDSetConfiguration &configs2) {

    auto iterSelectedSensorCoefficient = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eSelectedSensorCoefficient);

    ASSERT_NEAR(configs1.selectedFeedbackCoefficient, configs2.selectedFeedbackCoefficient, iterSelectedSensorCoefficient->second.equalityInterval);

}
void EqualityCheckBaseMotController(const ctre::phoenix::motorcontrol::can::BaseMotorControllerConfiguration &configs1, const ctre::phoenix::motorcontrol::can::BaseMotorControllerConfiguration &configs2) {
    EqualityCheckCustomParam(configs1, configs2);
    EqualityCheckSlot(configs1.slot0, configs2.slot0);
    EqualityCheckSlot(configs1.slot1, configs2.slot1);
    EqualityCheckSlot(configs1.slot2, configs2.slot2);
    EqualityCheckSlot(configs1.slot3, configs1.slot3);
    EqualityCheckFilter(configs1.remoteFilter0, configs2.remoteFilter0);
    EqualityCheckFilter(configs1.remoteFilter1, configs2.remoteFilter1);

    auto iterOpenloopRamp = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eOpenloopRamp);

    ASSERT_NEAR(configs1.openloopRamp, configs2.openloopRamp, RampConversion(iterOpenloopRamp->second.equalityInterval));
 
    auto iterClosedloopRamp = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eClosedloopRamp);

    ASSERT_NEAR(configs1.closedloopRamp, configs2.closedloopRamp, RampConversion(iterClosedloopRamp->second.equalityInterval));
 
    auto iterPeakPosOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakPosOutput);

    ASSERT_NEAR(configs1.peakOutputForward, configs2.peakOutputForward, Div_1023(iterPeakPosOutput->second.equalityInterval));
 
    auto iterPeakNegOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakNegOutput);

    ASSERT_NEAR(configs1.peakOutputReverse, configs2.peakOutputReverse, Div_1023(iterPeakNegOutput->second.equalityInterval));
 
    auto iterNominalPosOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNominalPosOutput);

    ASSERT_NEAR(configs1.nominalOutputForward, configs2.nominalOutputForward, Div_1023(iterNominalPosOutput->second.equalityInterval));
 
    auto iterNominalNegOutput = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNominalNegOutput);

    ASSERT_NEAR(configs1.nominalOutputReverse, configs2.nominalOutputReverse, Div_1023(iterNominalNegOutput->second.equalityInterval));
 
    auto iterNeutralDeadband = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNeutralDeadband);

    ASSERT_NEAR(configs1.neutralDeadband, configs2.neutralDeadband, Div_1023(iterNeutralDeadband->second.equalityInterval));
 
    auto iterNominalBatteryVoltage = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eNominalBatteryVoltage);

    ASSERT_NEAR(configs1.voltageCompSaturation, configs2.voltageCompSaturation, iterNominalBatteryVoltage->second.equalityInterval);
 
    auto iterBatteryVoltageFilterSize = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eBatteryVoltageFilterSize);

    ASSERT_NEAR(configs1.voltageMeasurementFilter, configs2.voltageMeasurementFilter, iterBatteryVoltageFilterSize->second.equalityInterval);
 
    auto iterSampleVelocityPeriod = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityPeriod);

    ASSERT_NEAR(configs1.velocityMeasurementPeriod, configs2.velocityMeasurementPeriod, iterSampleVelocityPeriod->second.equalityInterval);
 
    auto iterSampleVelocityWindow = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSampleVelocityWindow);

    ASSERT_NEAR(configs1.velocityMeasurementWindow, configs2.velocityMeasurementWindow, iterSampleVelocityWindow->second.equalityInterval);
 
    auto iterForwardSoftLimitThreshold = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eForwardSoftLimitThreshold);

    ASSERT_NEAR(configs1.forwardSoftLimitThreshold, configs2.forwardSoftLimitThreshold, iterForwardSoftLimitThreshold->second.equalityInterval);
 
    auto iterReverseSoftLimitThreshold = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eReverseSoftLimitThreshold);

    ASSERT_NEAR(configs1.reverseSoftLimitThreshold, configs2.reverseSoftLimitThreshold, iterReverseSoftLimitThreshold->second.equalityInterval);
 
    auto iterForwardSoftLimitEnable = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eForwardSoftLimitEnable);

    ASSERT_NEAR(configs1.forwardSoftLimitEnable, configs2.forwardSoftLimitEnable, iterForwardSoftLimitEnable->second.equalityInterval);
 
    auto iterReverseSoftLimitEnable = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eReverseSoftLimitEnable);

    ASSERT_NEAR(configs1.reverseSoftLimitEnable, configs2.reverseSoftLimitEnable, iterReverseSoftLimitEnable->second.equalityInterval);
 
    auto iterPIDLoopPolarity = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::ePIDLoopPolarity);

    ASSERT_NEAR(configs1.auxPIDPolarity, configs2.auxPIDPolarity, iterPIDLoopPolarity->second.equalityInterval);
 
    auto iterMotMag_VelCruise = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eMotMag_VelCruise);

    ASSERT_NEAR(configs1.motionCruiseVelocity, configs2.motionCruiseVelocity, iterMotMag_VelCruise->second.equalityInterval);
 
    auto iterMotMag_Accel = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eMotMag_Accel);

    ASSERT_NEAR(configs1.motionAcceleration, configs2.motionAcceleration, iterMotMag_Accel->second.equalityInterval);
 
    auto iterMotionProfileTrajectoryPointDurationMs = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eMotionProfileTrajectoryPointDurationMs);

    ASSERT_NEAR(configs1.motionProfileTrajectoryPeriod, configs2.motionProfileTrajectoryPeriod, iterMotionProfileTrajectoryPointDurationMs->second.equalityInterval);
 
    auto iterFeedbackNotContinuous = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackNotContinuous);

    ASSERT_NEAR(configs1.feedbackNotContinuous, configs2.feedbackNotContinuous, iterFeedbackNotContinuous->second.equalityInterval);
 
    auto itereRemoteSensorClosedLoopDisableNeutralOnLOS = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eRemoteSensorClosedLoopDisableNeutralOnLOS);

    ASSERT_NEAR(configs1.remoteSensorClosedLoopDisableNeutralOnLOS, configs2.remoteSensorClosedLoopDisableNeutralOnLOS, itereRemoteSensorClosedLoopDisableNeutralOnLOS->second.equalityInterval);
 
    auto iterClearPositionOnLimitF = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitF);

    ASSERT_NEAR(configs1.clearPositionOnLimitF, configs2.clearPositionOnLimitF, iterClearPositionOnLimitF->second.equalityInterval);
 
    auto iterClearPositionOnLimitR = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnLimitR);

    ASSERT_NEAR(configs1.clearPositionOnLimitR, configs2.clearPositionOnLimitR, iterClearPositionOnLimitR->second.equalityInterval);
 
    auto iterClearPositionOnQuadIdx = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eClearPositionOnQuadIdx);

    ASSERT_NEAR(configs1.clearPositionOnQuadIdx, configs2.clearPositionOnQuadIdx, iterClearPositionOnQuadIdx->second.equalityInterval);
 
    auto iterLimitSwitchDisableNeutralOnLOS = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchDisableNeutralOnLOS);

    ASSERT_NEAR(configs1.limitSwitchDisableNeutralOnLOS, configs2.limitSwitchDisableNeutralOnLOS, iterLimitSwitchDisableNeutralOnLOS->second.equalityInterval);
 
    auto iterSoftLimitDisableNeutralOnLOS = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::eSoftLimitDisableNeutralOnLOS);

    ASSERT_NEAR(configs1.softLimitDisableNeutralOnLOS, configs2.softLimitDisableNeutralOnLOS, iterSoftLimitDisableNeutralOnLOS->second.equalityInterval);
 
    auto iterPulseWidthPeriod_EdgesPerRot = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::ePulseWidthPeriod_EdgesPerRot);

    ASSERT_NEAR(configs1.pulseWidthPeriod_EdgesPerRot, configs2.pulseWidthPeriod_EdgesPerRot, iterPulseWidthPeriod_EdgesPerRot->second.equalityInterval);
 
    auto iterPulseWidthPeriod_FilterWindowSz = sensorParamEnumSets.find(ctre::phoenix::ParamEnum::ePulseWidthPeriod_FilterWindowSz);

    ASSERT_NEAR(configs1.pulseWidthPeriod_FilterWindowSz, configs2.pulseWidthPeriod_FilterWindowSz, iterPulseWidthPeriod_FilterWindowSz->second.equalityInterval);
 

}
void EqualityCheckTalonPID(const ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration &configs1, const ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration &configs2) {
    EqualityCheckBasePID(configs1, configs2);
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    ASSERT_NEAR(configs1.selectedFeedbackSensor, configs2.selectedFeedbackSensor, iterFeedbackSensorType->second.equalityInterval);

}
void EqualityCheckVictorPID(const ctre::phoenix::motorcontrol::can::VictorSPXPIDSetConfiguration &configs1, const ctre::phoenix::motorcontrol::can::VictorSPXPIDSetConfiguration &configs2) {
    EqualityCheckBasePID(configs1, configs2);
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    ASSERT_NEAR(configs1.selectedFeedbackSensor, configs2.selectedFeedbackSensor, iterFeedbackSensorType->second.equalityInterval);

}
void EqualityCheckTalon(const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &configs1, const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &configs2) {
    EqualityCheckBaseMotController(configs1, configs2);
    EqualityCheckTalonPID(configs1.primaryPID, configs2.primaryPID);
    EqualityCheckTalonPID(configs1.auxilaryPID, configs2.auxilaryPID);

    auto iterLimitSwitchSource = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchSource);

    ASSERT_NEAR(configs1.forwardLimitSwitchSource, configs2.forwardLimitSwitchSource, iterLimitSwitchSource->second.equalityInterval);
 
    ASSERT_NEAR(configs1.reverseLimitSwitchSource, configs2.reverseLimitSwitchSource, iterLimitSwitchSource->second.equalityInterval);
 
    auto iterLimitSwitchRemoteDevID = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID);

    ASSERT_NEAR(configs1.forwardLimitSwitchDeviceID, configs2.forwardLimitSwitchDeviceID, iterLimitSwitchRemoteDevID->second.equalityInterval);
 
    ASSERT_NEAR(configs1.reverseLimitSwitchDeviceID, configs2.reverseLimitSwitchDeviceID, iterLimitSwitchRemoteDevID->second.equalityInterval);
 
    auto iterLimitSwitchNormClosedAndDis = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis);

    ASSERT_NEAR(configs1.forwardLimitSwitchNormal, configs2.forwardLimitSwitchNormal, iterLimitSwitchNormClosedAndDis->second.equalityInterval);
 
    ASSERT_NEAR(configs1.reverseLimitSwitchNormal, configs2.reverseLimitSwitchNormal, iterLimitSwitchNormClosedAndDis->second.equalityInterval);
 
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    ASSERT_NEAR(configs1.sum0Term, configs2.sum0Term, iterFeedbackSensorType->second.equalityInterval);
 
    ASSERT_NEAR(configs1.sum1Term, configs2.sum1Term, iterFeedbackSensorType->second.equalityInterval);
 
    ASSERT_NEAR(configs1.diff0Term, configs2.diff0Term, iterFeedbackSensorType->second.equalityInterval);
 
    ASSERT_NEAR(configs1.diff1Term, configs2.diff1Term, iterFeedbackSensorType->second.equalityInterval);
 
    auto iterePeakCurrentLimitAmps = currentParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakCurrentLimitAmps);

    ASSERT_NEAR(configs1.peakCurrentLimit, configs2.peakCurrentLimit, iterePeakCurrentLimitAmps->second.equalityInterval);
 
    auto iterPeakCurrentLimitMs = currentParamEnumSets.find(ctre::phoenix::ParamEnum::ePeakCurrentLimitMs);

    ASSERT_NEAR(configs1.peakCurrentDuration, configs2.peakCurrentDuration, iterPeakCurrentLimitMs->second.equalityInterval);
 
    auto iterContinuousCurrentLimitAmps = currentParamEnumSets.find(ctre::phoenix::ParamEnum::eContinuousCurrentLimitAmps);

    ASSERT_NEAR(configs1.continuousCurrentLimit, configs2.continuousCurrentLimit, iterContinuousCurrentLimitAmps->second.equalityInterval);
 

}
void EqualityCheckVictor(const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &configs1, const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &configs2) {
    
    EqualityCheckBaseMotController(configs1, configs2);
    EqualityCheckVictorPID(configs1.primaryPID, configs2.primaryPID);
    EqualityCheckVictorPID(configs1.auxilaryPID, configs2.auxilaryPID);

    auto iterLimitSwitchSource = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchSource);

    ASSERT_NEAR(configs1.forwardLimitSwitchSource, configs2.forwardLimitSwitchSource, iterLimitSwitchSource->second.equalityInterval);

    ASSERT_NEAR(configs1.reverseLimitSwitchSource, configs2.reverseLimitSwitchSource, iterLimitSwitchSource->second.equalityInterval);
 
    auto iterLimitSwitchRemoteDevID = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchRemoteDevID);

    ASSERT_NEAR(configs1.forwardLimitSwitchDeviceID, configs2.forwardLimitSwitchDeviceID, iterLimitSwitchRemoteDevID->second.equalityInterval);

    ASSERT_NEAR(configs1.reverseLimitSwitchDeviceID, configs2.reverseLimitSwitchDeviceID, iterLimitSwitchRemoteDevID->second.equalityInterval);
 
    auto iterLimitSwitchNormClosedAndDis = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eLimitSwitchNormClosedAndDis);

    ASSERT_NEAR(configs1.forwardLimitSwitchNormal, configs2.forwardLimitSwitchNormal, iterLimitSwitchNormClosedAndDis->second.equalityInterval);

    ASSERT_NEAR(configs1.reverseLimitSwitchNormal, configs2.reverseLimitSwitchNormal, iterLimitSwitchNormClosedAndDis->second.equalityInterval);
 
    auto iterFeedbackSensorType = motControllerParamEnumSets.find(ctre::phoenix::ParamEnum::eFeedbackSensorType);

    ASSERT_NEAR(configs1.sum0Term, configs2.sum0Term, iterFeedbackSensorType->second.equalityInterval);

    ASSERT_NEAR(configs1.sum1Term, configs2.sum1Term, iterFeedbackSensorType->second.equalityInterval);
 
    ASSERT_NEAR(configs1.diff0Term, configs2.diff0Term, iterFeedbackSensorType->second.equalityInterval);

    ASSERT_NEAR(configs1.diff1Term, configs2.diff1Term, iterFeedbackSensorType->second.equalityInterval);

}
