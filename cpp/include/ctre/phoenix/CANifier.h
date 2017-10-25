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

#ifndef CTR_EXCLUDE_WPILIB_CLASSES

#include <cstdint>
#include "ctre/phoenix/core/CtreCanMap.h"

namespace CTRE {
class CANifier: public CtreCanMap {
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
	CTR_Code GetGeneralInputs(PinValues &allPins, int arraySize);
	bool GetGeneralInput(GeneralPin inputPin);
	int GetLastError();
	CTR_Code SetPWMOutput(int pwmChannel, float dutyCycle);
	CTR_Code EnablePWMOutput(int pwmChannel, bool bEnable);
	CTR_Code GetPWMInput(PWMChannel pwmChannel, float dutyCycleAndPeriod[]);

private:
	void* m_handle;
	bool _tempPins[11];
};
}
#endif // CTR_EXCLUDE_WPILIB_CLASSES
