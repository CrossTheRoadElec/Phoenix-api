package com.ctre.phoenix.motorcontrol.can;

/**
 * Util class to help with VictorSPX's PID configs
 */
public class VictorSPXPIDSetConfigUtil {
	private static VictorSPXPIDSetConfiguration _default = new VictorSPXPIDSetConfiguration();
	
	static boolean selectedFeedbackSensorDifferent (VictorSPXPIDSetConfiguration settings) { return (!(settings.selectedFeedbackSensor == _default.selectedFeedbackSensor)); }
	static boolean selectedFeedbackCoefficientDifferent (VictorSPXPIDSetConfiguration settings) { return (!(settings.selectedFeedbackCoefficient == _default.selectedFeedbackCoefficient)); }
}