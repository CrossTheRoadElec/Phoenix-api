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

//import edu.wpi.first.wpilibj.hal.HAL;
import com.ctre.phoenix.CANifierConfiguration;
import com.ctre.phoenix.VelocityPeriod;
import com.ctre.phoenix.ErrorCollection;
import com.ctre.phoenix.ParamEnum;

/**
 * CTRE CANifier
 *
 * Device for interfacing common devices to the CAN bus.
 */
public class CANifier {
	private long m_handle;


	
	/**
	 * Enum for the LED Output Channels
	 */
	public enum LEDChannel {
		/**
		 * LED Channel A
		 */
		LEDChannelA(0), 
		/**
		 * LED Channel B
		 */
		LEDChannelB(1), 
		/**
		 * LED Channel C
		 */
		LEDChannelC(2);

		/**
		 * Get the LED Channel from a specified value
		 * @param value integer value to get LEDChannel from
		 * @return LEDChannel of specified value
		 */
		public static LEDChannel valueOf(int value) {
			for (LEDChannel mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}

		/**
		 * Value of LEDChannel
		 */
		public final int value;

		/**
		 * Create LEDChannel from initValue
		 * @param initValue LEDChannel value
		 */
		LEDChannel(int initValue) {
			this.value = initValue;
		}
	}

	/**
	 * Enum for the PWM Input Channels
	 */
	public enum PWMChannel {
		/**
		 * PWM Channel 0
		 */
		PWMChannel0(0), 
		/**
		 * PWM Channel 1
		 */
		PWMChannel1(1), 
		/**
		 * PWM Channel 2
		 */
		PWMChannel2(2), 
		/** 
		 * PWM Channel 3
		 */
		PWMChannel3(3);

		/**
		 * Get the PWM Channel from a specified value
		 * @param value integer value to get pwm channel from
		 * @return PWM Channel of specified value
		 */
		public static PWMChannel valueOf(int value) {
			for (PWMChannel mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}

		/**
		 * Value of PWM Channel
		 */
		public final int value;

		/**
		 * Create a PWM Channel of initValue
		 * @param initValue PWM Channel value
		 */
		PWMChannel(int initValue) {
			this.value = initValue;
		}
	}

	/**
	 * Number of PWM channels available to CANifier
	 */
	public final int PWMChannelCount = 4;

	/**
	 * General IO Pins on the CANifier
	 */
	public enum GeneralPin {
		/**
		 * Quadrature Idx pin
		 */
		QUAD_IDX (CANifierJNI.GeneralPin.QUAD_IDX.value),
		/**
		 * Quadrature B pin
		 */
		QUAD_B (CANifierJNI.GeneralPin.QUAD_B.value),
		/**
		 * Quadrature A pin
		 */
		QUAD_A (CANifierJNI.GeneralPin.QUAD_A.value),
		/**
		 * Reverse limit pin
		 */
		LIMR (CANifierJNI.GeneralPin.LIMR.value),
		/**
		 * Forward limit pin
		 */
		LIMF (CANifierJNI.GeneralPin.LIMF.value),
		/**
		 * SDA pin
		 */
		SDA (CANifierJNI.GeneralPin.SDA.value),
		/**
		 * SCL pin
		 */
		SCL (CANifierJNI.GeneralPin.SCL.value),
		/**
		 * SPI_CS pin
		 */
		SPI_CS (CANifierJNI.GeneralPin.SPI_CS.value),
		/**
		 * SPI_MISO_PWM2 pin
		 */
		SPI_MISO_PWM2P (CANifierJNI.GeneralPin.SPI_MISO_PWM2P.value),
		/**
		 * SPI_MOSI_PWM1 pin
		 */
		SPI_MOSI_PWM1P (CANifierJNI.GeneralPin.SPI_MOSI_PWM1P.value),
		/**
		 * SPI_CLK_PWM0 pin
		 */
		SPI_CLK_PWM0P (CANifierJNI.GeneralPin.SPI_CLK_PWM0P.value);

