package com.ctre.phoenix;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.CTRLoggerJNI;

import org.junit.jupiter.api.Test;

class CTRLoggerTest {
   
    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() {
        String origin = "test origin";
        String stackTrace = "test stackTrace";
        CTRLoggerJNI.JNI_Logger_Log((byte)0, origin, stackTrace);
    }
}   
