//#include <ctre/phoenix/MotorControl/DeviceCatalog.h>
//#include "ctre/phoenix/Drive/Tank.h"
//#include "HAL/DriverStation.h"
//
//namespace CTRE { namespace Drive {
//
//Tank::Tank(CTRE::Mechanical::Gearbox *left, CTRE::Mechanical::Gearbox *right,
//		bool leftInvert, bool rightInvert)
//{
//    _left = left;
//    _right = right;
//
//    _left->SetInverted(leftInvert);
//    _right->SetInverted(rightInvert);
//}
//Tank::Tank(CTRE::MotorControl::IMotorController *left, CTRE::MotorControl::IMotorController *right,
//		bool leftInvert, bool rightInvert)
//{
//    /* Create 2 single motor gearboxes */
//    CTRE::Mechanical::Gearbox *temp1 = new CTRE::Mechanical::Gearbox(left);
//    CTRE::Mechanical::Gearbox *temp2 = new CTRE::Mechanical::Gearbox(right);
//
//    _left = temp1;
//    _right = temp2;
//
//    _left->SetInverted(leftInvert);
//    _right->SetInverted(rightInvert);
//}
//void Tank::Set(Styles::Basic mode, float forward, float turn){
//    float l, r;
//	l = forward + turn;
//    r = forward - turn;
//
//    Drive(mode, l, r);
//}
//void Tank::SetVoltageRampRate(float rampRate){
//    _left->SetVoltageRampRate(rampRate);
//    _right->SetVoltageRampRate(rampRate);
//}
//void Tank::SetVoltageCompensationRampRate(float rampRate){
//    _left->SetVoltageCompensationRate(rampRate);
//    _right->SetVoltageCompensationRate(rampRate);
//}
//void Tank::ConfigPeakPercentOutputVoltage(float forwardVoltage, float reverseVoltage){
//    _left->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    _right->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void Tank::ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage){
//    _left->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    _right->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void Tank::Drive(Styles::Basic mode, float left, float right){
//    if (mode == Styles::Basic::VoltageBasic)
//    {
//        _left->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kVoltageBasic);
//        _right->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kVoltageBasic);
//    }
//    else if (mode == Styles::Basic::PercentOutputBasic)
//    {
//        _left->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kPercentVbusBasic);
//        _right->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kPercentVbusBasic);
//    }
//
//    _left->Set(left);
//    _right->Set(right);
//}
//
//}}
