//#include <ctre/phoenix/MotorControl/DeviceCatalog.h>
//#include "ctre/phoenix/Drive/Tank.h"
//#include "HAL/DriverStation.h"
//
//namespace ctre { namespace drive {
//
//Tank::tank(ctre::Mechanical::Gearbox *left, ctre::Mechanical::Gearbox *right,
//		bool leftInvert, bool rightInvert)
//{
//    _left = left;
//    _right = right;
//
//    _left->SetInverted(leftInvert);
//    _right->SetInverted(rightInvert);
//}
//Tank::tank(ctre::motorcontrol::IMotorController *left, ctre::motorcontrol::IMotorController *right,
//		bool leftInvert, bool rightInvert)
//{
//    /* Create 2 single motor gearboxes */
//    ctre::Mechanical::Gearbox *temp1 = new ctre::Mechanical::Gearbox(left);
//    ctre::Mechanical::Gearbox *temp2 = new ctre::Mechanical::Gearbox(right);
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
//        _left->SetControlMode(ctre::motorcontrol::ControlMode::BasicControlMode::kVoltageBasic);
//        _right->SetControlMode(ctre::motorcontrol::ControlMode::BasicControlMode::kVoltageBasic);
//    }
//    else if (mode == Styles::Basic::PercentOutputBasic)
//    {
//        _left->SetControlMode(ctre::motorcontrol::ControlMode::BasicControlMode::kPercentVbusBasic);
//        _right->SetControlMode(ctre::motorcontrol::ControlMode::BasicControlMode::kPercentVbusBasic);
//    }
//
//    _left->Set(left);
//    _right->Set(right);
//}
//
//}}
