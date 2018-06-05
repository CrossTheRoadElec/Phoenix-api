package com.ctre.phoenix;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class CANifierConfiguration extends CANBusAddressableConfiguration{
	CANifierVelocityMeasPeriod VelocityMeasurementPeriod;
	int VelocityMeasurementWindow;
	CANifierConfiguration() {
		VelocityMeasurementPeriod = 1; //TODO: Check this 
		VelocityMeasurementWindow = 0; //TODO: Check this
	}
}
