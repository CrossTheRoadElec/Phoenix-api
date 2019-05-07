package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.BasePIDSetConfiguration;

/**
 * Configurables available to TalonSRX's PID
 */
public class TalonSRXPIDSetConfiguration extends BasePIDSetConfiguration {
    /**
     * Feedback device for a particular PID loop.
     */
    public FeedbackDevice selectedFeedbackSensor;

    public TalonSRXPIDSetConfiguration() {
        selectedFeedbackSensor = FeedbackDevice.QuadEncoder;
    }

    /**
     * @return string representation of configs
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

        String retstr = prependString + ".selectedFeedbackSensor = " + selectedFeedbackSensor.toString() + ";\n";
        retstr += super.toString(prependString);
        return retstr;
    }

}


