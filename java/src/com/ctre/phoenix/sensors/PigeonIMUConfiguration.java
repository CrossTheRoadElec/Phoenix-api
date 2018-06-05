package com.ctre.phoenix.sensors;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class PidgeonIMUConfiguration extends CANBusAddressableConfiguration {
	public boolean TemperatureCompensationEnable;
	public PidgeonIMUConfiguration() {
		TemperatureCompensationEnable = false; //Check
	}
}
