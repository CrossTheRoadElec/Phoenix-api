/**
 * Private class wrapper to adapt CTRE motor controllers to WPILIB.
 * This prevents WPILIB interface functions from polluting the function list
 * with redundant functions.
 */
#pragma once

#include "ctre/Phoenix/ErrorCode.h"

namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace can {
class BaseMotorController;
}
}
}
}

namespace ctre {
namespace phoenix {
namespace motorcontrol {

class SensorCollection {
public:

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

	int GetAnalogIn();

	/**
	 * Sets analog position.
	 *
	 * @param   newPosition The new position.
	 * @param   timeoutMs   (Optional) The timeout in milliseconds.
	 *
	 * @return  an ErrorCode.
	 */

	ErrorCode SetAnalogPosition(int newPosition, int timeoutMs);

	/**
	 * Get the position of whatever is in the analog pin of the Talon, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the ADC (0 - 1023) on analog pin of the Talon.
	 */

	int GetAnalogInRaw();

	/**
	 * Get the position of whatever is in the analog pin of the Talon, regardless of
	 *   whether it is actually being used for feedback.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the value (0 - 1023) on the analog pin of the Talon.
	 */

	int GetAnalogInVel();

	/**
	 * Get the position of whatever is in the analog pin of the Talon, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @param [out] param   The value to fill with the Quad pos.
	 *
	 * @return  the Error code of the request.
	 */

	int GetQuadraturePosition();

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

	ErrorCode SetQuadraturePosition(int newPosition, int timeoutMs);

	/**
	 * Get the position of whatever is in the analog pin of the Talon, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the value (0 - 1023) on the analog pin of the Talon.
	 */

	int GetQuadratureVelocity();

	/**
	 * Gets pulse width position.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the pulse width position.
	 */

	int GetPulseWidthPosition();

	/**
	 * Sets pulse width position.
	 *
	 * @param   newPosition The position value to apply to the sensor.
	 * @param   timeoutMs   (Optional) How long to wait for confirmation.  Pass zero so that call
	 *                      does not block.
	 *
	 * @return  an ErrErrorCode
	 */
	ErrorCode SetPulseWidthPosition(int newPosition, int timeoutMs);

	/**
	 * Gets pulse width velocity.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the pulse width velocity.
	 */

	int GetPulseWidthVelocity();

	/**
	 * Gets pulse width rise to fall us.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the pulse width rise to fall us.
	 */

	int GetPulseWidthRiseToFallUs();

	/**
	 * Gets pulse width rise to rise us.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the pulse width rise to rise us.
	 */

	int GetPulseWidthRiseToRiseUs();

	/**
	 * Gets pin state quad a.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  the pin state quad a.
	 */

	int GetPinStateQuadA();

	/**
	 * Gets pin state quad b.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  Digital level of QUADB pin.
	 */

	int GetPinStateQuadB();

	/**
	 * Gets pin state quad index.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  Digital level of QUAD Index pin.
	 */

	int GetPinStateQuadIdx();

	/**
	 * Is forward limit switch closed.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  '1' iff forward limit switch is closed, 0 iff switch is open. This function works
	 *          regardless if limit switch feature is enabled.
	 */

	int IsFwdLimitSwitchClosed();

	/**
	 * Is reverse limit switch closed.
	 *
	 * @param [out] param   The parameter to fill.
	 *
	 * @return  '1' iff reverse limit switch is closed, 0 iff switch is open. This function works
	 *          regardless if limit switch feature is enabled.
	 */

	int IsRevLimitSwitchClosed();

private:
	SensorCollection(void * handle);
	friend class ctre::phoenix::motorcontrol::can::BaseMotorController;
	void* _handle;

};

} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
