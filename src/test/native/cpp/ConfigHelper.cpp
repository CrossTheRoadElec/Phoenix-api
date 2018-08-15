#include "ConfigHelper.h"
#include <memory>

void ConfigAllIndividualTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes) {

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

void ConfigAllIndividualVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes) {
    
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

void ConfigAllIndividualPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes) {
    
    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);

    errorCodes.push_back(std::make_pair(testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam0, 0, timeoutMs),
        "testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam0, 0, timeoutMs)"));
    errorCodes.push_back(std::make_pair(testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam1, 1, timeoutMs),
        "testPigeon->ConfigSetCustomParam(testPigeonConfigs.customParam1, 1, timeoutMs)"));

    
}

void ConfigAllIndividualCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes) {
    
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

void ConfigAllTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);
    
    errorCodes.push_back(std::make_pair(testTalon->ConfigAllSettings(testTalonConfigs, timeoutMs),
        "testTalon->ConfigAllSettings(testTalonConfigs, timeoutMs)"));
    
    
}

void ConfigAllVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
    
    errorCodes.push_back(std::make_pair(testVictor->ConfigAllSettings(testVictorConfigs, timeoutMs),
        "testVictor->ConfigAllSettings(testVictorConfigs, timeoutMs)"));

    
}

void ConfigAllPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
    
    errorCodes.push_back(std::make_pair(testPigeon->ConfigAllSettings(testPigeonConfigs, timeoutMs),
        "testPigeon->ConfigAllSettings(testPigeonConfigs, timeoutMs)"));

    
}

void ConfigAllCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes) {

    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    
    errorCodes.push_back(std::make_pair(testCANifier->ConfigAllSettings(testCANifierConfigs, timeoutMs),
        "testCANifier->ConfigAllSettings(testCANifierConfigs, timeoutMs)"));

    
}
