package com.ctre.phoenix.platform.can;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.platform.can.PlatformCANJNI;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;

import org.junit.jupiter.api.Test;

class PlatformCANTest {
   
    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() {
        char[] array3c = {'c', 'a', 'n'}; //Note that the size of this array is arbitrary

        PlatformCANJNI.JNI_SetCANInterface(array3c);

        //PlatformCANJNI.JNI_DestroyAll();

        //PlatformCANJNI.JNI_StartAll();
    }
}
