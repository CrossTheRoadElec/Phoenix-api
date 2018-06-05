package com.ctre.phoenix;

/** 
* Enum for velocity periods used for CANifier 
*/ 

public enum VelocityPeriod { 
	Period_1Ms(1), 
	Period_2Ms(2), 
	Period_5Ms(5), 
	Period_10Ms(10), 
	Period_20Ms(20), 
	Period_25Ms(25), 
	Period_50Ms(50), 
	Period_100Ms(100); 
	public static VelocityPeriod valueOf(int value) { 
		for(VelocityPeriod period : values()) { 
			if(period.value == value) { 
				return period; 
			} 
		} 
		return null; 
	} 
	public final int value; 
	VelocityPeriod(int initValue) { 
		this.value = initValue; 
	} 
} 
