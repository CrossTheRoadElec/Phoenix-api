#include "ParamHelper.h"
#include <memory>

void GetAllParamsTalon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);
    
    for(auto &paramPair : paramsToGet) {    
        paramPair.second.value = testTalon->ConfigGetParameter(paramPair.first, paramPair.second.ordinal, timeoutMs);
        ctre::phoenix::ErrorCode code = testTalon->GetLastError();
        errorCodes.push_back(std::make_pair(code, "testTalon->ConfigGetParameter(" + paramPair.second.name + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ");"));
    }
}

void GetAllParamsVictor(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
    
    for(auto &paramPair : paramsToGet) {    
        paramPair.second.value = testVictor->ConfigGetParameter(paramPair.first, paramPair.second.ordinal, timeoutMs);
        ctre::phoenix::ErrorCode code = testVictor->GetLastError();
        errorCodes.push_back(std::make_pair(code, "testVictor->ConfigGetParameter(" + paramPair.second.name + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ");"));
    }
}

void GetAllParamsPigeon(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
    for(auto &paramPair : paramsToGet) {    
        paramPair.second.value = testPigeon->ConfigGetParameter(paramPair.first, paramPair.second.ordinal, timeoutMs);
        ctre::phoenix::ErrorCode code = testPigeon->GetLastError();
        errorCodes.push_back(std::make_pair(code, "testPigeon->ConfigGetParameter(" + paramPair.second.name + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ");"));
    }
}

void GetAllParamsCANifier(int id, int timeoutMs, ParamEnumString &paramsToGet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    for(auto &paramPair : paramsToGet) {    
        paramPair.second.value = testCANifier->ConfigGetParameter(paramPair.first, paramPair.second.ordinal, timeoutMs);
        ctre::phoenix::ErrorCode code = testCANifier->GetLastError();
        errorCodes.push_back(std::make_pair(code, "testCANifier->ConfigGetParameter(" + paramPair.second.name + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ");"));
    }
}



void SetAllParamsTalon(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon = std::make_shared<ctre::phoenix::motorcontrol::can::TalonSRX>(id);
    for(auto &paramPair : paramsToSet) {    
        errorCodes.push_back(std::make_pair(testTalon->ConfigSetParameter(paramPair.first, paramPair.second.value, paramPair.second.subValue, paramPair.second.ordinal, timeoutMs), "testTalon->ConfigSetParameter(" + std::to_string(paramPair.first) + ", " + std::to_string(paramPair.second.value) + ", " + std::to_string(paramPair.second.subValue) + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ")"));
    }
}

void SetAllParamsVictor(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor = std::make_shared<ctre::phoenix::motorcontrol::can::VictorSPX>(id);
    for(auto &paramPair : paramsToSet) {    
        errorCodes.push_back(std::make_pair(testVictor->ConfigSetParameter(paramPair.first, paramPair.second.value, paramPair.second.subValue, paramPair.second.ordinal, timeoutMs), "testVictor->ConfigSetParameter(" + std::to_string(paramPair.first) + ", " + std::to_string(paramPair.second.value) + ", " + std::to_string(paramPair.second.subValue) + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ")"));
    }
}

void SetAllParamsPigeon(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon = std::make_shared<ctre::phoenix::sensors::PigeonIMU>(id);
    for(auto &paramPair : paramsToSet) {    
        errorCodes.push_back(std::make_pair(testPigeon->ConfigSetParameter(paramPair.first, paramPair.second.value, paramPair.second.subValue, paramPair.second.ordinal, timeoutMs), "testPigeon->ConfigSetParameter(" + std::to_string(paramPair.first) + ", " + std::to_string(paramPair.second.value) + ", " + std::to_string(paramPair.second.subValue) + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ")"));
    }
}

void SetAllParamsCANifier(int id, int timeoutMs, const ParamEnumString &paramsToSet, ErrorCodeString &errorCodes) {
    std::shared_ptr<ctre::phoenix::CANifier> testCANifier = std::make_shared<ctre::phoenix::CANifier>(id);
    for(auto &paramPair : paramsToSet) {    
        errorCodes.push_back(std::make_pair(testCANifier->ConfigSetParameter(paramPair.first, paramPair.second.value, paramPair.second.subValue, paramPair.second.ordinal, timeoutMs), "testCANifier->ConfigSetParameter(" + std::to_string(paramPair.first) + ", " + std::to_string(paramPair.second.value) + ", " + std::to_string(paramPair.second.subValue) + ", " + std::to_string(paramPair.second.ordinal) + ", " + std::to_string(timeoutMs) + ")"));
    }
}
