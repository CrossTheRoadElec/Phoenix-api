#include "ctre/phoenix/motorcontrol/SensorCollection.h"
#include "ctre/phoenix/cci/MotController_CCI.h"

using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol;

SensorCollection::SensorCollection(void * handle) {
	_handle = handle;
}

/**
 * Get the position of whatever is in the analog pin of the Talon, regardless of
 *   whether it is actually being used for feedback.
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
 * @param   timeoutMs
 *            Timeout value in ms. If nonzero, function will wait for
 *            config success and report an error if it times out.
 *            If zero, no blocking or checking is performed.
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
 * @return  the ADC (0 - 1023) on analog pin of the Talon.
 */

int SensorCollection::GetAnalogInRaw() {
	int retval = 0;
	c_MotController_GetAnalogInRaw(_handle, &retval);
	return retval;
}

/**
 * Get the velocity of whatever is in the analog pin of the Talon, regardless of
 *   whether it is actually being used for feedback.
 *
 * @return  the speed in units per 100ms where 1024 units is one rotation.
 */

int SensorCollection::GetAnalogInVel() {
	int retval = 0;
	c_MotController_GetAnalogInVel(_handle, &retval);
	return retval;
}

/**
 * Get the quadrature position of the Talon, regardless of whether
 *   it is actually being used for feedback.
 *
 * @return  the quadrature position.
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
 * @param   timeoutMs
 *            Timeout value in ms. If nonzero, function will wait for
 *            config success and report an error if it times out.
 *            If zero, no blocking or checking is performed.
 *
 * @return  error code.
 */

ErrorCode SensorCollection::SetQuadraturePosition(int newPosition,
		int timeoutMs) {
	return c_MotController_SetQuadraturePosition(_handle, newPosition,
			timeoutMs);
}

/**
 * Change the quadrature reported position based on pulse width. This can be used to 
 * effectively make quadrature absolute. For rotary mechanisms with >360 movement (such
 * as typical swerve modules) bookend0 and bookend1 can be both set to 0 and 
 * bCrossZeroOnInterval can be set to true. For mechanisms with less than 360 travel (such
 * as arms), bookend0 and bookend1 should be set to the pulse width values at the two 
 * extremes. If the interval crosses over the pulse width value of 0 (or any multiple of
 * 4096), bCrossZeroOnInterval should be true and otherwise should be false. An offset can
 * also be set.
 *
 * @param   bookend0    value at extreme 0
 * @param   bookend1    value at extreme 1
 * @param   bCrossZeroOnInterval    True iff zero/wrap-around cross occurs as mechanism moves from bookend0 to bookend1.
 * @param   offset      (Optional) Value to add to pulse width 
 * @param   timeoutMs   (Optional) How long to wait for confirmation.  Pass zero so that call
 *                      does not block.
 *
 * @return  error code.
 */

ErrorCode SensorCollection::SyncQuadratureWithPulseWidth(int bookend0, int bookend1, bool bCrossZeroOnInterval, int offset, int timeoutMs) {   
    int ticksPerRevolution = 4096;
    /* Normalize bookends (should be 0 - ticksPerRevolution) */
    bookend0 &= (ticksPerRevolution - 1);
    bookend1 &= (ticksPerRevolution - 1);
  
    /* Assign greater and lesser bookend */
    int greaterBookend;
    int lesserBookend;
    
    if(bookend0 > bookend1)
    {
        greaterBookend = bookend0;
        lesserBookend = bookend1;
    }
    else
    {
        greaterBookend = bookend1;
        lesserBookend = bookend0;
    }

    int average = (greaterBookend + lesserBookend) / 2;

    /* Get Fractional Part of Pulse Width Position (0 - ticksPerRevolution) */
    int pulseWidth = GetPulseWidthPosition();
    pulseWidth &= (ticksPerRevolution - 1);
    
    if(bCrossZeroOnInterval) 
    {
        /*
         * If the desire is to have the *** part be the interval 
         * (2048 - 3277 and crosses over 0): 
         *
         *                            
         *                        1024
         *                     *********    
         *                    ***********   
         *                   *************  
         *                  *************** 
         *                 *****************
         *                 *****************
         *                 *****************
         *            2048 ***************** 0
         *                         *********
         *                         *********
         *                         *********
         *                         *********
         *                        **********
         *                        ********* 
         *                        ********  
         *                       ********   
         *                       *******
         *                     3277   
         *
         * The goal is to center the discontinuoity between 2048 and 3277 in the blank.
         * So all pulse width values greater than the avg of the two bookends should be 
         * reduced by ticksPerRevolution.
         */
        if(pulseWidth > average)
        {            
            pulseWidth -= ticksPerRevolution;
        }
    }
    else
    {
        /*
         * If the desire is to have the blank part be the interval 
         * (2048 - 3277 and crosses over 0): 
         *
         *                            
         *                        1024
         *                     *********    
         *                    ***********   
         *                   *************  
         *                  *************** 
         *                 *****************
         *                 *****************
         *                 *****************
         *            2048 ***************** 0
         *                         *********
         *                         *********
         *                         *********
         *                         *********
         *                        **********
         *                        ********* 
         *                        ********  
         *                       ********   
         *                       *******
         *                     3277   
         *
         * The goal is to center the discontinuoity between 2048 and 3277 in the ***.
         * So all pulse width values less than the (ticksPerRevolution / 2 - avg of 
         * the two bookends) & ticksPerRevolution should be increased by 
         * ticksPerRevolution.
         */
        if(pulseWidth < ((ticksPerRevolution / 2 - average) & 0x0FFF))
        {            
            pulseWidth += ticksPerRevolution;
        }
    }
   
    pulseWidth += offset;

    return SetQuadraturePosition(pulseWidth, timeoutMs);
}

