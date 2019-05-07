package com.ctre.phoenix.motorcontrol;
import com.ctre.phoenix.motorcontrol.IMotorController;

/**
 * Interface for followers
 */
public interface IFollower
{
	/**
	 * Set the control mode and output value so that this motor controller will
	 * follow another motor controller. Currently supports following Victor SPX
	 * and Talon SRX.
	 *
	 * @param masterToFollow
	 *						Motor Controller object to follow.
	 */
	void follow(IMotorController masterToFollow);
	/**
	 * When master makes a device, this routine is called to signal the update.
	 */
	void valueUpdated();
}