		/**
		 * Gets the GeneralPin of a specified value
		 * @param value integer value of GeneralPin
		 * @return GeneralPin of specified value
		 */
		public static GeneralPin valueOf(int value) {
			for (GeneralPin mode : values()) {
				if (mode.value == value) {
					return mode;
				}
			}
			return null;
		}

		/**
		 * Value of specified pin
		 */
		public final int value;

		/**
		 * Create GeneralPin of initValue value
		 * @param initValue Value of Pin
		 */
		GeneralPin(int initValue) {
			this.value = initValue;
		}
	}

	/**
	 * Class to hold the pin values.
	 */
	public static class PinValues {
		/**
		 * Quadrature Idx pin
		 */
		public boolean QUAD_IDX;
		/**
		 * Quadrature B pin
		 */
		public boolean QUAD_B;
		/**
		 * Quadrature A pin
		 */
		public boolean QUAD_A;
		/**
		 * Reverse limit pin
		 */
		public boolean LIMR;
		/**
		 * Forward limit pin
		 */
		public boolean LIMF;
		/**
		 * SDA pin
		 */
		public boolean SDA;
		/**
		 * SCL pin
		 */
		public boolean SCL;
		/**
		 * SPI_CS_PWM3 pin
		 */
		public boolean SPI_CS_PWM3;
		/**
		 * SPI_MISO_PWM2 pin
		 */
		public boolean SPI_MISO_PWM2;
		/**
		 * SPI_MOSI_PWM1 pin
		 */
		public boolean SPI_MOSI_PWM1;
		/**
		 * SPI_CLK_PWM0 pin
		 */
		public boolean SPI_CLK_PWM0;
	}

	private boolean[] _tempPins = new boolean[11];

	private int m_deviceNumber;
	/**
	 * Constructor.
	 * @param deviceId	The CAN Device ID of the CANifier.
	 */
	public CANifier(int deviceId) {
		m_handle = CANifierJNI.JNI_new_CANifier(deviceId);
		m_deviceNumber = deviceId;
	}

	/**
	 * Destructor
	 * @return Error Code generated by function. 0 indicates no error.
	 */
    public ErrorCode DestroyObject() {
        return ErrorCode.valueOf(CANifierJNI.JNI_destroy_CANifier(m_handle));
    }

	/**
	 * Sets the LED Output
	 * @param percentOutput Output duty cycle expressed as percentage.
	 * @param ledChannel 		Channel to set the output of.
	 */
	public void setLEDOutput(double percentOutput, LEDChannel ledChannel) {
		/* convert float to integral fixed pt */
		if (percentOutput > 1) {
			percentOutput = 1;
		}
		if (percentOutput < 0) {
			percentOutput = 0;
		}
		int dutyCycle = (int) (percentOutput * 1023); // [0,1023]

		CANifierJNI.JNI_SetLEDOutput(m_handle, dutyCycle, ledChannel.value);
	}

	/**
	 * Sets the output of a General Pin
	 * @param outputPin 		The pin to use as output.
	 * @param outputValue 	The desired output state.
	 * @param outputEnable	Whether this pin is an output. "True" enables output.
	 */
	public void setGeneralOutput(GeneralPin outputPin, boolean outputValue, boolean outputEnable) {
		CANifierJNI.JNI_SetGeneralOutput(m_handle, outputPin.value, outputValue, outputEnable);
	}

	/**
	 * Sets the output of all General Pins
	 * @param outputBits 	A bit mask of all the output states.  LSB->MSB is in the order of the com.ctre.phoenix.CANifier.GeneralPin enum.
	 * @param isOutputBits A boolean bit mask that sets the pins to be outputs or inputs.  A bit of 1 enables output.
	 */
	public void setGeneralOutputs(int outputBits, int isOutputBits) {
		CANifierJNI.JNI_SetGeneralOutputs(m_handle, outputBits, isOutputBits);
	}

