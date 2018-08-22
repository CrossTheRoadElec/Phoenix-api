#include <gtest/gtest.h>

#include "ConfigHelper.h"
#include "ParamHelper.h"
#include "ctre/phoenix/platform/PlatformSim.h"
#include "ctre/phoenix/platform/can/PlatformCAN.h"
#include <chrono>
#include <thread>

std::string baseErrString = "Failed due to error from ";

#ifdef SIMULATION_TEST

std::uniform_int_distribution<int> idDistribution(0, 62);

#else

std::uniform_int_distribution<int> idDistribution(1, 62); //0 is reserved for wired devices (for now)

#endif

//Each test has its own random engine to ensure that each test mey be individually replicated (with the correct seed)

TEST(Error, ConfigSetTimeoutError) {
    std::default_random_engine engine{static_cast<unsigned int>(testing::UnitTest::GetInstance()->random_seed())};

    ctre::phoenix::platform::can::PlatformCAN::StartAll();    

    int timeoutMs = 1;
    int id;    

    ctre::phoenix::motorcontrol::can::TalonSRXConfiguration testTalonConfigs;
    ctre::phoenix::motorcontrol::can::VictorSPXConfiguration testVictorConfigs;
    ctre::phoenix::sensors::PigeonIMUConfiguration testPigeonConfigs;
    ctre::phoenix::CANifierConfiguration testCANifierConfigs;
  
    ErrorCodeString errorCodes;
 
    id = idDistribution(engine);
    ConfigAllIndividualTalon(id, timeoutMs, testTalonConfigs, errorCodes);

    id = idDistribution(engine);
    ConfigAllIndividualVictor(id, timeoutMs, testVictorConfigs, errorCodes);

    id = idDistribution(engine);
    ConfigAllIndividualPigeon(id, timeoutMs, testPigeonConfigs, errorCodes);

    id = idDistribution(engine);
    ConfigAllIndividualCANifier(id, timeoutMs, testCANifierConfigs, errorCodes);

    id = idDistribution(engine);
    ConfigFactoryDefaultTalon(id, timeoutMs, errorCodes);

    id = idDistribution(engine);
    ConfigFactoryDefaultVictor(id, timeoutMs, errorCodes);

    id = idDistribution(engine);
    ConfigFactoryDefaultPigeon(id, timeoutMs, errorCodes);

    id = idDistribution(engine);
    ConfigFactoryDefaultCANifier(id, timeoutMs, errorCodes);

    id = idDistribution(engine);
    ConfigAllTalon(id, timeoutMs, testTalonConfigs, errorCodes);

    id = idDistribution(engine);
    ConfigAllVictor(id, timeoutMs, testVictorConfigs, errorCodes);

    id = idDistribution(engine);
    ConfigAllPigeon(id, timeoutMs, testPigeonConfigs, errorCodes);

    id = idDistribution(engine);
    ConfigAllCANifier(id, timeoutMs, testCANifierConfigs, errorCodes);

    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }
   
    ctre::phoenix::platform::can::PlatformCAN::DestroyAll();    
}

TEST(Error, GetParamTimeoutError) {
    std::default_random_engine engine{static_cast<unsigned int>(testing::UnitTest::GetInstance()->random_seed())};

    ctre::phoenix::platform::can::PlatformCAN::StartAll();    

    ErrorCodeString errorCodes;

    ParamEnumSet enums;    

    enums.insert(genericParamEnumSets.begin(), genericParamEnumSets.end()); 
    enums.insert(sensorParamEnumSets.begin(), sensorParamEnumSets.end()); 
    enums.insert(motControllerParamEnumSets.begin(), motControllerParamEnumSets.end()); 
    enums.insert(currentParamEnumSets.begin(), currentParamEnumSets.end()); 
    enums.insert(imuParamEnumSets.begin(), imuParamEnumSets.end()); 
    
    std::map<ctre::phoenix::platform::DeviceType, int> idMap = {{ctre::phoenix::platform::DeviceType::TalonSRXType, idDistribution(engine)}, {ctre::phoenix::platform::DeviceType::VictorSPXType, idDistribution(engine)}, {ctre::phoenix::platform::DeviceType::CANifierType, idDistribution(engine)}, {ctre::phoenix::platform::DeviceType::PigeonIMUType, idDistribution(engine)}};
    int timeoutMs = 1;
  
    GetAllParams(idMap, timeoutMs, enums, errorCodes); 
 
    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }

    ctre::phoenix::platform::can::PlatformCAN::DestroyAll();    
}

TEST(Error, SetParamTimeoutError) {
    ctre::phoenix::platform::can::PlatformCAN::StartAll();    

    std::default_random_engine engine{static_cast<unsigned int>(testing::UnitTest::GetInstance()->random_seed())};

    ErrorCodeString errorCodes;
    
    ParamEnumSet enums;

    enums.insert(genericParamEnumSets.begin(), genericParamEnumSets.end()); 
    enums.insert(sensorParamEnumSets.begin(), sensorParamEnumSets.end()); 
    enums.insert(motControllerParamEnumSets.begin(), motControllerParamEnumSets.end()); 
    enums.insert(currentParamEnumSets.begin(), currentParamEnumSets.end()); 
    enums.insert(imuParamEnumSets.begin(), imuParamEnumSets.end()); 
   
    GenerateSendValues(enums, engine);
 
    std::map<ctre::phoenix::platform::DeviceType, int> idMap = {{ctre::phoenix::platform::DeviceType::TalonSRXType, idDistribution(engine)}, {ctre::phoenix::platform::DeviceType::VictorSPXType, idDistribution(engine)}, {ctre::phoenix::platform::DeviceType::CANifierType, idDistribution(engine)}, {ctre::phoenix::platform::DeviceType::PigeonIMUType, idDistribution(engine)}};

    int timeoutMs = 1;
 
    SetAllParams(idMap, timeoutMs, enums, errorCodes); 
 
    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::SIG_NOT_UPDATED, err.first) << baseErrString << err.second;
    }

    ctre::phoenix::platform::can::PlatformCAN::DestroyAll();    
}

