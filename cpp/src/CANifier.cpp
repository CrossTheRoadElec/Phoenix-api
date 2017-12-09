/*
 *  Software License Agreement
 *
 * Copyright (C) Cross The Road Electronics.  All rights
 * reserved.
 * 
 * Cross The Road Electronics (CTRE) licenses to you the right to 
 * use, publish, and distribute copies of CRF (Cross The Road) firmware files (*.crf) and Software
 * API Libraries ONLY when in use with Cross The Road Electronics hardware products.
 * 
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * CROSS THE ROAD ELECTRONICS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
 */

#ifndef CTR_EXCLUDE_WPILIB_CLASSES
#include "ctre/phoenix/CANifier.h"
#include "ctre/phoenix/CCI/CANifier_CCI.h"
#include "ctre/phoenix/CTRLogger.h"

namespace CTRE {
namespace Phoenix {
CANifier::CANifier(int deviceNumber): CANBusAddressable(deviceNumber)
{
	m_handle = c_CANifier_Create1(deviceNumber);
}

CTR_Code CANifier::SetLEDOutput(double percentOutput, LEDChannel ledChannel) {
	/* convert float to integral fixed pt */
	if (percentOutput > 1) {
		percentOutput = 1;
	}
	if (percentOutput < 0) {
		percentOutput = 0;
	}
	int dutyCycle = (int) (percentOutput * 1023); // [0,1023]

	return c_CANifier_SetLEDOutput(m_handle, dutyCycle, ledChannel);
}

CTR_Code CANifier::SetGeneralOutput(GeneralPin outputPin, bool outputValue,
		bool outputEnable) {
	return  c_CANifier_SetGeneralOutput(m_handle, outputPin, outputValue,
			outputEnable);
}

CTR_Code CANifier::SetGeneralOutputs(int outputBits, int isOutputBits) {
	return c_CANifier_SetGeneralOutputs(m_handle, outputBits, isOutputBits);
}

CTR_Code CANifier::GetGeneralInputs(CANifier::PinValues &allPins) {
	CTR_Code err = c_CANifier_GetGeneralInputs(m_handle, _tempPins, sizeof(_tempPins));
	allPins.LIMF = _tempPins[LIMF];
	allPins.LIMR = _tempPins[LIMR];
	allPins.QUAD_A = _tempPins[QUAD_A];
	allPins.QUAD_B = _tempPins[QUAD_B];
	allPins.QUAD_IDX = _tempPins[QUAD_IDX];
	allPins.SCL = _tempPins[SCL];
	allPins.SDA = _tempPins[SDA];
	allPins.SPI_CLK_PWM0 = _tempPins[SPI_CLK_PWM0P];
	allPins.SPI_MOSI_PWM1 = _tempPins[SPI_MOSI_PWM1P];
	allPins.SPI_MISO_PWM2 = _tempPins[SPI_MISO_PWM2P];
	allPins.SPI_CS_PWM3 = _tempPins[SPI_CS];
	return err;
}

bool CANifier::GetGeneralInput(GeneralPin inputPin) {
	bool retval = false;
	(void)c_CANifier_GetGeneralInput(m_handle, inputPin, &retval);
	return retval;
}

/**
 * Call GetLastError() to determine success.
 * @return true if specified input is high, false o/w.
 */
CTR_Code CANifier::GetLastError() {
	return c_CANifier_GetLastError(m_handle);
}

CTR_Code CANifier::SetPWMOutput(int pwmChannel, double dutyCycle) {
	if (dutyCycle < 0) {
		dutyCycle = 0;
	} else if (dutyCycle > 1) {
		dutyCycle = 1;
	}
	if (pwmChannel < 0) {
		pwmChannel = 0;
	}

	int dutyCyc10bit = (int) (1023 * dutyCycle);

	return c_CANifier_SetPWMOutput(m_handle, (int) pwmChannel,
			dutyCyc10bit);
}

CTR_Code CANifier::EnablePWMOutput(int pwmChannel, bool bEnable) {
	if (pwmChannel < 0) {
		pwmChannel = 0;
	}

	return c_CANifier_EnablePWMOutput(m_handle, (int) pwmChannel,
			bEnable);
}

CTR_Code CANifier::GetPWMInput(PWMChannel pwmChannel, double dutyCycleAndPeriod[]) {
	return c_CANifier_GetPWMInput(m_handle, pwmChannel,
			dutyCycleAndPeriod);
}

//------ Custom Persistent Params ----------//
ErrorCode CANifier::ConfigSetCustomParam(int newValue,
		int paramIndex, int timeoutMs) {
	return c_CANifier_ConfigSetCustomParam(m_handle, newValue, paramIndex, timeoutMs);
}
int CANifier::ConfigGetCustomParam(
		int paramIndex, int timeoutMs) {
	int readValue;
	c_CANifier_ConfigGetCustomParam(m_handle, &readValue, paramIndex, timeoutMs);
	return readValue;
}

//------ Generic Param API, typically not used ----------//
ErrorCode CANifier::ConfigSetParameter(ParamEnum param, double value,
		uint8_t subValue, int ordinal, int timeoutMs) {
	return c_CANifier_ConfigSetParameter(m_handle, param, value, subValue, ordinal, timeoutMs);

}
double CANifier::ConfigGetParameter(ParamEnum param, int ordinal, int timeoutMs) {
	double value = 0;
	c_CANifier_ConfigGetParameter(m_handle, param, &value, ordinal, timeoutMs);
	return value;
}

}}
#endif // CTR_EXCLUDE_WPILIB_CLASSES
