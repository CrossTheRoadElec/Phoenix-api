#include <gtest/gtest.h>
#include "ConfigHelper.h"
#include "ParamHelper.h"
#include "ctre/phoenix/platform/Platform.h"
#include <chrono>
#include <thread>
#include <random>

std::string baseErrString = "Failed due to error from ";
std::default_random_engine generator;
std::uniform_int_distribution<int> idDistribution(0,62);

TEST(Error, ConfigSetTimeoutError) {
    int timeoutMs = 1;
    int id;    

    ctre::phoenix::motorcontrol::can::TalonSRXConfiguration testTalonConfigs;
    ctre::phoenix::motorcontrol::can::VictorSPXConfiguration testVictorConfigs;
    ctre::phoenix::sensors::PigeonIMUConfiguration testPigeonConfigs;
    ctre::phoenix::CANifierConfiguration testCANifierConfigs;
  
    ErrorCodeString errorCodes;
 
    id = idDistribution(generator);
    ConfigAllIndividualTalon(id, timeoutMs, testTalonConfigs, errorCodes);

    id = idDistribution(generator);
    ConfigAllIndividualVictor(id, timeoutMs, testVictorConfigs, errorCodes);

    id = idDistribution(generator);
    ConfigAllIndividualPigeon(id, timeoutMs, testPigeonConfigs, errorCodes);

    id = idDistribution(generator);
    ConfigAllIndividualCANifier(id, timeoutMs, testCANifierConfigs, errorCodes);

    id = idDistribution(generator);
    ConfigFactoryDefaultTalon(id, timeoutMs, errorCodes);

    id = idDistribution(generator);
    ConfigFactoryDefaultVictor(id, timeoutMs, errorCodes);

    id = idDistribution(generator);
    ConfigFactoryDefaultPigeon(id, timeoutMs, errorCodes);

    id = idDistribution(generator);
    ConfigFactoryDefaultCANifier(id, timeoutMs, errorCodes);

    id = idDistribution(generator);
    ConfigAllTalon(id, timeoutMs, testTalonConfigs, errorCodes);

    id = idDistribution(generator);
    ConfigAllVictor(id, timeoutMs, testVictorConfigs, errorCodes);

    id = idDistribution(generator);
    ConfigAllPigeon(id, timeoutMs, testPigeonConfigs, errorCodes);

    id = idDistribution(generator);
    ConfigAllCANifier(id, timeoutMs, testCANifierConfigs, errorCodes);

    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }
}

TEST(Error, GetParamTimeoutError) {

    ErrorCodeString errorCodes;

    ParamEnumString talonEnums;    
    ParamEnumString victorEnums;    
    ParamEnumString pigeonEnums;    
    ParamEnumString canifierEnums;    

    talonEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    talonEnums.insert(sensorParamEnumStrings.begin(), sensorParamEnumStrings.end()); 
    talonEnums.insert(motControllerParamEnumStrings.begin(), motControllerParamEnumStrings.end()); 
    talonEnums.insert(currentParamEnumStrings.begin(), currentParamEnumStrings.end()); 
    
    victorEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    victorEnums.insert(motControllerParamEnumStrings.begin(), motControllerParamEnumStrings.end()); 
    
    pigeonEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    pigeonEnums.insert(imuParamEnumStrings.begin(), imuParamEnumStrings.end()); 
    
    canifierEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    canifierEnums.insert(sensorParamEnumStrings.begin(), sensorParamEnumStrings.end()); 
    
    int id;
    int timeoutMs = 1;
  
    id = idDistribution(generator);
    GetAllParamsTalon(id, timeoutMs, talonEnums, errorCodes); 
    
    id = idDistribution(generator);
    GetAllParamsVictor(id, timeoutMs, victorEnums, errorCodes); 
    
    id = idDistribution(generator);
    GetAllParamsPigeon(id, timeoutMs, pigeonEnums, errorCodes); 
    
    id = idDistribution(generator);
    GetAllParamsCANifier(id, timeoutMs, canifierEnums, errorCodes); 
 
    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }

}

TEST(Error, SetParamTimeoutError) {

    ErrorCodeString errorCodes;

    ParamEnumString talonEnums;    
    ParamEnumString victorEnums;    
    ParamEnumString pigeonEnums;    
    ParamEnumString canifierEnums;    

    talonEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    talonEnums.insert(sensorParamEnumStrings.begin(), sensorParamEnumStrings.end()); 
    talonEnums.insert(motControllerParamEnumStrings.begin(), motControllerParamEnumStrings.end()); 
    talonEnums.insert(currentParamEnumStrings.begin(), currentParamEnumStrings.end()); 
    
    victorEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    victorEnums.insert(motControllerParamEnumStrings.begin(), motControllerParamEnumStrings.end()); 
    
    pigeonEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    pigeonEnums.insert(imuParamEnumStrings.begin(), imuParamEnumStrings.end()); 
    
    canifierEnums.insert(genericParamEnumStrings.begin(), genericParamEnumStrings.end()); 
    canifierEnums.insert(sensorParamEnumStrings.begin(), sensorParamEnumStrings.end()); 
    
    int id;
    int timeoutMs = 1;
  
    id = idDistribution(generator);
    SetAllParamsTalon(id, timeoutMs, talonEnums, errorCodes); 
    
    id = idDistribution(generator);
    SetAllParamsVictor(id, timeoutMs, victorEnums, errorCodes); 
    
    id = idDistribution(generator);
    SetAllParamsPigeon(id, timeoutMs, pigeonEnums, errorCodes); 
    
    id = idDistribution(generator);
    SetAllParamsCANifier(id, timeoutMs, canifierEnums, errorCodes); 
 
    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }

}

TEST(DeviceID, Get) {
    for(int i = 0; i < 63; i++) {
        std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(i);
        std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(i);
        std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(i);
        std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(i);

        ASSERT_EQ(testTalon->GetDeviceID(), i) << "Failed at Talon id " << i;
        ASSERT_EQ(testVictor->GetDeviceID(), i) << "Failed at Victor id " << i;
        ASSERT_EQ(testPigeon->GetDeviceNumber(), i) << "Failed at Pigeon id " << i;
        ASSERT_EQ(testCANifier->GetDeviceNumber(), i) << "Failed at CANifier id " << i;
    }
} 

TEST(Simulator, Load) {
    //In windows, this becomes increasingly slower per talon as the number of talons loaded increases (~300 ms for 8 Talons, ~10000 ms for 32 talons, and ~32000 ms for 63 talons).
    //Based on some testing, the time required to copy the file and the time required to get a function pointer expand over time. 
    //No such increasing cost occurs in linux and the load time is generally far lower.
    //This is likely because the while loop in firmware uses as much cpu as it can    

    //Linux now has the exact same issue

    for(int i = 0; i < 4; i++) { 
        int id = idDistribution(generator);
        ctre::phoenix::platform::SimCreate(ctre::phoenix::platform::DeviceType::TalonSRXType, id);  
    }
    
    //ctre::phoenix::platform::SimDestroyAll();  
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); //Guarantee all msgs are stale
}

//TEST(Param, ParamSetGet) {
//    ctre::phoenix::platform::SimCreate(ctre::phoenix::platform::DeviceType::TalonSRXType, 0);  
//}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
