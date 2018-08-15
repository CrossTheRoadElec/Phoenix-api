#include "ParamHelper.h"
#include <memory>

void GetAllParamsTalon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);
    
    for(auto &paramPair : paramsToGet) {    
        double paramVal = testTalon->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs);
        ctre::phoenix::ErrorCode code = testTalon->GetLastError();
        errorCodes.push_back(std::make_pair(std::make_pair(paramVal, code), "testTalon->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
    }
}

void GetAllParamsVictor(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
    
    for(auto &paramPair : paramsToGet) {    
        double paramVal = testVictor->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs);
        ctre::phoenix::ErrorCode code = testVictor->GetLastError();
        errorCodes.push_back(std::make_pair(std::make_pair(paramVal, code), "testTalon->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
    }
}

void GetAllParamsPigeon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
    for(auto &paramPair : paramsToGet) {    
        double paramVal = testPigeon->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs);
        ctre::phoenix::ErrorCode code = testPigeon->GetLastError();
        errorCodes.push_back(std::make_pair(std::make_pair(paramVal, code), "testTalon->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
    }
}

void GetAllParamsCANifier(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    for(auto &paramPair : paramsToGet) {    
        double paramVal = testCANifier->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs);
        ctre::phoenix::ErrorCode code = testCANifier->GetLastError();
        errorCodes.push_back(std::make_pair(std::make_pair(paramVal, code), "testTalon->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
    }
}



//void SetAllParamsTalon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
//    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);
//    for(auto &paramPair : paramsToGet) {    
//        errorCodes.push_back(std::make_pair(std::pair<double, ctre::phoenix::ErrorCode>(testTalon->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs), testTalon->GetLastError()), "testTalon->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
//    }
//}
//
//void SetAllParamsVictor(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
//    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
//    for(auto &paramPair : paramsToGet) {    
//        errorCodes.push_back(std::make_pair(std::pair<double, ctre::phoenix::ErrorCode>(testVictor->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs), testVictor->GetLastError()), "testVictor->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
//    }
//}
//
//void SetAllParamsPigeon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
//    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
//    for(auto &paramPair : paramsToGet) {    
//        errorCodes.push_back(std::make_pair(std::pair<double, ctre::phoenix::ErrorCode>(testCANifier->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs), testCANifier->GetLastError()), "testCANifier->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
//    }
//}
//
//void SetAllParamsCANifier(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeDoubleString &errorCodes) {
//    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
//    
//    for(auto &paramPair : paramsToGet) {    
//        errorCodes.push_back(std::make_pair(std::pair<double, ctre::phoenix::ErrorCode>(testCANifier->ConfigGetParameter(paramPair.second.paramEnum, 0, timeoutMs), testCANifier->GetLastError()), "testCANifier->ConfigGetParameter(" + paramPair.first +", 0, " + std::to_string(timeoutMs) + ");"));
//    }
//}
