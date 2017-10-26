//#include "ctre/phoenix/Mechanical/SensoredGearbox.h"
//
//using namespace CTRE::MotorControl;
//
//namespace CTRE{ namespace Mechanical{
//
//SensoredGearbox::SensoredGearbox(float gearRatio, SmartMotorController *talon, SmartMotorController::FeedbackDevice feedbackDevice){
//	master = talon;
//	_gearRatio = gearRatio;
//	master->SetFeedbackDevice(feedbackDevice);
//}
//SensoredGearbox::SensoredGearbox(float gearRatio, SmartMotorController *talon, IFollower *slave1, SmartMotorController::FeedbackDevice feedbackDevice){
//	master = talon;
//	_gearRatio = gearRatio;
//	master->SetFeedbackDevice(feedbackDevice);
//	slave1->Follow(master);
//}
//SensoredGearbox::SensoredGearbox(float gearRatio, SmartMotorController *talon, IFollower *slave1, IFollower *slave2, SmartMotorController::FeedbackDevice feedbackDevice){
//	master = talon;
//	_gearRatio = gearRatio;
//	master->SetFeedbackDevice(feedbackDevice);
//	slave1->Follow(master);
//	slave2->Follow(master);
//}
//SensoredGearbox::SensoredGearbox(float gearRatio, SmartMotorController *talon, IFollower *slave1, IFollower *slave2, IFollower *slave3, SmartMotorController::FeedbackDevice feedbackDevice){
//	master = talon;
//	_gearRatio = gearRatio;
//	master->SetFeedbackDevice(feedbackDevice);
//	slave1->Follow(master);
//	slave2->Follow(master);
//	slave3->Follow(master);
//}
//float SensoredGearbox::GetPosition(){
//	return master->GetPosition() / _gearRatio;
//}
//float SensoredGearbox::GetVelocity(){
//	return master->GetSpeed() / _gearRatio;
//}
//void SensoredGearbox::SetCurrentLimit(unsigned int currentLimitAmps){
//	master->SetCurrentLimit(currentLimitAmps);
//}
//void SensoredGearbox::Set(float output){
//	if(_isInverted)
//		output = -output;
//	master->Set(output);
//}
//void SensoredGearbox::SetControlMode(CTRE::MotorControl::ControlMode::SmartControlMode mode){
//	master->SetControlMode(mode);
//}
//void SensoredGearbox::SetLimits(float forwardLimit, float reverseLimit){
//	master->ConfigForwardLimit(forwardLimit);
//	master->ConfigReverseLimit(reverseLimit);
//}
//void SensoredGearbox::DisableLimits(){
//	master->ConfigLimitMode(2);
//}
//void SensoredGearbox::SetInverted(bool invert){
//	_isInverted = invert;
//}
//bool SensoredGearbox::GetInverted() const{
//	return _isInverted;
//}
//void SensoredGearbox::InvertSensor(bool invert){
//	master->SetSensorDirection(invert);
//}
//void SensoredGearbox::SetSensor(float position){
//	master->SetPosition(position);
//}
//void SensoredGearbox::ConfigNominalOutputVoltage(float forwardVoltage, float reverseVoltage){
//	master->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void SensoredGearbox::ConfigPeakOutputVoltage(float forwardVoltage, float reverseVoltage){
//	master->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void SensoredGearbox::SetVoltageCompensationRampRate(float rampRate){
//	master->SetVoltageCompensationRampRate(rampRate);
//}
//void SensoredGearbox::SetVoltageRampRate(float rampRate){
//	master->SetVoltageRampRate(rampRate);
//}
//void SensoredGearbox::SetMotionMagicCruiseVelocity(float RPM){
//	master->SetMotionMagicCruiseVelocity(RPM);
//}
//void SensoredGearbox::SetMotionMagicAcceleration(float RPM){
//	master->SetMotionMagicAcceleration(RPM);
//}
//CTRE::MotorControl::IMotorController *SensoredGearbox::GetMaster(){
//	return master;
//}
//
//
//}}
