#pragma once

#include <cstdint>
#include "ctre/phoenix/CANBusAddressable.h"
#include "ctre/phoenix/CustomParamConfiguration.h"
#include "ctre/phoenix/ErrorCode.h"
#include "ctre/phoenix/paramEnum.h"
#include "ctre/phoenix/CANifierControlFrame.h"
#include "ctre/phoenix/CANifierStatusFrame.h"
#include "ctre/phoenix/CANifierStickyFaults.h"
#include "ctre/phoenix/CANifierFaults.h"
#include "ctre/phoenix/CANifierVelocityMeasPeriod.h"

namespace ctre {namespace phoenix {
	
	/**
	 * CTRE CANifier
	 *
	 * Device for interfacing common devices to the CAN bus.
	 */

struct CANifierConfiguration : CustomParamConfiguration{
    CANifierVelocityMeasPeriod velocityMeasurementPeriod;
	int velocityMeasurementWindow;
    bool clearPositionOnLimitF;
    bool clearPositionOnLimitR;
    bool clearPositionOnQuadIdx;
	CANifierConfiguration() : 
		velocityMeasurementPeriod(Period_100Ms), 
		velocityMeasurementWindow(64), 	
	    clearPositionOnLimitF(false),
        clearPositionOnLimitR(false),
        clearPositionOnQuadIdx(false)
    {
	}

	std::string toString() {
		return toString("");
	}

    std::string toString(std::string prependString) {

        std::string retstr = prependString + ".velocityMeasurementPeriod = " + CANifierVelocityMeasPeriodRoutines::toString(velocityMeasurementPeriod) + ";\n";
        retstr += prependString + ".velocityMeasurementWindow = " + std::to_string(velocityMeasurementWindow) + ";\n";
        retstr += prependString + ".clearPositionOnLimitF = " + std::to_string(clearPositionOnLimitF) + ";\n";
        retstr += prependString + ".clearPositionOnLimitR = " + std::to_string(clearPositionOnLimitR) + ";\n";
        retstr += prependString + ".clearPositionOnQuadIdx = " + std::to_string(clearPositionOnQuadIdx) + ";\n";
        
        retstr += CustomParamConfiguration::toString(prependString);

        return retstr;
    }

};// struct CANifierConfiguration

struct CANifierConfigUtils {
private:
	static CANifierConfiguration _default;
public:
	static bool VelocityMeasurementPeriodDifferent (const CANifierConfiguration & settings) { return (!(settings.velocityMeasurementPeriod == _default.velocityMeasurementPeriod)) || !settings.enableOptimizations; }
	static bool VelocityMeasurementWindowDifferent (const CANifierConfiguration & settings) { return (!(settings.velocityMeasurementWindow == _default.velocityMeasurementWindow)) || !settings.enableOptimizations; }
	static bool ClearPositionOnLimitFDifferent (const CANifierConfiguration & settings) { return (!(settings.clearPositionOnLimitF == _default.clearPositionOnLimitF)) || !settings.enableOptimizations; }
	static bool ClearPositionOnLimitRDifferent (const CANifierConfiguration & settings) { return (!(settings.clearPositionOnLimitR == _default.clearPositionOnLimitR)) || !settings.enableOptimizations; }
	static bool ClearPositionOnQuadIdxDifferent (const CANifierConfiguration & settings) { return (!(settings.clearPositionOnQuadIdx == _default.clearPositionOnQuadIdx)) || !settings.enableOptimizations; }
	static bool CustomParam0Different (const CANifierConfiguration & settings) { return (!(settings.customParam0 == _default.customParam0)) || !settings.enableOptimizations; }
	static bool CustomParam1Different (const CANifierConfiguration & settings) { return (!(settings.customParam1 == _default.customParam1)) || !settings.enableOptimizations; }
};


class CANifier: public CANBusAddressable {
public:
	/**
	 * Enum for the LED Output Channels
	 */
	enum LEDChannel {
		LEDChannelA = 0, LEDChannelB = 1, LEDChannelC = 2,
	};

	/**
	 * Enum for the PWM Input Channels
	 */
	enum PWMChannel {
		PWMChannel0 = 0, PWMChannel1 = 1, PWMChannel2 = 2, PWMChannel3 = 3,
	};
	const int PWMChannelCount = 4;

	/**
	 * General IO Pins on the CANifier
	 */
	enum GeneralPin {
		QUAD_IDX = 0,	//----- Must match CANifier_CCI enums -----//
		QUAD_B = 1,
		QUAD_A = 2,
		LIMR = 3,
		LIMF = 4,
		SDA = 5,
		SCL = 6,
		SPI_CS = 7,
		SPI_MISO_PWM2P = 8,
		SPI_MOSI_PWM1P = 9,
		SPI_CLK_PWM0P = 10,
	};

