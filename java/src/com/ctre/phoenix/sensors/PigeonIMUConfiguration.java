package com.ctre.phoenix.sensors;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class PigeonIMUConfiguration extends CANBusAddressableConfiguration {
	public boolean TemperatureCompensationEnable;
	public PigeonIMUConfiguration() {
		this.TemperatureCompensationEnable = false; //Check
	}
}
