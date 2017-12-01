package com.ctre.phoenix;

import java.util.Arrays;

public class CTRLogger
{
	public static void close() {
		CTRLoggerJNI.JNI_Logger_Close();
	}
	
	public static int log(int code, String origin) {
		String stack = Arrays.toString(Thread.currentThread().getStackTrace());
		stack = stack.replaceAll(",", "\n");
		return CTRLoggerJNI.JNI_Logger_Log(code, origin, stack);
	}
	
	public static void open() {
		CTRLoggerJNI.JNI_Logger_Open(2);
	}
	
	public static String getVerbose(int code) {
		return CTRLoggerJNI.JNI_Logger_GetLong(code);
	}
	public static String getShort(int code) {
		return CTRLoggerJNI.JNI_Logger_GetShort(code);
	}
}

