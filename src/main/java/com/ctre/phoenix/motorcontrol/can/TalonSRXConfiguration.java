package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.TalonSRXPIDSetConfiguration;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;

public class TalonSRXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {

    public TalonSRXPIDSetConfiguration primaryPID;
    public TalonSRXPIDSetConfiguration auxilaryPID;
    public LimitSwitchSource forwardLimitSwitchSource;
    public LimitSwitchSource reverseLimitSwitchSource;
    public FeedbackDevice sum_0;
    public FeedbackDevice sum_1;
    public FeedbackDevice diff_0;
    public FeedbackDevice diff_1;
    public int peakCurrentLimit;
    public int peakCurrentDuration;
    public int continuousCurrentLimit;

	public TalonSRXConfiguration() {
        primaryPID = new TalonSRXPIDSetConfiguration(); 
        auxilaryPID = new TalonSRXPIDSetConfiguration(); 

        forwardLimitSwitchSource = LimitSwitchSource.FeedbackConnector;
        reverseLimitSwitchSource = LimitSwitchSource.FeedbackConnector;
        sum_0 = FeedbackDevice.QuadEncoder;
        sum_1 = FeedbackDevice.QuadEncoder;
        diff_0 = FeedbackDevice.QuadEncoder;
        diff_1 = FeedbackDevice.QuadEncoder;
        peakCurrentLimit = 1;
        peakCurrentDuration = 1;
        continuousCurrentLimit = 1;
	}
    public String toString(String prependString) {


        String retstr = primaryPID.toString(prependString + ".primaryPID");
        retstr += auxilaryPID.toString(prependString + ".auxilaryPID");
        retstr += prependString + ".forwardLimitSwitchSource = " + forwardLimitSwitchSource.toString() + ";\n";
        retstr += prependString + ".reverseLimitSwitchSource = " + reverseLimitSwitchSource.toString() + ";\n";
        retstr += prependString + ".sum_0 = " + sum_0.toString() + ";\n";
        retstr += prependString + ".sum_1 = " + sum_1.toString() + ";\n";
        retstr += prependString + ".diff_0 = " + diff_0.toString() + ";\n";
        retstr += prependString + ".diff_1 = " + diff_1.toString() + ";\n";
        retstr += prependString + ".peakCurrentLimit = " + String.valueOf(peakCurrentLimit) + ";\n";
        retstr += prependString + ".peakCurrentDuration = " + String.valueOf(peakCurrentDuration) + ";\n";
        retstr += prependString + ".continuousCurrentLimit = " + String.valueOf(continuousCurrentLimit) + ";\n";
         retstr += super.toString(prependString);

       return retstr;
    }

}

