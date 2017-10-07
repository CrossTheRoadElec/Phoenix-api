#pragma once

#include "ControlMode.h"
#include "ctre/phoenix/Signals/IInvertable.h"
#include "ctre/phoenix/Signals/IOutputSignal.h"
#include "IFollower.h"

namespace CTRE { namespace MotorControl {

class IMotorController
		: public CTRE::Signals::IOutputSignal,
		  public CTRE::Signals::IInvertable,
		  public IFollower{
public:
	virtual void SetControlMode(ControlMode::BasicControlMode mode) = 0;
	virtual void SetVoltageRampRate(double rampRate) = 0;
	virtual void SetVoltageCompensationRampRate(double rampRate) = 0;
	virtual void ConfigPeakOutputVoltage(double forwardVoltage, double reverseVoltage) = 0;
	virtual void ConfigNominalOutputVoltage(double forwardVoltage, double reverseVoltage) = 0;
	virtual double GetBusVoltage() const = 0;
	virtual int GetDeviceID() = 0;
};

}}
