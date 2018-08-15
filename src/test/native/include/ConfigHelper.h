#pragma once

#include "ctre/Phoenix.h"
#include <string>
#include <utility>
#include <vector>

typedef std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ErrorCodeString;

void ConfigAllIndividualTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes);

void ConfigAllIndividualVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes);

void ConfigAllIndividualPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes);

void ConfigAllIndividualCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultTalon(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultVictor(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultPigeon(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigFactoryDefaultCANifier(int id, int timeoutMs, ErrorCodeString &errorCodes);

void ConfigAllTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs, ErrorCodeString &errorCodes);

void ConfigAllVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs, ErrorCodeString &errorCodes);

void ConfigAllPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs, ErrorCodeString &errorCodes);

void ConfigAllCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs, ErrorCodeString &errorCodes);
