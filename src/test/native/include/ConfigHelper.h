#pragma once

#include "ctre/Phoenix.h"
#include <string>
#include <utility>
#include <vector>
#include "ParamHelper.h"

void ConfigAllIndividualTalon(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes);

void ConfigAllIndividualVictor(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes);

void ConfigAllIndividualPigeon(int id, int timeoutMs, const ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes);

void ConfigAllIndividualCANifier(int id, int timeoutMs, const ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultTalon(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultVictor(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultPigeon(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultCANifier(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigAllTalon(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes);

void ConfigAllVictor(int id, int timeoutMs, const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes);

void ConfigAllPigeon(int id, int timeoutMs, const ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes);

void ConfigAllCANifier(int id, int timeoutMs, const ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes);

void ConfigGetAllTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes);

void ConfigGetAllVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes);

void ConfigGetAllPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes);

void ConfigGetAllCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes);

void GetAllConfigsTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes);

void GetAllConfigsVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes);

void GetAllConfigsPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes);

void GetAllConfigsCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes);

void GenerateCustomParamSendValues(ctre::phoenix::CustomParamConfiguration &configs, std::default_random_engine &engine);

void GenerateCANifierSendValues(ctre::phoenix::CANifierConfiguration &configs, std::default_random_engine &engine);

void GeneratePigeonSendValues(ctre::phoenix::sensors::PigeonIMUConfiguration &configs, std::default_random_engine &engine);

void GenerateSlotSendValues(ctre::phoenix::motorcontrol::can::SlotConfiguration &configs, std::default_random_engine &engine);

void GenerateFilterSendValues(ctre::phoenix::motorcontrol::can::FilterConfiguration &configs, std::default_random_engine &engine);

void GenerateBasePIDSendValues(ctre::phoenix::motorcontrol::can::BaseMotorControllerConfiguration &configs, std::default_random_engine &engine);

void GenerateBaseMotControllerSendValues(ctre::phoenix::motorcontrol::can::BasePIDSetConfiguration &configs, std::default_random_engine &engine);

void GenerateTalonPIDSendValues(ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration &configs, std::default_random_engine &engine);

void GenerateVictorPIDSendValues(ctre::phoenix::motorcontrol::can::VictorSPXPIDSetConfiguration &configs, std::default_random_engine &engine);

void GenerateTalonSendValues(ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &configs, std::default_random_engine &engine);

void GenerateVictorSendValues(ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &configs, std::default_random_engine &engine);


void EqualityCheckCustomParam(const ctre::phoenix::CustomParamConfiguration &configs1, const ctre::phoenix::CustomParamConfiguration &configs2);

void EqualityCheckCANifier(const ctre::phoenix::CANifierConfiguration &configs1, const ctre::phoenix::CANifierConfiguration &configs2);

void EqualityCheckPigeon(const ctre::phoenix::sensors::PigeonIMUConfiguration &configs1, const ctre::phoenix::sensors::PigeonIMUConfiguration &configs2);

void EqualityCheckSlot(const ctre::phoenix::motorcontrol::can::SlotConfiguration &configs1, const ctre::phoenix::motorcontrol::can::SlotConfiguration &configs2);

void EqualityCheckFilter(const ctre::phoenix::motorcontrol::can::FilterConfiguration &configs1, const ctre::phoenix::motorcontrol::can::FilterConfiguration &configs2);

void EqualityCheckBasePID(const ctre::phoenix::motorcontrol::can::BasePIDSetConfiguration &configs1, const ctre::phoenix::motorcontrol::can::BasePIDSetConfiguration &configs2);

void EqualityCheckBaseMotController(const ctre::phoenix::motorcontrol::can::BaseMotorControllerConfiguration &configs1, const ctre::phoenix::motorcontrol::can::BaseMotorControllerConfiguration &configs2);

void EqualityCheckTalonPID(const ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration &configs1, const ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration &configs2);

void EqualityCheckVictorPID(const ctre::phoenix::motorcontrol::can::VictorSPXPIDSetConfiguration &configs1, const ctre::phoenix::motorcontrol::can::VictorSPXPIDSetConfiguration &configs2);

void EqualityCheckTalon(const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &configs1, const ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &configs2);

void EqualityCheckVictor(const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &configs1, const ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &configs2);
