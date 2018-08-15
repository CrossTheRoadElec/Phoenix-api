#pragma once

#include "ctre/Phoenix.h"
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllIndividualTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllIndividualVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllIndividualPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllIndividualCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigFactoryDefaultTalon(int id, int timeoutMs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigFactoryDefaultVictor(int id, int timeoutMs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigFactoryDefaultPigeon(int id, int timeoutMs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigFactoryDefaultCANifier(int id, int timeoutMs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllTalon(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::TalonSRXConfiguration &testTalonConfigs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllVictor(int id, int timeoutMs, ctre::phoenix::motorcontrol::can::VictorSPXConfiguration &testVictorConfigs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllPigeon(int id, int timeoutMs, ctre::phoenix::sensors::PigeonIMUConfiguration &testPigeonConfigs);

std::vector<std::pair<ctre::phoenix::ErrorCode, std::string>> ConfigAllCANifier(int id, int timeoutMs, ctre::phoenix::CANifierConfiguration &testCANifierConfigs);