	/**
	 * Gets the state of all General Pins
	 * @param allPins A structure to fill with the current state of all pins.
	 */
	public void getGeneralInputs(PinValues allPins) {
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

	/**
	 * Gets the state of the specified pin
	 * @param inputPin  The index of the pin.
	 * @return The state of the pin.
	 */
	public boolean getGeneralInput(GeneralPin inputPin) {
		return CANifierJNI.JNI_GetGeneralInput(m_handle, inputPin.value);
	}

	/**
	 * Call GetLastError() generated by this object.
	 * Not all functions return an error code but can
	 * potentially report errors.
	 *
	 * This function can be used to retrieve those error codes.
	 *
	 * @return The last ErrorCode generated.
	 */
	public ErrorCode getLastError() {
		int retval = CANifierJNI.JNI_GetLastError(m_handle);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Sets the PWM Output
	 * Currently supports PWM 0, PWM 1, and PWM 2
	 * @param pwmChannel  Index of the PWM channel to output.
	 * @param dutyCycle   Duty Cycle (0 to 1) to output.  Default period of the signal is 4.2 ms.
	 */
	public void setPWMOutput(int pwmChannel, double dutyCycle) {
		if (dutyCycle < 0) {
			dutyCycle = 0;
		} else if (dutyCycle > 1) {
			dutyCycle = 1;
		}
		if (pwmChannel < 0) {
			pwmChannel = 0;
		}

		int dutyCyc10bit = (int) (1023 * dutyCycle);

		CANifierJNI.JNI_SetPWMOutput(m_handle, (int) pwmChannel, dutyCyc10bit);
	}

	/**
	 * Enables PWM Outputs
	 * Currently supports PWM 0, PWM 1, and PWM 2
	 * @param pwmChannel  Index of the PWM channel to enable.
	 * @param bEnable			"True" enables output on the pwm channel.
	 */
	public void enablePWMOutput(int pwmChannel, boolean bEnable) {
		if (pwmChannel < 0) {
			pwmChannel = 0;
		}

		CANifierJNI.JNI_EnablePWMOutput(m_handle, (int) pwmChannel, bEnable);
	}

	/**
	 * Gets the PWM Input
	 * @param pwmChannel  PWM channel to get.
	 * @param pulseWidthAndPeriod	Double array to hold Duty Cycle [0] and Period [1].
	 */
	public void getPWMInput(PWMChannel pwmChannel, double[] pulseWidthAndPeriod) {
		CANifierJNI.JNI_GetPWMInput(m_handle, pwmChannel.value, pulseWidthAndPeriod);
	}
	
	/**
	 * Gets the quadrature encoder's position
	 * @return Position of encoder 
	 */
	public int getQuadraturePosition() {
		return CANifierJNI.JNI_GetQuadraturePosition(m_handle);
	}
	
	/**
	 * Sets the quadrature encoder's position
	 * @param newPosition  Position to set
	 * @param timeoutMs  
					Timeout value in ms. If nonzero, function will wait for
					config success and report an error if it times out.
					If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setQuadraturePosition(int newPosition, int timeoutMs) {
		return ErrorCode.valueOf(CANifierJNI.JNI_SetQuadraturePosition(m_handle, newPosition, timeoutMs));
	}
	
	/**
	 * Gets the quadrature encoder's velocity
	 * @return Velocity of encoder
	 */
	public int getQuadratureVelocity() {
		return CANifierJNI.JNI_GetQuadratureVelocity(m_handle);
	}
	
	/**
	 * Configures the period of each velocity sample.
	 * Every 1ms a position value is sampled, and the delta between that sample
	 * and the position sampled kPeriod ms ago is inserted into a filter.
	 * kPeriod is configured with this function.
	 *
	 * @param period
	 *            Desired period for the velocity measurement. @see
	 *            com.ctre.phoenix.motorcontrol.VelocityMeasPeriod
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVelocityMeasurementPeriod(VelocityPeriod period, int timeoutMs) {
		int retval = CANifierJNI.JNI_ConfigVelocityMeasurementPeriod(m_handle, period.value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	/**
	 * Configures the period of each velocity sample.
	 * Every 1ms a position value is sampled, and the delta between that sample
	 * and the position sampled kPeriod ms ago is inserted into a filter.
	 * kPeriod is configured with this function.
	 *
	 * @param period
	 *            Desired period for the velocity measurement. @see
	 *            com.ctre.phoenix.motorcontrol.VelocityMeasPeriod
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVelocityMeasurementPeriod(VelocityPeriod period) {
		int timeoutMs = 0;
		return configVelocityMeasurementPeriod(period, timeoutMs);	
	}
	
	/**
	 * Sets the number of velocity samples used in the rolling average velocity
	 * measurement.
	 *
	 * @param windowSize
	 *            Number of samples in the rolling average of velocity
	 *            measurement. Valid values are 1,2,4,8,16,32. If another
	 *            value is specified, it will truncate to nearest support value.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVelocityMeasurementWindow(int windowSize, int timeoutMs) {
		int retval = CANifierJNI.JNI_ConfigVelocityMeasurementWindow(m_handle, windowSize, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	/**
	 * Sets the number of velocity samples used in the rolling average velocity
	 * measurement.
	 *
	 * @param windowSize
	 *            Number of samples in the rolling average of velocity
	 *            measurement. Valid values are 1,2,4,8,16,32. If another
	 *            value is specified, it will truncate to nearest support value.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVelocityMeasurementWindow(int windowSize) {
		int timeoutMs = 0;
		return configVelocityMeasurementWindow( windowSize,  timeoutMs);
	}

    /**
     * Enables clearing the position of the feedback sensor when the forward 
     * limit switch is triggered
     *
     * @param clearPositionOnLimitF     Whether clearing is enabled, defaults false
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configClearPositionOnLimitF(boolean clearPositionOnLimitF, int timeoutMs) {
        int retval = CANifierJNI.JNI_ConfigClearPositionOnLimitF(m_handle, clearPositionOnLimitF, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    /**
     * Enables clearing the position of the feedback sensor when the reverse 
     * limit switch is triggered
     *
     * @param clearPositionOnLimitR     Whether clearing is enabled, defaults false
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configClearPositionOnLimitR(boolean clearPositionOnLimitR, int timeoutMs) {
        int retval = CANifierJNI.JNI_ConfigClearPositionOnLimitR(m_handle, clearPositionOnLimitR, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    /**
     * Enables clearing the position of the feedback sensor when the quadrature index signal
     * is detected
     *
     * @param clearPositionOnQuadIdx    Whether clearing is enabled, defaults false
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configClearPositionOnQuadIdx(boolean clearPositionOnQuadIdx, int timeoutMs) {
        int retval = CANifierJNI.JNI_ConfigClearPositionOnQuadIdx(m_handle, clearPositionOnQuadIdx, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
	/**
	 * Sets the value of a custom parameter. This is for arbitrary use.
     *
     * Sometimes it is necessary to save calibration/duty cycle/output
     * information in the device. Particularly if the
     * device is part of a subsystem that can be replaced.
	 *
	 * @param newValue
	 *            Value for custom parameter.
	 * @param paramIndex
	 *            Index of custom parameter. [0-1]
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetCustomParam(int newValue, int paramIndex, int timeoutMs) {
		int retval = CANifierJNI.JNI_ConfigSetCustomParam(m_handle, newValue, paramIndex, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	/**
	 * Sets the value of a custom parameter. This is for arbitrary use.
     *
     * Sometimes it is necessary to save calibration/duty cycle/output
     * information in the device. Particularly if the
     * device is part of a subsystem that can be replaced.
	 *
	 * @param newValue
	 *            Value for custom parameter.
	 * @param paramIndex
	 *            Index of custom parameter. [0-1]
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetCustomParam(int newValue, int paramIndex) {

		int timeoutMs = 0;
		return configSetCustomParam( newValue,  paramIndex,  timeoutMs);
	}

	/**
	 * Gets the value of a custom parameter. This is for arbitrary use.
     *
     * Sometimes it is necessary to save calibration/duty cycle/output
     * information in the device. Particularly if the
     * device is part of a subsystem that can be replaced.
	 *
	 * @param paramIndex
	 *            Index of custom parameter. [0-1]
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Value of the custom param.
	 */
	public int configGetCustomParam(int paramIndex, int timeoutMs) {
		int retval = CANifierJNI.JNI_ConfigGetCustomParam(m_handle, paramIndex, timeoutMs);
		return retval;
	}
	/**
	 * Gets the value of a custom parameter. This is for arbitrary use.
     *
     * Sometimes it is necessary to save calibration/duty cycle/output
     * information in the device. Particularly if the
     * device is part of a subsystem that can be replaced.
	 *
	 * @param paramIndex
	 *            Index of custom parameter. [0-1]
	 * @return Value of the custom param.
	 */
	public int configGetCustomParam(int paramIndex) {
		int timeoutMs = 0;
		return configGetCustomParam( paramIndex,  timeoutMs);
	}

	/**
	 * Sets a parameter. Generally this is not used.
     * This can be utilized in
     * - Using new features without updating API installation.
     * - Errata workarounds to circumvent API implementation.
     * - Allows for rapid testing / unit testing of firmware.
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
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetParameter(ParamEnum param, double value, int subValue, int ordinal, int timeoutMs) {
		return configSetParameter(param.value, value, subValue, ordinal, timeoutMs);
	}
	/**
	 * Sets a parameter. Generally this is not used.
     * This can be utilized in
     * - Using new features without updating API installation.
     * - Errata workarounds to circumvent API implementation.
     * - Allows for rapid testing / unit testing of firmware.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param value
	 *            Value of parameter.
	 * @param subValue
	 *            Subvalue for parameter. Maximum value of 255.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetParameter(ParamEnum param, double value, int subValue, int ordinal) {
		int timeoutMs = 0;
		return configSetParameter(param, value, subValue, ordinal, timeoutMs);
	}

	/**
	 * Sets a parameter. Generally this is not used.
     * This can be utilized in
     * - Using new features without updating API installation.
     * - Errata workarounds to circumvent API implementation.
     * - Allows for rapid testing / unit testing of firmware.
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
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetParameter(int param, double value, int subValue, int ordinal, int timeoutMs) {
		int retval = CANifierJNI.JNI_ConfigSetParameter(m_handle, param, value, subValue, ordinal,
				timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	/**
	 * Sets a parameter. Generally this is not used.
     * This can be utilized in
     * - Using new features without updating API installation.
     * - Errata workarounds to circumvent API implementation.
     * - Allows for rapid testing / unit testing of firmware.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param value
	 *            Value of parameter.
	 * @param subValue
	 *            Subvalue for parameter. Maximum value of 255.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetParameter(int param, double value, int subValue, int ordinal) {
		int timeoutMs = 0;
		return configSetParameter( param,  value,  subValue,  ordinal,  timeoutMs);
	}
	/**
	 * Gets a parameter. Generally this is not used.
     * This can be utilized in
     * - Using new features without updating API installation.
     * - Errata workarounds to circumvent API implementation.
     * - Allows for rapid testing / unit testing of firmware.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Value of parameter.
	 */
	public double configGetParameter(ParamEnum param, int ordinal, int timeoutMs) {
		return CANifierJNI.JNI_ConfigGetParameter(m_handle, param.value, ordinal, timeoutMs);
	}
	/**
	 * Gets a parameter. Generally this is not used.
     * This can be utilized in
     * - Using new features without updating API installation.
     * - Errata workarounds to circumvent API implementation.
     * - Allows for rapid testing / unit testing of firmware.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @return Value of parameter.
	 */
	public double configGetParameter(ParamEnum param, int ordinal) {
		int timeoutMs = 0;
		return configGetParameter(param,  ordinal,  timeoutMs);
	}
	/**
	 * Sets the period of the given status frame.
	 *
	 * @param statusFrame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setStatusFramePeriod(CANifierStatusFrame statusFrame, int periodMs, int timeoutMs) {
		int retval = CANifierJNI.JNI_SetStatusFramePeriod(m_handle, statusFrame.value, periodMs, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	/**
	 * Sets the period of the given status frame.
	 *
	 * @param statusFrame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setStatusFramePeriod(CANifierStatusFrame statusFrame, int periodMs) {
		int timeoutMs = 0;
		return setStatusFramePeriod(statusFrame,  periodMs,  timeoutMs);
	}
	/**
	 * Sets the period of the given status frame.
	 *
	 * @param statusFrame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setStatusFramePeriod(int statusFrame, int periodMs, int timeoutMs) {
		int retval = CANifierJNI.JNI_SetStatusFramePeriod(m_handle, statusFrame, periodMs, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	/**
	 * Sets the period of the given status frame.
	 *
	 * @param statusFrame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setStatusFramePeriod(int statusFrame, int periodMs) {
		int timeoutMs = 0;
		return setStatusFramePeriod( statusFrame,  periodMs,  timeoutMs);
	}

	/**
	 * Gets the period of the given status frame.
	 *
	 * @param frame
	 *            Frame to get the period of.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 * @return Period of the given status frame.
	 */
	public int getStatusFramePeriod(CANifierStatusFrame frame, int timeoutMs) {
		return CANifierJNI.JNI_GetStatusFramePeriod(m_handle, frame.value, timeoutMs);
	}
	/**
	 * Gets the period of the given status frame.
	 *
	 * @param frame
	 *            Frame to get the period of.
	 * @return Period of the given status frame.
	 */
	public int getStatusFramePeriod(CANifierStatusFrame frame) {
		int timeoutMs = 0;
		return getStatusFramePeriod(frame, timeoutMs);	
	}

	/**
	 * Sets the period of the given control frame.
	 *
	 * @param frame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setControlFramePeriod(CANifierControlFrame frame, int periodMs) {
		int retval = CANifierJNI.JNI_SetControlFramePeriod(m_handle, frame.value, periodMs);
		return ErrorCode.valueOf(retval);
	}
	/**
	 * Sets the period of the given control frame.
	 *
	 * @param frame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setControlFramePeriod(int frame, int periodMs) {
		int retval = CANifierJNI.JNI_SetControlFramePeriod(m_handle, frame, periodMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Gets the firmware version of the device.
	 *
	 * @return Firmware version of device.
	 */
	public int getFirmwareVersion() {
		return CANifierJNI.JNI_GetFirmwareVersion(m_handle);
	}

	/**
	 * Returns true if the device has reset since last call.
	 *
	 * @return Has a Device Reset Occurred?
	 */
	public boolean hasResetOccurred() {
		return CANifierJNI.JNI_HasResetOccurred(m_handle);
	}

	// ------ Faults ----------//
	/**
	 * Gets the CANifier fault status
	 *
	 * @param toFill
	 *            Container for fault statuses.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode getFaults(CANifierFaults toFill) {
		int bits = CANifierJNI.JNI_GetFaults(m_handle);
		toFill.update(bits);
		return getLastError();
	}
	/**
	 * Gets the CANifier sticky fault status
	 *
	 * @param toFill
	 *            Container for sticky fault statuses.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode getStickyFaults(CANifierStickyFaults toFill) {
		int bits = CANifierJNI.JNI_GetStickyFaults(m_handle);
		toFill.update(bits);
		return getLastError();
	}
	/**
	 * Clears the Sticky Faults
	 * 
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
	 *
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode clearStickyFaults(int timeoutMs) {
		int retval = CANifierJNI.JNI_ClearStickyFaults(m_handle, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Gets the bus voltage seen by the device.
	 *
	 * @return The bus voltage value (in volts).
	 */
	public double getBusVoltage() {
		return CANifierJNI.JNI_GetBusVoltage(m_handle);
	}

	/**
	 * @return The Device Number
	 */
	public int getDeviceID(){
		return m_deviceNumber;
	}

	//------ All Configs ----------//
    /**
     * Configures all peristant settings.
     *
	 * @param allConfigs        Object with all of the persistant settings
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
	public ErrorCode configAllSettings(CANifierConfiguration allConfigs, int timeoutMs) {
        ErrorCollection errorCollection = new ErrorCollection();
		
		errorCollection.NewError(configFactoryDefault(timeoutMs));
		
		if(CANifierConfigUtil.velocityMeasurementPeriodDifferent(allConfigs)) errorCollection.NewError(configVelocityMeasurementPeriod(allConfigs.velocityMeasurementPeriod, timeoutMs));
		if(CANifierConfigUtil.velocityMeasurementWindowDifferent(allConfigs)) errorCollection.NewError(configVelocityMeasurementWindow(allConfigs.velocityMeasurementWindow, timeoutMs));
		if(CANifierConfigUtil.clearPositionOnLimitFDifferent(allConfigs)) errorCollection.NewError(configClearPositionOnLimitF(allConfigs.clearPositionOnLimitF, timeoutMs));
		if(CANifierConfigUtil.clearPositionOnLimitRDifferent(allConfigs)) errorCollection.NewError(configClearPositionOnLimitR(allConfigs.clearPositionOnLimitR, timeoutMs));
		if(CANifierConfigUtil.clearPositionOnQuadIdxDifferent(allConfigs)) errorCollection.NewError(configClearPositionOnQuadIdx(allConfigs.clearPositionOnQuadIdx, timeoutMs));

		//Custom Parameters
		if(CustomParamConfigUtil.customParam0Different(allConfigs)) errorCollection.NewError(configSetCustomParam(allConfigs.customParam0, 0, timeoutMs));
		if(CustomParamConfigUtil.customParam1Different(allConfigs)) errorCollection.NewError(configSetCustomParam(allConfigs.customParam1, 1, timeoutMs));
        
    
        return errorCollection._worstError;

	}
    /**
     * Configures all peristant settings (overloaded so timeoutMs is 50 ms).
     *
	 * @param allConfigs        Object with all of the persistant settings
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
	public ErrorCode configAllSettings(CANifierConfiguration allConfigs) {
		int timeoutMs = 50;
		return configAllSettings(allConfigs, timeoutMs);
	}
    /**
     * Gets all persistant settings.
     *
	 * @param allConfigs        Object with all of the persistant settings
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     */
    public void getAllConfigs(CANifierConfiguration allConfigs, int timeoutMs) {

        allConfigs.velocityMeasurementPeriod = VelocityPeriod.valueOf( (int) configGetParameter(ParamEnum.eSampleVelocityPeriod, 0,  timeoutMs));
        allConfigs.velocityMeasurementWindow = (int) configGetParameter(ParamEnum.eSampleVelocityWindow, 0,  timeoutMs);
        allConfigs.clearPositionOnLimitF  = configGetParameter(ParamEnum.eClearPositionOnLimitF, 0, timeoutMs) != 0.0;
        allConfigs.clearPositionOnLimitR  = configGetParameter(ParamEnum.eClearPositionOnLimitR, 0, timeoutMs) != 0.0;
        allConfigs.clearPositionOnQuadIdx = configGetParameter(ParamEnum.eClearPositionOnQuadIdx, 0, timeoutMs) != 0.0;
        allConfigs.customParam0 = (int) configGetParameter(ParamEnum.eCustomParam, 0,  timeoutMs);
        allConfigs.customParam1 = (int) configGetParameter(ParamEnum.eCustomParam, 1,  timeoutMs);
    }
    /**
     * Gets all persistant settings (overloaded so timeoutMs is 50 ms).
     *
	 * @param allConfigs        Object with all of the persistant settings
     */
    public void getAllConfigs(CANifierConfiguration allConfigs) {
        int timeoutMs = 50;
        getAllConfigs(allConfigs, timeoutMs);
    }
    /**
     * Configures all peristant settings to defaults.
     *
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
	public ErrorCode configFactoryDefault(int timeoutMs) {
	    return ErrorCode.valueOf(CANifierJNI.JNI_ConfigFactoryDefault(m_handle, timeoutMs));
	}
    /**
     * Configures all peristant settings to defaults (overloaded so timeoutMs is 50 ms).
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
	public ErrorCode configFactoryDefault() {
		int timeoutMs = 50;	
		return configFactoryDefault( timeoutMs);
	}


}
