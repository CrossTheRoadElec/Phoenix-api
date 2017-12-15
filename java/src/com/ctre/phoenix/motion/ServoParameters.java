//package com.ctre.phoenix.motion;
//
//public class ServoParameters
//{
//	public double P = 0;
//	public double I = 0;
//	public double D = 0;
//	public double maxOut = 0;
//	public double nominalOut = 0;
//	public double IZone = 0;
//	public double IMax = 0;
//	public double allowedError = 0;
//	public double timeToDone = 0;
//	
//	private double IAccum = 0;
//	private com.ctre.phoenix.time.StopWatch _st = new com.ctre.phoenix.time.StopWatch();
//	private boolean hasStarted = false;
//	
//	
//	public void resetIAccum() { IAccum = 0; } 
//	public void onStart() 
//	{
//		//Clear variables since servo objects can be used more than once
//		hasStarted = false;
//		resetIAccum();
//	}
//	
//	//Sensor Derivative added for use with Pigeon get raw gyro and Talon get velocity measurement
//	public double PID(double error, double sensorDerivative)
//	{
//		//First call to PID means the stopwatch is guaranteed to have started
//		hasStarted = true;
//		IAccum += I * error;
//		if(IAccum > IMax) IAccum = IMax;
//		if(IAccum < -IMax) IAccum = -IMax;
//		if(Math.abs(error) > IZone) resetIAccum();
//		
//		double out = (P * error) + IAccum - (D * sensorDerivative);
//		if(Math.abs(error) > allowedError)
//		{
//			if(out > maxOut) out = maxOut;
//			if(out < -maxOut) out = -maxOut;
//			if(out < nominalOut && out > 0) out = nominalOut;
//			if(out > -nominalOut && out < 0) out = -nominalOut;
//			_st.start();
//		}
//		else
//		{
//			out = 0;
//		}
//		return out;
//	}
//	//Stopwatch time has to be greater than specified time plus one loop cycle to ensure it's not just lag from the stopwatch
//	public boolean isDone() { return _st.getDuration() > (timeToDone + 0.01) && hasStarted; }
//}