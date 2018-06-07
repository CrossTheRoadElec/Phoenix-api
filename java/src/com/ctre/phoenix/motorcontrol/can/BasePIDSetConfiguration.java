package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.RemoteSensorSource;

public class BasePIDSetConfiguration{
    public double SelectedFeedbackCoefficient;
    public SensorTerm sensorTerm;

    //Remote feedback filter information isn't used unless the device is a remote
    public int RemoteFeedbackFilter;
    public int DeviceID;
    public RemoteSensorSource remoteSensorSource;
	public BasePIDSetConfiguration() {
        SelectedFeedbackCoefficient = 1.0;
        sensorTerm = SensorTerm.Sum0;
        RemoteFeedbackFilter = 0;
        DeviceID = 0;
        //remoteSensorSource = ; TODO fix
	}
} // class BasePIDSetConfiguration
