package com.ctre.phoenix.platform;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.platform.PlatformJNI;

import org.junit.jupiter.api.Test;

class PlatformTest {
   
    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() {
        PlatformJNI.JNI_SimCreate(0, 0);
        PlatformJNI.JNI_SimConfigGet(0, 0, 0, 0, 0);
        PlatformJNI.JNI_SimConfigSet(0, 0, 0, 0, 0, 0);
    }

    @Test
    void Create() {
        for(int i = 0; i < 8; i++) {
            Platform.simCreate(DeviceType.TalonSRX, i);  
        }
    }
}
