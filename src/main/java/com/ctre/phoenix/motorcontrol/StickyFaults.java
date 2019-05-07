package com.ctre.phoenix.motorcontrol;

/**
 * All the sticky faults available to motor controllers
 */
public class StickyFaults {
	/**
	 * Motor Controller is under 6.5V
	 */
	public boolean UnderVoltage;
	/**
	 * Forward limit switch is tripped and device is trying to go forward
	 * Only trips when the device is limited
	 */
	public boolean ForwardLimitSwitch;
	/**
	 * Reverse limit switch is tripped and device is trying to go reverse
	 * Only trips when the device is limited
	 */
	public boolean ReverseLimitSwitch;
	/**
	 * Sensor is beyond forward soft limit and device is trying to go forward
	 * Only trips when the device is limited
	 */
	public boolean ForwardSoftLimit;
	/**
	 * Sensor is beyond reverse soft limit and device is trying to go reverse
	 * Only trips when the device is limited
	 */
	public boolean ReverseSoftLimit;
	/**
	 * Device was powered-on or reset while robot is enabled.
	 * Check your breakers and wiring.
	 */
	public boolean ResetDuringEn;
	/**
	 * Device's sensor overflowed
	 */
	public boolean SensorOverflow;
	/**
	 * Device detects its sensor is out of phase
	 */
	public boolean SensorOutOfPhase;
	/**
	 * Not used, @see ResetDuringEn
	 */
	public boolean HardwareESDReset;
	/**
	 * Remote Sensor is no longer detected on bus
	 */
	public boolean RemoteLossOfSignal;

	/**
	 * @return true if any faults are tripped
	 */
	public boolean hasAnyFault() {
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
	/**
	 * @return Current fault list as a bit field
	 */
	public int toBitfield() {
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
	/**
	 * Updates current fault list with specified bit field of faults
	 * 
	 * @param bits bit field of faults to update with
	 */
	public void update(int bits) {
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
	/**
	 * @return string representation of current faults tripped
	 */
	public String toString() {
		StringBuilder work = new StringBuilder();
		work.append(" UnderVoltage:"); work.append(UnderVoltage ? "1" : "0");
		work.append( " ForwardLimitSwitch:"); work.append(ForwardLimitSwitch ? "1" : "0");
		work.append( " ReverseLimitSwitch:"); work.append(ReverseLimitSwitch ? "1" : "0");
		work.append( " ForwardSoftLimit:"); work.append(ForwardSoftLimit ? "1" : "0");
		work.append( " ReverseSoftLimit:"); work.append(ReverseSoftLimit ? "1" : "0");
		work.append( " ResetDuringEn:"); work.append(ResetDuringEn ? "1" : "0");
		work.append( " SensorOverflow:"); work.append(SensorOverflow ? "1" : "0");
		work.append( " SensorOutOfPhase:"); work.append(SensorOutOfPhase ? "1" : "0");
		work.append( " HardwareESDReset:"); work.append(HardwareESDReset ? "1" : "0");
		work.append( " RemoteLossOfSignal:"); work.append(RemoteLossOfSignal ? "1" : "0");
		return work.toString();
	}
};

