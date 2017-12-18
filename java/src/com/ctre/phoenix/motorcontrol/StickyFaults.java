package com.ctre.phoenix.motorcontrol;

public class StickyFaults {
	public boolean UnderVoltage;
	public boolean ForwardLimitSwitch;
	public boolean ReverseLimitSwitch;
	public boolean ForwardSoftLimit;
	public boolean ReverseSoftLimit;
	public boolean ResetDuringEn;
	public boolean SensorOverflow;
	public boolean SensorOutOfPhase;
	public boolean HardwareESDReset;
	public boolean RemoteLossOfSignal;

	//!< True iff any of the above flags are true.
	public boolean HasAnyFault() {
		return 	UnderVoltage |
				ForwardLimitSwitch |
				ReverseLimitSwitch |
				ForwardSoftLimit |
				ReverseSoftLimit |
				ResetDuringEn |
				SensorOverflow |
				SensorOutOfPhase |
				HardwareESDReset |
				RemoteLossOfSignal;
	}
	public int ToBitfield() {
		int retval = 0;
		int mask = 1;
		retval |= UnderVoltage ? mask : 0; mask <<= 1;
		retval |= ForwardLimitSwitch ? mask : 0; mask <<= 1;
		retval |= ReverseLimitSwitch ? mask : 0; mask <<= 1;
		retval |= ForwardSoftLimit ? mask : 0; mask <<= 1;
		retval |= ReverseSoftLimit ? mask : 0; mask <<= 1;
		retval |= ResetDuringEn ? mask : 0; mask <<= 1;
		retval |= SensorOverflow ? mask : 0; mask <<= 1;
		retval |= SensorOutOfPhase ? mask : 0; mask <<= 1;
		retval |= HardwareESDReset ? mask : 0; mask <<= 1;
		retval |= RemoteLossOfSignal ? mask : 0; mask <<= 1;
		return retval;
	}
	public void Update(int bits) {
		int mask = 1;
		UnderVoltage = ((bits & mask)!=0) ? true : false; mask <<= 1;
		ForwardLimitSwitch = ((bits & mask)!=0) ? true : false; mask <<= 1;
		ReverseLimitSwitch = ((bits & mask)!=0) ? true : false; mask <<= 1;
		ForwardSoftLimit = ((bits & mask)!=0) ? true : false; mask <<= 1;
		ReverseSoftLimit = ((bits & mask)!=0) ? true : false; mask <<= 1;
		ResetDuringEn = ((bits & mask)!=0) ? true : false; mask <<= 1;
		SensorOverflow = ((bits & mask)!=0) ? true : false; mask <<= 1;
		SensorOutOfPhase = ((bits & mask)!=0) ? true : false; mask <<= 1;
		HardwareESDReset = ((bits & mask)!=0) ? true : false; mask <<= 1;
		RemoteLossOfSignal = ((bits & mask)!=0) ? true : false; mask <<= 1;
	}
	public StickyFaults() {
		UnderVoltage = false;
		ForwardLimitSwitch = false;
		ReverseLimitSwitch = false;
		ForwardSoftLimit = false;
		ReverseSoftLimit = false;
		ResetDuringEn = false;
		SensorOverflow = false;
		SensorOutOfPhase = false;
		HardwareESDReset = false;
		RemoteLossOfSignal = false;
	}
};

