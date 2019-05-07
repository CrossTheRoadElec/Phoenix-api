package com.ctre.phoenix;

/**
 * Util class to help with configuring CANifier
 */
class CANifierConfigUtil extends CustomParamConfigUtil{
	private static CANifierConfiguration _default = new CANifierConfiguration();
	
	static boolean velocityMeasurementPeriodDifferent (CANifierConfiguration settings) { return (!(settings.velocityMeasurementPeriod == _default.velocityMeasurementPeriod)) || !settings.enableOptimizations; }
	static boolean velocityMeasurementWindowDifferent (CANifierConfiguration settings) { return (!(settings.velocityMeasurementWindow == _default.velocityMeasurementWindow)) || !settings.enableOptimizations; }
	static boolean clearPositionOnLimitFDifferent (CANifierConfiguration settings) { return (!(settings.clearPositionOnLimitF == _default.clearPositionOnLimitF)) || !settings.enableOptimizations; }
	static boolean clearPositionOnLimitRDifferent (CANifierConfiguration settings) { return (!(settings.clearPositionOnLimitR == _default.clearPositionOnLimitR)) || !settings.enableOptimizations; }
	static boolean clearPositionOnQuadIdxDifferent (CANifierConfiguration settings) { return (!(settings.clearPositionOnQuadIdx == _default.clearPositionOnQuadIdx)) || !settings.enableOptimizations; }
}