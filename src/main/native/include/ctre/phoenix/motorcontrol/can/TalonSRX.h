#pragma once

#include "ctre/phoenix/motorcontrol/can/BaseMotorController.h"
#include "ctre/phoenix/motorcontrol/IMotorControllerEnhanced.h"
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

	std::string toString() {
		return toString("");
	}

    std::string toString(std::string prependString) {

        std::string retstr = prependString + ".selectedFeedbackSensor = " + FeedbackDeviceRoutines::toString(selectedFeedbackSensor) + ";\n";
        retstr += BasePIDSetConfiguration::toString(prependString);
        return retstr;
    }
};

struct TalonSRXPIDSetConfigUtil {
	private:
		static TalonSRXPIDSetConfiguration _default;
	public:
		static bool SelectedFeedbackSensorDifferent (const TalonSRXPIDSetConfiguration & settings) { return (!(settings.selectedFeedbackSensor == _default.selectedFeedbackSensor)); }
		static bool SelectedFeedbackCoefficientDifferent (const TalonSRXPIDSetConfiguration & settings) { return (!(settings.selectedFeedbackCoefficient == _default.selectedFeedbackCoefficient)); }
};


struct TalonSRXConfiguration : BaseMotorControllerConfiguration{
	TalonSRXPIDSetConfiguration primaryPID;
	TalonSRXPIDSetConfiguration auxilaryPID;
	LimitSwitchSource forwardLimitSwitchSource;
	LimitSwitchSource reverseLimitSwitchSource;
	int forwardLimitSwitchDeviceID; //Limit Switch device id isn't used unless device is a remote
	int reverseLimitSwitchDeviceID;
	LimitSwitchNormal forwardLimitSwitchNormal;
	LimitSwitchNormal reverseLimitSwitchNormal;
    FeedbackDevice sum0Term;
	FeedbackDevice sum1Term;
	FeedbackDevice diff0Term;
	FeedbackDevice diff1Term;
	int peakCurrentLimit; 
    int peakCurrentDuration;
    int continuousCurrentLimit; 
    TalonSRXConfiguration() :
		forwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector),
		reverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector),
        forwardLimitSwitchDeviceID(0),
        reverseLimitSwitchDeviceID(0),
        forwardLimitSwitchNormal(LimitSwitchNormal_NormallyOpen), 
        reverseLimitSwitchNormal(LimitSwitchNormal_NormallyOpen), 
		sum0Term (QuadEncoder),
		sum1Term (QuadEncoder),
		diff0Term(QuadEncoder),
		diff1Term(QuadEncoder),
        peakCurrentLimit(1),
		peakCurrentDuration(1), 
		continuousCurrentLimit(1)
	{
	}

	std::string toString() {
		return toString("");
	}

    std::string toString(std::string prependString) {


        std::string retstr = primaryPID.toString(prependString + ".primaryPID");
	    retstr += auxilaryPID.toString(prependString + ".auxilaryPID");
	    retstr += prependString + ".forwardLimitSwitchSource = " + LimitSwitchRoutines::toString(forwardLimitSwitchSource) + ";\n";
	    retstr += prependString + ".reverseLimitSwitchSource = " + LimitSwitchRoutines::toString(reverseLimitSwitchSource) + ";\n";
        retstr += prependString + ".forwardLimitSwitchDeviceID = " + std::to_string(forwardLimitSwitchDeviceID) + ";\n";
        retstr += prependString + ".reverseLimitSwitchDeviceID = " + std::to_string(reverseLimitSwitchDeviceID) + ";\n";
        retstr += prependString + ".forwardLimitSwitchNormal = " + LimitSwitchRoutines::toString(forwardLimitSwitchNormal) + ";\n";
        retstr += prependString + ".reverseLimitSwitchNormal = " + LimitSwitchRoutines::toString(reverseLimitSwitchNormal) + ";\n";
	    retstr += prependString + ".sum0Term = " + FeedbackDeviceRoutines::toString(sum0Term) + ";\n";
	    retstr += prependString + ".sum1Term = " + FeedbackDeviceRoutines::toString(sum1Term) + ";\n";
	    retstr += prependString + ".diff0Term = " + FeedbackDeviceRoutines::toString(diff0Term) + ";\n";
	    retstr += prependString + ".diff1Term = " + FeedbackDeviceRoutines::toString(diff1Term) + ";\n";
	    retstr += prependString + ".peakCurrentLimit = " + std::to_string(peakCurrentLimit) + ";\n"; 
        retstr += prependString + ".peakCurrentDuration = " + std::to_string(peakCurrentDuration) + ";\n";
        retstr += prependString + ".continuousCurrentLimit = " + std::to_string(continuousCurrentLimit) + ";\n"; 
         retstr += BaseMotorControllerConfiguration::toString(prependString);

       return retstr; 
    }
};// struct TalonSRXConfiguration

