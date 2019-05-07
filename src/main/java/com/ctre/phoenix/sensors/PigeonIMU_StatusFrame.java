package com.ctre.phoenix.sensors;

/**
 * Enumerated types for frame rate ms.
 */
public enum PigeonIMU_StatusFrame {
	/**
	 * General Status of Pigeon
	 */
	CondStatus_1_General(0x042000),
	/**
	 * Yaw Pitch Roll information from Pigeon 
	 */ 
	CondStatus_9_SixDeg_YPR(0x042200), 
	/**
	 * 9-Axis fused value
	 */
	CondStatus_6_SensorFusion(0x042140), 
	/**
	 * Accumulated Gyro information from Pigeon
	 */
	CondStatus_11_GyroAccum(0x042280), 
	/**
	 * General Compass information from Pigeon
	 */
	CondStatus_2_GeneralCompass(0x042040), 
	/**
	 * General Accelerometer information from Pigeon
	 */
	CondStatus_3_GeneralAccel(0x042080), 
	/**
	 * Quaternion value information from Pigeon
	 */
	CondStatus_10_SixDeg_Quat(0x042240), 
	/**
	 * Raw Magnetometer information from Pigeon
	 */
	RawStatus_4_Mag(0x041CC0), 
	/**
	 * Biased Gyro information from Pigeon
	 */
	BiasedStatus_2_Gyro(0x041C40), 
	/**
	 * Biased Magnetometer information from Pigeon
	 */
	BiasedStatus_4_Mag(0x041CC0), 
	/**
	 * Biased Accelerometer information from Pigeon
	 */
	BiasedStatus_6_Accel(0x41D40);

	/**
	 * value of Status frame
	 */
	public final int value;

	/**
	 * Create status frame of initValue
	 * @param initValue value of status frame
	 */
	PigeonIMU_StatusFrame(int initValue) {
		this.value = initValue;
	}

	/**
	 * Get StatusFrame of specified value
	 * @param value value of status frame
	 * @return PigeonIMU_StatusFrame of specified value
	 */
	public static PigeonIMU_StatusFrame valueOf(int value) {
		for (PigeonIMU_StatusFrame mode : values()) {
			if (mode.value == value) {
				return mode;
			}
		}
		return null;
	}
}