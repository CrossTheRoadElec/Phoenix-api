package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BaseSlotConfiguration;

public class VictorSPXSlotConfiguration extends BaseSlotConfiguration {
    public RemoteFeedbackDevice SelectedFeedbackSensor;

    public VictorSPXSlotConfiguration() {
        SelectedFeedbackSensor = RemoteFeedbackDevice.None;
    }

}

