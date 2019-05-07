package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.RemoteSensorSource;

/**
 * Base set of configurables related to PID
 */
public class BasePIDSetConfiguration{
    /**
     *  Feedback coefficient of selected sensor
     */
    public double selectedFeedbackCoefficient;

	public BasePIDSetConfiguration() {
        selectedFeedbackCoefficient = 1.0;
	}

    /**
     * @return String representation of configs
     */
	public String toString() {
		return toString("");
	}

    /**
     * @param prependString
     *              String to prepend to configs
     * @return String representation of configs
     */
    public String toString(String prependString) {
        return prependString + ".selectedFeedbackCoefficient = " + String.valueOf(selectedFeedbackCoefficient) + ";\n";

    }

} // class BasePIDSetConfiguration
