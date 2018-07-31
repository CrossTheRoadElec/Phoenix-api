package com.ctre.phoenix;

import com.ctre.phoenix.motorcontrol.can.VictorSPXConfiguration;

public class CustomParamConfigUtil {
	private static CustomParamConfiguration _default = new VictorSPXConfiguration();
	
	public static boolean customParam0Different (CustomParamConfiguration settings) { return (!(settings.customParam0 == _default.customParam0)) || !settings.enableOptimizations; }
	public static boolean customParam1Different (CustomParamConfiguration settings) { return (!(settings.customParam1 == _default.customParam1)) || !settings.enableOptimizations; }
}