package com.ctre.phoenix.unmanaged;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.unmanaged.UnmanagedJNI;

import org.junit.jupiter.api.Test;

class UnmanagedTest {
   
    //Just see if these functions can be called without regard for success
    //Some may have been indirectly called in other tests

    @Test
    void NoJNICrash() {
        UnmanagedJNI.JNI_FeedEnable(0);
        UnmanagedJNI.JNI_GetEnableState();
    }
}
