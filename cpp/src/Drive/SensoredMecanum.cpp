//#include <ctre/phoenix/MotorControl/DeviceCatalog.h>
//#include "ctre/phoenix/Drive/SensoredMecanum.h"
//#include "HAL/DriverStation.h"
//
//namespace ctre { namespace drive {
//
//SensoredMecanum::SensoredMecanum(ctre::motorcontrol::SmartMotorController *m1, ctre::motorcontrol::SmartMotorController *m2, ctre::motorcontrol::SmartMotorController *m3, ctre::motorcontrol::SmartMotorController *m4,
//			ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice, bool useLeftFrontSensor, bool useRightFrontSensor, float thisWheelRadius)
//{
//	ctre::Mechanical::SensoredGearbox *temp1 = new ctre::Mechanical::SensoredGearbox(1, m1, feedbackDevice);
//	ctre::Mechanical::SensoredGearbox *temp2 = new ctre::Mechanical::SensoredGearbox(1, m2, feedbackDevice);
//	ctre::Mechanical::SensoredGearbox *temp3 = new ctre::Mechanical::SensoredGearbox(1, m3, feedbackDevice);
//	ctre::Mechanical::SensoredGearbox *temp4 = new ctre::Mechanical::SensoredGearbox(1, m4, feedbackDevice);
//
//	_leftSensor = useLeftFrontSensor;
//	_rightSensor = useRightFrontSensor;
//
//	_1 = temp1;
//	_2 = temp2;
//	_3 = temp3;
//	_4 = temp4;
//
//	if(thisWheelRadius < 0.01)
//		HAL_SendError(true, 1, false, "CTR: Sensored Mecanum cannot have wheel radius less than 0.01", "", "", true);
//	wheelRadius = thisWheelRadius;
//}
//SensoredMecanum::SensoredMecanum(ctre::Mechanical::SensoredGearbox *m1, ctre::Mechanical::SensoredGearbox *m2,
//		ctre::Mechanical::SensoredGearbox *m3, ctre::Mechanical::SensoredGearbox *m4, float thisWheelRadius)
//{
//	_1 = m1;
//	_2 = m2;
//	_3 = m3;
//	_4 = m4;
//
//	_leftSensor = true;
//	_rightSensor = true;
//	if(thisWheelRadius < 0.01)
//		HAL_SendError(true, 1, false, "CTR: Sensored Mecanum cannot have wheel radius less than 0.01", "", "", true);
//	wheelRadius = thisWheelRadius;
//}
//void SensoredMecanum::Set(Styles::Smart mode, float forward, float turn){
//	Drive(mode, forward, 0, turn);
//}
//void SensoredMecanum::Set(Styles::Basic mode, float forward, float turn){
//	Drive(Styles::Promote(mode), forward, 0, turn);
//}
//void SensoredMecanum::Set(Styles::Smart mode, float forward, float strafe, float turn){
//	Drive(mode, forward, strafe, turn);
//}
//void SensoredMecanum::Set(Styles::Basic mode, float forward, float strafe, float turn){
//	Drive(Styles::Promote(mode), forward, strafe, turn);
//}
//void SensoredMecanum::SetCurrentLimit(unsigned int currentLimitAmps){
//    _1->SetCurrentLimit(currentLimitAmps);
//    _2->SetCurrentLimit(currentLimitAmps);
//    _3->SetCurrentLimit(currentLimitAmps);
//    _4->SetCurrentLimit(currentLimitAmps);
//}
//float SensoredMecanum::GetDistance(){
//    float l = GetLeftPosition();
//    float r = GetRightPosition();
//
//    return (l + r) * 0.5f;
//}
//float SensoredMecanum::GetVelocity(){
//    float l = GetLeftVelocity();
//    float r = GetRightVelocity();
//
//    return (l + r) * 0.5f;
//}
//float SensoredMecanum::GetEncoderHeading(){
//    float l = GetLeftPosition();
//    float r = GetRightPosition();
//
//    if (wheelRadius < 0.01)
//    {
//    	HAL_SendError(true, 1, false, "CTR: Sensored Mecanum has too small of a wheel radius, cannot get heading", "", "", true);
//        return 0;
//    }
//
//    if (ticksPerRev == 0)
//    {
//    	HAL_SendError(true, 1, false, "CTR: Sensored Mecanum has not set ticks per wheel revolution, cannot get heading", "", "", true);
//        return 0;
//    }
//
//    if (distanceBetweenWheels < 0.01)
//    {
//    	HAL_SendError(true, 1, false, "CTR: Sensored Mecanum has too small of a distance between wheels, cannot get heading", "", "", true);
//        return 0;
//    }
//
//    float unitsPerTick = (float)(2 * 3.14159 * wheelRadius) / ticksPerRev;
//    float theta = ((r - l) / (distanceBetweenWheels / unitsPerTick) * (float)(180 / 3.14159)) * tinyScalar;
//
//    return theta;
//}
//void SensoredMecanum::SetPosition(float position){
//    _1->SetSensor(position);
//    _2->SetSensor(position);
//    _3->SetSensor(position);
//    _4->SetSensor(position);
//}
//void SensoredMecanum::Drive(Styles::Smart mode, float forward, float strafe, float turn){
//    float leftFrnt_throt = (forward + strafe + turn); // left front moves positive for forward, strafe-right, turn-right
//    float leftRear_throt = (forward - strafe + turn); // left rear moves positive for forward, strafe-left, turn-right
//    float rghtFrnt_throt = (forward - strafe - turn); // right front moves positive for forward, strafe-left, turn-left
//    float rghtRear_throt = (forward + strafe - turn); // right rear moves positive for forward, strafe-right, turn-left
//
//    if (mode == Styles::Smart::Voltage)
//    {
//        _1->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kVoltage);
//        _2->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kVoltage);
//        _3->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kVoltage);
//        _4->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kVoltage);
//    }
//    else if (mode == Styles::Smart::PercentOutput)
//    {
//        _1->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kPercentVbus);
//        _2->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kPercentVbus);
//        _3->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kPercentVbus);
//        _4->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kPercentVbus);
//    }
//    else if(mode == Styles::Smart::VelocityClosedLoop)
//    {
//        _1->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kSpeed);
//        _2->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kSpeed);
//        _3->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kSpeed);
//        _4->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kSpeed);
//    }
//
//    _1->Set(leftFrnt_throt);
//    _2->Set(leftRear_throt);
//    _3->Set(rghtFrnt_throt);
//    _4->Set(rghtRear_throt);
//}
//void SensoredMecanum::ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage){
//    _1->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    _2->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    _3->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//    _4->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void SensoredMecanum::ConfigPeakPercentOtputVoltage(float forwardVoltage, float reverseVoltage){
//    _1->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    _2->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    _3->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//    _4->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void SensoredMecanum::SetVoltageCompensationRampRate(float RampRate){
//    _1->SetVoltageCompensationRampRate(RampRate);
//    _2->SetVoltageCompensationRampRate(RampRate);
//    _3->SetVoltageCompensationRampRate(RampRate);
//    _4->SetVoltageCompensationRampRate(RampRate);
//}
//void SensoredMecanum::SetVoltageRampRate(float RampRate){
//    _1->SetVoltageRampRate(RampRate);
//    _2->SetVoltageRampRate(RampRate);
//    _3->SetVoltageRampRate(RampRate);
//    _4->SetVoltageRampRate(RampRate);
//}
//void SensoredMecanum::SetMotionMagicAcceleration(float rotationsPerMinPerSec){
//    _1->SetMotionMagicAcceleration(rotationsPerMinPerSec);
//    _2->SetMotionMagicAcceleration(rotationsPerMinPerSec);
//    _3->SetMotionMagicAcceleration(rotationsPerMinPerSec);
//    _4->SetMotionMagicAcceleration(rotationsPerMinPerSec);
//}
//void SensoredMecanum::SetMotionMagicCruiseVelocity(float rotationsPerMin){
//    _1->SetMotionMagicCruiseVelocity(rotationsPerMin);
//    _2->SetMotionMagicCruiseVelocity(rotationsPerMin);
//    _3->SetMotionMagicCruiseVelocity(rotationsPerMin);
//    _4->SetMotionMagicCruiseVelocity(rotationsPerMin);
//}
//float SensoredMecanum::GetLeftPosition(){
//    if (_leftSensor)
//        return _1->GetPosition();
//    else
//        return _2->GetPosition();
//}
//float SensoredMecanum::GetRightPosition(){
//    if (_rightSensor)
//        return _4->GetPosition();
//    else
//        return _3->GetPosition();
//}
//float SensoredMecanum::GetLeftVelocity(){
//    if (_leftSensor)
//        return _1->GetVelocity();
//    else
//        return _2->GetVelocity();
//}
//float SensoredMecanum::GetRightVelocity(){
//    if (_rightSensor)
//        return _4->GetVelocity();
//    else
//        return _3->GetVelocity();
//}
//
//
//}}
