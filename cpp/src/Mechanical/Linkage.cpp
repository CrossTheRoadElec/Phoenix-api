//#include "ctre/phoenix/Mechanical/Linkage.h"
//
//
//namespace CTRE{ namespace Mechanical{
//
//Linkage::Linkage(CTRE::MotorControl::IMotorController *mc1) {
//	_motor = mc1;
//	Setup();
//}
//Linkage::Linkage(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2){
//	_motor = mc1;
//	_follower[_followerCount++] = mc2;
//	Setup();
//}
//Linkage::Linkage(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3){
//	_motor = mc1;
//	_follower[_followerCount++] = mc2;
//	_follower[_followerCount++] = mc3;
//	Setup();
//}
//Linkage::Linkage(CTRE::MotorControl::IMotorController *mc1, CTRE::MotorControl::IFollower *mc2, CTRE::MotorControl::IFollower *mc3, CTRE::MotorControl::IFollower *mc4){
//	_motor = mc1;
//	_follower[_followerCount++] = mc2;
//	_follower[_followerCount++] = mc3;
//	_follower[_followerCount++] = mc4;
//	Setup();
//}
//void Linkage::Set(double output){
//	if(_isInverted)
//		output = -output;
//	_motor->Set(output);
//}
//void Linkage::SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode mode){
//	_motor->SetControlMode(mode);
//}
//void Linkage::SetInverted(bool invert){
//	_isInverted = invert;
//}
//bool Linkage::GetInverted() const{
//	return _isInverted;
//}
//void Linkage::SetVoltageRampRate(float rampRate){
//	_motor->SetVoltageRampRate(rampRate);
//}
//void Linkage::SetVoltageCompensationRate(float rampRate){
//	_motor->SetVoltageRampRate(rampRate);
//}
//void Linkage::ConfigNominalOutputVoltage(float forwardVoltage, float reverseVoltage){
//	_motor->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
//}
//void Linkage::ConfigPeakOutputVoltage(float forwardVoltage, float reverseVoltage){
//	_motor->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
//}
//CTRE::MotorControl::IMotorController *Linkage::GetMaster(){
//	return _motor;
//}
//void Linkage::Setup(){
//	for(int i = 0; i < _followerCount; i++){
//		_follower[i]->Follow(_motor);
//	}
//}
//
//}}
