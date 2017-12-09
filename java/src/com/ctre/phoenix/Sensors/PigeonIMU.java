/*
 *  Software License Agreement
 *
 * Copyright (C) Cross The Road Electronics.  All rights
 * reserved.
 * 
 * Cross The Road Electronics (CTRE) licenses to you the right to 
 * use, publish, and distribute copies of CRF (Cross The Road) firmware files (*.crf) and Software
 * API Libraries ONLY when in use with Cross The Road Electronics hardware products.
 * 
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * CROSS THE ROAD ELECTRONICS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
 */
package com.ctre.phoenix.Sensors;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.ParamEnum;
import com.ctre.phoenix.MotorControl.CAN.TalonSRX;

/**
 * Pigeon IMU Class. Class supports communicating over CANbus and over
 * ribbon-cable (CAN Talon SRX).
 */
public class PigeonIMU {
	private long m_handle;

	/** Data object for holding fusion information. */
	public static class FusionStatus {
		public double heading;
		public boolean bIsValid;
		public boolean bIsFusing;

		/**
		 * Same as getLastError()
		 */
		public ErrorCode lastError;

		public String ToString() {
			String description;
			if (lastError != ErrorCode.OKAY) {
				description = "Could not receive status frame.  Check wiring and web-config.";
			} else if (bIsValid == false) {
				description = "Fused Heading is not valid.";
			} else if (bIsFusing == false) {
				description = "Fused Heading is valid.";
			} else {
				description = "Fused Heading is valid and is fusing compass.";
			}
			return description;
		}
	}

	/** Various calibration modes supported by Pigeon. */
	public enum CalibrationMode {
		BootTareGyroAccel(0), Temperature(1), Magnetometer12Pt(2), Magnetometer360(3), Accelerometer(5), Unknown(-1);
		public final int value;

		private CalibrationMode(int initValue) {
			this.value = initValue;
		}

		public static CalibrationMode valueOf(int value) {
			for (CalibrationMode e : CalibrationMode.values()) {
				if (e.value == value) {
					return e;
				}
			}
			return Unknown;
		}
	};

	/** Overall state of the Pigeon. */
	public enum PigeonState {
		NoComm(0), Initializing(1), Ready(2), UserCalibration(3), Unknown(-1);
		public final int value;

		private PigeonState(int initValue) {
			this.value = initValue;
		}

		public static PigeonState valueOf(int value) {
			for (PigeonState e : PigeonState.values()) {
				if (e.value == value) {
					return e;
				}
			}
			return Unknown;
		}
	};

	/**
	 * Data object for status on current calibration and general status.
	 *
	 * Pigeon has many calibration modes supported for a variety of uses. The
	 * modes generally collects and saves persistently information that makes
	 * the Pigeon signals more accurate. This includes collecting temperature,
	 * gyro, accelerometer, and compass information.
	 *
	 * For FRC use-cases, typically compass and temperature calibration is not
	 * required.
	 *
	 * Additionally when motion driver software in the Pigeon boots, it will
	 * perform a fast boot calibration to initially bias gyro and setup
	 * accelerometer.
	 *
	 * These modes can be enabled with the EnterCalibration mode.
	 *
	 * When a calibration mode is entered, caller can expect...
	 *
	 * - PigeonState to reset to Initializing and bCalIsBooting is set to true.
	 * Pigeon LEDs will blink the boot pattern. This is similar to the normal
	 * boot cal, however it can an additional ~30 seconds since calibration
	 * generally requires more information. currentMode will reflect the user's
	 * selected calibration mode.
	 *
	 * - PigeonState will eventually settle to UserCalibration and Pigeon LEDs
	 * will show cal specific blink patterns. bCalIsBooting is now false.
	 *
	 * - Follow the instructions in the Pigeon User Manual to meet the
	 * calibration specific requirements. When finished calibrationError will
	 * update with the result. Pigeon will solid-fill LEDs with red (for
	 * failure) or green (for success) for ~5 seconds. Pigeon then perform
	 * boot-cal to cleanly apply the newly saved calibration data.
	 */
	public static class GeneralStatus {
		/**
		 * The current state of the motion driver. This reflects if the sensor
		 * signals are accurate. Most calibration modes will force Pigeon to
		 * reinit the motion driver.
		 */
		public PigeonState state;
		/**
		 * The currently applied calibration mode if state is in UserCalibration
		 * or if bCalIsBooting is true. Otherwise it holds the last selected
		 * calibration mode (when calibrationError was updated).
		 */
		public CalibrationMode currentMode;
		/**
		 * The error code for the last calibration mode. Zero represents a
		 * successful cal (with solid green LEDs at end of cal) and nonzero is a
		 * failed calibration (with solid red LEDs at end of cal). Different
		 * calibration
		 */
		public int calibrationError;
		/**
		 * After caller requests a calibration mode, pigeon will perform a
		 * boot-cal before entering the requested mode. During this period, this
		 * flag is set to true.
		 */
		public boolean bCalIsBooting;
		/**
		 * Temperature in Celsius
		 */
		public double tempC;
		/**
		 * Number of seconds Pigeon has been up (since boot). This register is
		 * reset on power boot or processor reset. Register is capped at 255
		 * seconds with no wrap around.
		 */
		public int upTimeSec;
		/**
		 * Number of times the Pigeon has automatically rebiased the gyro. This
		 * counter overflows from 15 -> 0 with no cap.
		 */
		public int noMotionBiasCount;
		/**
		 * Number of times the Pigeon has temperature compensated the various
		 * signals. This counter overflows from 15 -> 0 with no cap.
		 */
		public int tempCompensationCount;
		/**
		 * Same as getLastError()
		 */
		public ErrorCode lastError;

