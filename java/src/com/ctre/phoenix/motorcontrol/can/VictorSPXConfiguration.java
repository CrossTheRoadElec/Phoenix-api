package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.motorcontrol.can.VictorSPXPIDSetConfiguration;
import com.ctre.phoenix.motorcontrol.RemoteLimitSwitchSource;
import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;

public class VictorSPXConfiguration extends com.ctre.phoenix.motorcontrol.can.BaseMotorControllerConfiguration {
	public VictorSPXPIDSetConfiguration primaryPID;
    public VictorSPXPIDSetConfiguration auxilaryPID;
    public RemoteLimitSwitchSource forwardLimitSwitchSource;
    public RemoteLimitSwitchSource reverseLimitSwitchSource;
    public RemoteFeedbackDevice sum_0;
    public RemoteFeedbackDevice sum_1;
    public RemoteFeedbackDevice diff_0;
    public RemoteFeedbackDevice diff_1;

	
	public VictorSPXConfiguration() {
        primaryPID = new  VictorSPXPIDSetConfiguration(); 
        auxilaryPID = new VictorSPXPIDSetConfiguration(); 
        
        forwardLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;
        reverseLimitSwitchSource = RemoteLimitSwitchSource.Deactivated;
        sum_0 =  RemoteFeedbackDevice.RemoteSensor0; 
        sum_1 =  RemoteFeedbackDevice.RemoteSensor0;
        diff_0 = RemoteFeedbackDevice.RemoteSensor0;
        diff_1 = RemoteFeedbackDevice.RemoteSensor0;
        //NOTE: while the factory default value is 0, this value can't 
        //be set by the API. Thus, RemoteSensor0 is the default

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
        retstr += super.toString(prependString);

        return retstr;
    }


}

