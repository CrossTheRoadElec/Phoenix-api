#include "ParamHelper.h"
#include <memory>
#include <gtest/gtest.h>

double BasicCast (int32_t recieveValue, uint8_t /*recieveSubValue*/) {
    return recieveValue;
}

double SubValueCast (int32_t /*recieveValue*/, uint8_t recieveSubValue) {
    return recieveSubValue;
}

double RampConversion (double recieveValue) {
    return  1023.0 / 100.0 / recieveValue;
}

double Div_1023 (double recieveValue) {
    return recieveValue / 1023.0;
}

double Div_1023 (int32_t recieveValue, uint8_t /*recieveSubValue*/) {
    return Div_1023(recieveValue);
}

double ToFloat10_22 (int32_t recieveValue, uint8_t /*recieveSubValue*/) {
    return recieveValue * FXP_TO_FLOAT_10_22;
}

double Div_256 (int32_t recieveValue, uint8_t /*recieveSubValue*/) {
    return recieveValue / 256.0;
}

double Div_65536 (int32_t recieveValue, uint8_t /*recieveSubValue*/) {
    return recieveValue / 65536.0;
}

double DoubleInRange(std::vector<double> minMax, std::default_random_engine &engine) {
    std::uniform_real_distribution<double> unif(minMax[0], minMax[1]);
    return unif(engine);
}

double IntInRange(std::vector<double> minMax, std::default_random_engine &engine) {
    std::uniform_int_distribution<int>  unif(static_cast<int>(minMax[0]), static_cast<int>(minMax[1]));
    return unif(engine);
}
double OneOfValues(std::vector<double> values, std::default_random_engine &engine) {
    std::uniform_int_distribution<size_t>  unif(0, values.size() - 1);
    return values[unif(engine)];
}

void GenerateSendValues(ParamEnumSet &toFill, std::default_random_engine &engine) {
    for(auto &paramParameterSet : toFill) {
        for(auto &device : paramParameterSet.second.ValueSet) {
            for(auto &paramValues : device.second) {
                paramValues.second.sendValue = ( *paramParameterSet.second.generateToSend)(paramParameterSet.second.generationParams, engine);
            }
        }
    }
}

//We pass idMap so we can skip devices which aren't tested
void DefaultCheck(ParamEnumSet &toCheck, std::map<ctre::phoenix::platform::DeviceType, int> &idMap) {
    for(auto &paramParameterSet : toCheck) {
        for(auto &device : paramParameterSet.second.ValueSet) {
            auto iter = idMap.find(device.first);
            
            //make sure device is an instantiated device
            if(iter == idMap.end())
                continue;
            for(auto &paramValues : device.second) {
                ASSERT_NEAR(paramValues.second.defaultValue, (* paramParameterSet.second.recieveToSend)(paramValues.second.recieveValue, paramValues.second.recieveSubValue), paramParameterSet.second.equalityInterval) << "Failed due to error from param default equality check of " <<  paramParameterSet.second.name << ". recieveValue: " <<  paramValues.second.recieveValue << " recieveSubValue: " << unsigned(paramValues.second.recieveSubValue) << " Device: " << device.first << " Index (in hex): " << std::hex << paramValues.first << std::dec;
            }
        }
    }
}

void EqualityCheck(ParamEnumSet &toCheck, std::map<ctre::phoenix::platform::DeviceType, int> &idMap) {
    for(auto &paramParameterSet : toCheck) {
        for(auto &device : paramParameterSet.second.ValueSet) {
            auto iter = idMap.find(device.first);
            
            //make sure device is an instantiated device
            if(iter == idMap.end())
                continue;
            for(auto &paramValues : device.second) {
                ASSERT_NEAR(paramValues.second.sendValue, (* paramParameterSet.second.recieveToSend)(paramValues.second.recieveValue, paramValues.second.recieveSubValue), paramParameterSet.second.equalityInterval) << "Failed due to error from param equality check of " <<  paramParameterSet.second.name << ". recieveValue: " <<  paramValues.second.recieveValue << " recieveSubValue: " << unsigned(paramValues.second.recieveSubValue) << " Device: " << device.first << " Index (in hex): " << std::hex << paramValues.first << std::dec;
            }
        }
    }
}



