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
 
 package com.ctre.phoenix;
 
 
 public class CANifier
 {
	private long m_handle;
	 
	public enum LEDChannel
	{
		LEDChannelA(0),
		LEDChannelB(1),
		LEDChannelC(2);
		public static LEDChannel valueOf(int value) {
			for (LEDChannel mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}
		public int value; LEDChannel(int value) { this.value = value; } 
	}

	public enum PWMChannel
	{
		PWMChannel0(0),
		PWMChannel1(1),
		PWMChannel2(2),
		PWMChannel3(3);
		public static PWMChannel valueOf(int value) {
			for (PWMChannel mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}
		public int value; PWMChannel(int value) { this.value = value; } 
	}
	
	public final int PWMChannelCount = 4;
	
	public enum GeneralPin
	{
		QUAD_IDX (CANifierJNI.GeneralPin.QUAD_IDX.value),
		QUAD_B (CANifierJNI.GeneralPin.QUAD_B.value),
		QUAD_A (CANifierJNI.GeneralPin.QUAD_A.value),
		LIMR (CANifierJNI.GeneralPin.LIMR.value),
		LIMF (CANifierJNI.GeneralPin.LIMF.value),
		SDA (CANifierJNI.GeneralPin.SDA.value),
		SCL (CANifierJNI.GeneralPin.SCL.value),
		SPI_CS (CANifierJNI.GeneralPin.SPI_CS.value),
		SPI_MISO_PWM2P (CANifierJNI.GeneralPin.SPI_MISO_PWM2P.value),
		SPI_MOSI_PWM1P (CANifierJNI.GeneralPin.SPI_MOSI_PWM1P.value),
		SPI_CLK_PWM0P (CANifierJNI.GeneralPin.SPI_CLK_PWM0P.value);
		public static GeneralPin valueOf(int value) {
			for (GeneralPin mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}
		public int value; GeneralPin(int value) { this.value = value; } 
	}
	
	public static class PinValues
	{
		public boolean QUAD_IDX;
		public boolean QUAD_B;
		public boolean QUAD_A;
		public boolean LIMR;
		public boolean LIMF;
		public boolean SDA;
		public boolean SCL;
		public boolean SPI_CS_PWM3;
		public boolean SPI_MISO_PWM2;
		public boolean SPI_MOSI_PWM1;
		public boolean SPI_CLK_PWM0;
	}

	public enum StatusFrameRate
	{
		Status1_General (0),
		Status2_General (1),
		Status3_PwmInput0 (2),
		Status4_PwmInput1 (3),
		Status5_PwmInput2 (4),
		Status6_PwmInput3 (5);
		public static StatusFrameRate valueOf(int value) {
			for (StatusFrameRate mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}
		public int value; StatusFrameRate(int value) { this.value = value; } 
	}
	
	private boolean[] _tempPins = new boolean[11];
	
	public CANifier(int deviceId)
	{
		m_handle = CANifierJNI.JNI_new_CANifier(deviceId);
	}
	
	public void SetLEDOutput(double percentOutput, LEDChannel ledChannel)
	{
		/* convert float to integral fixed pt */
		if (percentOutput > 1) { percentOutput = 1; }
		if (percentOutput < 0) { percentOutput = 0; }
		int dutyCycle = (int)(percentOutput * 1023); // [0,1023]

		CANifierJNI.JNI_SetLEDOutput(m_handle, dutyCycle, ledChannel.value);
	}
	
	public void SetGeneralOutput(GeneralPin outputPin, boolean outputValue, boolean outputEnable)
	{
		CANifierJNI.JNI_SetGeneralOutput(m_handle, outputPin.value, outputValue, outputEnable);
	}
	
	public void SetGeneralOutputs(int outputBits, int isOutputBits)
	{
		CANifierJNI.JNI_SetGeneralOutputs(m_handle, outputBits, isOutputBits);
	}
	
	public void GetGeneralInputs(PinValues allPins)
	{
		CANifierJNI.JNI_GetGeneralInputs(m_handle, _tempPins);
		allPins.LIMF = _tempPins[GeneralPin.LIMF.value];
		allPins.LIMR = _tempPins[GeneralPin.LIMR.value];
		allPins.QUAD_A = _tempPins[GeneralPin.QUAD_A.value];
		allPins.QUAD_B = _tempPins[GeneralPin.QUAD_B.value];
		allPins.QUAD_IDX = _tempPins[GeneralPin.QUAD_IDX.value];
		allPins.SCL = _tempPins[GeneralPin.SCL.value];
		allPins.SDA = _tempPins[GeneralPin.SDA.value];
		allPins.SPI_CLK_PWM0 = _tempPins[GeneralPin.SPI_CLK_PWM0P.value];
		allPins.SPI_MOSI_PWM1 = _tempPins[GeneralPin.SPI_MOSI_PWM1P.value];
		allPins.SPI_MISO_PWM2 = _tempPins[GeneralPin.SPI_MISO_PWM2P.value];
		allPins.SPI_CS_PWM3 = _tempPins[GeneralPin.SPI_CS.value];
	}
	
	public boolean GetGeneralInput(GeneralPin inputPin)
	{
		return CANifierJNI.JNI_GetGeneralInput(m_handle, inputPin.value);
	}
	
	/**
	 * Call GetLastError() to determine success.
	 * @return true if specified input is high, false o/w.  
	 */
	public int GetLastError()
	{
		return CANifierJNI.JNI_GetLastError(m_handle);
	}
	
	public void SetPWMOutput(int pwmChannel, float dutyCycle)
	{
		if (dutyCycle < 0) { dutyCycle = 0; } else if(dutyCycle > 1) { dutyCycle = 1; }
		if(pwmChannel < 0) { pwmChannel = 0;}

		int dutyCyc10bit = (int)(1023 * dutyCycle);

		CANifierJNI.JNI_SetPWMOutput(m_handle, (int)pwmChannel, dutyCyc10bit);
	}

	public void EnablePWMOutput(int pwmChannel, boolean bEnable)
	{
		if(pwmChannel < 0) { pwmChannel = 0;}

		CANifierJNI.JNI_EnablePWMOutput(m_handle, (int)pwmChannel, bEnable);
	}
	
	public void GetPWMInput(PWMChannel pwmChannel, float[] dutyCycleAndPeriod)
	{
		CANifierJNI.JNI_GetPWMInput(m_handle, pwmChannel.value, dutyCycleAndPeriod);
	}
 }