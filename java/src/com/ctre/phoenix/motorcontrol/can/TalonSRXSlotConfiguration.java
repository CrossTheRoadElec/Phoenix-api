package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BaseSlotConfiguration;

public class TalonSRXSlotConfiguration extends BaseSlotConfiguration {
    public FeedbackDevice SelectedFeedbackSensor;

    public TalonSRXSlotConfiguration() {
        SelectedFeedbackSensor = FeedbackDevice.QuadEncoder;
    }
}


