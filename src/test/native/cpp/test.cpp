#include <gtest/gtest.h>
#include "ctre/Phoenix.h"
#include <iostream>


TEST(IDTest, NormalSet) {
    for(int i = 0; i < 63; i++) {
        ctre::phoenix::motorcontrol::can::TalonSRX testTalon(i);
        ctre::phoenix::motorcontrol::can::VictorSPX testVictor(i);

        ASSERT_EQ(testTalon.GetDeviceID(), i);
        ASSERT_EQ(testVictor.GetDeviceID(), i);
    }
} 
TEST(IDTest, InvalidSet) {
    for(int i = 63; i < 140; i++) {
        ctre::phoenix::motorcontrol::can::TalonSRX testTalon(i);
        ctre::phoenix::motorcontrol::can::VictorSPX testVictor(i);

        ASSERT_EQ(testTalon.GetDeviceID(), i & 0x3F);
        ASSERT_EQ(testVictor.GetDeviceID(), i & 0x3F);
    }
}
TEST(ErrorTest, ConfigSetTimeoutError) {
  
    std::vector<ctre::phoenix::ErrorCode> errorCodes;

    int timeoutMs = 1; //Minimum value to reduce the time required for this test

    ctre::phoenix::motorcontrol::can::TalonSRX testTalon(0);
    ctre::phoenix::motorcontrol::can::VictorSPX testVictor(0);
    ctre::phoenix::sensors::PigeonIMU testPigeon(0);
    ctre::phoenix::CANifier testCANifier(0);

    ctre::phoenix::motorcontrol::can::TalonSRXConfiguration testTalonConfigs;
    ctre::phoenix::motorcontrol::can::VictorSPXConfiguration testVictorConfigs;
    ctre::phoenix::sensors::PigeonIMUConfiguration testPigeonConfigs;
    ctre::phoenix::CANifierConfiguration testCANifierConfigs;

    //CANifier
    errorCodes.push_back(testCANifier.ConfigVelocityMeasurementPeriod(testCANifierConfigs.velocityMeasurementPeriod, timeoutMs));
    errorCodes.push_back(testCANifier.ConfigVelocityMeasurementWindow(testCANifierConfigs.velocityMeasurementWindow, timeoutMs));
    errorCodes.push_back(testCANifier.ConfigClearPositionOnLimitF(testCANifierConfigs.clearPositionOnLimitF, timeoutMs));
    errorCodes.push_back(testCANifier.ConfigClearPositionOnLimitR(testCANifierConfigs.clearPositionOnLimitR, timeoutMs));
    errorCodes.push_back(testCANifier.ConfigClearPositionOnQuadIdx(testCANifierConfigs.clearPositionOnQuadIdx, timeoutMs));
    errorCodes.push_back(testCANifier.ConfigSetCustomParam(testCANifierConfigs.customParam0, 0, timeoutMs));
    errorCodes.push_back(testCANifier.ConfigSetCustomParam(testCANifierConfigs.customParam1, 1, timeoutMs));

    //Pigeon
    errorCodes.push_back(testPigeon.ConfigSetCustomParam(testPigeonConfigs.customParam0, 0, timeoutMs));
    errorCodes.push_back(testPigeon.ConfigSetCustomParam(testPigeonConfigs.customParam1, 1, timeoutMs));

    //TalonSRX
    errorCodes.push_back(testTalon.ConfigOpenloopRamp(testTalonConfigs.openloopRamp, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedloopRamp(testTalonConfigs.closedloopRamp, timeoutMs));
    errorCodes.push_back(testTalon.ConfigPeakOutputForward(testTalonConfigs.peakOutputForward, timeoutMs));
    errorCodes.push_back(testTalon.ConfigPeakOutputReverse(testTalonConfigs.peakOutputReverse, timeoutMs));
    errorCodes.push_back(testTalon.ConfigNominalOutputForward(testTalonConfigs.nominalOutputForward, timeoutMs));
    errorCodes.push_back(testTalon.ConfigNominalOutputReverse(testTalonConfigs.nominalOutputReverse, timeoutMs));
    errorCodes.push_back(testTalon.ConfigNeutralDeadband(testTalonConfigs.neutralDeadband, timeoutMs));
    errorCodes.push_back(testTalon.ConfigVoltageCompSaturation(testTalonConfigs.voltageCompSaturation, timeoutMs));
    errorCodes.push_back(testTalon.ConfigVoltageMeasurementFilter(testTalonConfigs.voltageMeasurementFilter, timeoutMs));
    errorCodes.push_back(testTalon.ConfigVelocityMeasurementPeriod(testTalonConfigs.velocityMeasurementPeriod, timeoutMs));
    errorCodes.push_back(testTalon.ConfigVelocityMeasurementWindow(testTalonConfigs.velocityMeasurementWindow, timeoutMs));
    errorCodes.push_back(testTalon.ConfigForwardSoftLimitThreshold(testTalonConfigs.forwardSoftLimitThreshold, timeoutMs));
    errorCodes.push_back(testTalon.ConfigReverseSoftLimitThreshold(testTalonConfigs.reverseSoftLimitThreshold, timeoutMs));
    errorCodes.push_back(testTalon.ConfigForwardSoftLimitEnable(testTalonConfigs.forwardSoftLimitEnable, timeoutMs));
    errorCodes.push_back(testTalon.ConfigReverseSoftLimitEnable(testTalonConfigs.reverseSoftLimitEnable, timeoutMs));
    errorCodes.push_back(testTalon.ConfigAuxPIDPolarity(testTalonConfigs.auxPIDPolarity, timeoutMs));
    errorCodes.push_back(testTalon.ConfigMotionCruiseVelocity(testTalonConfigs.motionCruiseVelocity, timeoutMs));
    errorCodes.push_back(testTalon.ConfigMotionAcceleration(testTalonConfigs.motionAcceleration, timeoutMs));
    errorCodes.push_back(testTalon.ConfigMotionProfileTrajectoryPeriod(testTalonConfigs.motionProfileTrajectoryPeriod, timeoutMs));
    errorCodes.push_back(testTalon.ConfigFeedbackNotContinuous(testTalonConfigs.feedbackNotContinuous, timeoutMs));
    errorCodes.push_back(testTalon.ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(testTalonConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClearPositionOnLimitF(testTalonConfigs.clearPositionOnLimitF, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClearPositionOnLimitR(testTalonConfigs.clearPositionOnLimitR, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClearPositionOnQuadIdx(testTalonConfigs.clearPositionOnQuadIdx, timeoutMs));
    errorCodes.push_back(testTalon.ConfigLimitSwitchDisableNeutralOnLOS(testTalonConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs));
    errorCodes.push_back(testTalon.ConfigSoftLimitDisableNeutralOnLOS(testTalonConfigs.softLimitDisableNeutralOnLOS, timeoutMs));
    errorCodes.push_back(testTalon.ConfigPulseWidthPeriod_EdgesPerRot(testTalonConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs));
    errorCodes.push_back(testTalon.ConfigPulseWidthPeriod_FilterWindowSz(testTalonConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs));
   
    errorCodes.push_back(testTalon.ConfigRemoteFeedbackFilter(testTalonConfigs.remoteFilter0.remoteSensorDeviceID, testTalonConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs));
    errorCodes.push_back(testTalon.ConfigRemoteFeedbackFilter(testTalonConfigs.remoteFilter1.remoteSensorDeviceID, testTalonConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs));

    errorCodes.push_back(testTalon.Config_kP(0, testTalonConfigs.slot0.kP, timeoutMs));
    errorCodes.push_back(testTalon.Config_kI(0, testTalonConfigs.slot0.kI, timeoutMs));
    errorCodes.push_back(testTalon.Config_kD(0, testTalonConfigs.slot0.kD, timeoutMs));
    errorCodes.push_back(testTalon.Config_kF(0, testTalonConfigs.slot0.kF, timeoutMs));
    errorCodes.push_back(testTalon.Config_IntegralZone(0, testTalonConfigs.slot0.integralZone, timeoutMs));
    errorCodes.push_back(testTalon.ConfigAllowableClosedloopError(0, testTalonConfigs.slot0.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testTalon.ConfigMaxIntegralAccumulator(0, testTalonConfigs.slot0.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeakOutput(0, testTalonConfigs.slot0.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeriod(0, testTalonConfigs.slot0.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testTalon.Config_kP(1, testTalonConfigs.slot1.kP, timeoutMs));
    errorCodes.push_back(testTalon.Config_kI(1, testTalonConfigs.slot1.kI, timeoutMs));
    errorCodes.push_back(testTalon.Config_kD(1, testTalonConfigs.slot1.kD, timeoutMs));
    errorCodes.push_back(testTalon.Config_kF(1, testTalonConfigs.slot1.kF, timeoutMs));
    errorCodes.push_back(testTalon.Config_IntegralZone(1, testTalonConfigs.slot1.integralZone, timeoutMs));
    errorCodes.push_back(testTalon.ConfigAllowableClosedloopError(1, testTalonConfigs.slot1.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testTalon.ConfigMaxIntegralAccumulator(1, testTalonConfigs.slot1.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeakOutput(1, testTalonConfigs.slot1.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeriod(1, testTalonConfigs.slot1.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testTalon.Config_kP(2, testTalonConfigs.slot2.kP, timeoutMs));
    errorCodes.push_back(testTalon.Config_kI(2, testTalonConfigs.slot2.kI, timeoutMs));
    errorCodes.push_back(testTalon.Config_kD(2, testTalonConfigs.slot2.kD, timeoutMs));
    errorCodes.push_back(testTalon.Config_kF(2, testTalonConfigs.slot2.kF, timeoutMs));
    errorCodes.push_back(testTalon.Config_IntegralZone(2, testTalonConfigs.slot2.integralZone, timeoutMs));
    errorCodes.push_back(testTalon.ConfigAllowableClosedloopError(2, testTalonConfigs.slot2.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testTalon.ConfigMaxIntegralAccumulator(2, testTalonConfigs.slot2.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeakOutput(2, testTalonConfigs.slot2.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeriod(2, testTalonConfigs.slot2.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testTalon.Config_kP(3, testTalonConfigs.slot3.kP, timeoutMs));
    errorCodes.push_back(testTalon.Config_kI(3, testTalonConfigs.slot3.kI, timeoutMs));
    errorCodes.push_back(testTalon.Config_kD(3, testTalonConfigs.slot3.kD, timeoutMs));
    errorCodes.push_back(testTalon.Config_kF(3, testTalonConfigs.slot3.kF, timeoutMs));
    errorCodes.push_back(testTalon.Config_IntegralZone(3, testTalonConfigs.slot3.integralZone, timeoutMs));
    errorCodes.push_back(testTalon.ConfigAllowableClosedloopError(3, testTalonConfigs.slot3.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testTalon.ConfigMaxIntegralAccumulator(3, testTalonConfigs.slot3.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeakOutput(3, testTalonConfigs.slot3.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testTalon.ConfigClosedLoopPeriod(3, testTalonConfigs.slot3.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testTalon.ConfigSelectedFeedbackCoefficient(testTalonConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs));
    errorCodes.push_back(testTalon.ConfigSelectedFeedbackSensor(testTalonConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs));
    errorCodes.push_back(testTalon.ConfigSelectedFeedbackCoefficient(testTalonConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs));
    errorCodes.push_back(testTalon.ConfigSelectedFeedbackSensor(testTalonConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs));

    errorCodes.push_back(testTalon.ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, testTalonConfigs.sum0Term, timeoutMs));
    errorCodes.push_back(testTalon.ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, testTalonConfigs.sum1Term, timeoutMs));
    errorCodes.push_back(testTalon.ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, testTalonConfigs.diff0Term, timeoutMs));
    errorCodes.push_back(testTalon.ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, testTalonConfigs.diff1Term, timeoutMs));
    
    //Unique to just Talon
    errorCodes.push_back(testTalon.ConfigForwardLimitSwitchSource(testTalonConfigs.forwardLimitSwitchSource, testTalonConfigs.forwardLimitSwitchNormal, timeoutMs));
    errorCodes.push_back(testTalon.ConfigReverseLimitSwitchSource(testTalonConfigs.reverseLimitSwitchSource, testTalonConfigs.reverseLimitSwitchNormal, timeoutMs));
    
    errorCodes.push_back(testTalon.ConfigPeakCurrentLimit(testTalonConfigs.peakCurrentLimit, timeoutMs));
    errorCodes.push_back(testTalon.ConfigPeakCurrentDuration(testTalonConfigs.peakCurrentDuration, timeoutMs));
    errorCodes.push_back(testTalon.ConfigContinuousCurrentLimit(testTalonConfigs.continuousCurrentLimit, timeoutMs));

    //VictorSPX
    errorCodes.push_back(testVictor.ConfigOpenloopRamp(testVictorConfigs.openloopRamp, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedloopRamp(testVictorConfigs.closedloopRamp, timeoutMs));
    errorCodes.push_back(testVictor.ConfigPeakOutputForward(testVictorConfigs.peakOutputForward, timeoutMs));
    errorCodes.push_back(testVictor.ConfigPeakOutputReverse(testVictorConfigs.peakOutputReverse, timeoutMs));
    errorCodes.push_back(testVictor.ConfigNominalOutputForward(testVictorConfigs.nominalOutputForward, timeoutMs));
    errorCodes.push_back(testVictor.ConfigNominalOutputReverse(testVictorConfigs.nominalOutputReverse, timeoutMs));
    errorCodes.push_back(testVictor.ConfigNeutralDeadband(testVictorConfigs.neutralDeadband, timeoutMs));
    errorCodes.push_back(testVictor.ConfigVoltageCompSaturation(testVictorConfigs.voltageCompSaturation, timeoutMs));
    errorCodes.push_back(testVictor.ConfigVoltageMeasurementFilter(testVictorConfigs.voltageMeasurementFilter, timeoutMs));
    errorCodes.push_back(testVictor.ConfigVelocityMeasurementPeriod(testVictorConfigs.velocityMeasurementPeriod, timeoutMs));
    errorCodes.push_back(testVictor.ConfigVelocityMeasurementWindow(testVictorConfigs.velocityMeasurementWindow, timeoutMs));
    errorCodes.push_back(testVictor.ConfigForwardSoftLimitThreshold(testVictorConfigs.forwardSoftLimitThreshold, timeoutMs));
    errorCodes.push_back(testVictor.ConfigReverseSoftLimitThreshold(testVictorConfigs.reverseSoftLimitThreshold, timeoutMs));
    errorCodes.push_back(testVictor.ConfigForwardSoftLimitEnable(testVictorConfigs.forwardSoftLimitEnable, timeoutMs));
    errorCodes.push_back(testVictor.ConfigReverseSoftLimitEnable(testVictorConfigs.reverseSoftLimitEnable, timeoutMs));
    errorCodes.push_back(testVictor.ConfigAuxPIDPolarity(testVictorConfigs.auxPIDPolarity, timeoutMs));
    errorCodes.push_back(testVictor.ConfigMotionCruiseVelocity(testVictorConfigs.motionCruiseVelocity, timeoutMs));
    errorCodes.push_back(testVictor.ConfigMotionAcceleration(testVictorConfigs.motionAcceleration, timeoutMs));
    errorCodes.push_back(testVictor.ConfigMotionProfileTrajectoryPeriod(testVictorConfigs.motionProfileTrajectoryPeriod, timeoutMs));
    errorCodes.push_back(testVictor.ConfigFeedbackNotContinuous(testVictorConfigs.feedbackNotContinuous, timeoutMs));
    errorCodes.push_back(testVictor.ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(testVictorConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClearPositionOnLimitF(testVictorConfigs.clearPositionOnLimitF, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClearPositionOnLimitR(testVictorConfigs.clearPositionOnLimitR, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClearPositionOnQuadIdx(testVictorConfigs.clearPositionOnQuadIdx, timeoutMs));
    errorCodes.push_back(testVictor.ConfigLimitSwitchDisableNeutralOnLOS(testVictorConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs));
    errorCodes.push_back(testVictor.ConfigSoftLimitDisableNeutralOnLOS(testVictorConfigs.softLimitDisableNeutralOnLOS, timeoutMs));
    errorCodes.push_back(testVictor.ConfigPulseWidthPeriod_EdgesPerRot(testVictorConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs));
    errorCodes.push_back(testVictor.ConfigPulseWidthPeriod_FilterWindowSz(testVictorConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs));
   
    errorCodes.push_back(testVictor.ConfigRemoteFeedbackFilter(testVictorConfigs.remoteFilter0.remoteSensorDeviceID, testVictorConfigs.remoteFilter0.remoteSensorSource, 0, timeoutMs));
    errorCodes.push_back(testVictor.ConfigRemoteFeedbackFilter(testVictorConfigs.remoteFilter1.remoteSensorDeviceID, testVictorConfigs.remoteFilter1.remoteSensorSource, 1, timeoutMs));

    errorCodes.push_back(testVictor.Config_kP(0, testVictorConfigs.slot0.kP, timeoutMs));
    errorCodes.push_back(testVictor.Config_kI(0, testVictorConfigs.slot0.kI, timeoutMs));
    errorCodes.push_back(testVictor.Config_kD(0, testVictorConfigs.slot0.kD, timeoutMs));
    errorCodes.push_back(testVictor.Config_kF(0, testVictorConfigs.slot0.kF, timeoutMs));
    errorCodes.push_back(testVictor.Config_IntegralZone(0, testVictorConfigs.slot0.integralZone, timeoutMs));
    errorCodes.push_back(testVictor.ConfigAllowableClosedloopError(0, testVictorConfigs.slot0.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testVictor.ConfigMaxIntegralAccumulator(0, testVictorConfigs.slot0.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeakOutput(0, testVictorConfigs.slot0.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeriod(0, testVictorConfigs.slot0.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testVictor.Config_kP(1, testVictorConfigs.slot1.kP, timeoutMs));
    errorCodes.push_back(testVictor.Config_kI(1, testVictorConfigs.slot1.kI, timeoutMs));
    errorCodes.push_back(testVictor.Config_kD(1, testVictorConfigs.slot1.kD, timeoutMs));
    errorCodes.push_back(testVictor.Config_kF(1, testVictorConfigs.slot1.kF, timeoutMs));
    errorCodes.push_back(testVictor.Config_IntegralZone(1, testVictorConfigs.slot1.integralZone, timeoutMs));
    errorCodes.push_back(testVictor.ConfigAllowableClosedloopError(1, testVictorConfigs.slot1.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testVictor.ConfigMaxIntegralAccumulator(1, testVictorConfigs.slot1.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeakOutput(1, testVictorConfigs.slot1.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeriod(1, testVictorConfigs.slot1.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testVictor.Config_kP(2, testVictorConfigs.slot2.kP, timeoutMs));
    errorCodes.push_back(testVictor.Config_kD(2, testVictorConfigs.slot2.kD, timeoutMs));
    errorCodes.push_back(testVictor.Config_kF(2, testVictorConfigs.slot2.kF, timeoutMs));
    errorCodes.push_back(testVictor.Config_IntegralZone(2, testVictorConfigs.slot2.integralZone, timeoutMs));
    errorCodes.push_back(testVictor.ConfigAllowableClosedloopError(2, testVictorConfigs.slot2.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testVictor.ConfigMaxIntegralAccumulator(2, testVictorConfigs.slot2.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeakOutput(2, testVictorConfigs.slot2.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeriod(2, testVictorConfigs.slot2.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testVictor.Config_kP(3, testVictorConfigs.slot3.kP, timeoutMs));
    errorCodes.push_back(testVictor.Config_kI(3, testVictorConfigs.slot3.kI, timeoutMs));
    errorCodes.push_back(testVictor.Config_kD(3, testVictorConfigs.slot3.kD, timeoutMs));
    errorCodes.push_back(testVictor.Config_kF(3, testVictorConfigs.slot3.kF, timeoutMs));
    errorCodes.push_back(testVictor.Config_IntegralZone(3, testVictorConfigs.slot3.integralZone, timeoutMs));
    errorCodes.push_back(testVictor.ConfigAllowableClosedloopError(3, testVictorConfigs.slot3.allowableClosedloopError, timeoutMs));
    errorCodes.push_back(testVictor.ConfigMaxIntegralAccumulator(3, testVictorConfigs.slot3.maxIntegralAccumulator, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeakOutput(3, testVictorConfigs.slot3.closedLoopPeakOutput, timeoutMs));
    errorCodes.push_back(testVictor.ConfigClosedLoopPeriod(3, testVictorConfigs.slot3.closedLoopPeriod, timeoutMs));

    errorCodes.push_back(testVictor.ConfigSelectedFeedbackCoefficient(testVictorConfigs.primaryPID.selectedFeedbackCoefficient, 0, timeoutMs));
    errorCodes.push_back(testVictor.ConfigSelectedFeedbackSensor(testVictorConfigs.primaryPID.selectedFeedbackSensor, 0, timeoutMs));
    errorCodes.push_back(testVictor.ConfigSelectedFeedbackCoefficient(testVictorConfigs.auxilaryPID.selectedFeedbackCoefficient, 1, timeoutMs));
    errorCodes.push_back(testVictor.ConfigSelectedFeedbackSensor(testVictorConfigs.auxilaryPID.selectedFeedbackSensor, 1, timeoutMs));
    
    errorCodes.push_back(testVictor.ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, testVictorConfigs.sum0Term, timeoutMs));
    errorCodes.push_back(testVictor.ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, testVictorConfigs.sum1Term, timeoutMs));
    errorCodes.push_back(testVictor.ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, testVictorConfigs.diff0Term, timeoutMs));
    errorCodes.push_back(testVictor.ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, testVictorConfigs.diff1Term, timeoutMs));
    
    //Unique to just Victor    
    errorCodes.push_back(testVictor.ConfigForwardLimitSwitchSource(testVictorConfigs.forwardLimitSwitchSource,
            testVictorConfigs.forwardLimitSwitchNormal, testVictorConfigs.forwardLimitSwitchDeviceID, timeoutMs));
    errorCodes.push_back(testVictor.ConfigReverseLimitSwitchSource(testVictorConfigs.reverseLimitSwitchSource,
            testVictorConfigs.reverseLimitSwitchNormal, testVictorConfigs.reverseLimitSwitchDeviceID, timeoutMs));
 
    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err);
    }
}
//TEST(ErrorTest, ConfigGetTimeoutError) {
//
//
//
//}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
