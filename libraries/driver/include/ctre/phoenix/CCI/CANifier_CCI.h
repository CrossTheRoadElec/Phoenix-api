#pragma once

#include "ctre/Phoenix/core/ErrorCode.h"
#include <set>

namespace CANifier_CCI{
	enum GeneralPin{
	QUAD_IDX = 0,
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
}

extern "C"{
	void *c_CANifier_Create1(int deviceNumber);
	CTR_Code c_CANifier_SetLEDOutput(void *handle,  uint32_t  dutyCycle,  uint32_t  ledChannel);
	CTR_Code c_CANifier_SetGeneralOutputs(void *handle,  uint32_t  outputsBits,  uint32_t  isOutputBits);
	CTR_Code c_CANifier_SetGeneralOutput(void *handle,  uint32_t  outputPin,  bool  outputValue,  bool  outputEnable);
	CTR_Code c_CANifier_SetPWMOutput(void *handle,  uint32_t  pwmChannel,  uint32_t  dutyCycle);
	CTR_Code c_CANifier_EnablePWMOutput(void *handle, uint32_t pwmChannel, bool bEnable);
	CTR_Code c_CANifier_GetGeneralInputs(void *handle, bool allPins[], uint32_t capacity);
	CTR_Code c_CANifier_GetGeneralInput(void *handle, uint32_t inputPin, bool * measuredInput);
	CTR_Code c_CANifier_GetPWMInput(void *handle,  uint32_t  pwmChannel,  double dutyCycleAndPeriod [2]);
	CTR_Code c_CANifier_GetLastError(void *handle);
	CTR_Code c_CANifier_GetBatteryVoltage(void *handle, double * batteryVoltage);
	void c_CANifier_SetLastError(void *handle, int error);
	CTR_Code c_CANifier_ConfigSetParameter(void *handle, int param, double value, int subValue, int ordinal, int timeoutMs);
	CTR_Code c_CANifier_ConfigGetParameter(void *handle, int param, double *value, int ordinal, int timeoutMs);
	CTR_Code c_CANifier_ConfigSetCustomParam(void *handle, int newValue, int paramIndex, int timeoutMs);
	CTR_Code c_CANifier_ConfigGetCustomParam(void *handle, int *readValue, int paramIndex, int timoutMs);
}
