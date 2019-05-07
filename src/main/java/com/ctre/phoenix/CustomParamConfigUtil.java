package com.ctre.phoenix;

import com.ctre.phoenix.motorcontrol.can.VictorSPXConfiguration;

/**
 * Util class to help custom configs
 */
public class CustomParamConfigUtil {
	private static CustomParamConfiguration _default = new VictorSPXConfiguration();
	
	/**
	 * @param settings Settings to compare against
	 * @return Whether CustomParam0 is different
	 */
	public static boolean customParam0Different (CustomParamConfiguration settings) { return (!(settings.customParam0 == _default.customParam0)) || !settings.enableOptimizations; }
	/**
	 * @param settings Settings to compare against
	 * @return Whether CustomParam1 is different
	 */
	public static boolean customParam1Different (CustomParamConfiguration settings) { return (!(settings.customParam1 == _default.customParam1)) || !settings.enableOptimizations; }
}