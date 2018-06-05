package com.ctre.phoenix;

import com.ctre.phoenix.CANBusAddressableConfiguration;

public class CANifierConfiguration extends CANBusAddressableConfiguration{
	public CANifierVelocityMeasPeriod VelocityMeasurementPeriod;
	public int VelocityMeasurementWindow;
	public CANifierConfiguration() {
		VelocityMeasurementPeriod = 1; //TODO: Check this 
		VelocityMeasurementWindow = 0; //TODO: Check this
	}
}
