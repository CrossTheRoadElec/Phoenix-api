package com.ctre.phoenix.sensors;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.sensors.PigeonImuJNI;

import org.junit.jupiter.api.Test;

class PigeonIMUTest {
    

    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() {
        double [] array8d = {0, 0, 0, 0, 0, 0, 0, 0};

        double [] array3d = {0, 0, 0};

        short [] array3s = {0, 0, 0};
    
        PigeonImuJNI.JNI_new_PigeonImu_Talon(0);
        long handle = PigeonImuJNI.JNI_new_PigeonImu(0);
	    PigeonImuJNI.JNI_new_PigeonImu(0);
	    PigeonImuJNI.JNI_ConfigSetCustomParam(handle, 0, 0, 0);
	    PigeonImuJNI.JNI_ConfigGetCustomParam(handle, 0, 0);
	    PigeonImuJNI.JNI_ConfigSetParameter(handle, 0, 0, 0, 0, 0);
	    PigeonImuJNI.JNI_ConfigGetParameter(handle, 0, 0, 0);
	    PigeonImuJNI.JNI_ConfigFactoryDefault(handle, 0);
	    PigeonImuJNI.JNI_SetStatusFramePeriod(handle, 0, 0, 0);
	    PigeonImuJNI.JNI_SetYaw(handle, 0, 0);
	    PigeonImuJNI.JNI_AddYaw(handle, 0, 0);
	    PigeonImuJNI.JNI_SetYawToCompass(handle, 0);
	    PigeonImuJNI.JNI_SetFusedHeading(handle, 0, 0);
	    PigeonImuJNI.JNI_AddFusedHeading(handle, 0, 0);
	    PigeonImuJNI.JNI_SetFusedHeadingToCompass(handle, 0);
	    PigeonImuJNI.JNI_SetAccumZAngle(handle, 0, 0);
	    PigeonImuJNI.JNI_SetTemperatureCompensationDisable(handle, 0, 0);
	    PigeonImuJNI.JNI_SetCompassDeclination(handle, 0, 0);
	    PigeonImuJNI.JNI_SetCompassAngle(handle, 0, 0);
	    PigeonImuJNI.JNI_EnterCalibrationMode(handle, 0, 0);
	    PigeonImuJNI.JNI_GetGeneralStatus(handle, array8d);
	    PigeonImuJNI.JNI_Get6dQuaternion(handle, array3d);
	    PigeonImuJNI.JNI_GetYawPitchRoll(handle, array3d);
	    PigeonImuJNI.JNI_GetAccumGyro(handle, array3d);
	    PigeonImuJNI.JNI_GetAbsoluteCompassHeading(handle);
	    PigeonImuJNI.JNI_GetCompassHeading(handle);
	    PigeonImuJNI.JNI_GetCompassFieldStrength(handle);
	    PigeonImuJNI.JNI_GetTemp(handle);
	    PigeonImuJNI.JNI_GetUpTime(handle);
	    PigeonImuJNI.JNI_GetRawMagnetometer(handle, array3s);
	    PigeonImuJNI.JNI_GetBiasedMagnetometer(handle, array3s);
	    PigeonImuJNI.JNI_GetBiasedAccelerometer(handle, array3s);
	    PigeonImuJNI.JNI_GetRawGyro(handle, array3d);
	    PigeonImuJNI.JNI_GetAccelerometerAngles(handle, array3d);
	    PigeonImuJNI.JNI_GetFusedHeading(handle, array3d);
	    PigeonImuJNI.JNI_GetState(handle);
	    PigeonImuJNI.JNI_GetResetCount(handle);
	    PigeonImuJNI.JNI_GetResetFlags(handle);
	    PigeonImuJNI.JNI_GetFirmwareVersion(handle);
	    PigeonImuJNI.JNI_GetLastError(handle);
	    PigeonImuJNI.JNI_HasResetOccurred(handle);
	    PigeonImuJNI.JNI_GetStatusFramePeriod(handle, 0, 0);
	    PigeonImuJNI.JNI_SetControlFramePeriod(handle, 0, 0);
	    PigeonImuJNI.JNI_GetFaults(handle);
	    PigeonImuJNI.JNI_GetStickyFaults(handle);
	    PigeonImuJNI.JNI_ClearStickyFaults(handle, 0);
        //PigeonImuJNI.JNI_destroy_PigeonImu(handle);
        //PigeonImuJNI.JNI_destroy_AllPigeonImus();
    }
}
