package com.ctre.phoenix.motion;

/**
 * Motion Profile Trajectory Point This is simply a data transer object.
 */
public class TrajectoryPoint {
	public enum TrajectoryDuration
	{
		Trajectory_Duration_5ms,
		Trajectory_Duration_10ms,
		Trajectory_Duration_15ms,
		Trajectory_Duration_20ms,
		Trajectory_Duration_30ms,
		Trajectory_Duration_40ms,
		Trajectory_Duration_50ms,
		Trajectory_Duration_100ms,
	}
	
	public double position; // !< The position to servo to.
	public double velocity; // !< The velocity to feed-forward.
	public double headingDeg;

	/**
	 * Which slot to get PIDF gains. PID is used for position servo. F is used
	 * as the Kv constant for velocity feed-forward. Typically this is hardcoded
	 * to the a particular slot, but you are free gain schedule if need be.
	 * Choose from [0,3]
	 */
	public int profileSlotSelect0;
	
	/**
	 * Which slot to get PIDF gains for cascaded PId.
	 * This only has impact during MotionProfileArc Control mode.
	 * Choose from [0,1].
	 */
	public int profileSlotSelect1;

	/**
	 * Set to true to signal Talon that this is the final point, so do not
	 * attempt to pop another trajectory point from out of the Talon buffer.
	 * Instead continue processing this way point. Typically the velocity member
	 * variable should be zero so that the motor doesn't spin indefinitely.
	 */
	public boolean isLastPoint;
	/**
	 * Set to true to signal Talon to zero the selected sensor. When generating
	 * MPs, one simple method is to make the first target position zero, and the
	 * final target position the target distance from the current position. Then
	 * when you fire the MP, the current position gets set to zero. If this is
	 * the intent, you can set zeroPos on the first trajectory point.
	 *
	 * Otherwise you can leave this false for all points, and offset the
	 * positions of all trajectory points so they are correct.
	 */
	public boolean zeroPos;
	
	/**
	 * Duration to apply this trajectory pt.
	 */
	public TrajectoryDuration timeDur;
}
