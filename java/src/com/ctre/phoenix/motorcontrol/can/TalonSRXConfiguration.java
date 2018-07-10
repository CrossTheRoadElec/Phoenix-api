package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.TalonSRXPIDSetConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;

public class TalonSRXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {

    public TalonSRXPIDSetConfiguration primaryPID;
    public TalonSRXPIDSetConfiguration auxilaryPID;
    public LimitSwitchSource forwardLimitSwitchSource;
    public LimitSwitchSource reverseLimitSwitchSource;
    public int forwardLimitSwitchDeviceID; //Limit Switch device id isn't used unless device is a remote
    public int reverseLimitSwitchDeviceID;
    public LimitSwitchNormal forwardLimitSwitchNormal;
    public LimitSwitchNormal reverseLimitSwitchNormal;
    public FeedbackDevice sum0Term;
    public FeedbackDevice sum1Term;
    public FeedbackDevice diff0Term;
    public FeedbackDevice diff1Term;
    public int peakCurrentLimit;
    public int peakCurrentDuration;
    public int continuousCurrentLimit;

	public TalonSRXConfiguration() {
        primaryPID = new TalonSRXPIDSetConfiguration(); 
        auxilaryPID = new TalonSRXPIDSetConfiguration(); 

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
    public String toString(String prependString) {


        String retstr = primaryPID.toString(prependString + ".primaryPID");
        retstr += auxilaryPID.toString(prependString + ".auxilaryPID");
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