		/**
		 * general string description of current status
		 */
		public String ToString() {
			String description;
			/* build description string */
			if (lastError != ErrorCode.OKAY) { // same as NoComm
				description = "Status frame was not received, check wired connections and web-based config.";
			} else if (bCalIsBooting) {
				description = "Pigeon is boot-caling to properly bias accel and gyro.  Do not move Pigeon.  When finished biasing, calibration mode will start.";
			} else if (state == PigeonState.UserCalibration) {
				/* mode specific descriptions */
				switch (currentMode) {
				case BootTareGyroAccel:
					description = "Boot-Calibration: Gyro and Accelerometer are being biased.";
					break;
				case Temperature:
					description = "Temperature-Calibration: Pigeon is collecting temp data and will finish when temp range is reached. \n";
					description += "Do not moved Pigeon.";
					break;
				case Magnetometer12Pt:
					description = "Magnetometer Level 1 calibration: Orient the Pigeon PCB in the 12 positions documented in the User's Manual.";
					break;
				case Magnetometer360:
					description = "Magnetometer Level 2 calibration: Spin robot slowly in 360' fashion.  ";
					break;
				case Accelerometer:
					description = "Accelerometer Calibration: Pigeon PCB must be placed on a level source.  Follow User's Guide for how to level surfacee.  ";
					break;
				default:
				case Unknown:
					description = "Unknown status";
					break;
				}
			} else if (state == PigeonState.Ready) {
				/*
				 * definitely not doing anything cal-related. So just instrument
				 * the motion driver state
				 */
				description = "Pigeon is running normally.  Last CAL error code was ";
				description += Integer.toString(calibrationError);
				description += ".";
			} else if (state == PigeonState.Initializing) {
				/*
				 * definitely not doing anything cal-related. So just instrument
				 * the motion driver state
				 */
				description = "Pigeon is boot-caling to properly bias accel and gyro.  Do not move Pigeon.";
			} else {
				description = "Not enough data to determine status.";
			}
			return description;
		}
	};

	/**
	 * Enumerated types for frame rate ms.
	 */
	public enum StatusFrame {
		CondStatus_1_General(0x042000), CondStatus_9_SixDeg_YPR(0x042200), CondStatus_6_SensorFusion(
				0x042140), CondStatus_11_GyroAccum(0x042280), CondStatus_2_GeneralCompass(
						0x042040), CondStatus_3_GeneralAccel(0x042080), CondStatus_10_SixDeg_Quat(
								0x042240), RawStatus_4_Mag(0x041CC0), BiasedStatus_2_Gyro(
										0x041C40), BiasedStatus_4_Mag(0x041CC0), BiasedStatus_6_Accel(0x41D40);

		public final int value;

		StatusFrame(int initValue) {
			this.value = initValue;
		}

		public static StatusFrame valueOf(int value) {
			for (StatusFrame mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}
	}

	private int m_deviceNumber = 0;

	private double[] _generalStatus = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	private double[] _fusionStatus = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	/**
	 * Create a Pigeon object that communicates with Pigeon on CAN Bus.
	 * 
	 * @param deviceNumber
	 *            CAN Device Id of Pigeon [0,62]
	 */
	public PigeonIMU(int deviceNumber) {
		m_handle = PigeonImuJNI.JNI_new_PigeonImu(deviceNumber);
		m_deviceNumber = deviceNumber;
	}

