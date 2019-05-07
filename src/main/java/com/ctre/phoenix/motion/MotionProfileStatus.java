package com.ctre.phoenix.motion;

/**
 * Motion Profile Status This is simply a data transer object.
 */
public class MotionProfileStatus {
	/**
	 * The available empty slots in the trajectory buffer.
	 *
	 * The robot API holds a "top buffer" of trajectory points, so your
	 * applicaion can dump several points at once. The API will then stream them
	 * into the Talon's low-level buffer, allowing the Talon to act on them.
	 */
	public int topBufferRem;
	/**
	 * The number of points in the top trajectory buffer.
	 */
	public int topBufferCnt;
	/**
	 * The number of points in the low level Talon/Victor buffer.
	 */
	public int btmBufferCnt;
	/**
	 * Set if isUnderrun ever gets set. Only is cleared by
	 * clearMotionProfileHasUnderrun() to ensure robot logic can react or
	 * instrument it.
	 *
	 * @see com.ctre.phoenix.motorcontrol.can.BaseMotorController#clearMotionProfileHasUnderrun(int)
	 */
	public boolean hasUnderrun;
	/**
	 * This is set if Talon/Victor needs to shift a point from its buffer into the
	 * active trajectory point however the buffer is empty. This gets cleared
	 * automatically when is resolved.
	 */
	public boolean isUnderrun;
	/**
	 * True if the active trajectory point is not empty, false otherwise. The
	 * members in activePoint are only valid if this signal is set.
	 */
	public boolean activePointValid;

	/**
	 * True if the active trajectory point is the last point of the profile
	 */
	public boolean isLast;

	/**
	 * The selected PID[0] profile slot of current profile
	 */
	public int profileSlotSelect;
	/**
	 * The current output mode of the motion profile executer (disabled,
	 * enabled, or hold). When changing the set() value in MP mode, it's
	 * important to check this signal to confirm the change takes effect before
	 * interacting with the top buffer.
	 */
	public SetValueMotionProfile outputEnable;
	
	/**
	 * The duration in ms of current trajectory point
	 */
	public int timeDurMs;
	
	/**
	 * The selected auxiliary PID[1] profile slot of current profile
	 */
	public int profileSlotSelect1;
}