class TalonConfigUtil {
	private:
		static struct TalonSRXConfiguration _default;
	public:
		static bool ForwardLimitSwitchSourceDifferent (const TalonSRXConfiguration & settings) { return (!(settings.forwardLimitSwitchSource == _default.forwardLimitSwitchSource)) || !settings.enableOptimizations; }
		static bool ReverseLimitSwitchSourceDifferent (const TalonSRXConfiguration & settings) { return (!(settings.reverseLimitSwitchSource == _default.reverseLimitSwitchSource)) || !settings.enableOptimizations; }
		static bool ForwardLimitSwitchDeviceIDDifferent (const TalonSRXConfiguration & settings) { return (!(settings.forwardLimitSwitchDeviceID == _default.forwardLimitSwitchDeviceID)) || !settings.enableOptimizations; }
		static bool ReverseLimitSwitchDeviceIDDifferent (const TalonSRXConfiguration & settings) { return (!(settings.reverseLimitSwitchDeviceID == _default.reverseLimitSwitchDeviceID)) || !settings.enableOptimizations; }
		static bool ForwardLimitSwitchNormalDifferent (const TalonSRXConfiguration & settings) { return (!(settings.forwardLimitSwitchNormal == _default.forwardLimitSwitchNormal)) || !settings.enableOptimizations; }
		static bool ReverseLimitSwitchNormalDifferent (const TalonSRXConfiguration & settings) { return (!(settings.reverseLimitSwitchNormal == _default.reverseLimitSwitchNormal)) || !settings.enableOptimizations; }
		static bool Sum0TermDifferent (const TalonSRXConfiguration & settings) { return (!(settings.sum0Term == _default.sum0Term)) || !settings.enableOptimizations; }
		static bool Sum1TermDifferent (const TalonSRXConfiguration & settings) { return (!(settings.sum1Term == _default.sum1Term)) || !settings.enableOptimizations; }
		static bool Diff0TermDifferent (const TalonSRXConfiguration & settings) { return (!(settings.diff0Term == _default.diff0Term)) || !settings.enableOptimizations; }
		static bool Diff1TermDifferent (const TalonSRXConfiguration & settings) { return (!(settings.diff1Term == _default.diff1Term)) || !settings.enableOptimizations; }
		static bool PeakCurrentLimitDifferent (const TalonSRXConfiguration & settings) { return (!(settings.peakCurrentLimit == _default.peakCurrentLimit)) || !settings.enableOptimizations; }
		static bool PeakCurrentDurationDifferent (const TalonSRXConfiguration & settings) { return (!(settings.peakCurrentDuration == _default.peakCurrentDuration)) || !settings.enableOptimizations; }
		static bool ContinuousCurrentLimitDifferent (const TalonSRXConfiguration & settings) { return (!(settings.continuousCurrentLimit == _default.continuousCurrentLimit)) || !settings.enableOptimizations; }

		static bool ForwardLimitSwitchDifferent (const TalonSRXConfiguration & settings) {
			return ForwardLimitSwitchDeviceIDDifferent(settings) || ForwardLimitSwitchNormalDifferent(settings) || ForwardLimitSwitchSourceDifferent(settings);
		}
		static bool ReverseLimitSwitchDifferent (const TalonSRXConfiguration & settings) {
			return ReverseLimitSwitchDeviceIDDifferent(settings) || ReverseLimitSwitchNormalDifferent(settings) || ReverseLimitSwitchSourceDifferent(settings);
		}
};

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

	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,uint8_t periodMs, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrame frame,uint8_t periodMs, int timeoutMs = 0);

	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs = 0);
	virtual int GetStatusFramePeriod(StatusFrame frame, int timeoutMs = 0);
	
	//------ General Status ----------//
    virtual double GetOutputCurrent();

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

	ctre::phoenix::ErrorCode ConfigurePID(const TalonSRXPIDSetConfiguration &pid, int pidIdx = 0, int timeoutMs = 50, bool enableOptimizations = true);
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
