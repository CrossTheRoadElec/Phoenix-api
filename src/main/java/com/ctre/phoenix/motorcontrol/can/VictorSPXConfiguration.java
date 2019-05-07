package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.VictorSPXPIDSetConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.RemoteLimitSwitchSource;
import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;

/**
 * Configurables available to VictorSPX
 */
public class VictorSPXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {
    /**
     * Primary PID configuration
     */
	public VictorSPXPIDSetConfiguration primaryPID;
    /**
     * Auxiliary PID configuration
     */
    public VictorSPXPIDSetConfiguration auxiliaryPID;
    /**
     * Forward Limit Switch Source
     * 
     * User can choose between the feedback connector, remote Talon SRX, CANifier, or deactivate the feature
     */
    public RemoteLimitSwitchSource forwardLimitSwitchSource;
    /**
     * Reverse Limit Switch Source
     * 
     * User can choose between the feedback connector, remote Talon SRX, CANifier, or deactivate the feature
     */
    public RemoteLimitSwitchSource reverseLimitSwitchSource;
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
    public RemoteFeedbackDevice sum0Term;
    /**
     * Feedback Device for Sum 1 Term
     */
    public RemoteFeedbackDevice sum1Term;
    /**
     * Feedback Device for Diff 0 Term
     */
    public RemoteFeedbackDevice diff0Term;
    /**
     * Feedback Device for Diff 1 Term
     */
    public RemoteFeedbackDevice diff1Term;

	
	public VictorSPXConfiguration() {
        primaryPID = new  VictorSPXPIDSetConfiguration(); 
        auxiliaryPID = new VictorSPXPIDSetConfiguration(); 
        
        forwardLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;
        reverseLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;
        forwardLimitSwitchDeviceID = 0;
        reverseLimitSwitchDeviceID = 0;
        forwardLimitSwitchNormal = LimitSwitchNormal.NormallyOpen;
        reverseLimitSwitchNormal = LimitSwitchNormal.NormallyOpen;
        sum0Term =  RemoteFeedbackDevice.RemoteSensor0; 
        sum1Term =  RemoteFeedbackDevice.RemoteSensor0;
        diff0Term = RemoteFeedbackDevice.RemoteSensor0;
        diff1Term = RemoteFeedbackDevice.RemoteSensor0;
        //NOTE: while the factory default value is 0, this value can't 
        //be set by the API. Thus, RemoteSensor0 is the default

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
        retstr += super.toString(prependString);

        return retstr;
    }
}

