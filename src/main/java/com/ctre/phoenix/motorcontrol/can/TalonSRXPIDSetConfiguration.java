package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BasePIDSetConfiguration;

public class TalonSRXPIDSetConfiguration extends BasePIDSetConfiguration {
    public FeedbackDevice selectedFeedbackSensor;

    public TalonSRXPIDSetConfiguration() {
        selectedFeedbackSensor = FeedbackDevice.QuadEncoder;
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


