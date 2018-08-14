package com.ctre.phoenix.motorcontrol.can;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.motorcontrol.can.MotControllerJNI;
import com.ctre.phoenix.motion.TrajectoryPoint;

import org.junit.jupiter.api.Test;

//This is the place for any test which are talon or victor specific (such as jni link testing)

class MotControllerTest {
    

    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() {
        int [] array9i = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int [] array11i = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            
	    long handle = MotControllerJNI.Create(0);
        MotControllerJNI.GetDeviceNumber(handle); 
	    MotControllerJNI.SetDemand(handle, 0, 0, 0);
	    MotControllerJNI.Set_4(handle, 0, 0, 0, 0);
	    MotControllerJNI.SetNeutralMode(handle, 0);
	    MotControllerJNI.SetSensorPhase(handle, false);
	    MotControllerJNI.SetInverted(handle, false);
	    MotControllerJNI.ConfigFactoryDefault(handle, 0);
	    MotControllerJNI.ConfigOpenLoopRamp(handle, 0, 0);
	    MotControllerJNI.ConfigClosedLoopRamp(handle, 0, 0);
	    MotControllerJNI.ConfigPeakOutputForward(handle, 0, 0);
	    MotControllerJNI.ConfigPeakOutputReverse(handle, 0, 0);
	    MotControllerJNI.ConfigNominalOutputForward(handle, 0, 0);
	    MotControllerJNI.ConfigNominalOutputReverse(handle, 0, 0);
	    MotControllerJNI.ConfigNeutralDeadband(handle, 0, 0);
	    MotControllerJNI.ConfigVoltageCompSaturation(handle, 0, 0);
	    MotControllerJNI.ConfigVoltageMeasurementFilter(handle, 0, 0);
	    MotControllerJNI.EnableVoltageCompensation(handle, false);
	    MotControllerJNI.GetBusVoltage(handle);
	    MotControllerJNI.GetMotorOutputPercent(handle);
	    MotControllerJNI.GetOutputCurrent(handle);
	    MotControllerJNI.GetTemperature(handle);
	    MotControllerJNI.ConfigRemoteFeedbackFilter(handle, 0, 0, 0, 0);
	    MotControllerJNI.ConfigSelectedFeedbackSensor(handle, 0, 0, 0);
	    MotControllerJNI.ConfigSensorTerm(handle, 0, 0, 0);
	    MotControllerJNI.GetSelectedSensorPosition(handle, 0);
	    MotControllerJNI.GetSelectedSensorVelocity(handle, 0);
	    MotControllerJNI.SetSelectedSensorPosition(handle, 0, 0, 0);
	    MotControllerJNI.SetControlFramePeriod(handle, 0, 0);
	    MotControllerJNI.SetStatusFramePeriod(handle, 0, 0, 0);
	    MotControllerJNI.GetStatusFramePeriod(handle, 0, 0);
	    MotControllerJNI.ConfigVelocityMeasurementPeriod(handle, 0, 0);
	    MotControllerJNI.ConfigVelocityMeasurementWindow(handle, 0, 0);
	    MotControllerJNI.ConfigForwardLimitSwitchSource(handle, 0, 0, 0, 0);
	    MotControllerJNI.ConfigReverseLimitSwitchSource(handle, 0, 0, 0, 0);
	    MotControllerJNI.OverrideLimitSwitchesEnable(handle, false);
	    MotControllerJNI.ConfigForwardSoftLimitThreshold(handle, 0, 0);
	    MotControllerJNI.ConfigReverseSoftLimitThreshold(handle, 0, 0);
	    MotControllerJNI.ConfigForwardSoftLimitEnable(handle, false, 0);
	    MotControllerJNI.ConfigReverseSoftLimitEnable(handle, false, 0);
	    MotControllerJNI.OverrideSoftLimitsEnable(handle, false);
	    MotControllerJNI.Config_kP(handle, 0, 0, 0);
	    MotControllerJNI.Config_kI(handle, 0, 0, 0);
	    MotControllerJNI.Config_kD(handle, 0, 0, 0);
	    MotControllerJNI.Config_kF(handle, 0, 0, 0);
	    MotControllerJNI.Config_IntegralZone(handle, 0, 0, 0);
	    MotControllerJNI.ConfigAllowableClosedloopError(handle, 0, 0, 0);
	    MotControllerJNI.ConfigMaxIntegralAccumulator(handle, 0, 0, 0);
	    MotControllerJNI.SetIntegralAccumulator(handle, 0, 0, 0);
	    MotControllerJNI.GetClosedLoopError(handle, 0);
	    MotControllerJNI.GetIntegralAccumulator(handle, 0);
	    MotControllerJNI.GetErrorDerivative(handle, 0);
	    MotControllerJNI.SelectProfileSlot(handle, 0, 0);
	    MotControllerJNI.GetActiveTrajectoryPosition(handle);
	    MotControllerJNI.GetActiveTrajectoryVelocity(handle);
	    MotControllerJNI.GetActiveTrajectoryHeading(handle);
	    MotControllerJNI.ConfigMotionCruiseVelocity(handle, 0, 0);
	    MotControllerJNI.ConfigMotionAcceleration(handle, 0, 0);
	    MotControllerJNI.ClearMotionProfileTrajectories(handle);
	    MotControllerJNI.GetMotionProfileTopLevelBufferCount(handle);
	    MotControllerJNI.PushMotionProfileTrajectory(handle, 0, 0, 0, 0, false, false);
	    MotControllerJNI.PushMotionProfileTrajectory2(handle, 0, 0, 0, 0, 0, false, false, 0);
	    MotControllerJNI.IsMotionProfileTopLevelBufferFull(handle);
	    MotControllerJNI.ProcessMotionProfileBuffer(handle);
	    MotControllerJNI.GetMotionProfileStatus(handle, array9i);
	    MotControllerJNI.GetMotionProfileStatus2(handle, array11i);
	    MotControllerJNI.ClearMotionProfileHasUnderrun(handle, 0);
	    MotControllerJNI.ChangeMotionControlFramePeriod(handle, 0);
	    MotControllerJNI.ConfigMotionProfileTrajectoryPeriod(handle, 0, 0);
        MotControllerJNI.ConfigFeedbackNotContinuous(handle, false, 0);
        MotControllerJNI.ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(handle, false, 0);
        MotControllerJNI.ConfigClearPositionOnLimitF(handle, false, 0);
        MotControllerJNI.ConfigClearPositionOnLimitR(handle, false, 0);
        MotControllerJNI.ConfigClearPositionOnQuadIdx(handle, false, 0);
        MotControllerJNI.ConfigLimitSwitchDisableNeutralOnLOS(handle, false, 0);
        MotControllerJNI.ConfigSoftLimitDisableNeutralOnLOS(handle, false, 0);
        MotControllerJNI.ConfigPulseWidthPeriod_EdgesPerRot(handle, 0, 0);
        MotControllerJNI.ConfigPulseWidthPeriod_FilterWindowSz(handle, 0, 0);
	    MotControllerJNI.GetLastError(handle);
	    MotControllerJNI.GetFirmwareVersion(handle);
	    MotControllerJNI.HasResetOccurred(handle);
	    MotControllerJNI.ConfigSetCustomParam(handle, 0, 0, 0);
	    MotControllerJNI.ConfigGetCustomParam(handle, 0, 0);
	    MotControllerJNI.ConfigSetParameter(handle, 0, 0, 0, 0, 0);
	    MotControllerJNI.ConfigGetParameter(handle, 0, 0, 0);
	    MotControllerJNI.ConfigPeakCurrentLimit(handle, 0, 0);
	    MotControllerJNI.ConfigPeakCurrentDuration(handle, 0, 0);
	    MotControllerJNI.ConfigContinuousCurrentLimit(handle, 0, 0);
	    MotControllerJNI.EnableCurrentLimit(handle, false);
	    MotControllerJNI.GetAnalogIn(handle);
	    MotControllerJNI.SetAnalogPosition(handle, 0, 0);
	    MotControllerJNI.GetAnalogInRaw(handle);
	    MotControllerJNI.GetAnalogInVel(handle);
	    MotControllerJNI.GetQuadraturePosition(handle);
	    MotControllerJNI.SetQuadraturePosition(handle, 0, 0);
	    MotControllerJNI.GetQuadratureVelocity(handle);
	    MotControllerJNI.GetPulseWidthPosition(handle);
	    MotControllerJNI.SetPulseWidthPosition(handle, 0, 0);
	    MotControllerJNI.GetPulseWidthVelocity(handle);
	    MotControllerJNI.GetPulseWidthRiseToFallUs(handle);
	    MotControllerJNI.GetPulseWidthRiseToRiseUs(handle);
	    MotControllerJNI.GetPinStateQuadA(handle);
	    MotControllerJNI.GetPinStateQuadB(handle);
	    MotControllerJNI.GetPinStateQuadIdx(handle);
	    MotControllerJNI.IsFwdLimitSwitchClosed(handle);
	    MotControllerJNI.IsRevLimitSwitchClosed(handle);
	    MotControllerJNI.GetFaults(handle);
	    MotControllerJNI.GetStickyFaults(handle);
	    MotControllerJNI.ClearStickyFaults(handle, 0);
	    MotControllerJNI.SelectDemandType(handle, 0);
	    MotControllerJNI.SetMPEOutput(handle, 0);
	    MotControllerJNI.EnableHeadingHold(handle, 0);
	    MotControllerJNI.GetClosedLoopTarget(handle, 0);
	    MotControllerJNI.ConfigSelectedFeedbackCoefficient(handle, 0, 0, 0);
	    MotControllerJNI.ConfigClosedLoopPeakOutput(handle, 0, 0, 0);
	    MotControllerJNI.ConfigClosedLoopPeriod(handle, 0, 0, 0);
    }
    
    @Test
    void pushMotionProfileTrajectoryNullPointerCheck () {
        TrajectoryPoint emptyPoint = new TrajectoryPoint();
        TalonSRX testMotController = new TalonSRX(0);
        testMotController.pushMotionProfileTrajectory(emptyPoint);       
    }
    
}
