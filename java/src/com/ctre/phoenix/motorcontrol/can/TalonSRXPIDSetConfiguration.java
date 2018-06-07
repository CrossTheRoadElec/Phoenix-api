package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BasePIDSetConfiguration;

public class TalonSRXPIDSetConfiguration extends BasePIDSetConfiguration {
    public FeedbackDevice SelectedFeedbackSensor;

    public TalonSRXPIDSetConfiguration() {
        SelectedFeedbackSensor = FeedbackDevice.QuadEncoder;
    }
}