/**
 * Get the quadrature velocity, regardless of whether
 *   it is actually being used for feedback.
 *
 * @return  the quadrature velocity in units per 100ms.
 */

int SensorCollection::GetQuadratureVelocity() {
	int retval = 0;
	c_MotController_GetQuadratureVelocity(_handle, &retval);
	return retval;
}

/**
 * Gets pulse width position, regardless of whether
 *   it is actually being used for feedback.
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
 * @param   timeoutMs
 *            Timeout value in ms. If nonzero, function will wait for
 *            config success and report an error if it times out.
 *            If zero, no blocking or checking is performed.
 *
 * @return  an ErrErrorCode
 */
ErrorCode SensorCollection::SetPulseWidthPosition(int newPosition,
		int timeoutMs) {
	return c_MotController_SetPulseWidthPosition(_handle, newPosition,
			timeoutMs);
}

/**
 * Gets pulse width velocity, regardless of whether
 *   it is actually being used for feedback.
 *
 * @return  the pulse width velocity in units per 100ms (where 4096 units is 1 rotation).
 */

int SensorCollection::GetPulseWidthVelocity() {
	int retval = 0;
	c_MotController_GetPulseWidthVelocity(_handle, &retval);
	return retval;
}

/**
 * Gets pulse width rise to fall time.
 *
 * @return  the pulse width rise to fall time in microseconds.
 */

int SensorCollection::GetPulseWidthRiseToFallUs() {
	int retval = 0;
	c_MotController_GetPulseWidthRiseToFallUs(_handle, &retval);
	return retval;
}

/**
 * Gets pulse width rise to rise time.
 *
 * @return  the pulse width rise to rise time in microseconds.
 */

int SensorCollection::GetPulseWidthRiseToRiseUs() {
	int retval = 0;
	c_MotController_GetPulseWidthRiseToRiseUs(_handle, &retval);
	return retval;
}

/**
 * Gets pin state quad a.
 *
 * @return  the pin state of quad a (1 if asserted, 0 if not asserted).
 */

int SensorCollection::GetPinStateQuadA() {
	int retval = 0;
	c_MotController_GetPinStateQuadA(_handle, &retval);
	return retval;
}

/**
 * Gets pin state quad b.
 *
 * @return  Digital level of QUADB pin (1 if asserted, 0 if not asserted).
 */

int SensorCollection::GetPinStateQuadB() {
	int retval = 0;
	c_MotController_GetPinStateQuadB(_handle, &retval);
	return retval;
}

/**
 * Gets pin state quad index.
 *
 * @return  Digital level of QUAD Index pin (1 if asserted, 0 if not asserted).
 */

int SensorCollection::GetPinStateQuadIdx() {
	int retval = 0;
	c_MotController_GetPinStateQuadIdx(_handle, &retval);
	return retval;
}

/**
 * Is forward limit switch closed.
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
 * @return  '1' iff reverse limit switch is closed, 0 iff switch is open. This function works
 *          regardless if limit switch feature is enabled.
 */

int SensorCollection::IsRevLimitSwitchClosed() {
	int retval = 0;
	c_MotController_IsRevLimitSwitchClosed(_handle, &retval);
	return retval;
}
