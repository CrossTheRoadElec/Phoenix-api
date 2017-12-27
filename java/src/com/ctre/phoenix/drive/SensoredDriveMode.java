package com.ctre.phoenix.drive;

public enum SensoredDriveMode {
	Voltage(0), PercentOutput(1), VelocityClosedLoop(2);

	public final int value;

	SensoredDriveMode(int value) {
		this.value = value;
	}

	public static SensoredDriveMode valueOf(int value) {
		for (SensoredDriveMode e : SensoredDriveMode.values()) {
			if (e.value == value) {
				return e;
			}
		}
		return Voltage;
	}
}
