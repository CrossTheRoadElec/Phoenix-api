package com.ctre.phoenix.motorcontrol;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.motorcontrol.can.BaseMotorController;
import com.ctre.phoenix.motorcontrol.can.MotControllerJNI;

/**
 * Collection of sensors available to a motor controller.
 *
 * For best performance and update-rate, 
 * we recommend using the configSelectedFeedbackSensor() and getSelectedSensor*() routines.
 * However there are occasions where accessing raw sensor values may be useful or convenient.
 * Particularly if you are seeding one sensor based on another, or need to circumvent sensor-phase.
 *
 * Use the getSensorCollection() routine inside your motor controller to create a sensor collection.
 */
public class SensorCollection {

	private long _handle;

	/**
	 * Constructor for SensorCollection
	 * @param motorController Motor Controller to connect Collection to
	 */
	public SensorCollection(BaseMotorController motorController) {
		_handle = motorController.getHandle();

	}

	/**
	 * Get the position of whatever is in the analog pin of the Talon, regardless of
	 *   whether it is actually being used for feedback.
	 *
	 * @return  the 24bit analog value.  The bottom ten bits is the ADC (0 - 1023)
	 *          on the analog pin of the Talon. The upper 14 bits tracks the overflows and underflows
	 *          (continuous sensor).
	 */

	public int getAnalogIn() {
		return MotControllerJNI.GetAnalogIn(_handle);
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

	public ErrorCode setAnalogPosition(int newPosition, int timeoutMs) {
		int retval = MotControllerJNI.SetAnalogPosition(_handle, newPosition, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Get the position of whatever is in the analog pin of the Talon, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @return  the ADC (0 - 1023) on analog pin of the Talon.
	 */

	public int getAnalogInRaw() {
		return MotControllerJNI.GetAnalogInRaw(_handle);
	}

	/**
	 * Get the velocity of whatever is in the analog pin of the Talon, regardless of
	 *   whether it is actually being used for feedback.
	 *
	 * @return  the speed in units per 100ms where 1024 units is one rotation.
	 */

	public int getAnalogInVel() {
		return MotControllerJNI.GetAnalogInVel(_handle);
	}

	/**
	 * Get the quadrature position of the Talon, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @return  the quadrature position.
	 */

	public int getQuadraturePosition() {
		return MotControllerJNI.GetQuadraturePosition(_handle);
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

	public ErrorCode setQuadraturePosition(int newPosition, int timeoutMs) {
		int retval = MotControllerJNI.SetQuadraturePosition(_handle, newPosition, timeoutMs);
		return ErrorCode.valueOf(retval);
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

    public ErrorCode syncQuadratureWithPulseWidth(int bookend0, int bookend1, boolean bCrossZeroOnInterval, int offset, int timeoutMs) {   
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
        int pulseWidth = getPulseWidthPosition();
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
 
        return setQuadraturePosition(pulseWidth, timeoutMs);
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
     *
     * @return  error code.
     */
    public ErrorCode syncQuadratureWithPulseWidth(int bookend0, int bookend1, boolean bCrossZeroOnInterval) {
        int offset = 0;
        int timeoutMs = 0;
        return syncQuadratureWithPulseWidth(bookend0, bookend1, bCrossZeroOnInterval, offset, timeoutMs);
    }   
	/**
	 * Get the quadrature velocity, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @return  the quadrature velocity in units per 100ms.
	 */

	public int getQuadratureVelocity() {
		return MotControllerJNI.GetQuadratureVelocity(_handle);
	}

	/**
	 * Gets pulse width position, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @return  the pulse width position.
	 */

	public int getPulseWidthPosition() {
		return MotControllerJNI.GetPulseWidthPosition(_handle);
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
	public ErrorCode setPulseWidthPosition(int newPosition, int timeoutMs) {
		int retval = MotControllerJNI.SetPulseWidthPosition(_handle, newPosition, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Gets pulse width velocity, regardless of whether
	 *   it is actually being used for feedback.
	 *
	 * @return  the pulse width velocity in units per 100ms (where 4096 units is 1 rotation).
	 */

	public int getPulseWidthVelocity() {
		return MotControllerJNI.GetPulseWidthVelocity(_handle);
	}

	/**
	 * Gets pulse width rise to fall time.
	 *
	 * @return  the pulse width rise to fall time in microseconds.
	 */

	public int getPulseWidthRiseToFallUs() {
		return MotControllerJNI.GetPulseWidthRiseToFallUs(_handle);
	}

	/**
	 * Gets pulse width rise to rise time.
	 *
	 * @return  the pulse width rise to rise time in microseconds.
	 */

	public int getPulseWidthRiseToRiseUs() {
		return MotControllerJNI.GetPulseWidthRiseToRiseUs(_handle);
	}

	/**
	 * Gets pin state quad a.
	 *
	 * @return  the pin state of quad a (1 if asserted, 0 if not asserted).
	 */

	public boolean getPinStateQuadA() {
		return MotControllerJNI.GetPinStateQuadA(_handle) != 0;
	}

	/**
	 * Gets pin state quad b.
	 *
	 * @return  Digital level of QUADB pin (1 if asserted, 0 if not asserted).
	 */

	public boolean getPinStateQuadB() {
		return MotControllerJNI.GetPinStateQuadB(_handle) != 0;
	}

	/**
	 * Gets pin state quad index.
	 *
	 * @return  Digital level of QUAD Index pin (1 if asserted, 0 if not asserted).
	 */

	public boolean getPinStateQuadIdx() {
		return MotControllerJNI.GetPinStateQuadIdx(_handle) != 0;
	}

	/**
	 * Is forward limit switch closed.
	 *
	 * @return  '1' iff forward limit switch is closed, 0 iff switch is open. This function works
	 *          regardless if limit switch feature is enabled.
	 */

	public boolean isFwdLimitSwitchClosed() {
		return MotControllerJNI.IsFwdLimitSwitchClosed(_handle) != 0;
	}

	/**
	 * Is reverse limit switch closed.
	 *
	 * @return  '1' iff reverse limit switch is closed, 0 iff switch is open. This function works
	 *          regardless if limit switch feature is enabled.
	 */

	public boolean isRevLimitSwitchClosed() {
		return MotControllerJNI.IsRevLimitSwitchClosed(_handle) != 0;
	}
}
