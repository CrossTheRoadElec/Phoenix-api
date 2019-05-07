/*
 *  Software License Agreement
 *
 * Copyright (C) Cross The Road Electronics.  All rights
 * reserved.
 * 
 * Cross The Road Electronics (CTRE) licenses to you the right to 
 * use, publish, and distribute copies of CRF (Cross The Road) firmware files (*.crf) and Software
 * API Libraries ONLY when in use with Cross The Road Electronics hardware products.
 * 
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * CROSS THE ROAD ELECTRONICS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
 */
package com.ctre.phoenix.platform;

/**
 * Class for simulation as a platform
 */
public class PlatformSim {
    
    /**
     * Create Device
     * @param type Device Type
     * @param id Device ID
     * @return ErrorCode
     */
    public static int simCreate(DeviceType type, int id) {
        return PlatformJNI.JNI_SimCreate(type.value, id);
    }
    
    /**
     * Destroy Device
     * @param type Device Type
     * @param id Device ID
     * @return ErrorCode
     */
    public static int simDestroy(DeviceType type, int id) {
        return PlatformJNI.JNI_SimDestroy(type.value, id);
    }
    
    /**
     * Destroy all devices in sim
     * @return ErrorCode
     */
    public static int simDestroyAll() {
        return PlatformJNI.JNI_SimDestroyAll();
    }
   
    /**
     * Get configs of simulated device
     * @param type Device Type
     * @param param Param to get 
     * @param valueToSend subValue
     * @param ordinal Ordinal
     * @param id Device ID
     * @return Parameter requested
     */
    public static int simConfigGet(DeviceType type, int param, int valueToSend, int ordinal, int id) {
        return PlatformJNI.JNI_SimConfigGet(type.value, param, valueToSend, ordinal, id);
    }

    /**
     * Sets configs of simulated device
     * @param type Device Type
     * @param param Param to send
     * @param value Value to send
     * @param subValue Subvalue to send
     * @param ordinal Ordinal
     * @param id Device ID
     * @return ErrorCode
     */
    public static int simConfigSet(DeviceType type, int param, int value, int subValue, int ordinal, int id) {
        return PlatformJNI.JNI_SimConfigSet(type.value, param, value, subValue, ordinal, id);
    }

}
