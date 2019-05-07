package com.ctre.phoenix.motion;

/**
 * Motion Profile Trajectory Point This is simply a data transfer object.
 */
public class TrajectoryPoint {

	/** The position to servo to (in sensor units).*/
	public double position = 0; 
	/** The velocity to feed-forward (in sensor-units per 100ms).  */
	public double velocity = 0; 
	/** Added to the output of PID[0], should be within [-1,+1] where 0.01 = 1%. */
	public double arbFeedFwd = 0; 
	/** Not used.  Use auxiliaryPos instead.  @see auxiliaryPos */
	public double headingDeg = 0; 
	/** The position for auxiliary PID[1] to target (in sensor units). */
	public double auxiliaryPos = 0; 
	/** The velocity for auxiliary PID[1] to target. (in sensor-units per 100ms). */
	public double auxiliaryVel = 0; 
	/** Added to the output of PID[1], should be within [-1,+1] where 0.01 = 1%. */
	public double auxiliaryArbFeedFwd = 0; 

	/**
	 * Which slot to get PIDF gains. PID is used for position servo. F is used
	 * as the Kv constant for velocity feed-forward. Typically this is hard-coded
	 * to a particular slot, but you are free to gain schedule if need be.
	 * Choose from [0,3]
	 */
	public int profileSlotSelect0 = 0;

	/**
	 * Which slot to get PIDF gains for auxiliary PId.
	 * This only has impact during MotionProfileArc Control mode.
	 * Choose from [0,3].
	 */
	public int profileSlotSelect1 = 0;

	/**
	 * Set to true to signal Talon that this is the final point, so do not
	 * attempt to pop another trajectory point from out of the Talon buffer.
	 * Instead continue processing this way point. Typically the velocity member
	 * variable should be zero so that the motor doesn't spin indefinitely.
	 */
	public boolean isLastPoint = false;
	/**
	 * Set to true to signal Talon to zero the selected sensor. When generating
	 * MPs, one simple method is to make the first target position zero, and the
	 * final target position the target distance from the current position. Then
	 * when you fire the MP, the current position gets set to zero. If this is
	 * the intent, you can set zeroPos on the first trajectory point.
	 *
	 * Otherwise you can leave this false for all points, and offset the
	 * positions of all trajectory points so they are correct.
	 *
	 * If using multiple sensor sources (Arc modes) we recommend you manually set sensor positions
	 * before arming MP, instead of using this feature.
	 */
	public boolean zeroPos = false;

	/**
	 * Duration (ms) to apply this trajectory pt.
	 * This time unit is ADDED to the existing base time set by
	 * ConfigMotionProfileTrajectoryPeriod().
	 */
	public int timeDur = 0;

	/**
	 * If using MotionProfileArc, this flag must be true on all points.
	 * If using MotionProfile, this flag must be false on all points.
	 */
	public boolean useAuxPID = false;
}
