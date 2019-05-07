package com.ctre.phoenix.motorcontrol.can;

/**
 * Util class to help with VictorSPX configs
 */
class VictorConfigUtil {
	private static VictorSPXConfiguration _default = new VictorSPXConfiguration();
	
	static boolean forwardLimitSwitchSourceDifferent (VictorSPXConfiguration settings) { return (!(settings.forwardLimitSwitchSource == _default.forwardLimitSwitchSource)) || !settings.enableOptimizations; }
	static boolean reverseLimitSwitchSourceDifferent (VictorSPXConfiguration settings) { return (!(settings.reverseLimitSwitchSource == _default.reverseLimitSwitchSource)) || !settings.enableOptimizations; }
	static boolean forwardLimitSwitchDeviceIDDifferent (VictorSPXConfiguration settings) { return (!(settings.forwardLimitSwitchDeviceID == _default.forwardLimitSwitchDeviceID)) || !settings.enableOptimizations; }
	static boolean reverseLimitSwitchDeviceIDDifferent (VictorSPXConfiguration settings) { return (!(settings.reverseLimitSwitchDeviceID == _default.reverseLimitSwitchDeviceID)) || !settings.enableOptimizations; }
	static boolean forwardLimitSwitchNormalDifferent (VictorSPXConfiguration settings) { return (!(settings.forwardLimitSwitchNormal == _default.forwardLimitSwitchNormal)) || !settings.enableOptimizations; }
	static boolean reverseLimitSwitchNormalDifferent (VictorSPXConfiguration settings) { return (!(settings.reverseLimitSwitchNormal == _default.reverseLimitSwitchNormal)) || !settings.enableOptimizations; }
	static boolean sum0TermDifferent (VictorSPXConfiguration settings) { return (!(settings.sum0Term == _default.sum0Term)) || !settings.enableOptimizations; }
	static boolean sum1TermDifferent (VictorSPXConfiguration settings) { return (!(settings.sum1Term == _default.sum1Term)) || !settings.enableOptimizations; }
	static boolean diff0TermDifferent (VictorSPXConfiguration settings) { return (!(settings.diff0Term == _default.diff0Term)) || !settings.enableOptimizations; }
	static boolean diff1TermDifferent (VictorSPXConfiguration settings) { return (!(settings.diff1Term == _default.diff1Term)) || !settings.enableOptimizations; }
	
	static boolean forwardLimitSwitchDifferent (VictorSPXConfiguration settings) {
		return forwardLimitSwitchDeviceIDDifferent(settings) || forwardLimitSwitchNormalDifferent(settings) || forwardLimitSwitchSourceDifferent(settings);
	}
	static boolean reverseLimitSwitchDifferent (VictorSPXConfiguration settings) {
		return reverseLimitSwitchDeviceIDDifferent(settings) || reverseLimitSwitchNormalDifferent(settings) || reverseLimitSwitchSourceDifferent(settings);
	}
}