#pragma once

#ifndef CTR_EXCLUDE_WPILIB_CLASSES

#include <cstdint>
#include "ctre/phoenix/LowLevel/CANBusAddressable.h"
#include "ctre/Phoenix/ErrorCode.h"
#include "ctre/phoenix/paramEnum.h"

namespace ctre {namespace phoenix {
class CANifier: public CANBusAddressable {
public:
	enum LEDChannel {
		LEDChannelA = 0, LEDChannelB = 1, LEDChannelC = 2,
	};

	enum PWMChannel {
		PWMChannel0 = 0, PWMChannel1 = 1, PWMChannel2 = 2, PWMChannel3 = 3,
	};
	const int PWMChannelCount = 4;

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

	enum StatusFrameRate {
		Status1_General = 0,
		Status2_General = 1,
		Status3_PwmInput0 = 2,
		Status4_PwmInput1 = 3,
		Status5_PwmInput2 = 4,
		Status6_PwmInput3 = 5,
	};

	CANifier(int deviceNumber);
	CTR_Code SetLEDOutput(double percentOutput, LEDChannel ledChannel);
	CTR_Code SetGeneralOutput(GeneralPin outputPin, bool outputValue, bool outputEnable);
	CTR_Code SetGeneralOutputs(int outputBits, int isOutputBits);
	CTR_Code GetGeneralInputs(PinValues &allPins);
	bool GetGeneralInput(GeneralPin inputPin);
	CTR_Code GetLastError();
	CTR_Code SetPWMOutput(int pwmChannel, double dutyCycle);
	CTR_Code EnablePWMOutput(int pwmChannel, bool bEnable);
	CTR_Code GetPWMInput(PWMChannel pwmChannel, double dutyCycleAndPeriod[]);

	//------ Custom Persistent Params ----------//
	ErrorCode ConfigSetCustomParam(int newValue, int paramIndex,
			int timeoutMs);
	int ConfigGetCustomParam(int paramIndex,
			int timeoutMs);
	//------ Generic Param API, typically not used ----------//
	ErrorCode ConfigSetParameter(ParamEnum param, double value,
			uint8_t subValue, int ordinal, int timeoutMs);
	double ConfigGetParameter(ParamEnum param, int ordinal, int timeoutMs);
private:
	void* m_handle;
	bool _tempPins[11];
};
}}
#endif // CTR_EXCLUDE_WPILIB_CLASSES
