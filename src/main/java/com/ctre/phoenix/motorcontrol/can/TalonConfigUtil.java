package com.ctre.phoenix.motorcontrol.can;

/**
 * Util class to help with talon configs
 */
class TalonConfigUtil {
	private static TalonSRXConfiguration _default = new TalonSRXConfiguration();
	
	static boolean forwardLimitSwitchSourceDifferent (TalonSRXConfiguration settings) { return (!(settings.forwardLimitSwitchSource == _default.forwardLimitSwitchSource)) || !settings.enableOptimizations; }
	static boolean reverseLimitSwitchSourceDifferent (TalonSRXConfiguration settings) { return (!(settings.reverseLimitSwitchSource == _default.reverseLimitSwitchSource)) || !settings.enableOptimizations; }
	static boolean forwardLimitSwitchDeviceIDDifferent (TalonSRXConfiguration settings) { return (!(settings.forwardLimitSwitchDeviceID == _default.forwardLimitSwitchDeviceID)) || !settings.enableOptimizations; }
	static boolean reverseLimitSwitchDeviceIDDifferent (TalonSRXConfiguration settings) { return (!(settings.reverseLimitSwitchDeviceID == _default.reverseLimitSwitchDeviceID)) || !settings.enableOptimizations; }
	static boolean forwardLimitSwitchNormalDifferent (TalonSRXConfiguration settings) { return (!(settings.forwardLimitSwitchNormal == _default.forwardLimitSwitchNormal)) || !settings.enableOptimizations; }
	static boolean reverseLimitSwitchNormalDifferent (TalonSRXConfiguration settings) { return (!(settings.reverseLimitSwitchNormal == _default.reverseLimitSwitchNormal)) || !settings.enableOptimizations; }
	static boolean sum0TermDifferent (TalonSRXConfiguration settings) { return (!(settings.sum0Term == _default.sum0Term)) || !settings.enableOptimizations; }
	static boolean sum1TermDifferent (TalonSRXConfiguration settings) { return (!(settings.sum1Term == _default.sum1Term)) || !settings.enableOptimizations; }
	static boolean diff0TermDifferent (TalonSRXConfiguration settings) { return (!(settings.diff0Term == _default.diff0Term)) || !settings.enableOptimizations; }
	static boolean diff1TermDifferent (TalonSRXConfiguration settings) { return (!(settings.diff1Term == _default.diff1Term)) || !settings.enableOptimizations; }
	static boolean peakCurrentLimitDifferent (TalonSRXConfiguration settings) { return (!(settings.peakCurrentLimit == _default.peakCurrentLimit)) || !settings.enableOptimizations; }
	static boolean peakCurrentDurationDifferent (TalonSRXConfiguration settings) { return (!(settings.peakCurrentDuration == _default.peakCurrentDuration)) || !settings.enableOptimizations; }
	static boolean continuousCurrentLimitDifferent (TalonSRXConfiguration settings) { return (!(settings.continuousCurrentLimit == _default.continuousCurrentLimit)) || !settings.enableOptimizations; }
	
	static boolean forwardLimitSwitchDifferent (TalonSRXConfiguration settings) {
		return forwardLimitSwitchDeviceIDDifferent(settings) || forwardLimitSwitchNormalDifferent(settings) || forwardLimitSwitchSourceDifferent(settings);
	}
	static boolean reverseLimitSwitchDifferent (TalonSRXConfiguration settings) {
		return reverseLimitSwitchDeviceIDDifferent(settings) || reverseLimitSwitchNormalDifferent(settings) || reverseLimitSwitchSourceDifferent(settings);
	}
}