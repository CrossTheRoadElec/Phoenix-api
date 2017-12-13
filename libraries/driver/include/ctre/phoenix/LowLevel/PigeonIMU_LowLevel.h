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

#pragma once

#include "Device_LowLevel.h"
#include "ctre/Phoenix/core/ErrorCode.h"
#include <string>

/** 
 * Pigeon IMU Class.
 * Class supports communicating over CANbus and over ribbon-cable (CAN Talon SRX).
 */
class LowLevelPigeonImu : public Device_LowLevel {
public:
	/** Data object for holding fusion information. */
	struct FusionStatus {
		double heading;
		bool bIsValid;
		bool bIsFusing;
		std::string description;
		/**
		 * Same as GetLastError()
		 */
		int lastError;
	};
	/** Various calibration modes supported by Pigeon. */
	enum CalibrationMode {
		BootTareGyroAccel = 0,
		Temperature = 1,
		Magnetometer12Pt = 2,
		Magnetometer360 = 3,
		Accelerometer = 5,
	};
	/** Overall state of the Pigeon. */
	enum PigeonState {
		NoComm,
		Initializing,
		Ready,
		UserCalibration,
	};
	/**
	 * Data object for status on current calibration and general status.
	 *
	 * Pigeon has many calibration modes supported for a variety of uses.
	 * The modes generally collects and saves persistently information that makes
	 * the Pigeon signals more accurate.  This includes collecting temperature, gyro, accelerometer,
	 * and compass information.
	 *
	 * For FRC use-cases, typically compass and temperature calibration is not required.
	 *
	 * Additionally when motion driver software in the Pigeon boots, it will perform a fast boot calibration
	 * to initially bias gyro and setup accelerometer.
	 *
	 * These modes can be enabled with the EnterCalibration mode.
	 *
	 * When a calibration mode is entered, caller can expect...
	 *
	 *  - PigeonState to reset to Initializing and bCalIsBooting is set to true.  Pigeon LEDs will blink the boot pattern.
	 *  	This is similar to the normal boot cal, however it can an additional ~30 seconds since calibration generally
	 *  	requires more information.
	 *  	currentMode will reflect the user's selected calibration mode.
	 *
	 *  - PigeonState will eventually settle to UserCalibration and Pigeon LEDs will show cal specific blink patterns.
	 *  	bCalIsBooting is now false.
	 *
	 *  - Follow the instructions in the Pigeon User Manual to meet the calibration specific requirements.
	 * 		When finished calibrationError will update with the result.
	 * 		Pigeon will solid-fill LEDs with red (for failure) or green (for success) for ~5 seconds.
	 * 		Pigeon then perform boot-cal to cleanly apply the newly saved calibration data.
	 */
	struct GeneralStatus {
		/**
		 * The current state of the motion driver.  This reflects if the sensor signals are accurate.
		 * Most calibration modes will force Pigeon to reinit the motion driver.
		 */
		LowLevelPigeonImu::PigeonState state;
		/**
		 * The currently applied calibration mode if state is in UserCalibration or if bCalIsBooting is true.
		 * Otherwise it holds the last selected calibration mode (when calibrationError was updated).
		 */
		LowLevelPigeonImu::CalibrationMode currentMode;
		/**
		 * The error code for the last calibration mode.
		 * Zero represents a successful cal (with solid green LEDs at end of cal)
		 * and nonzero is a failed calibration (with solid red LEDs at end of cal).
		 * Different calibration
		 */
		int calibrationError;
		/**
		 * After caller requests a calibration mode, pigeon will perform a boot-cal before
		 * entering the requested mode.  During this period, this flag is set to true.
		 */
		bool bCalIsBooting;
		/**
		 * general string description of current status
		 */
		std::string description;
		/**
		 * Temperature in Celsius
		 */
		double tempC;
		/**
		 * Number of seconds Pigeon has been up (since boot).
		 * This register is reset on power boot or processor reset.
		 * Register is capped at 255 seconds with no wrap around.
		 */
		int upTimeSec;
		/**
		 * Number of times the Pigeon has automatically rebiased the gyro.
		 * This counter overflows from 15 -> 0 with no cap.
		 */
		int noMotionBiasCount;
		/**
		 * Number of times the Pigeon has temperature compensated the various signals.
		 * This counter overflows from 15 -> 0 with no cap.
		 */
		int tempCompensationCount;
		/**
		 * Same as GetLastError()
		 */
		int lastError;
	};

	/** Enumerated type for status frame types. */
	enum PigeonStatusFrame {
		Status_CondStatus_1_General = 0x042000,
		Status_CondStatus_9_SixDeg_YPR = 0x042200,
		Status_CondStatus_6_SensorFusion = 0x042140,
		Status_CondStatus_11_GyroAccum = 0x042280,
		Status_CondStatus_2_GeneralCompass = 0x042040,
		Status_CondStatus_3_GeneralAccel = 0x042080,
		Status_CondStatus_10_SixDeg_Quat = 0x042240,
		Status_RawStatus_4_Mag = 0x041CC0,
		Status_BiasedStatus_2_Gyro = 0x041C40,
		Status_BiasedStatus_4_Mag = 0x041CC0,
		Status_BiasedStatus_6_Accel = 0x41D40,
	};
	
	static LowLevelPigeonImu * CreatePigeon(int deviceNumber, bool talon);

	LowLevelPigeonImu(const LowLevelPigeonImu &) = delete;
	~LowLevelPigeonImu();


	CTR_Code SetLastError(CTR_Code error);

