package com.ctre.phoenix;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import java.util.stream.Collectors;
import java.util.Map;
import java.util.HashMap;

import com.ctre.phoenix.motorcontrol.can.TalonSRXConfiguration;
import com.ctre.phoenix.motorcontrol.can.VictorSPXConfiguration;
import com.ctre.phoenix.sensors.PigeonIMUConfiguration;
import com.ctre.phoenix.CANifierConfiguration;

import com.ctre.phoenix.ErrorCodeString;
import com.ctre.phoenix.ErrorCodeDoubleString;
import com.ctre.phoenix.ConfigHelper;

class Error {
    
    @Test
    void configSetTimeout() {
        List<ErrorCodeString> errorCodes = new ArrayList<ErrorCodeString>();

        int timeoutMs = 1; //Minimum value to reduce the time required for this test
        int id = 1;

        TalonSRXConfiguration testTalonConfigs = new TalonSRXConfiguration();
        VictorSPXConfiguration testVictorConfigs = new VictorSPXConfiguration();
        PigeonIMUConfiguration testPigeonConfigs = new PigeonIMUConfiguration();
        CANifierConfiguration testCANifierConfigs = new CANifierConfiguration();

        ConfigHelper.ConfigAllIndividualTalon(id, timeoutMs, testTalonConfigs, errorCodes);

        ConfigHelper.ConfigAllIndividualVictor(id, timeoutMs, testVictorConfigs, errorCodes);

        ConfigHelper.ConfigAllIndividualPigeon(id, timeoutMs, testPigeonConfigs, errorCodes);

        ConfigHelper.ConfigAllIndividualCANifier(id, timeoutMs, testCANifierConfigs, errorCodes);

        ConfigHelper.ConfigFactoryDefaultTalon(id, timeoutMs, errorCodes);

        ConfigHelper.ConfigFactoryDefaultVictor(id, timeoutMs, errorCodes);

        ConfigHelper.ConfigFactoryDefaultPigeon(id, timeoutMs, errorCodes);

        ConfigHelper.ConfigFactoryDefaultCANifier(id, timeoutMs, errorCodes);

        ConfigHelper.ConfigAllTalon(id, timeoutMs, testTalonConfigs, errorCodes);

        ConfigHelper.ConfigAllVictor(id, timeoutMs, testVictorConfigs, errorCodes);

        ConfigHelper.ConfigAllPigeon(id, timeoutMs, testPigeonConfigs, errorCodes);

        ConfigHelper.ConfigAllCANifier(id, timeoutMs, testCANifierConfigs, errorCodes);

        for(ErrorCodeString err : errorCodes) { 
            assertEquals(ErrorCode.SigNotUpdated, err.code, err.string);
        }
    }
    @Test
    void getParamTimeout() { 
 
        List<ErrorCodeDoubleString> errorCodes = new ArrayList<ErrorCodeDoubleString>();  
    
        int id = 0;
        int timeoutMs = 0;

        Map<ParamEnum, ParamEnumParameters> talonEnums = new HashMap<ParamEnum, ParamEnumParameters>();
        Map<ParamEnum, ParamEnumParameters> victorEnums = new HashMap<ParamEnum, ParamEnumParameters>();
        Map<ParamEnum, ParamEnumParameters> pigeonEnums = new HashMap<ParamEnum, ParamEnumParameters>();
        Map<ParamEnum, ParamEnumParameters> canifierEnums = new HashMap<ParamEnum, ParamEnumParameters>();

        talonEnums.putAll(ParamHelper.genericParamEnumStrings);
        talonEnums.putAll(ParamHelper.sensorParamEnumStrings);
        talonEnums.putAll(ParamHelper.motControllerParamEnumStrings);
        talonEnums.putAll(ParamHelper.currentParamEnumStrings);

        victorEnums.putAll(ParamHelper.genericParamEnumStrings);
        victorEnums.putAll(ParamHelper.motControllerParamEnumStrings);
        
        pigeonEnums.putAll(ParamHelper.genericParamEnumStrings);
        pigeonEnums.putAll(ParamHelper.imuParamEnumStrings);

        canifierEnums.putAll(ParamHelper.genericParamEnumStrings);
        canifierEnums.putAll(ParamHelper.sensorParamEnumStrings);
        
        ParamHelper.GetAllParamsTalon(id, timeoutMs, talonEnums, errorCodes); 
        ParamHelper.GetAllParamsVictor(id, timeoutMs, victorEnums, errorCodes); 
        ParamHelper.GetAllParamsPigeon(id, timeoutMs, pigeonEnums, errorCodes); 
        ParamHelper.GetAllParamsCANifier(id, timeoutMs, canifierEnums, errorCodes); 
        
        for(ErrorCodeString err : errorCodes) { 
            assertEquals(ErrorCode.SigNotUpdated, err.code, err.string);
        }
    }
}
