package com.ctre.phoenix;

import com.ctre.phoenix.CustomParamConfiguration;
import com.ctre.phoenix.VelocityPeriod;




public class CANifierConfiguration extends CustomParamConfiguration{
	public VelocityPeriod VelocityMeasurementPeriod;
	public int VelocityMeasurementWindow;
	public CANifierConfiguration() {
		//this.VelocityMeasurementPeriod = 1; //TODO: fix this 
		this.VelocityMeasurementWindow = 0; //TODO: Check this
	}
}
