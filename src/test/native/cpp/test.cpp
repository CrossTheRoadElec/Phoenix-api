#include <gtest/gtest.h>
#include "ConfigHelper.h"
#include "ParamHelper.h"
#include "ctre/phoenix/platform/Platform.h"
#include <chrono>
#include <thread>

std::string baseErrString = "Failed due to error from ";

TEST(Error, ConfigSetTimeoutError) {
    int id = 0;
    int timeoutMs = 1;
    
    ctre::phoenix::motorcontrol::can::TalonSRXConfiguration testTalonConfigs;
    ctre::phoenix::motorcontrol::can::VictorSPXConfiguration testVictorConfigs;
    ctre::phoenix::sensors::PigeonIMUConfiguration testPigeonConfigs;
    ctre::phoenix::CANifierConfiguration testCANifierConfigs;
  
    ErrorCodeString tempVector;
    ErrorCodeString errorCodes;
 
    ConfigAllIndividualTalon( id,  timeoutMs, testTalonConfigs, errorCodes);

    ConfigAllIndividualVictor( id,  timeoutMs, testVictorConfigs, errorCodes);

    ConfigAllIndividualPigeon( id,  timeoutMs, testPigeonConfigs, errorCodes);

    ConfigAllIndividualCANifier( id,  timeoutMs, testCANifierConfigs, errorCodes);

    ConfigFactoryDefaultTalon( id,  timeoutMs, errorCodes);

    ConfigFactoryDefaultVictor( id,  timeoutMs, errorCodes);

    ConfigFactoryDefaultPigeon( id,  timeoutMs, errorCodes);

    ConfigFactoryDefaultCANifier( id,  timeoutMs, errorCodes);

    ConfigAllTalon( id,  timeoutMs, testTalonConfigs, errorCodes);

    ConfigAllVictor( id,  timeoutMs, testVictorConfigs, errorCodes);

    ConfigAllPigeon( id,  timeoutMs, testPigeonConfigs, errorCodes);

    ConfigAllCANifier( id,  timeoutMs, testCANifierConfigs, errorCodes);

    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }
}

TEST(Error, GetParamTimeoutError) {

    ErrorCodeDoubleString errorCodes;

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
    
    int id = 0;
    int timeoutMs = 1;
  
    GetAllParamsTalon(id, timeoutMs, talonEnums, errorCodes); 
    GetAllParamsVictor(id, timeoutMs, victorEnums, errorCodes); 
    GetAllParamsPigeon(id, timeoutMs, pigeonEnums, errorCodes); 
    GetAllParamsCANifier(id, timeoutMs, canifierEnums, errorCodes); 
 
    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first.second) << baseErrString << err.second;
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


    #if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
    
    for(int i = 0; i < 8; i++) { 
    
    #else

    for(int i = 0; i < 63; i++) { 

    #endif

        ctre::phoenix::platform::SimCreate(ctre::phoenix::platform::DeviceType::TalonSRX, i);  
    }
    
    ctre::phoenix::platform::SimDestroyAll();  
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); //Guarantee all msgs are stale
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