	CTR_Code SetStatusFramePeriod(PigeonStatusFrame frame, int periodMs, int timeoutMs);

	CTR_Code SetYaw(double angleDeg, int timeoutMs);
	CTR_Code AddYaw(double angleDeg, int timeoutMs);
	CTR_Code SetYawToCompass(int timeoutMs);

	CTR_Code SetFusedHeading(double angleDeg, int timeoutMs);
	CTR_Code AddFusedHeading(double angleDeg, int timeoutMs);
	CTR_Code SetFusedHeadingToCompass(int timeoutMs);
	CTR_Code SetAccumZAngle(double angleDeg, int timeoutMs);
	CTR_Code ConfigTemperatureCompensationEnable(bool bTempCompEnable, int timeoutMs);
	CTR_Code SetCompassDeclination(double angleDegOffset, int timeoutMs);
	CTR_Code SetCompassAngle(double angleDeg, int timeoutMs);

	CTR_Code EnterCalibrationMode(CalibrationMode calMode, int timeoutMs);
	CTR_Code GetGeneralStatus(LowLevelPigeonImu::GeneralStatus & StatusToFill);
	CTR_Code GetGeneralStatus(int &state, int &currentMode, int &calibrationError, int &bCalIsBooting, double &tempC, int &upTimeSec, int &noMotionBiasCount, int &tempCompensationCount, int &lastError);
	CTR_Code GetLastError();
	CTR_Code Get6dQuaternion(double wxyz[4]);
	CTR_Code GetYawPitchRoll(double ypr[3]);
	CTR_Code GetAccumGyro(double xyz_deg[3]);
	CTR_Code GetAbsoluteCompassHeading(double &value);
	CTR_Code GetCompassHeading(double &value);
	CTR_Code GetCompassFieldStrength(double &value);
	CTR_Code GetTemp(double &value);
	PigeonState GetState();
	CTR_Code GetState(int &state);
	CTR_Code GetUpTime(int &value);
	CTR_Code GetRawMagnetometer(short rm_xyz[3]);

	CTR_Code GetBiasedMagnetometer(short bm_xyz[3]);
	CTR_Code GetBiasedAccelerometer(short ba_xyz[3]);
	CTR_Code GetRawGyro(double xyz_dps[3]);
	CTR_Code GetAccelerometerAngles(double tiltAngles[3]);

	CTR_Code GetFusedHeading(FusionStatus & status, double &value);
	CTR_Code GetFusedHeading(int &bIsFusing, int &bIsValid, double &value, int &lastError);
	CTR_Code GetFusedHeading(double &value);

	static std::string ToString(LowLevelPigeonImu::PigeonState state);
	static std::string ToString(CalibrationMode cm);

	const static int kMinFirmwareVersionMajor = 0;
	const static int kMinFirmwareVersionMinor = 40;

protected:
	virtual void EnableFirmStatusFrame(bool enable);
private:

	LowLevelPigeonImu(int32_t baseArbId,
			int32_t arbIdStartupFrame,
			int32_t paramReqId,
			int32_t paramRespId,
			int32_t paramSetId,
			int32_t arbIdFrameApiStatus);

	/** firmware state reported over CAN */
	enum MotionDriverState {
		Init0 = 0,
		WaitForPowerOff = 1,
		ConfigAg = 2,
		SelfTestAg = 3,
		StartDMP = 4,
		ConfigCompass_0 = 5,
		ConfigCompass_1 = 6,
		ConfigCompass_2 = 7,
		ConfigCompass_3 = 8,
		ConfigCompass_4 = 9,
		ConfigCompass_5 = 10,
		SelfTestCompass = 11,
		WaitForGyroStable = 12,
		AdditionalAccelAdjust = 13,
		Idle = 14,
		Calibration = 15,
		LedInstrum = 16,
		Error = 31,
	};
	/** sub command for the various Set param enums */
	enum TareType {
		SetValue = 0x00, AddOffset = 0x01, MatchCompass = 0x02, SetOffset = 0xFF,
	};

	/** Portion of the arbID for all status and control frames. */
	CTR_Code _lastError = OKAY;
	uint64_t _cache = 0;
	uint32_t _len = 0;

	void CheckFirm(int minMajor = kMinFirmwareVersionMajor, int minMinor = kMinFirmwareVersionMinor);
	CTR_Code ConfigSetWrapper(ParamEnum paramEnum, TareType tareType, double angleDeg, int timeoutMs);
	CTR_Code ConfigSetWrapper(ParamEnum paramEnum, double value, int timeoutMs);
	CTR_Code ReceiveCAN(int arbId);
	CTR_Code ReceiveCAN(int arbId, bool allowStale);
	CTR_Code SendCAN(int arbId, const uint64_t & data, int dataSize, int periodMs);
	CTR_Code GetTwoParam16(int arbId, short words[2]);
	CTR_Code GetThreeParam16(int arbId, short words[3]);
	CTR_Code GetThreeParam16(int arbId, double signals[3], double scalar);
	int GetThreeFloatAngles(int arbId, double signals[3], double scalar);
	CTR_Code GetThreeBoundedAngles(int arbId, double boundedAngles[3]);
	CTR_Code GetFourParam16(int arbId, double params[4], double scalar);
	CTR_Code GetThreeParam20(int arbId, double param[3], double scalar);

	LowLevelPigeonImu::PigeonState GetState(int errCode, const uint64_t & statusFrame);
	double GetTemp(const uint64_t & statusFrame);
};

