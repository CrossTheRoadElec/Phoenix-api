package com.ctre.phoenix;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.platform.Platform;
import com.ctre.phoenix.platform.DeviceType;

import org.junit.jupiter.api.Test;

class Load {
    
    @Test
    void Create() {
        for(int i = 0; i < 16; i++) { //Fails after 22nd Talon?
            Platform.SimCreate(DeviceType.TalonSRX, i);  
        }
    }
}
