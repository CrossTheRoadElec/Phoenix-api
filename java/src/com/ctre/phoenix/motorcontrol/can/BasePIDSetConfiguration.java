package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.RemoteSensorSource;

public class BasePIDSetConfiguration{
    public double selectedFeedbackCoefficient;

	public BasePIDSetConfiguration() {
        selectedFeedbackCoefficient = 1.0;
	}

	public String toString() {
		return toString("");
	}

    public String toString(String prependString) {
        return prependString + ".selectedFeedbackCoefficient = " + String.valueOf(selectedFeedbackCoefficient) + ";\n";

    }

} // class BasePIDSetConfiguration
