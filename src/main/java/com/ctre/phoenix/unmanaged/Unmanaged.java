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
package com.ctre.phoenix.unmanaged;

/**
 * Handles enabling when used in a non-FRC manner
 */
public class Unmanaged {
    /**
     * Feed the robot enable.
     * This function does nothing on a roborio during FRC use.
     * @param timeoutMs Timeout before disabling
     */
    public static void feedEnable(int timeoutMs) {
        UnmanagedJNI.JNI_FeedEnable(timeoutMs);
    }

    /**
     * @return true if non-FRC enabled
     */
    public static boolean getEnableState() {
        return  UnmanagedJNI.JNI_GetEnableState();
    }

    /**
     * @return Phoenix version
     */
    public static int getPhoenixVersion() {
        return UnmanagedJNI.JNI_GetPhoenixVersion();
    }

    /**
     * Calling this function will load and start
     * the Phoenix background tasks.
     * 
     * This can be useful if you need the
     * Enable/Disable functionality for CAN devices
     * but aren't using any of the CAN device classes.
     * 
     * This function does NOT need to be called if
     * you are using any of the Phoenix CAN device classes.
     */
    public static void loadPhoenix() {
        UnmanagedJNI.JNI_LoadPhoenix();
    }
}