void GetAllParams(std::map<ctre::phoenix::platform::DeviceType, int> &idMap, int timeoutMs, ParamEnumSet &paramsToGet, ErrorCodeString &errorCodes) {
    
    std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon;
    std::unique_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor;
    std::unique_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon;
    std::unique_ptr<ctre::phoenix::CANifier> testCANifier;
    
    for(auto &paramParameterSet : paramsToGet) {
        
        for(auto &device : paramParameterSet.second.ValueSet) {
            
            auto iter = idMap.find(device.first);
            
            //make sure device is an instantiated device
            if(iter == idMap.end())
                continue;

            int ArbId = iter->second;
            std::string deviceName = "";            

			switch (iter->first) {
			    case ctre::phoenix::platform::DeviceType::TalonSRXType:
                    testTalon = std::make_unique<ctre::phoenix::motorcontrol::can::TalonSRX>(iter->second);
                    ArbId |= 0x02040000;
                    deviceName = "testTalon";
                    break;
			    case ctre::phoenix::platform::DeviceType::VictorSPXType:
                    testVictor = std::make_unique<ctre::phoenix::motorcontrol::can::VictorSPX>(iter->second);
                    ArbId |= 0x01040000;
                    deviceName = "testVictor";
			    	break;
			    case ctre::phoenix::platform::DeviceType::CANifierType:
			    	testCANifier = std::make_unique<ctre::phoenix::CANifier>(iter->second);
                    ArbId |= 0x03040000;
                    deviceName = "testCANifier";
                    break;
			    case ctre::phoenix::platform::DeviceType::PigeonIMUType:
			    	testPigeon = std::make_unique<ctre::phoenix::sensors::PigeonIMU>(iter->second);
                    ArbId |= 0x15000000;
                    deviceName = "testPigeon";
			    	break;
            } 
            
            for(auto &paramValues : device.second) {
                int ordinal = 0;
                int valueToSend = 0;
                switch (paramParameterSet.second.paramUsage) {
                    case OrdinalUsedAsIndex:
                        ordinal = paramValues.first;
                        break;
                    case ValueUsedAsIndexAndBinaryORWithArbID:
                        valueToSend = paramValues.first | ArbId;
                        break;
                    default:
                        break;
                }
			    switch (iter->first) {
			        case ctre::phoenix::platform::DeviceType::TalonSRXType:
                        errorCodes.push_back(std::make_pair(testTalon->ConfigGetParameter(paramParameterSet.first, valueToSend, paramValues.second.recieveValue, paramValues.second.recieveSubValue, ordinal, timeoutMs), 
                            deviceName + "->ConfigGetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend) + ", paramValues.second.recieveValue, paramValues.second.recieveSubValue, " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
			        	break;
			        case ctre::phoenix::platform::DeviceType::VictorSPXType:
                        errorCodes.push_back(std::make_pair(testVictor->ConfigGetParameter(paramParameterSet.first, valueToSend, paramValues.second.recieveValue, paramValues.second.recieveSubValue, ordinal, timeoutMs), 
                            deviceName + "->ConfigGetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend) + ", paramValues.second.recieveValue, paramValues.second.recieveSubValue, " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
			        	break;
			        case ctre::phoenix::platform::DeviceType::CANifierType:
                        errorCodes.push_back(std::make_pair(testCANifier->ConfigGetParameter(paramParameterSet.first, valueToSend, paramValues.second.recieveValue, paramValues.second.recieveSubValue, ordinal, timeoutMs), 
                            deviceName + "->ConfigGetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend) + ", paramValues.second.recieveValue, paramValues.second.recieveSubValue, " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
                        break;
			        case ctre::phoenix::platform::DeviceType::PigeonIMUType:
                        errorCodes.push_back(std::make_pair(testPigeon->ConfigGetParameter(paramParameterSet.first, valueToSend, paramValues.second.recieveValue, paramValues.second.recieveSubValue, ordinal, timeoutMs), 
                            deviceName + "->ConfigGetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend) + ", paramValues.second.recieveValue, paramValues.second.recieveSubValue, " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
                        break;
                }
                
            }
        }
    }
}

void SetAllParams(std::map<ctre::phoenix::platform::DeviceType, int> &idMap, int timeoutMs, const ParamEnumSet &paramsToSet, ErrorCodeString &errorCodes) {
   
    std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon;
    std::unique_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor;
    std::unique_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon;
    std::unique_ptr<ctre::phoenix::CANifier> testCANifier;
    
    for(auto &paramParameterSet : paramsToSet) {
        
        for(auto &device : paramParameterSet.second.ValueSet) {
            
            auto iter = idMap.find(device.first);
            
            //make sure device is an instantiated device
            if(iter == idMap.end())
                continue;

            int ArbId = iter->second;
            std::string deviceName = "";         
            
			switch (iter->first) {
			    case ctre::phoenix::platform::DeviceType::TalonSRXType:
                    testTalon = std::make_unique<ctre::phoenix::motorcontrol::can::TalonSRX>(iter->second);
                    ArbId |= 0x02040000;
                    deviceName = "testTalon";
                    break;
			    case ctre::phoenix::platform::DeviceType::VictorSPXType:
                    testVictor = std::make_unique<ctre::phoenix::motorcontrol::can::VictorSPX>(iter->second);
                    ArbId |= 0x01040000;
                    deviceName = "testVictor";
			    	break;
			    case ctre::phoenix::platform::DeviceType::CANifierType:
			    	testCANifier = std::make_unique<ctre::phoenix::CANifier>(iter->second);
                    ArbId |= 0x03040000;
                    deviceName = "testCANifier";
                    break;
			    case ctre::phoenix::platform::DeviceType::PigeonIMUType:
			    	testPigeon = std::make_unique<ctre::phoenix::sensors::PigeonIMU>(iter->second);
                    ArbId |= 0x15000000;
                    deviceName = "testPigeon";
			    	break;
            } 
            
            for(auto &paramValues : device.second) {
                int ordinal = 0;
                double valueToSend = 0;
                uint8_t subValue = 0;
                switch (paramParameterSet.second.paramUsage) {
                    case OrdinalUsedAsIndex:
                        ordinal = paramValues.first;
                        valueToSend = paramValues.second.sendValue;
                        break;
                    case ValueUsedAsIndexAndBinaryORWithArbID:
                        valueToSend = paramValues.first | ArbId;
                        subValue = static_cast<uint8_t>(paramValues.second.sendValue);
                        break;
                    default:
                        valueToSend = paramValues.second.sendValue;
                        break;
                }

                switch (iter->first) {
			        case ctre::phoenix::platform::DeviceType::TalonSRXType:
                        errorCodes.push_back(std::make_pair(testTalon->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
			        	break;
			        case ctre::phoenix::platform::DeviceType::VictorSPXType:
                        errorCodes.push_back(std::make_pair(testVictor->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
			        	break;
			        case ctre::phoenix::platform::DeviceType::CANifierType:
                        errorCodes.push_back(std::make_pair(testCANifier->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
                        break;
			        case ctre::phoenix::platform::DeviceType::PigeonIMUType:
                        errorCodes.push_back(std::make_pair(testPigeon->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
                        break;
                }
            }
        }
    }
}

void SetAllParamsDefault(std::map<ctre::phoenix::platform::DeviceType, int> &idMap, int timeoutMs, const ParamEnumSet &paramsToSet, ErrorCodeString &errorCodes) {
   
    std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> testTalon;
    std::unique_ptr<ctre::phoenix::motorcontrol::can::VictorSPX> testVictor;
    std::unique_ptr<ctre::phoenix::sensors::PigeonIMU> testPigeon;
    std::unique_ptr<ctre::phoenix::CANifier> testCANifier;
    
    for(auto &paramParameterSet : paramsToSet) {
        
        for(auto &device : paramParameterSet.second.ValueSet) {
            
            auto iter = idMap.find(device.first);
            
            //make sure device is an instantiated device
            if(iter == idMap.end())
                continue;

            int ArbId = iter->second;
            std::string deviceName = "";         
            
			switch (iter->first) {
			    case ctre::phoenix::platform::DeviceType::TalonSRXType:
                    testTalon = std::make_unique<ctre::phoenix::motorcontrol::can::TalonSRX>(iter->second);
                    ArbId |= 0x02040000;
                    deviceName = "testTalon";
                    break;
			    case ctre::phoenix::platform::DeviceType::VictorSPXType:
                    testVictor = std::make_unique<ctre::phoenix::motorcontrol::can::VictorSPX>(iter->second);
                    ArbId |= 0x01040000;
                    deviceName = "testVictor";
			    	break;
			    case ctre::phoenix::platform::DeviceType::CANifierType:
			    	testCANifier = std::make_unique<ctre::phoenix::CANifier>(iter->second);
                    ArbId |= 0x03040000;
                    deviceName = "testCANifier";
                    break;
			    case ctre::phoenix::platform::DeviceType::PigeonIMUType:
			    	testPigeon = std::make_unique<ctre::phoenix::sensors::PigeonIMU>(iter->second);
                    ArbId |= 0x15000000;
                    deviceName = "testPigeon";
			    	break;
            } 
            
            for(auto &paramValues : device.second) {
                int ordinal = 0;
                double valueToSend = 0;
                uint8_t subValue = 0;
                switch (paramParameterSet.second.paramUsage) {
                    case OrdinalUsedAsIndex:
                        ordinal = paramValues.first;
                        valueToSend = paramValues.second.defaultValue;
                        break;
                    case ValueUsedAsIndexAndBinaryORWithArbID:
                        valueToSend = paramValues.first | ArbId;
                        subValue = static_cast<uint8_t>(paramValues.second.defaultValue);
                        break;
                    default:
                        valueToSend = paramValues.second.defaultValue;
                        break;
                }

                switch (iter->first) {
			        case ctre::phoenix::platform::DeviceType::TalonSRXType:
                        errorCodes.push_back(std::make_pair(testTalon->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
			        	break;
			        case ctre::phoenix::platform::DeviceType::VictorSPXType:
                        errorCodes.push_back(std::make_pair(testVictor->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
			        	break;
			        case ctre::phoenix::platform::DeviceType::CANifierType:
                        errorCodes.push_back(std::make_pair(testCANifier->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
                        break;
			        case ctre::phoenix::platform::DeviceType::PigeonIMUType:
                        errorCodes.push_back(std::make_pair(testPigeon->ConfigSetParameter(paramParameterSet.first, valueToSend, subValue, ordinal, timeoutMs), 
                        deviceName + "->ConfigSetParameter(" + paramParameterSet.second.name + ", " + std::to_string(valueToSend)+ ", " + std::to_string(subValue) + ", " + std::to_string(ordinal) + ", " + std::to_string(timeoutMs) + ");"));
                        break;
                }
            }
        }
    }
}
