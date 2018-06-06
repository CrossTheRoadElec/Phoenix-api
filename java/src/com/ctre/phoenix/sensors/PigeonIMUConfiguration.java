package com.ctre.phoenix.sensors;

import com.ctre.phoenix.CustomParamConfiguration;

public class PigeonIMUConfiguration extends CustomParamConfiguration {
	public boolean TemperatureCompensationEnable;
	public PigeonIMUConfiguration() {
		this.TemperatureCompensationEnable = false; //Check
	}
}
