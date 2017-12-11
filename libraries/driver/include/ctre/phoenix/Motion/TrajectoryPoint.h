#pragma once

namespace ctre {
namespace phoenix {
namespace motion {

/**
 * Motion Profile Trajectory Point
 * This is simply a data transer object.
 */
struct TrajectoryPoint {
	double position; //!< The position to servo to.
	double velocity; //!< The velocity to feed-forward.
	double headingDeg;

	/**
	 * Which slot to get PIDF gains.
	 * PID is used for position servo.
	 * F is used as the Kv constant for velocity feed-forward.
	 * Typically this is hardcoded to the a particular slot, but you are free
	 * gain schedule if need be.
	 */
	uint32_t profileSlotSelect;

	/**
	 * Set to true to signal Talon that this is the final point, so do not
	 * attempt to pop another trajectory point from out of the Talon buffer.
	 * Instead continue processing this way point.  Typically the velocity
	 * member variable should be zero so that the motor doesn't spin indefinitely.
	 */
	bool isLastPoint;
	/**
	 * Set to true to signal Talon to zero the selected sensor.
	 * When generating MPs, one simple method is to make the first target position zero,
	 * and the final target position the target distance from the current position.
	 * Then when you fire the MP, the current position gets set to zero.
	 * If this is the intent, you can set zeroPos on the first trajectory point.
	 *
	 * Otherwise you can leave this false for all points, and offset the positions
	 * of all trajectory points so they are correct.
	 */
	bool zeroPos;
};
} // namespace motion
} // namespace phoenix
} // namespace ctre
