//#include <ctre/phoenix/MotorControl/DeviceCatalog.h>
//#include "ctre/phoenix/Drive/SensoredTank.h"
//#include "ctre/phoenix/CTRLogger.h"
//#include "HAL/DriverStation.h"
//
//namespace ctre { namespace drive {
//
//SensoredTank::SensoredTank(ctre::Mechanical::SensoredGearbox *left, ctre::Mechanical::SensoredGearbox *right,
//		bool leftInverted, bool rightInverted, float thisWheelRadius)
//{
//    _left = left;
//    _right = right;
//
//    _left->SetInverted(leftInverted);
//    _right->SetInverted(rightInverted);
//
//    if (thisWheelRadius < 0.01)
//    	HAL_SendError(true, 1, false, "CTR: Sensored Tank wheel radius must be greater than 0.01", "", "", true);
//    wheelRadius = thisWheelRadius;
//}
//SensoredTank::SensoredTank(ctre::motorcontrol::SmartMotorController *left, ctre::motorcontrol::SmartMotorController *right,
//		ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice, bool leftInverted, bool rightInverted, float thisWheelRadius)
//{
//	/* Create 2 single motor gearboxes */
//	ctre::Mechanical::SensoredGearbox *temp1 = new ctre::Mechanical::SensoredGearbox(1, left, feedbackDevice);
//	ctre::Mechanical::SensoredGearbox *temp2 = new ctre::Mechanical::SensoredGearbox(1, right, feedbackDevice);
//
//	_left = temp1;
//	_right = temp2;
//
//	_left->SetInverted(leftInverted);
//	_right->SetInverted(rightInverted);
//
//	if (thisWheelRadius < 0.01)
//		HAL_SendError(true, 1, false, "CTR: Sensored Tank wheel radius must be greater than 0.01", "", "", true);
//	wheelRadius = thisWheelRadius;
//}
//void SensoredTank::Set(Styles::Smart mode, float forward, float turn){
//	float l, r;
//	l = forward + turn;
//	r = forward - turn;
//
//	Drive(mode, l, r);
//}
//void SensoredTank::Set(Styles::Basic mode, float forward, float turn){
//    Set(Styles::Promote(mode), forward, turn);
//}
//void SensoredTank::SetCurrentLimit(unsigned int currentAmps){
//    _left->SetCurrentLimit(currentAmps);
//    _right->SetCurrentLimit(currentAmps);
//}
//float SensoredTank::GetDistance(){
//    float l = _left->GetPosition();
//    float r = _right->GetPosition();
//
//    return (l + r) * 0.5f;
//}
//float SensoredTank::GetVelocity(){
//    float l = _left->GetVelocity();
//    float r = _right->GetVelocity();
//
//    return (l + r) * 0.5f;
//}
//float SensoredTank::GetEncoderHeading(){
//    float l = _left->GetPosition();
//    float r = _right->GetPosition();
//
//    if (wheelRadius < 0.01)
//    {
//		CTRLogger::Log(CTR_Code::WheelRadiusTooSmall, "Sensored Tank");
//        return 0;
//    }
//
//    if (ticksPerRev == 0)
//    {
//		CTRLogger::Log(CTR_Code::TicksPerRevZero, "Sensored Tank");
//        return 0;
//    }
//
//    if (distanceBetweenWheels < 0.01)
//    {
//		CTRLogger::Log(CTR_Code::DistanceBetweenWheelsTooSmall, "Sensored Tank");
//        return 0;
//    }
//
//    float unitsPerTick = (float)(2 * 3.14159 * wheelRadius) / ticksPerRev;
//    float theta = ((r-l) / (distanceBetweenWheels / unitsPerTick) * (float)(180 / 3.14159)) * tinyScalor;
//
//    return theta;
//}
//void SensoredTank::SetPosition(float position){
//    _left->SetSensor(position);
//    _right->SetSensor(position);
//}
//void SensoredTank::ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage){
//    _left->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    _right->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void SensoredTank::ConfigPeakPercentOutputVoltage(float forwardVoltage, float reverseVoltage){
//    _left->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    _right->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void SensoredTank::SetVoltageCompensationRampRate(float rampRate){
//    _left->SetVoltageCompensationRampRate(rampRate);
//    _right->SetVoltageCompensationRampRate(rampRate);
//}
//void SensoredTank::SetVoltageRampRate(float rampRate){
//    _left->SetVoltageRampRate(rampRate);
//    _right->SetVoltageRampRate(rampRate);
//}
//void SensoredTank::SetMotionMagicAcceleration(float rotationsPerMinPerSec){
//    /* RPMPS?? */
//    _left->SetMotionMagicAcceleration(rotationsPerMinPerSec);
//    _right->SetMotionMagicAcceleration(rotationsPerMinPerSec);
//}
//void SensoredTank::SetMotionMagicCruiseVelocity(float rotationsPerMin){
//    _left->SetMotionMagicCruiseVelocity(rotationsPerMin);
//    _right->SetMotionMagicCruiseVelocity(rotationsPerMin);
//}
//void SensoredTank::Drive(Styles::Smart mode, float left, float right){
//    if(mode == Styles::Smart::Voltage)
//    {
//        _left->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kVoltage);
//        _right->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kVoltage);
//    }
//    else if (mode == Styles::Smart::PercentOutput)
//    {
//        _left->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kPercentVbus);
//        _right->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kPercentVbus);
//    }
//    else if(mode == Styles::Smart::VelocityClosedLoop)
//    {
//        _left->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kSpeed);
//        _right->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kSpeed);
//    }
//
//    _left->Set(left);
//    _right->Set(right);
//}
//
//}}
