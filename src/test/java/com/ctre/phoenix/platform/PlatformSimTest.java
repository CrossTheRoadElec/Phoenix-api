package com.ctre.phoenix.platform;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.platform.PlatformJNI;

import org.junit.jupiter.api.Test;

import java.lang.Thread;

class PlatformSimTest {
   
    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() throws InterruptedException {
        PlatformJNI.JNI_SimCreate(0, 0);
        PlatformJNI.JNI_SimDestroy(0, 0);
        PlatformJNI.JNI_SimDestroyAll();
        PlatformJNI.JNI_SimConfigGet(0, 0, 0, 0, 0);
        PlatformJNI.JNI_SimConfigSet(0, 0, 0, 0, 0, 0);
        
        Thread.sleep(300); //Clear messages
    }

    @Test
    void Create() throws InterruptedException {
        for(int i = 1; i < 5; i++) {
            PlatformSim.simCreate(DeviceType.TalonSRX, i);  
        }

        PlatformSim.simDestroyAll();

        Thread.sleep(300); //Clear messages

    }
}
