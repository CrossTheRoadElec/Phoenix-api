package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BasePIDSetConfiguration;

public class VictorSPXPIDSetConfiguration extends BasePIDSetConfiguration {
    public RemoteFeedbackDevice selectedFeedbackSensor;

    public VictorSPXPIDSetConfiguration() {
        selectedFeedbackSensor = RemoteFeedbackDevice.RemoteSensor0; 
        //NOTE: while the factory default value is 0, this value can't 
        //be set by the API. Thus, RemoteSensor0 is the default
    }

	public String toString() {
		return toString("");
	}

    public String toString(String prependString) {

        String retstr = prependString + ".selectedFeedbackSensor = " + selectedFeedbackSensor.toString() + ";\n";
        retstr += super.toString(prependString);
        return retstr;
    }


}

