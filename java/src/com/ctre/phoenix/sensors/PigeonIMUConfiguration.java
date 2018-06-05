package com.ctre.phoenix.sensors;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class PidgeonIMUConfiguration extends CANBusAddressableConfiguration {
	boolean TemperatureCompensationEnable;
	PidgeonIMUConfiguration() {
		TemperatureCompensationEnable = false; //Check
	}
}