	/**
	 * Structure to hold the pin values.
	 */
	struct PinValues {
		bool QUAD_IDX;
		bool QUAD_B;
		bool QUAD_A;
		bool LIMR;
		bool LIMF;
		bool SDA;
		bool SCL;
		bool SPI_CS_PWM3;
		bool SPI_MISO_PWM2;
		bool SPI_MOSI_PWM1;
		bool SPI_CLK_PWM0;
	};

	CANifier(int deviceNumber);
    
    ~CANifier();

    static void DestroyAllCANifiers();
	
    ErrorCode SetLEDOutput(double percentOutput, LEDChannel ledChannel);
	ErrorCode SetGeneralOutput(GeneralPin outputPin, bool outputValue, bool outputEnable);
	ErrorCode SetGeneralOutputs(int outputBits, int isOutputBits);
	ErrorCode GetGeneralInputs(PinValues &allPins);
	bool GetGeneralInput(GeneralPin inputPin);
	int GetQuadraturePosition();
	int GetQuadratureVelocity();
	ErrorCode SetQuadraturePosition(int newPosition, int timeoutMs = 0);
	ErrorCode ConfigVelocityMeasurementPeriod(
			CANifierVelocityMeasPeriod period, int timeoutMs = 0);
	ErrorCode ConfigVelocityMeasurementWindow(int windowSize, int timeoutMs = 0);
	ErrorCode ConfigClearPositionOnLimitF (bool clearPositionOnLimitF, int timeoutMs = 0);
	ErrorCode ConfigClearPositionOnLimitR (bool clearPositionOnLimitR, int timeoutMs = 0);
	ErrorCode ConfigClearPositionOnQuadIdx(bool clearPositionOnQuadIdx, int timeoutMs = 0);
	/**
	 * Gets the bus voltage seen by the motor controller.
	 *
	 * @return The bus voltage value (in volts).
	 */
	double GetBusVoltage();
	ErrorCode GetLastError();
	ErrorCode SetPWMOutput(int pwmChannel, double dutyCycle);
	ErrorCode EnablePWMOutput(int pwmChannel, bool bEnable);
	ErrorCode GetPWMInput(PWMChannel pwmChannel, double pulseWidthAndPeriod[]);

	//------ Custom Persistent Params ----------//
	ErrorCode ConfigSetCustomParam(int newValue, int paramIndex,
			int timeoutMs = 0);
	int ConfigGetCustomParam(int paramIndex,
			int timeoutMs = 0);
	//------ Generic Param API, typically not used ----------//
	ErrorCode ConfigSetParameter(ParamEnum param, double value,
			uint8_t subValue, int ordinal, int timeoutMs = 0);
	double ConfigGetParameter(ParamEnum param, int ordinal, int timeoutMs = 0);
    
    ErrorCode ConfigGetParameter(ParamEnum param, int32_t valueToSend,
            int32_t & valueReceived, uint8_t & subValue, int32_t ordinal,
            int32_t timeoutMs);


	ErrorCode SetStatusFramePeriod(CANifierStatusFrame statusFrame,
			uint8_t periodMs, int timeoutMs = 0);
	/**
	 * Gets the period of the given status frame.
	 *
	 * @param frame
	 *            Frame to get the period of.
	 * @param timeoutMs
	 *            Timeout value in ms. @see #ConfigOpenLoopRamp
	 * @return Period of the given status frame.
	 */
	int GetStatusFramePeriod(CANifierStatusFrame frame, int timeoutMs = 0);
	ErrorCode SetControlFramePeriod(CANifierControlFrame frame, int periodMs);
	/**
	 * Gets the firmware version of the device.
	 *
	 * @return Firmware version of device.
	 */
	int GetFirmwareVersion();
	/**
	 * Returns true if the device has reset since last call.
	 *
	 * @return Has a Device Reset Occurred?
	 */
	bool HasResetOccurred();
	ErrorCode GetFaults(CANifierFaults & toFill);
	ErrorCode GetStickyFaults(CANifierStickyFaults & toFill);
	ErrorCode ClearStickyFaults(int timeoutMs = 0);
	
	//------ All Configs ----------//
    ctre::phoenix::ErrorCode ConfigAllSettings(const CANifierConfiguration &allConfigs, int timeoutMs = 50);
    void GetAllConfigs(CANifierConfiguration &allConfigs, int timeoutMs = 50);
    ErrorCode ConfigFactoryDefault(int timeoutMs = 50);


private:
	void* m_handle;
	bool _tempPins[11];
};// class CANifier 

} // namespace phoenix
} // namespace ctre