	/**
	 * Create a Pigeon object that communciates with Pigeon through the
	 * Gadgeteer ribbon
	 * 
	 * @param talonSrx
	 *            cable connected to a Talon on CAN Bus.
	 */
	public PigeonIMU(TalonSRX talonSrx) {
		m_deviceNumber = talonSrx.getDeviceID();
		m_handle = PigeonImuJNI.JNI_new_PigeonImu_Talon(m_deviceNumber);
	}

	public ErrorCode setStatusFramePeriod(StatusFrame stateFrameRate, int periodMs, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetStatusFramePeriod(m_handle, stateFrameRate.value, periodMs, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode setYaw(double angleDeg, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetYaw(m_handle, angleDeg, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Atomically add to the Yaw register.
	 */
	public ErrorCode addYaw(double angleDeg, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_AddYaw(m_handle, angleDeg, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode setYawToCompass(int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetYawToCompass(m_handle, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode setFusedHeading(double angleDeg, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetFusedHeading(m_handle, angleDeg, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode addFusedHeading(double angleDeg, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_AddFusedHeading(m_handle, angleDeg, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode setFusedHeadingToCompass(int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetFusedHeadingToCompass(m_handle, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode setAccumZAngle(double angleDeg, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetAccumZAngle(m_handle, angleDeg, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Enable/Disable Temp compensation. Pigeon defaults with this on at boot.
	 */
	public ErrorCode configTemperatureCompensationEnable(boolean bTempCompEnable, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_ConfigTemperatureCompensationEnable(m_handle, bTempCompEnable ? 1 : 0, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Set the declination for compass. Declination is the difference between
	 * Earth Magnetic north, and the geographic "True North".
	 */
	public ErrorCode setCompassDeclination(double angleDegOffset, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetCompassDeclination(m_handle, angleDegOffset, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Sets the compass angle. Although compass is absolute [0,360) degrees, the
	 * continuous compass register holds the wrap-arounds.
	 */
	public ErrorCode setCompassAngle(double angleDeg, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_SetCompassAngle(m_handle, angleDeg, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	// ----------------------- Calibration routines -----------------------//
	public ErrorCode enterCalibrationMode(CalibrationMode calMode, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_EnterCalibrationMode(m_handle, calMode.value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Get the status of the current (or previousley complete) calibration.
	 * 
	 * @param generalStatus
	 */
	public ErrorCode getGeneralStatus(GeneralStatus toFill) {
		int retval = PigeonImuJNI.JNI_GetGeneralStatus(m_handle, _generalStatus);
		toFill.state = PigeonState.valueOf((int) _generalStatus[0]);
		toFill.currentMode = CalibrationMode.valueOf((int) _generalStatus[1]);
		toFill.calibrationError = (int) _generalStatus[2];
		toFill.bCalIsBooting = _generalStatus[3] != 0;
		toFill.tempC = _generalStatus[4];
		toFill.upTimeSec = (int) _generalStatus[5];
		toFill.noMotionBiasCount = (int) _generalStatus[6];
		toFill.tempCompensationCount = (int) _generalStatus[7];
		toFill.lastError = ErrorCode.valueOf(retval);
		return toFill.lastError;
	}

	// ----------------------- General Error status -----------------------//
	/**
	 * Gets the last error generated by this object.
	 *
	 * @return Last Error Code generated by a function.
	 */
	public ErrorCode getLastError() {
		int retval = PigeonImuJNI.JNI_GetLastError(m_handle);
		return ErrorCode.valueOf(retval);
	}

	// ----------------------- Strongly typed Signal decoders
	// -----------------------//
	public ErrorCode get6dQuaternion(double[] wxyz) {
		int retval = PigeonImuJNI.JNI_Get6dQuaternion(m_handle, wxyz);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode getYawPitchRoll(double[] ypr_deg) {
		int retval = PigeonImuJNI.JNI_GetYawPitchRoll(m_handle, ypr_deg);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode getAccumGyro(double[] xyz_deg) {
		int retval = PigeonImuJNI.JNI_GetAccumGyro(m_handle, xyz_deg);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * @return compass heading [0,360) degrees.
	 */
	public double getAbsoluteCompassHeading() {
		double retval = PigeonImuJNI.JNI_GetAbsoluteCompassHeading(m_handle);
		return retval;
	}

	/**
	 * @return continuous compass heading [-23040, 23040) degrees. Use
	 *         SetCompassHeading to modify the wrap-around portion.
	 */
	public double getCompassHeading() {
		double retval = PigeonImuJNI.JNI_GetCompassHeading(m_handle);
		return retval;
	}

	/**
	 * @return field strength in Microteslas (uT).
	 */
	public double getCompassFieldStrength() {
		double retval = PigeonImuJNI.JNI_GetCompassFieldStrength(m_handle);
		return retval;
	}

	public double getTemp() {
		double retval = PigeonImuJNI.JNI_GetTemp(m_handle);
		return retval;
	}

	public PigeonState getState() {
		int retval = PigeonImuJNI.JNI_GetState(m_handle);
		return PigeonState.valueOf(retval);
	}

	/**
	 * @return How long has Pigeon been running in whole seconds. Value caps at
	 *         255.
	 */
	public int getUpTime() {
		int retval = PigeonImuJNI.JNI_GetUpTime(m_handle);
		return retval;
	}

	public ErrorCode getRawMagnetometer(short[] rm_xyz) {
		int retval = PigeonImuJNI.JNI_GetRawMagnetometer(m_handle, rm_xyz);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode getBiasedMagnetometer(short[] bm_xyz) {
		int retval = PigeonImuJNI.JNI_GetBiasedMagnetometer(m_handle, bm_xyz);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode getBiasedAccelerometer(short[] ba_xyz) {
		int retval = PigeonImuJNI.JNI_GetBiasedAccelerometer(m_handle, ba_xyz);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode getRawGyro(double[] xyz_dps) {
		int retval = PigeonImuJNI.JNI_GetRawGyro(m_handle, xyz_dps);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode getAccelerometerAngles(double[] tiltAngles) {
		int retval = PigeonImuJNI.JNI_GetAccelerometerAngles(m_handle, tiltAngles);
		return ErrorCode.valueOf(retval);
	}

	public ErrorCode getFusedHeading(FusionStatus toFill) {
		int retval = PigeonImuJNI.JNI_GetFusedHeading(m_handle, _fusionStatus);

		toFill.heading = _fusionStatus[0];
		toFill.bIsFusing = (_fusionStatus[1] != 0);
		toFill.bIsValid = (_fusionStatus[2] != 0);
		toFill.lastError = ErrorCode.valueOf(retval);

		return toFill.lastError;
	}

	/*
	 * @return param holds the version of the Talon. Talon must be powered
	 * cycled at least once.
	 */
	public int getFirmwareVersion() {
		int k = PigeonImuJNI.JNI_GetFirmwareVersion(m_handle);
		return k;
	}

	/**
	 * @return true iff a reset has occured since last call.
	 */
	public boolean hasResetOccurred() {
		boolean k = PigeonImuJNI.JNI_HasResetOccured(m_handle);
		return k;
	}

	/**
	 * Sets the value of a custom parameter.
	 *
	 * @param newValue
	 *            Value for custom parameter.
	 * @param paramIndex
	 *            Index of custom parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. @see #ConfigOpenLoopRamp
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetCustomParam(int newValue, int paramIndex, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_ConfigSetCustomParam(m_handle, newValue, paramIndex, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Gets the value of a custom parameter.
	 *
	 * @param paramIndex
	 *            Index of custom parameter.
	 * @param timoutMs
	 *            Timeout value in ms. @see #ConfigOpenLoopRamp
	 * @return Value of the custom param.
	 */
	public int configGetCustomParam(int paramIndex, int timoutMs) {
		int retval = PigeonImuJNI.JNI_ConfigGetCustomParam(m_handle, paramIndex, timoutMs);
		return retval;
	}

	/**
	 * Sets a parameter.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param value
	 *            Value of parameter.
	 * @param subValue
	 *            Subvalue for parameter. Maximum value of 255.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. @see #ConfigOpenLoopRamp
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetParameter(ParamEnum param, double value, int subValue, int ordinal, int timeoutMs) {
		int retval = PigeonImuJNI.JNI_ConfigSetParameter(m_handle, param.value, (float) value, subValue, ordinal,
				timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Gets a parameter.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. @see #ConfigOpenLoopRamp
	 * @return Value of parameter.
	 */
	public double configGetParameter(ParamEnum param, int ordinal, int timeoutMs) {
		return PigeonImuJNI.JNI_ConfigGetParameter(m_handle, param.value, ordinal, timeoutMs);
	}
}
