package com.ctre.phoenix;

/**
 * Class with basic utility methods
 */
public class Util
{
	/**
	 * Caps the value
	 * @param value Value to cap
	 * @param peak Maximum/-Minimum value can be
	 * @return Capped value
	 */
	public static double cap(double value, double peak)
	{
		if(value < -peak) value = -peak;
		if(value > peak) value = peak;
		return value;
	}
	
	/**
	 * Scales rotations to native units
	 * @param scalar Value to scale by
	 * @param fullRotations Number of rotations to scale by
	 * @return Scaled units
	 */
	public static int scaleRotationsToNativeUnits(double scalar, double fullRotations) {
		/* first assume we don't have config info, prep the default return */
		int retval = (int) fullRotations;
		/* apply scalar if its available */
		if (scalar > 0) {
		  retval = (int) (fullRotations * scalar);
		}
		return retval;
	}
	/**
	 * Scales velocity to native units
	 * @param scalar Value to scale by
	 * @param rpm Velocity in rotations per minute
	 * @return Scaled velocity
	 */
	public static int scaleVelocityToNativeUnits(double scalar, double rpm) {
		/* first assume we don't have config info, prep the default return */
		int retval = (int) rpm;
		/* apply scalar if its available */
		if (scalar > 0) {
		  retval = (int) (rpm * scalar);
		}
		return retval;
	}
	/**
	 * Scales native units to rotations
	 * @param scalar Value to scale by
	 * @param nativePos Native position units
	 * @return Scaled units
	 */
	public static double scaleNativeUnitsToRotations(double scalar, long nativePos) {
		/* first assume we don't have config info, prep the default return */
		double retval = (double) nativePos;
		/* retrieve scaling info */
		if (scalar > 0) {
		  retval = ((double) nativePos) / scalar;
		}
		return retval;
	}
	/**
	 * Scales Native units to velocity
	 * @param scalar Value to scale by
	 * @param nativeVel Native velocity units
	 * @return Scaled units
	 */
	public static double scaleNativeUnitsToRpm(double scalar, long nativeVel) {
		/* first assume we don't have config info, prep the default return */
		double retval = (double) nativeVel;
		/* apply scalar if its available */
		if (scalar > 0) {
		  retval = (double) (nativeVel) / (scalar);
		}
		return retval;
	}
}