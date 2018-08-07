package com.ctre.phoenix;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.ctre.phoenix.motorcontrol.can.VictorSPX;
import com.ctre.phoenix.sensors.PigeonIMU;
import com.ctre.phoenix.CANifier;

import org.junit.jupiter.api.Test;

class DeviceID {
    
    @Test
    void Get() {
       //System.loadLibrary("CTRE_PhoenixCanutils");
        for(int i = 0; i < 63; i++) { 
            TalonSRX testTalon = new TalonSRX(i);
            VictorSPX testVictor = new VictorSPX(i);
            PigeonIMU testPigeon = new PigeonIMU(i);
            CANifier testCANifier = new CANifier(i);

            assertEquals(testTalon.getDeviceID(),       i,     "Failed at Talon id " + String.valueOf(i));
            assertEquals(testVictor.getDeviceID(),      i,    "Failed at Victor id " + String.valueOf(i));
            assertEquals(testPigeon.getDeviceID(),      i,    "Failed at Pigeon id " + String.valueOf(i));
            assertEquals(testCANifier.getDeviceID(),    i,  "Failed at CANifier id " + String.valueOf(i));
        }
    }
}
