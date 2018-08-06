package com.ctre.phoenix.motorcontrol.can;

class FilterConfigUtil {
	private static FilterConfiguration _default = new FilterConfiguration();
	
	static boolean remoteSensorDeviceIDDifferent (FilterConfiguration settings) { return (!(settings.remoteSensorDeviceID == _default.remoteSensorDeviceID)); }
	static boolean remoteSensorSourceDifferent (FilterConfiguration settings) { return (!(settings.remoteSensorSource == _default.remoteSensorSource)); }
	static boolean filterConfigurationDifferent (FilterConfiguration settings) { return remoteSensorDeviceIDDifferent(settings) || remoteSensorSourceDifferent(settings); }
}