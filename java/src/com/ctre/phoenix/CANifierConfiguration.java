package com.ctre.phoenix;

import com.ctre.phoenix.CANBusAddressableConfiguration;
import com.ctre.phoenix.VelocityPeriod;




public class CANifierConfiguration extends CANBusAddressableConfiguration{
	public VelocityPeriod VelocityMeasurementPeriod;
	public int VelocityMeasurementWindow;
	public CANifierConfiguration() {
		//this.VelocityMeasurementPeriod = 1; //TODO: fix this 
		this.VelocityMeasurementWindow = 0; //TODO: Check this
	}
}
