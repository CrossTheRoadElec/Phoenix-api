
package com.ctre.phoenix.MotorControl;

import com.ctre.phoenix.MotorControl.CAN.BaseMotorController;
import edu.wpi.first.wpilibj.SpeedController;

public class WpilibSpeedController implements SpeedController {

	private BaseMotorController _mc;
	private double _speed;

	public WpilibSpeedController(BaseMotorController mc) {
		_mc = mc;
	}

	@Override
	public void set(double speed) {
		_speed = speed;
		_mc.set(ControlMode.PercentOutput, _speed);
	}

	@Override
	public void pidWrite(double output) {
		_speed = output;
		_mc.set(ControlMode.PercentOutput, _speed);
	}

	@Override
	public double get() {
		return _speed;
	}

	@Override
	public void setInverted(boolean isInverted) {
		_mc.setInverted(isInverted);
	}

	@Override
	public boolean getInverted() {
		return _mc.getInverted();
	}

	@Override
	public void disable() {
		_mc.neutralOutput();
	}

	@Override
	public void stopMotor() {
		_mc.neutralOutput();
	}
}
