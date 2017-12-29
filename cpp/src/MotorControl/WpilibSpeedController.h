/**
 * Private class wrapper to adapt CTRE motor controllers to WPILIB.
 * This prevents WPILIB interface functions from polluting the function list
 * with redundant functions.
 */
#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/MotorControl/IMotorControllerEnhanced.h"

#include "SmartDashboard/SendableBase.h"
#include "SmartDashboard/SendableBuilder.h"

namespace ctre {
namespace phoenix {
namespace motorcontrol {

class WpilibSpeedController: public virtual frc::SpeedController, public frc::SendableBase {
public:
	WpilibSpeedController(ctre::phoenix::motorcontrol::can::BaseMotorController * mc) {
		_mc = mc;
	}

	virtual ~WpilibSpeedController() {
	}

	/**
	 * Common interface for setting the speed of a speed controller.
	 *
	 * @param speed The speed to set.  Value should be between -1.0 and 1.0.
	 */
	virtual void Set(double speed) {
		_speed = speed;
		_mc->Set(_speed);
	}
	virtual void PIDWrite(double output) {
		_speed = output;
		_mc->Set(output);
	}

	/**
	 * Common interface for getting the current set speed of a speed controller.
	 *
	 * @return The current set speed.  Value is between -1.0 and 1.0.
	 */
	virtual double Get() const {
		return _speed;
	}

	/**
	 * Common interface for inverting direction of a speed controller.
	 *
	 * @param isInverted The state of inversion, true is inverted.
	 */
	virtual void SetInverted(bool isInverted) {
		_mc->SetInverted(isInverted);
	}

	/**
	 * Common interface for returning the inversion state of a speed controller.
	 *
	 * @return isInverted The state of inversion, true is inverted.
	 */
	virtual bool GetInverted() const {
		return _mc->GetInverted();
	}

	/**
	 * Common interface for disabling a motor.
	 */
	virtual void Disable() {
		_mc->NeutralOutput();
	}

	/**
	 * Common interface to stop the motor until Set is called again.
	 */
	virtual void StopMotor() {
		_mc->NeutralOutput();
	}
	
protected:
    virtual void InitSendable(frc::SendableBuilder& builder) {
	  builder.SetSmartDashboardType("Speed Controller");
	  builder.SetSafeState([=]() { StopMotor(); });
	  builder.AddDoubleProperty("Value", [=]() { return Get(); },
								[=](double value) { Set(value); });
	}

private:
	can::BaseMotorController * _mc;
	double _speed = 0;

};
// class WpilibSpeedController
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
