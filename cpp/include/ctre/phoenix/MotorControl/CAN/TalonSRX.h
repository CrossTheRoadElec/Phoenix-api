#pragma once

#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"
#include "ctre/phoenix/MotorControl/IMotorControllerEnhanced.h"
#include "ctre/phoenix/CustomParamConfiguration.h"

/* forward proto's */
namespace ctre {
namespace phoenix {
namespace motorcontrol {
class SensorCollection;
}
}
}

namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace can {

/**
 * CTRE Talon SRX Motor Configuration settings.
 */

struct TalonSRXPIDSetConfiguration : BasePIDSetConfiguration {
    FeedbackDevice selectedFeedbackSensor;

    TalonSRXPIDSetConfiguration() :
        selectedFeedbackSensor(QuadEncoder)
    {
    }
    std::string toString(std::string prependString) {

        std::string retstr = prependString + ".selectedFeedbackSensor = " + FeedbackDeviceRoutines::toString(selectedFeedbackSensor) + ";\n";
        retstr += BasePIDSetConfiguration::toString(prependString);
        return retstr;
    }

};


struct TalonSRXConfiguration : BaseMotorControllerConfiguration{
	TalonSRXPIDSetConfiguration primaryPID;
	TalonSRXPIDSetConfiguration auxilaryPID;
	LimitSwitchSource forwardLimitSwitchSource;
	LimitSwitchSource reverseLimitSwitchSource;
    FeedbackDevice sum_0;
	FeedbackDevice sum_1;
	FeedbackDevice diff_0;
	FeedbackDevice diff_1;
	int peakCurrentLimit; 
    int peakCurrentDuration;
    int continuousCurrentLimit; 
    TalonSRXConfiguration() :
		forwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector),
		reverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector),
		sum_0 (QuadEncoder),
		sum_1 (QuadEncoder),
		diff_0(QuadEncoder),
		diff_1(QuadEncoder),
        peakCurrentLimit(1),
		peakCurrentDuration(1), 
		continuousCurrentLimit(1)
	{
	}
    std::string toString(std::string prependString) {


        std::string retstr = primaryPID.toString(prependString + ".primaryPID");
	    retstr += auxilaryPID.toString(prependString + ".auxilaryPID");
	    retstr += prependString + ".forwardLimitSwitchSource = " + LimitSwitchRoutines::toString(forwardLimitSwitchSource) + ";\n";
	    retstr += prependString + ".reverseLimitSwitchSource = " + LimitSwitchRoutines::toString(reverseLimitSwitchSource) + ";\n";
	    retstr += prependString + ".sum_0 = " + FeedbackDeviceRoutines::toString(sum_0) + ";\n";
	    retstr += prependString + ".sum_1 = " + FeedbackDeviceRoutines::toString(sum_1) + ";\n";
	    retstr += prependString + ".diff_0 = " + FeedbackDeviceRoutines::toString(diff_0) + ";\n";
	    retstr += prependString + ".diff_1 = " + FeedbackDeviceRoutines::toString(diff_1) + ";\n";
	    retstr += prependString + ".peakCurrentLimit = " + std::to_string(peakCurrentLimit) + ";\n"; 
        retstr += prependString + ".peakCurrentDuration = " + std::to_string(peakCurrentDuration) + ";\n";
        retstr += prependString + ".continuousCurrentLimit = " + std::to_string(continuousCurrentLimit) + ";\n"; 
         retstr += BaseMotorControllerConfiguration::toString(prependString);

       return retstr; 
    }
};// struct TalonSRXConfiguration

/**
 * CTRE Talon SRX Motor Controller when used on CAN Bus.
 */

class TalonSRX: public virtual BaseMotorController,
		public virtual IMotorControllerEnhanced {
private:
	ctre::phoenix::motorcontrol::SensorCollection * _sensorColl;

public:
	TalonSRX(int deviceNumber);
	~TalonSRX();
	TalonSRX() = delete;
	TalonSRX(TalonSRX const&) = delete;
	TalonSRX& operator=(TalonSRX const&) = delete;

	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);

	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,int periodMs, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrame frame,int periodMs, int timeoutMs = 0);

	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs = 0);
	virtual int GetStatusFramePeriod(StatusFrame frame, int timeoutMs = 0);

	//------ Velocity measurement ----------//
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs = 0);

	//------ limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			LimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource limitSwitchSource,
			LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0);

	//------ Current Limit ----------//
	virtual ctre::phoenix::ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigPeakCurrentDuration(int milliseconds,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs = 0);
	virtual void EnableCurrentLimit(bool enable);
	
	//------ RAW Sensor API ----------//
	/**
	 * @retrieve object that can get/set individual RAW sensor values.
	 */
	ctre::phoenix::motorcontrol::SensorCollection & GetSensorCollection();

	//------ All Configs ----------//

	ctre::phoenix::ErrorCode ConfigurePID(const TalonSRXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50);
	void GetPIDConfigs(TalonSRXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50);
	ctre::phoenix::ErrorCode ConfigAllSettings(const TalonSRXConfiguration &allConfigs, int timeoutMs = 50);
	void GetAllConfigs(TalonSRXConfiguration &allConfigs, int timeoutMs = 50);

protected:
	ctre::phoenix::ErrorCode IfRemoteUseRemoteLimitSwitch( bool isForward, 
            LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0);
};// class TalonSRX




} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
