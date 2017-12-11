#include "ctre/phoenix/MotorControl/SensorCollection.h"
#include "ctre/phoenix/CCI/MotController_CCI.h"

using namespace ctre::phoenix::motorcontrol;

SensorCollection::SensorCollection(void * handle) {
	_handle = handle;
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 *   whether it is actually being used for feedback.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the 24bit analog value.  The bottom ten bits is the ADC (0 - 1023)
 *          on the analog pin of the Talon. The upper 14 bits tracks the overflows and underflows
 *          (continuous sensor).
 */

int SensorCollection::GetAnalogIn() {
	int retval = 0;
	c_MotController_GetAnalogIn(_handle, &retval);
	return retval;
}

/**
 * Sets analog position.
 *
 * @param   newPosition The new position.
 * @param   timeoutMs   (Optional) The timeout in milliseconds.
 *
 * @return  an ErrorCode.
 */

ErrorCode SensorCollection::SetAnalogPosition(int newPosition, int timeoutMs) {
	return c_MotController_SetAnalogPosition(_handle, newPosition, timeoutMs);
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of whether
 *   it is actually being used for feedback.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the ADC (0 - 1023) on analog pin of the Talon.
 */

int SensorCollection::GetAnalogInRaw() {
	int retval = 0;
	c_MotController_GetAnalogInRaw(_handle, &retval);
	return retval;
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 *   whether it is actually being used for feedback.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the value (0 - 1023) on the analog pin of the Talon.
 */

int SensorCollection::GetAnalogInVel() {
	int retval = 0;
	c_MotController_GetAnalogInVel(_handle, &retval);
	return retval;
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of whether
 *   it is actually being used for feedback.
 *
 * @param [out] param   The value to fill with the Quad pos.
 *
 * @return  the Error code of the request.
 */

int SensorCollection::GetQuadraturePosition() {
	int retval = 0;
	c_MotController_GetQuadraturePosition(_handle, &retval);
	return retval;
}

/**
 * Change the quadrature reported position.  Typically this is used to "zero" the
 *   sensor. This only works with Quadrature sensor.  To set the selected sensor position
 *   regardless of what type it is, see SetSelectedSensorPosition in the motor controller class.
 *
 * @param   newPosition The position value to apply to the sensor.
 * @param   timeoutMs   (Optional) How long to wait for confirmation.  Pass zero so that call
 *                      does not block.
 *
 * @return  error code.
 */

ErrorCode SensorCollection::SetQuadraturePosition(int newPosition,
		int timeoutMs) {
	return c_MotController_SetQuadraturePosition(_handle, newPosition,
			timeoutMs);
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of whether
 *   it is actually being used for feedback.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the value (0 - 1023) on the analog pin of the Talon.
 */

int SensorCollection::GetQuadratureVelocity() {
	int retval = 0;
	c_MotController_GetQuadratureVelocity(_handle, &retval);
	return retval;
}

/**
 * Gets pulse width position.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the pulse width position.
 */

int SensorCollection::GetPulseWidthPosition() {
	int retval = 0;
	c_MotController_GetPulseWidthPosition(_handle, &retval);
	return retval;
}

/**
 * Sets pulse width position.
 *
 * @param   newPosition The position value to apply to the sensor.
 * @param   timeoutMs   (Optional) How long to wait for confirmation.  Pass zero so that call
 *                      does not block.
 *
 * @return  an ErrErrorCode
 */
ErrorCode SensorCollection::SetPulseWidthPosition(int newPosition,
		int timeoutMs) {
	return c_MotController_SetPulseWidthPosition(_handle, newPosition,
			timeoutMs);
}

/**
 * Gets pulse width velocity.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the pulse width velocity.
 */

int SensorCollection::GetPulseWidthVelocity() {
	int retval = 0;
	c_MotController_GetPulseWidthVelocity(_handle, &retval);
	return retval;
}

/**
 * Gets pulse width rise to fall us.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the pulse width rise to fall us.
 */

int SensorCollection::GetPulseWidthRiseToFallUs() {
	int retval = 0;
	c_MotController_GetPulseWidthRiseToFallUs(_handle, &retval);
	return retval;
}

/**
 * Gets pulse width rise to rise us.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the pulse width rise to rise us.
 */

int SensorCollection::GetPulseWidthRiseToRiseUs() {
	int retval = 0;
	c_MotController_GetPulseWidthRiseToRiseUs(_handle, &retval);
	return retval;
}

/**
 * Gets pin state quad a.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  the pin state quad a.
 */

int SensorCollection::GetPinStateQuadA() {
	int retval = 0;
	c_MotController_GetPinStateQuadA(_handle, &retval);
	return retval;
}

/**
 * Gets pin state quad b.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  Digital level of QUADB pin.
 */

int SensorCollection::GetPinStateQuadB() {
	int retval = 0;
	c_MotController_GetPinStateQuadB(_handle, &retval);
	return retval;
}

/**
 * Gets pin state quad index.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  Digital level of QUAD Index pin.
 */

int SensorCollection::GetPinStateQuadIdx() {
	int retval = 0;
	c_MotController_GetPinStateQuadIdx(_handle, &retval);
	return retval;
}

/**
 * Is forward limit switch closed.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  '1' iff forward limit switch is closed, 0 iff switch is open. This function works
 *          regardless if limit switch feature is enabled.
 */

int SensorCollection::IsFwdLimitSwitchClosed() {
	int retval = 0;
	c_MotController_IsFwdLimitSwitchClosed(_handle, &retval);
	return retval;
}

/**
 * Is reverse limit switch closed.
 *
 * @param [out] param   The parameter to fill.
 *
 * @return  '1' iff reverse limit switch is closed, 0 iff switch is open. This function works
 *          regardless if limit switch feature is enabled.
 */

int SensorCollection::IsRevLimitSwitchClosed() {
	int retval = 0;
	c_MotController_IsRevLimitSwitchClosed(_handle, &retval);
	return retval;
}