TEST(DeviceID, Get) {

    ctre::phoenix::platform::can::PlatformCAN::StartAll();    
    
    for(int i = 0; i < 63; i++) {
        std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_unique<ctre::phoenix::motorcontrol::can::TalonSRX>(i);
        std::unique_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_unique<ctre::phoenix::motorcontrol::can::VictorSPX>(i);
        std::unique_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_unique<ctre::phoenix::sensors::PigeonIMU>(i);
        std::unique_ptr<ctre::phoenix::CANifier> testCANifier = std::make_unique<ctre::phoenix::CANifier>(i);

        ASSERT_EQ(testTalon->GetDeviceID(), i) << "Failed at Talon id " << i;
        ASSERT_EQ(testVictor->GetDeviceID(), i) << "Failed at Victor id " << i;
        ASSERT_EQ(testPigeon->GetDeviceNumber(), i) << "Failed at Pigeon id " << i;
        ASSERT_EQ(testCANifier->GetDeviceNumber(), i) << "Failed at CANifier id " << i;
    }
    
    ctre::phoenix::platform::can::PlatformCAN::DestroyAll();    
} 

#ifdef SIMULATION_TEST

TEST(Simulator, Load) {
    std::default_random_engine engine{static_cast<unsigned int>(testing::UnitTest::GetInstance()->random_seed())};
    
    ctre::phoenix::platform::can::PlatformCAN::StartAll();    
    //In windows, this becomes increasingly slower per talon as the number of talons loaded increases (~300 ms for 8 Talons, ~10000 ms for 32 talons, and ~32000 ms for 63 talons).
    //Based on some testing, the time required to copy the file and the time required to get a function pointer expand over time. 
    //No such increasing cost occurs in linux and the load time is generally far lower.
    //This is likely because the while loop in firmware uses as much cpu as it can    

    //Linux now has the exact same issue

    for(int i = 0; i < 4; i++) { 
        int id = idDistribution(engine);
        ctre::phoenix::platform::PlatformSim::SimCreate(ctre::phoenix::platform::DeviceType::TalonSRXType, id);  
    }
    
    ctre::phoenix::platform::PlatformSim::SimDestroyAll();  
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); //Guarantee all msgs are stale

    ctre::phoenix::platform::can::PlatformCAN::DestroyAll();    
}

#endif


TEST(Param, ConfigSetGet) {
   
    ctre::phoenix::platform::can::PlatformCAN::StartAll();    
    
    std::default_random_engine engine{static_cast<unsigned int>(testing::UnitTest::GetInstance()->random_seed())};
    
    ErrorCodeString errorCodes;
    
    ParamEnumSet enums;

    enums.insert(genericParamEnumSets.begin(), genericParamEnumSets.end()); 
    enums.insert(sensorParamEnumSets.begin(), sensorParamEnumSets.end()); 
    enums.insert(motControllerParamEnumSets.begin(), motControllerParamEnumSets.end()); 
    
    GenerateSendValues(enums, engine);

    int talonId = 0; //Id assumed 0 for non sim

    #ifdef SIMULATION_TEST
    
    talonId = idDistribution(engine);
    
    ctre::phoenix::platform::PlatformSim::SimCreate(ctre::phoenix::platform::DeviceType::TalonSRXType, talonId);

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); //Guarantee devices are initialized
    
    #endif
 
    std::map<ctre::phoenix::platform::DeviceType, int> idMap = {{ctre::phoenix::platform::DeviceType::TalonSRXType, talonId}};

    int timeoutMs = 500;
  
    SetAllParams(idMap, timeoutMs, enums, errorCodes); 
    
    GetAllParams(idMap, timeoutMs, enums, errorCodes); 

    for(const auto &err : errorCodes) { 
        ASSERT_EQ(ctre::phoenix::ErrorCode::OKAY, err.first) << baseErrString << err.second;
    }
    
    EqualityCheck(enums, idMap);     
    
    #ifdef SIMULATION_TEST
    
    ctre::phoenix::platform::PlatformSim::SimDestroyAll();  

    std::this_thread::sleep_for(std::chrono::milliseconds(300)); //Guarantee all msgs are stale
    
    #endif
   
    ctre::phoenix::platform::can::PlatformCAN::DestroyAll();    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    if(argc > 1) {
        
        std::cout << "Using interface: " << argv[1] << " (Note: this option only matters for some platforms)" << std::endl;
        ctre::phoenix::platform::can::PlatformCAN::SetCANInterface(argv[1]);
    }
   
    ctre::phoenix::platform::can::PlatformCAN::DestroyAll();    

    return RUN_ALL_TESTS();
}
