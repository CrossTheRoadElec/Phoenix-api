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
#include "../core/ctre.h"
#include <FRC_NetworkCommunication/CANSessionMux.h>  //CAN Comm
#include <map>

/** 
 * CANifier Class.
 * Class supports communicating over CANbus.
 */
class LowLevelCANifier : public Device_LowLevel {

public:
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
	
	
	explicit LowLevelCANifier(int deviceNumber = 0);

	CTR_Code SetLEDOutput( int  dutyCycle,  int  ledChannel);
	CTR_Code SetGeneralOutputs( int  outputsBits,  int  isOutputBits);
	CTR_Code SetGeneralOutput(GeneralPin outputPin, bool bOutputValue, bool bOutputEnable);
	CTR_Code SetPWMOutput( int  pwmChannel,  int  dutyCycle);
	CTR_Code EnablePWMOutput( int  pwmChannel,  bool  bEnable);
	CTR_Code GetGeneralInputs(bool allPins[], uint32_t capacity);
	CTR_Code GetGeneralInput(GeneralPin inputPin, bool * measuredInput);
	CTR_Code GetPWMInput( int  pwmChannel,  double dutyCycleAndPeriod[2]);
	CTR_Code GetLastError();
	CTR_Code GetBatteryVoltage(double * batteryVoltage);
	CTR_Code SetLastError(CTR_Code error);


	const static int kMinFirmwareVersionMajor = 0;
	const static int kMinFirmwareVersionMinor = 40;

private:

	static const int kDefaultControlPeriodMs = 20;
	static const int kDefaultPwmOutputPeriodMs = 20;

	bool _SendingPwmOutput = false;

    uint32_t _regInput = 0; //!< Decoded inputs
    uint32_t _regLat = 0; //!< Decoded output latch
    uint32_t _regIsOutput = 0; //!< Decoded data direction register

	CTR_Code _lastError = OKAY;

	void CheckFirm(int minMajor = kMinFirmwareVersionMajor, int minMinor = kMinFirmwareVersionMinor);
	void EnsurePwmOutputFrameIsTransmitting();
	void EnableFirmStatusFrame(bool enable);
};

