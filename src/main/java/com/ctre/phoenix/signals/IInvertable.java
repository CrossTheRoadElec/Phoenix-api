package com.ctre.phoenix.signals;

/**
 * Interface for invertable objects
 */
public interface IInvertable
{
	/**
	 * Inverts the hbridge output of the motor controller.
	 *
	 * This does not impact sensor phase and should not be used to correct sensor polarity.
	 *
	 * This will invert the hbridge output but NOT the LEDs.
	 * This ensures....
	 *  - Green LEDs always represents positive request from robot-controller/closed-looping mode.
	 *  - Green LEDs correlates to forward limit switch.
	 *  - Green LEDs correlates to forward soft limit.
	 *
	 * @param invert
	 *            Invert state to set.
	 */
	void setInverted(boolean invert);
	/**
	 * @return invert setting of motor output.
	 */
	boolean getInverted();
}