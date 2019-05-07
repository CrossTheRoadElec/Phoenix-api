package com.ctre.phoenix.motorcontrol.can;

/**
 * Util class to help with TalonSRX's PID configs
 */
public class TalonSRXPIDSetConfigUtil {
	private static TalonSRXPIDSetConfiguration _default = new TalonSRXPIDSetConfiguration();
	
	static boolean selectedFeedbackSensorDifferent (TalonSRXPIDSetConfiguration settings) { return (!(settings.selectedFeedbackSensor == _default.selectedFeedbackSensor)); }
	static boolean selectedFeedbackCoefficientDifferent (TalonSRXPIDSetConfiguration settings) { return (!(settings.selectedFeedbackCoefficient == _default.selectedFeedbackCoefficient)); }
}