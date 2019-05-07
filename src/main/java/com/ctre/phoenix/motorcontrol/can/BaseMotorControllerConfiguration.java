package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.can.SlotConfiguration;
import com.ctre.phoenix.motorcontrol.can.FilterConfiguration;

/**
 * Configurables available to base motor controllers
 */
public abstract class BaseMotorControllerConfiguration extends CustomParamConfiguration{
    /**
     * Seconds to go from 0 to full in open loop
     */
    public double openloopRamp;
    /**
     * Seconds to go from 0 to full in closed loop
     */
    public double closedloopRamp;
    /**
     * Peak output in forward direction [0,1]
     */
    public double peakOutputForward;
    /**
     * Peak output in reverse direction [-1,0]
     */
    public double peakOutputReverse;
    /**
     * Nominal/Minimum output in forward direction [0,1]
     */
    public double nominalOutputForward;
    /**
     * Nominal/Minimum output in reverse direction [-1,0]
     */
    public double nominalOutputReverse;
    /**
     * Neutral deadband [0.001, 0.25]
     */
    public double neutralDeadband;
    /**
	 * This is the max voltage to apply to the hbridge when voltage
	 * compensation is enabled.  For example, if 10 (volts) is specified
	 * and a TalonSRX is commanded to 0.5 (PercentOutput, closed-loop, etc)
	 * then the TalonSRX will attempt to apply a duty-cycle to produce 5V.
     */
    public double voltageCompSaturation;
    /**
     * Number of samples in rolling average for voltage
     */
    public int voltageMeasurementFilter;
    /**
     * Desired period for velocity measurement
     */
    public VelocityMeasPeriod velocityMeasurementPeriod;
    /**
     * Desired window for velocity measurement
     */
    public int velocityMeasurementWindow;
    /**
     * Threshold for soft limits in forward direction (in raw sensor units)
     */
    public int forwardSoftLimitThreshold;
    /**
     * Threshold for soft limits in reverse direction (in raw sensor units)
     */
    public int reverseSoftLimitThreshold;
    /**
     * Enable forward soft limit
     */
    public boolean forwardSoftLimitEnable;
    /**
     * Enable reverse soft limit
     */
    public boolean reverseSoftLimitEnable;
    /**
     * Configuration for slot 0
     */
    public SlotConfiguration slot0;
    /**
     * Configuration for slot 1
     */
    public SlotConfiguration slot1;
    /**
     * Configuration for slot 2
     */
    public SlotConfiguration slot2;
    /**
     * Configuration for slot 3
     */
    public SlotConfiguration slot3;
    /**
     * PID polarity inversion
     * 
	 * Standard Polarity:
	 *    Primary Output = PID0 + PID1,
	 *    Auxiliary Output = PID0 - PID1,
	 *
	 * Inverted Polarity:
	 *    Primary Output = PID0 - PID1,
	 *    Auxiliary Output = PID0 + PID1,
     */
    public boolean auxPIDPolarity;
    /**
     * Configuration for RemoteFilter 0
     */
    public FilterConfiguration remoteFilter0;
    /**
     * Configuration for RemoteFilter 1
     */
    public FilterConfiguration remoteFilter1;
    /**
     * Motion Magic cruise velocity in raw sensor units per 100 ms.
     */
    public int motionCruiseVelocity;
    /**
     * Motion Magic acceleration in (raw sensor units per 100 ms) per second.
     */
    public int motionAcceleration;
    /**
	 * Zero to use trapezoidal motion during motion magic.  [1,8] for S-Curve, higher value for greater smoothing.
	 */
	public int motionCurveStrength;
    /**
     * Motion profile base trajectory period in milliseconds.
     * 
     * The period specified in a trajectory point will be
     * added on to this value
     */
    public int motionProfileTrajectoryPeriod;
    /**
     * Determine whether feedback sensor is continuous or not
     */
    public boolean feedbackNotContinuous;
    /**
     * Disable neutral'ing the motor when remote sensor is lost on CAN bus
     */
    public boolean remoteSensorClosedLoopDisableNeutralOnLOS;
    /**
     * Clear the position on forward limit
     */
    public boolean clearPositionOnLimitF;
    /**
     * Clear the position on reverse limit
     */
    public boolean clearPositionOnLimitR;
    /**
     * Clear the position on index
     */
    public boolean clearPositionOnQuadIdx;
    /**
     * Disable neutral'ing the motor when remote limit switch is lost on CAN bus
     */
    public boolean limitSwitchDisableNeutralOnLOS;
    /**
     * Disable neutral'ing the motor when remote soft limit is lost on CAN bus
     */
    public boolean softLimitDisableNeutralOnLOS;
    /**
     * Number of edges per rotation for a tachometer sensor
     */
    public int pulseWidthPeriod_EdgesPerRot;
    /**
     * Desired window size for a tachometer sensor
     */
    public int pulseWidthPeriod_FilterWindowSz;
    /**
     * Enable motion profile trajectory point interpolation (defaults to true).
     */
    public boolean trajectoryInterpolationEnable;

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
        motionCurveStrength = 0;
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
        trajectoryInterpolationEnable = true;


	}

    /**
     * @return String representation of configs
     */
	public String toString() {
		return toString("");
	}

    /**
     * @param prependString
     *              String to prepend to configs
     * @return String representation of configs
     */
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
        retstr += prependString + ".motionCurveStrength = " + String.valueOf(motionCurveStrength) + ";\n";
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
        retstr += prependString + ".trajectoryInterpolationEnable = " + String.valueOf(trajectoryInterpolationEnable) + ";\n";

        retstr += super.toString(prependString);

        return retstr;
    }


		
}
