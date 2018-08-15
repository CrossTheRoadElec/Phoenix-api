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

public class Platform {
    
    public static int simCreate(DeviceType type, int id) {
        return PlatformJNI.JNI_SimCreate(type.value, id);
    }
    
    public static void simDestroy(DeviceType type, int id) {
        PlatformJNI.JNI_SimDestroy(type.value, id);
    }
    
    public static void simDestroyAll() {
        PlatformJNI.JNI_SimDestroyAll();
    }
   
    public static int simConfigGet(DeviceType type, int param, int valueToSend, int ordinal, int id) {
        return PlatformJNI.JNI_SimConfigGet(type.value, param, valueToSend, ordinal, id);
    }

    public static int simConfigSet(DeviceType type, int param, int value, int subValue, int ordinal, int id) {
        return PlatformJNI.JNI_SimConfigSet(type.value, param, value, subValue, ordinal, id);
    }

}
