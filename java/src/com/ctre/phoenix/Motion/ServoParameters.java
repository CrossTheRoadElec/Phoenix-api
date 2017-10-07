package com.ctre.phoenix.Motion;

public class ServoParameters
{
	public float P = 0;
	public float I = 0;
	public float D = 0;
	public float maxOut = 0;
	public float nominalOut = 0;
	public float IZone = 0;
	public float IMax = 0;
	public float allowedError = 0;
	public float timeToDone = 0;
	
	private float IAccum = 0;
	private com.ctre.phoenix.Time.StopWatch _st = new com.ctre.phoenix.Time.StopWatch();
	private boolean hasStarted = false;
	
	
	public void resetIAccum() { IAccum = 0; } 
	public void OnStart() 
	{
		//Clear variables since servo objects can be used more than once
		hasStarted = false;
		resetIAccum();
	}
	
	//Sensor Derivative added for use with Pigeon get raw gyro and Talon get velocity measurement
	public float PID(float error, float sensorDerivative)
	{
		//First call to PID means the stopwatch is guaranteed to have started
		hasStarted = true;
		IAccum += I * error;
		if(IAccum > IMax) IAccum = IMax;
		if(IAccum < -IMax) IAccum = -IMax;
		if(Math.abs(error) > IZone) resetIAccum();
		
		float out = (P * error) + IAccum - (D * sensorDerivative);
		if(Math.abs(error) > allowedError)
		{
			if(out > maxOut) out = maxOut;
			if(out < -maxOut) out = -maxOut;
			if(out < nominalOut && out > 0) out = nominalOut;
			if(out > -nominalOut && out < 0) out = -nominalOut;
			_st.start();
		}
		else
		{
			out = 0;
		}
		return out;
	}
	//Stopwatch time has to be greater than specified time plus one loop cycle to ensure it's not just lag from the stopwatch
	public boolean IsDone() { return _st.getDuration() > (timeToDone + 0.01) && hasStarted; }
}