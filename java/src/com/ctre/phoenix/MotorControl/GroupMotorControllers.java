package com.ctre.phoenix.MotorControl;

import java.util.*;

public class GroupMotorControllers
{
	static List<IMotorController> _ms = new ArrayList<IMotorController>();
	
	public static void Register(IMotorController mc)
	{
		_ms.add(mc);
	}
	
	public static int GetCount()
	{
		return _ms.size();
	}
	
	public static IMotorController Get(int idx)
	{
		return _ms.get(idx);
	}
}