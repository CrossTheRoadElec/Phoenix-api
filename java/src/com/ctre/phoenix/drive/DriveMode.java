package com.ctre.phoenix.drive;

public enum DriveMode {
	Voltage(0), PercentOutput(1);

	public final int value;

	DriveMode(int value) {
		this.value = value;
	}

	public static DriveMode valueOf(int value) {
		for (DriveMode e : DriveMode.values()) {
			if (e.value == value) {
				return e;
			}
		}
		return Voltage;
	}
}