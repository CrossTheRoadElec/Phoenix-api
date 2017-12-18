package com.ctre.phoenix.motorcontrol;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.motorcontrol.can.BaseMotorController;
import com.ctre.phoenix.motorcontrol.can.MotControllerJNI;

public class SensorCollection {

	private long _handle;

	public SensorCollection(BaseMotorController motorController) {
		_handle = motorController.getHandle();

	}

	/**
	 * Get the position of whatever is in the analog pin of the Talon,
	 * regardless of whether it is actually being used for feedback.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the 24bit analog value. The bottom ten bits is the ADC (0 - 1023)
	 *         on the analog pin of the Talon. The upper 14 bits tracks the
	 *         overflows and underflows (continuous sensor).
	 */

	public int getAnalogIn() {
		return MotControllerJNI.GetAnalogIn(_handle);
	}

	/**
	 * Sets analog position.
	 *
	 * @param newPosition
	 *            The new position.
	 * @param timeoutMs
	 *            (Optional) The timeout in milliseconds.
	 *
	 * @return an ErrorCode.
	 */

	public ErrorCode setAnalogPosition(int newPosition, int timeoutMs) {
		int retval = MotControllerJNI.SetAnalogPosition(_handle, newPosition, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Get the position of whatever is in the analog pin of the Talon,
	 * regardless of whether it is actually being used for feedback.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the ADC (0 - 1023) on analog pin of the Talon.
	 */

	public int getAnalogInRaw() {
		return MotControllerJNI.GetAnalogInRaw(_handle);
	}

	/**
	 * Get the position of whatever is in the analog pin of the Talon,
	 * regardless of whether it is actually being used for feedback.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the value (0 - 1023) on the analog pin of the Talon.
	 */

	public int getAnalogInVel() {
		return MotControllerJNI.GetAnalogInVel(_handle);
	}

	/**
	 * Get the position of whatever is in the analog pin of the Talon,
	 * regardless of whether it is actually being used for feedback.
	 *
	 * @param [out]
	 *            param The value to fill with the Quad pos.
	 *
	 * @return the Error code of the request.
	 */

	public int getQuadraturePosition() {
		return MotControllerJNI.GetQuadraturePosition(_handle);
	}

	/**
	 * Change the quadrature reported position. Typically this is used to "zero"
	 * the sensor. This only works with Quadrature sensor. To set the selected
	 * sensor position regardless of what type it is, see
	 * SetSelectedSensorPosition in the motor controller class.
	 *
	 * @param newPosition
	 *            The position value to apply to the sensor.
	 * @param timeoutMs
	 *            (Optional) How long to wait for confirmation. Pass zero so
	 *            that call does not block.
	 *
	 * @return error code.
	 */

	public ErrorCode setQuadraturePosition(int newPosition, int timeoutMs) {
		int retval = MotControllerJNI.SetQuadraturePosition(_handle, newPosition, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Get the position of whatever is in the analog pin of the Talon,
	 * regardless of whether it is actually being used for feedback.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the value (0 - 1023) on the analog pin of the Talon.
	 */

	public int getQuadratureVelocity() {
		return MotControllerJNI.GetQuadratureVelocity(_handle);
	}

	/**
	 * Gets pulse width position.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the pulse width position.
	 */

	public int getPulseWidthPosition() {
		return MotControllerJNI.GetPulseWidthPosition(_handle);
	}

	/**
	 * Sets pulse width position.
	 *
	 * @param newPosition
	 *            The position value to apply to the sensor.
	 * @param timeoutMs
	 *            (Optional) How long to wait for confirmation. Pass zero so
	 *            that call does not block.
	 *
	 * @return an ErrErrorCode
	 */
	public ErrorCode setPulseWidthPosition(int newPosition, int timeoutMs) {
		int retval = MotControllerJNI.SetPulseWidthPosition(_handle, newPosition, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Gets pulse width velocity.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the pulse width velocity.
	 */

	public int getPulseWidthVelocity() {
		return MotControllerJNI.GetPulseWidthVelocity(_handle);
	}

	/**
	 * Gets pulse width rise to fall us.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the pulse width rise to fall us.
	 */

	public int getPulseWidthRiseToFallUs() {
		return MotControllerJNI.GetPulseWidthRiseToFallUs(_handle);
	}

	/**
	 * Gets pulse width rise to rise us.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the pulse width rise to rise us.
	 */

	public int getPulseWidthRiseToRiseUs() {
		return MotControllerJNI.GetPulseWidthRiseToRiseUs(_handle);
	}

	/**
	 * Gets pin state quad a.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return the pin state quad a.
	 */

	public boolean getPinStateQuadA() {
		return MotControllerJNI.GetPinStateQuadA(_handle) != 0;
	}

	/**
	 * Gets pin state quad b.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return Digital level of QUADB pin.
	 */

	public boolean getPinStateQuadB() {
		return MotControllerJNI.GetPinStateQuadB(_handle) != 0;
	}

	/**
	 * Gets pin state quad index.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return Digital level of QUAD Index pin.
	 */

	public boolean getPinStateQuadIdx() {
		return MotControllerJNI.GetPinStateQuadIdx(_handle) != 0;
	}

	/**
	 * Is forward limit switch closed.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return '1' iff forward limit switch is closed, 0 iff switch is open.
	 *         This function works regardless if limit switch feature is
	 *         enabled.
	 */

	public boolean isFwdLimitSwitchClosed() {
		return MotControllerJNI.IsFwdLimitSwitchClosed(_handle) != 0;
	}

	/**
	 * Is reverse limit switch closed.
	 *
	 * @param [out]
	 *            param The parameter to fill.
	 *
	 * @return '1' iff reverse limit switch is closed, 0 iff switch is open.
	 *         This function works regardless if limit switch feature is
	 *         enabled.
	 */

	public boolean isRevLimitSwitchClosed() {
		return MotControllerJNI.IsRevLimitSwitchClosed(_handle) != 0;
	}
}
