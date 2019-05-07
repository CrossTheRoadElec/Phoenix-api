package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.TalonSRXPIDSetConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;

/**
 * Configurables available to TalonSRX
 */
public class TalonSRXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {

    /**
     * Primary PID configuration
     */
    public TalonSRXPIDSetConfiguration primaryPID;
    /**
     * Auxiliary PID configuration
     */
    public TalonSRXPIDSetConfiguration auxiliaryPID;
    /**
     * Forward Limit Switch Source
     * 
     * User can choose between the feedback connector, remote Talon SRX, CANifier, or deactivate the feature
     */
    public LimitSwitchSource forwardLimitSwitchSource;
    /**
     * Reverse Limit Switch Source
     * 
     * User can choose between the feedback connector, remote Talon SRX, CANifier, or deactivate the feature
     */
    public LimitSwitchSource reverseLimitSwitchSource;
    /**
     * Forward limit switch device ID
     * 
     * Limit Switch device id isn't used unless device is a remote
     */
    public int forwardLimitSwitchDeviceID; 
    /**
     * Reverse limit switch device ID
     * 
     * Limit Switch device id isn't used unless device is a remote
     */
    public int reverseLimitSwitchDeviceID;
    /**
     * Forward limit switch normally open/closed
     */
    public LimitSwitchNormal forwardLimitSwitchNormal;
    /**
     * Reverse limit switch normally open/closed
     */
    public LimitSwitchNormal reverseLimitSwitchNormal;
    /**
     * Feedback Device for Sum 0 Term
     */
    public FeedbackDevice sum0Term;
    /**
     * Feedback Device for Sum 1 Term
     */
    public FeedbackDevice sum1Term;
    /**
     * Feedback Device for Diff 0 Term
     */
    public FeedbackDevice diff0Term;
    /**
     * Feedback Device for Diff 1 Term
     */
    public FeedbackDevice diff1Term;
    /**
     * Peak current in amps
     * 
	 * Current limit is activated when current exceeds the peak limit for longer
	 * than the peak duration. Then software will limit to the continuous limit.
	 * This ensures current limiting while allowing for momentary excess current
	 * events.
     */
    public int peakCurrentLimit;
    /**
     * Peak Current duration in milliseconds
     * 
	 * Current limit is activated when current exceeds the peak limit for longer
	 * than the peak duration. Then software will limit to the continuous limit.
	 * This ensures current limiting while allowing for momentary excess current
	 * events.
     */
    public int peakCurrentDuration;
    /**
     * Continuous current in amps
     * 
	 * Current limit is activated when current exceeds the peak limit for longer
	 * than the peak duration. Then software will limit to the continuous limit.
	 * This ensures current limiting while allowing for momentary excess current
	 * events.
     */
    public int continuousCurrentLimit;

	public TalonSRXConfiguration() {
        primaryPID = new TalonSRXPIDSetConfiguration(); 
        auxiliaryPID = new TalonSRXPIDSetConfiguration(); 

        forwardLimitSwitchSource = LimitSwitchSource.FeedbackConnector;
        reverseLimitSwitchSource = LimitSwitchSource.FeedbackConnector;
        forwardLimitSwitchDeviceID = 0;
        reverseLimitSwitchDeviceID = 0;
        forwardLimitSwitchNormal = LimitSwitchNormal.NormallyOpen;
        reverseLimitSwitchNormal = LimitSwitchNormal.NormallyOpen;
        sum0Term = FeedbackDevice.QuadEncoder;
        sum1Term = FeedbackDevice.QuadEncoder;
        diff0Term = FeedbackDevice.QuadEncoder;
        diff1Term = FeedbackDevice.QuadEncoder;
        peakCurrentLimit = 1;
        peakCurrentDuration = 1;
        continuousCurrentLimit = 1;
	}

    /**
     * @return String representation of all the configs
     */
	public String toString() {
		return toString("");
	}

    /**
     * @param prependString
     *              String to prepend to all the configs
     * @return String representation of all the configs
     */
    public String toString(String prependString) {


        String retstr = primaryPID.toString(prependString + ".primaryPID");
        retstr += auxiliaryPID.toString(prependString + ".auxiliaryPID");
        retstr += prependString + ".forwardLimitSwitchSource = " + forwardLimitSwitchSource.toString() + ";\n";
        retstr += prependString + ".reverseLimitSwitchSource = " + reverseLimitSwitchSource.toString() + ";\n";
        retstr += prependString + ".forwardLimitSwitchDeviceID = " + String.valueOf(forwardLimitSwitchDeviceID) + ";\n";
        retstr += prependString + ".reverseLimitSwitchDeviceID = " + String.valueOf(reverseLimitSwitchDeviceID) + ";\n";
        retstr += prependString + ".forwardLimitSwitchNormal = " + forwardLimitSwitchNormal.toString() + ";\n";
        retstr += prependString + ".reverseLimitSwitchNormal = " + reverseLimitSwitchNormal.toString() + ";\n";
        retstr += prependString + ".sum0Term = " + sum0Term.toString() + ";\n";
        retstr += prependString + ".sum1Term = " + sum1Term.toString() + ";\n";
        retstr += prependString + ".diff0Term = " + diff0Term.toString() + ";\n";
        retstr += prependString + ".diff1Term = " + diff1Term.toString() + ";\n";
        retstr += prependString + ".peakCurrentLimit = " + String.valueOf(peakCurrentLimit) + ";\n";
        retstr += prependString + ".peakCurrentDuration = " + String.valueOf(peakCurrentDuration) + ";\n";
        retstr += prependString + ".continuousCurrentLimit = " + String.valueOf(continuousCurrentLimit) + ";\n";
         retstr += super.toString(prependString);

       return retstr;
    }

}

