package com.ctre.phoenix.motorcontrol;

import java.util.*;

/**
 * Group of motor controllers
 */
public class GroupMotorControllers
{
	static List<IMotorController> _ms = new ArrayList<IMotorController>();
	
	/**
	 * Add motor controller to the group
	 * @param mc motor controller to add
	 */
	public static void register(IMotorController mc)
	{
		_ms.add(mc);
	}
	
	/**
	 * @return number of motorcontrollers in group
	 */
	public static int getCount()
	{
		return _ms.size();
	}
	
	/**
	 * @param idx Index of motor controller to get
	 * @return Motor controller at specified index
	 */
	public static IMotorController get(int idx)
	{
		return _ms.get(idx);
	}
}