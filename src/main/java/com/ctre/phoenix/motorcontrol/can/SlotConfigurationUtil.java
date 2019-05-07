package com.ctre.phoenix.motorcontrol.can;

/**
 * Util Class to help with slot configs
 */
class SlotConfigurationUtil {
	private static SlotConfiguration _default = new SlotConfiguration();
	
	static boolean kPDifferent (SlotConfiguration settings) { return (!(settings.kP == _default.kP)); }
	static boolean kIDifferent (SlotConfiguration settings) { return (!(settings.kI == _default.kI)); }
	static boolean kDDifferent (SlotConfiguration settings) { return (!(settings.kD == _default.kD)); }
	static boolean kFDifferent (SlotConfiguration settings) { return (!(settings.kF == _default.kF)); }
	static boolean integralZoneDifferent (SlotConfiguration settings) { return (!(settings.integralZone == _default.integralZone)); }
	static boolean allowableClosedloopErrorDifferent (SlotConfiguration settings) { return (!(settings.allowableClosedloopError == _default.allowableClosedloopError)); }
	static boolean maxIntegralAccumulatorDifferent (SlotConfiguration settings) { return (!(settings.maxIntegralAccumulator == _default.maxIntegralAccumulator)); }
	static boolean closedLoopPeakOutputDifferent (SlotConfiguration settings) { return (!(settings.closedLoopPeakOutput == _default.closedLoopPeakOutput)); }
	static boolean closedLoopPeriodDifferent (SlotConfiguration settings) { return (!(settings.closedLoopPeriod == _default.closedLoopPeriod)); }
}