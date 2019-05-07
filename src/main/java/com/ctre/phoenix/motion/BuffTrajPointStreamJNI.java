package com.ctre.phoenix.motion;

import com.ctre.phoenix.CTREJNIWrapper;

public class BuffTrajPointStreamJNI extends CTREJNIWrapper {

    public static native long Create1();

    public static native void DestroyAll();

    public static native int Destroy(long handle);

    public static native int Clear(long handle);

    public static native int Write(long handle, double position, double velocity, double arbFeedFwd, double auxiliaryPos, double auxiliaryVel, double auxiliaryArbFeedFwd, int profileSlotSelect0, int profileSlotSelect1, boolean isLastPoint, boolean zeroPos, int timeDur, boolean useAuxPID);
}