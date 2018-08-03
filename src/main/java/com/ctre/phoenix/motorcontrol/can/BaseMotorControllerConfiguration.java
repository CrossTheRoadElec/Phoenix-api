package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.can.SlotConfiguration;
import com.ctre.phoenix.motorcontrol.can.FilterConfiguration;

public abstract class BaseMotorControllerConfiguration extends CustomParamConfiguration{
    public double openloopRamp;
    public double closedloopRamp;
    public double peakOutputForward;
    public double peakOutputReverse;
    public double nominalOutputForward;
    public double nominalOutputReverse;
    public double neutralDeadband;
    public double voltageCompSaturation;
    public int voltageMeasurementFilter;
    public VelocityMeasPeriod velocityMeasurementPeriod;
    public int velocityMeasurementWindow;
    public int forwardSoftLimitThreshold;
    public int reverseSoftLimitThreshold;
    public boolean forwardSoftLimitEnable;
    public boolean reverseSoftLimitEnable;
    public SlotConfiguration slot0;
    public SlotConfiguration slot1;
    public SlotConfiguration slot2;
    public SlotConfiguration slot3;
    public boolean auxPIDPolarity;
    public FilterConfiguration remoteFilter0;
    public FilterConfiguration remoteFilter1;
    public int motionCruiseVelocity;
    public int motionAcceleration;
    public int motionProfileTrajectoryPeriod;
    public boolean feedbackNotContinuous;
    public boolean remoteSensorClosedLoopDisableNeutralOnLOS;
    public boolean clearPositionOnLimitF;
    public boolean clearPositionOnLimitR;
    public boolean clearPositionOnQuadIdx;
    public boolean limitSwitchDisableNeutralOnLOS;
    public boolean softLimitDisableNeutralOnLOS;
    public int pulseWidthPeriod_EdgesPerRot;
    public int pulseWidthPeriod_FilterWindowSz;


	public BaseMotorControllerConfiguration() { 
        slot0 = new SlotConfiguration();
        slot1 = new SlotConfiguration();
        slot2 = new SlotConfiguration();
        slot3 = new SlotConfiguration();

        remoteFilter0 = new FilterConfiguration();
        remoteFilter1 = new FilterConfiguration();

        openloopRamp = 0.0;
        closedloopRamp = 0.0;
        peakOutputForward = 1.0;
        peakOutputReverse = -1.0;
        nominalOutputForward = 0.0;
        nominalOutputReverse = 0.0;
        neutralDeadband = 0.04;
        voltageCompSaturation = 0.0;
        voltageMeasurementFilter = 32;
        velocityMeasurementPeriod = VelocityMeasPeriod.Period_100Ms;
        velocityMeasurementWindow = 64;
        forwardSoftLimitThreshold = 0;
        reverseSoftLimitThreshold = 0;
        forwardSoftLimitEnable = false;
        reverseSoftLimitEnable = false;
        auxPIDPolarity = false;
        motionCruiseVelocity = 0;
        motionAcceleration = 0;
        motionProfileTrajectoryPeriod = 0;
        feedbackNotContinuous = false;
        remoteSensorClosedLoopDisableNeutralOnLOS = false;
        clearPositionOnLimitF = false;
        clearPositionOnLimitR = false;
        clearPositionOnQuadIdx = false;
        limitSwitchDisableNeutralOnLOS = false;
        softLimitDisableNeutralOnLOS = false;
        pulseWidthPeriod_EdgesPerRot = 1;
        pulseWidthPeriod_FilterWindowSz = 1;


	}

	public String toString() {
		return toString("");
	}

    public String toString(String prependString) {

        String retstr = prependString + ".openloopRamp = " + String.valueOf(openloopRamp) + ";\n";
        retstr += prependString + ".closedloopRamp = " + String.valueOf(closedloopRamp) + ";\n";
        retstr += prependString + ".peakOutputForward = " + String.valueOf(peakOutputForward) + ";\n";
        retstr += prependString + ".peakOutputReverse = " + String.valueOf(peakOutputReverse) + ";\n";
        retstr += prependString + ".nominalOutputForward = " + String.valueOf(nominalOutputForward) + ";\n";
        retstr += prependString + ".nominalOutputReverse = " + String.valueOf(nominalOutputReverse) + ";\n";
        retstr += prependString + ".neutralDeadband = " + String.valueOf(neutralDeadband) + ";\n";
        retstr += prependString + ".voltageCompSaturation = " + String.valueOf(voltageCompSaturation) + ";\n";
        retstr += prependString + ".voltageMeasurementFilter = " + String.valueOf(voltageMeasurementFilter) + ";\n";
        retstr += prependString + ".velocityMeasurementPeriod = " + velocityMeasurementPeriod.toString() + ";\n";
        retstr += prependString + ".velocityMeasurementWindow = " + String.valueOf(velocityMeasurementWindow) + ";\n";
        retstr += prependString + ".forwardSoftLimitThreshold = " + String.valueOf(forwardSoftLimitThreshold) + ";\n";
        retstr += prependString + ".reverseSoftLimitThreshold = " + String.valueOf(reverseSoftLimitThreshold) + ";\n";
        retstr += prependString + ".forwardSoftLimitEnable = " + String.valueOf(forwardSoftLimitEnable) + ";\n";
        retstr += prependString + ".reverseSoftLimitEnable = " + String.valueOf(reverseSoftLimitEnable) + ";\n";
        retstr += slot0.toString(prependString + ".slot0");
        retstr += slot1.toString(prependString + ".slot1");
        retstr += slot2.toString(prependString + ".slot2");
        retstr += slot3.toString(prependString + ".slot3");
        retstr += prependString + ".auxPIDPolarity = " + String.valueOf(auxPIDPolarity) + ";\n";
        retstr += remoteFilter0.toString(prependString + ".filter0");
        retstr += remoteFilter1.toString(prependString + ".filter1");
        retstr += prependString + ".motionCruiseVelocity = " + String.valueOf(motionCruiseVelocity) + ";\n";
        retstr += prependString + ".motionAcceleration = " + String.valueOf(motionAcceleration) + ";\n";
        retstr += prependString + ".motionProfileTrajectoryPeriod = " + String.valueOf(motionProfileTrajectoryPeriod) + ";\n";
        retstr += prependString + ".feedbackNotContinuous = " + String.valueOf(feedbackNotContinuous) + ";\n";
        retstr += prependString + ".remoteSensorClosedLoopDisableNeutralOnLOS = " + String.valueOf(remoteSensorClosedLoopDisableNeutralOnLOS) + ";\n";
        retstr += prependString + ".clearPositionOnLimitF = " + String.valueOf(clearPositionOnLimitF) + ";\n";
        retstr += prependString + ".clearPositionOnLimitR = " + String.valueOf(clearPositionOnLimitR) + ";\n";
        retstr += prependString + ".clearPositionOnQuadIdx = " + String.valueOf(clearPositionOnQuadIdx) + ";\n";
        retstr += prependString + ".limitSwitchDisableNeutralOnLOS = " + String.valueOf(limitSwitchDisableNeutralOnLOS) + ";\n";
        retstr += prependString + ".softLimitDisableNeutralOnLOS = " + String.valueOf(softLimitDisableNeutralOnLOS) + ";\n";
        retstr += prependString + ".pulseWidthPeriod_EdgesPerRot = " + String.valueOf(pulseWidthPeriod_EdgesPerRot) + ";\n";
        retstr += prependString + ".pulseWidthPeriod_FilterWindowSz = " + String.valueOf(pulseWidthPeriod_FilterWindowSz) + ";\n";

        retstr += super.toString(prependString);

        return retstr;
    }


		
}
