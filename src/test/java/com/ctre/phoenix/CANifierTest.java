package com.ctre.phoenix;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.CANifierJNI;

import org.junit.jupiter.api.Test;

class CANifierTest {
    

    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() {
        boolean [] array11b = {false, false, false, false, false, false, false, false, false, false, false};
	    
        double [] array2d = {0, 0, 0};

        long handle = CANifierJNI.JNI_new_CANifier(0);
	    CANifierJNI.JNI_SetLEDOutput(handle, 0, 0);
	    CANifierJNI.JNI_SetGeneralOutputs(handle, 0, 0);
	    CANifierJNI.JNI_SetGeneralOutput(handle, 0, false, false);
	    CANifierJNI.JNI_SetPWMOutput(handle, 0, 0);
	    CANifierJNI.JNI_EnablePWMOutput(handle, 0, false);
	    CANifierJNI.JNI_GetGeneralInputs(handle, array11b);
	    CANifierJNI.JNI_GetGeneralInput(handle, 0);
	    CANifierJNI.JNI_GetPWMInput(handle, 0, array2d);
	    CANifierJNI.JNI_GetLastError(handle);
	    CANifierJNI.JNI_GetBatteryVoltage(handle);
	    CANifierJNI.JNI_GetQuadraturePosition(handle);
	    CANifierJNI.JNI_SetQuadraturePosition(handle, 0, 0);
	    CANifierJNI.JNI_GetQuadratureVelocity(handle);
	    CANifierJNI.JNI_ConfigVelocityMeasurementPeriod(handle, 0, 0);
	    CANifierJNI.JNI_ConfigVelocityMeasurementWindow(handle, 0, 0);
        CANifierJNI.JNI_ConfigClearPositionOnLimitF(handle, false, 0);
        CANifierJNI.JNI_ConfigClearPositionOnLimitR(handle, false, 0);
        CANifierJNI.JNI_ConfigClearPositionOnQuadIdx(handle, false, 0);
        CANifierJNI.JNI_ConfigSetCustomParam(handle, 0, 0, 0);
	    CANifierJNI.JNI_ConfigGetCustomParam(handle, 0, 0);
	    CANifierJNI.JNI_ConfigSetParameter(handle, 0, 0, 0, 0, 0);
	    CANifierJNI.JNI_ConfigGetParameter(handle, 0, 0, 0);
	    CANifierJNI.JNI_ConfigFactoryDefault(handle, 0);
	    CANifierJNI.JNI_SetStatusFramePeriod(handle, 0, 0, 0);
	    CANifierJNI.JNI_GetStatusFramePeriod(handle, 0, 0);
	    CANifierJNI.JNI_SetControlFramePeriod(handle, 0, 0);
	    CANifierJNI.JNI_GetFirmwareVersion(handle);
	    CANifierJNI.JNI_HasResetOccurred(handle);
	    CANifierJNI.JNI_GetFaults(handle);
	    CANifierJNI.JNI_GetStickyFaults(handle);
	    CANifierJNI.JNI_ClearStickyFaults(handle, 0);
	    CANifierJNI.JNI_GetBusVoltage(handle);
        //CANifierJNI.JNI_destroy_CANifier(handle);
        //CANifierJNI.JNI_destroy_AllCANifiers();
    }
}
