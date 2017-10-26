//#include "ctre/phoenix/Motion/ServoVelocity.h"
//
//namespace CTRE { namespace Motion {
//
//ServoVelocity::ServoVelocity(CTRE::MotorControl::SmartMotorController *motor,
//		CTRE::MotorControl::SmartMotorController::FeedbackDevice feedbackDevice, float velocity)
//{
//    CTRE::Mechanical::SensoredGearbox *temp1 = new CTRE::Mechanical::SensoredGearbox(1, motor, feedbackDevice);
//    _gearbox = temp1;
//    _targetVelocity = velocity;
//}
//ServoVelocity::ServoVelocity(CTRE::Mechanical::SensoredGearbox *gearbox, float velocity){
//	_gearbox = gearbox;
//    _targetVelocity = velocity;
//}
//void ServoVelocity::Set(float targetSpeed, float maxOutput){
//	_gearbox->ConfigPeakOutputVoltage(maxOutput, -maxOutput);
//	_gearbox->SetControlMode(CTRE::MotorControl::ControlMode::SmartControlMode::kSpeed);
//	_gearbox->Set(targetSpeed);
//}
//void ServoVelocity::OnStart(){
//
//}
//void ServoVelocity::OnStop(){
//    /* stop the talon */
//	_gearbox->SetControlMode(CTRE::MotorControl::ControlMode::kPercentVbus);
//	_gearbox->Set(0);
//}
//bool ServoVelocity::IsDone(){
//	return false;
//}
//void ServoVelocity::OnLoop(){
//	_gearbox->SetControlMode(CTRE::MotorControl::ControlMode::kSpeed);
//	_gearbox->Set(_targetVelocity);
//}
//
//
//}}
