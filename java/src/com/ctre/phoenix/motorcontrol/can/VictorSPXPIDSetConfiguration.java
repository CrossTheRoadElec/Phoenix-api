package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BasePIDSetConfiguration;

public class VictorSPXPIDSetConfiguration extends BasePIDSetConfiguration {
    public RemoteFeedbackDevice SelectedFeedbackSensor;

    public VictorSPXPIDSetConfiguration() {
        SelectedFeedbackSensor = RemoteFeedbackDevice.None;
    }

}

