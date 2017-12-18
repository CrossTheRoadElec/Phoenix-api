//#include "ctre/phoenix/Motion/ServoVelocity.h"
//
//namespace ctre { namespace motion {
//
//ServoVelocity::ServoVelocity(ctre::motorcontrol::SmartMotorController *motor,
//		ctre::motorcontrol::SmartMotorController::FeedbackDevice feedbackDevice, float velocity)
//{
//    ctre::Mechanical::SensoredGearbox *temp1 = new ctre::Mechanical::SensoredGearbox(1, motor, feedbackDevice);
//    _gearbox = temp1;
//    _targetVelocity = velocity;
//}
//ServoVelocity::ServoVelocity(ctre::Mechanical::SensoredGearbox *gearbox, float velocity){
//	_gearbox = gearbox;
//    _targetVelocity = velocity;
//}
//void ServoVelocity::Set(float targetSpeed, float maxOutput){
//	_gearbox->ConfigPeakOutputVoltage(maxOutput, -maxOutput);
//	_gearbox->SetControlMode(ctre::motorcontrol::ControlMode::SmartControlMode::kSpeed);
//	_gearbox->Set(targetSpeed);
//}
//void ServoVelocity::OnStart(){
//
//}
//void ServoVelocity::OnStop(){
//    /* stop the talon */
//	_gearbox->SetControlMode(ctre::motorcontrol::ControlMode::kPercentVbus);
//	_gearbox->Set(0);
//}
//bool ServoVelocity::IsDone(){
//	return false;
//}
//void ServoVelocity::OnLoop(){
//	_gearbox->SetControlMode(ctre::motorcontrol::ControlMode::kSpeed);
//	_gearbox->Set(_targetVelocity);
//}
//
//
//}}
