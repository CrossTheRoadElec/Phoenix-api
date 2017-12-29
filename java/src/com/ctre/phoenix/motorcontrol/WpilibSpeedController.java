
package com.ctre.phoenix.motorcontrol;

import com.ctre.phoenix.motorcontrol.can.BaseMotorController;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.Sendable;
import edu.wpi.first.wpilibj.SendableBase;
import edu.wpi.first.wpilibj.smartdashboard.SendableBuilder;

public class WpilibSpeedController extends SendableBase implements SpeedController, Sendable {

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
	
	@Override
    public void initSendable(SendableBuilder builder) {
    builder.setSmartDashboardType("Speed Controller");
    builder.setSafeState(this::stopMotor);
    builder.addDoubleProperty("Value", this::get, this::set);
  }
}
