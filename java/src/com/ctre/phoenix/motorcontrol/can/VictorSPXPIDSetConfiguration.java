package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BasePIDSetConfiguration;

public class VictorSPXPIDSetConfiguration extends BasePIDSetConfiguration {
    public RemoteFeedbackDevice selectedFeedbackSensor;

    public VictorSPXPIDSetConfiguration() {
        selectedFeedbackSensor = RemoteFeedbackDevice.None;
    }
    public String toString(String prependString) {

        String retstr = prependString + ".selectedFeedbackSensor = " + selectedFeedbackSensor.toString() + ";\n";
        retstr += super.toString(prependString);
        return retstr;
    }


}

