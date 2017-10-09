#pragma once

#include <vector>
#include "ctre/phoenix/CANifier.h"
#include "ctre/phoenix/Tasking/IProcessable.h"

namespace CTRE{
	
class RCRadio3Ch : public CTRE::Tasking::IProcessable{
public:
	enum Channel{
		Channel1,
		Channel2,
		Channel3,
	};
	enum Status{
		LossOfCAN,
		LossOfPwm,
		Okay,
	};
	Status CurrentStatus = Status::Okay;

	RCRadio3Ch(CTRE::CANifier *canifier);
	float GetDutyCycleUs(Channel channel);
	float GetDutyCyclePerc(Channel channel);
	bool GetSwitchValue(Channel channel);
	float GetPeriodUs(Channel channel);

	//ILoopable
	void Process();

private:
	int _errorCodes[4];
	CTRE::CANifier *_canifier;


	//This is only a 2d array??
	float _dutyCycleAndPeriods[4][2] =
	{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
	};
	double Interpolate(std::vector<double> &xData, std::vector<double> &yData, double x, bool extrapolate);
};

}
