package com.ctre.phoenix.Drive;

public class Styles
{
	public enum Smart
	{
		Voltage(0),
		PercentOutput(1),
		VelocityClosedLoop(2);
		
		public int value;
		Smart(int value)
		{
			this.value = value;
		}
	};
	
	public enum Basic
	{
		Voltage(0),
		PercentOutput(1);
		
		public int value;
		Basic(int value)
		{
			this.value = value;
		}
	};
	
	public static Styles.Smart promote(Basic basicStyle)
	{
		return Styles.Smart.values()[basicStyle.value];
	}
}