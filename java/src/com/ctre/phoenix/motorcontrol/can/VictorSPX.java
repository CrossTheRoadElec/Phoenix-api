package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.IMotorController;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.ErrorCollection;
import com.ctre.phoenix.ParamEnum;
import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.RemoteLimitSwitchSource;

import edu.wpi.first.wpilibj.hal.HAL;
/**
 * VEX Victor SPX Motor Controller when used on CAN Bus.
 */
public class VictorSPX extends com.ctre.phoenix.motorcontrol.can.BaseMotorController
    implements IMotorController {
	/**
	 * Constructor
	 * 
	 * @param deviceNumber
	 *            [0,62]
	 */
	public VictorSPX(int deviceNumber) {
		super(deviceNumber | 0x01040000);
		HAL.report(65, deviceNumber + 1);
	}
	
	ErrorCode configurePID(VictorSPXPIDSetConfiguration pid, int pidIdx, int timeoutMs) {
        ErrorCollection errorCollection = new ErrorCollection();
        
        //------ sensor selection ----------//      

        errorCollection.NewError(baseConfigurePID(pid, pidIdx, timeoutMs));
        errorCollection.NewError(configSelectedFeedbackSensor(pid.selectedFeedbackSensor, pidIdx, timeoutMs));
        

        return errorCollection._worstError;

	}

    
	ErrorCode configurePID(VictorSPXPIDSetConfiguration pid) {
        int pidIdx = 0;
        int timeoutMs = 50;
        return configurePID(pid, pidIdx, timeoutMs);
    }


    public void getPIDConfigs(VictorSPXPIDSetConfiguration pid, int pidIdx, int timeoutMs)
    {
        baseGetPIDConfigs(pid, pidIdx, timeoutMs);
        pid.selectedFeedbackSensor = RemoteFeedbackDevice.valueOf(configGetParameter(ParamEnum.eFeedbackSensorType, pidIdx, timeoutMs));
    
    }
	public void getPIDConfigs(VictorSPXPIDSetConfiguration pid) {
        int pidIdx = 0;
        int timeoutMs = 50;
        getPIDConfigs(pid, pidIdx, timeoutMs);
    }

	public ErrorCode configAllSettings(VictorSPXConfiguration allConfigs, int timeoutMs) {
	
        ErrorCollection errorCollection = new ErrorCollection();
        
        errorCollection.NewError(baseConfigAllSettings(allConfigs, timeoutMs));

        //------ remote limit switch ----------//   
        errorCollection.NewError(configForwardLimitSwitchSource(allConfigs.forwardLimitSwitchSource, allConfigs.forwardLimitSwitchNormal, allConfigs.forwardLimitSwitchDeviceID, timeoutMs));
        errorCollection.NewError(configReverseLimitSwitchSource(allConfigs.reverseLimitSwitchSource, allConfigs.reverseLimitSwitchNormal, allConfigs.reverseLimitSwitchDeviceID, timeoutMs));
        

        //--------PIDs---------------//

        errorCollection.NewError(configurePID(allConfigs.primaryPID, 0, timeoutMs));
        errorCollection.NewError(configurePID(allConfigs.auxilaryPID, 1, timeoutMs));
        errorCollection.NewError(configSensorTerm(SensorTerm.Sum0, allConfigs.sum_0, timeoutMs));
        errorCollection.NewError(configSensorTerm(SensorTerm.Sum1, allConfigs.sum_1, timeoutMs));
        errorCollection.NewError(configSensorTerm(SensorTerm.Diff0, allConfigs.diff_0, timeoutMs));
        errorCollection.NewError(configSensorTerm(SensorTerm.Diff1, allConfigs.diff_1, timeoutMs));

        return errorCollection._worstError;

	}
	public ErrorCode configAllSettings(VictorSPXConfiguration allConfigs) {
		int timeoutMs = 50;
		return configAllSettings(allConfigs, timeoutMs);
	}	
	public ErrorCode configFactoryDefault(int timeoutMs) {
		VictorSPXConfiguration defaults = new VictorSPXConfiguration();
		configAllSettings(defaults, timeoutMs);
		
		return ErrorCode.FeatureNotSupported;
	}
	public ErrorCode configFactoryDefault() {
		int timeoutMs = 50;
		return configFactoryDefault(timeoutMs);
	}
    public void getAllConfigs(VictorSPXConfiguration allConfigs, int timeoutMs) {
    
        baseGetAllConfigs(allConfigs, timeoutMs);
    
        getPIDConfigs(allConfigs.primaryPID, 0, timeoutMs);
        getPIDConfigs(allConfigs.auxilaryPID, 1, timeoutMs);
        allConfigs.sum_0 =  RemoteFeedbackDevice.valueOf(configGetParameter(ParamEnum.eSensorTerm, 0, timeoutMs));
        allConfigs.sum_1 =  RemoteFeedbackDevice.valueOf(configGetParameter(ParamEnum.eSensorTerm, 1, timeoutMs));
        allConfigs.diff_0 = RemoteFeedbackDevice.valueOf(configGetParameter(ParamEnum.eSensorTerm, 2, timeoutMs));
        allConfigs.diff_1 = RemoteFeedbackDevice.valueOf(configGetParameter(ParamEnum.eSensorTerm, 3, timeoutMs));
    
        allConfigs.forwardLimitSwitchSource = RemoteLimitSwitchSource.valueOf(configGetParameter(ParamEnum.eLimitSwitchSource, 0, timeoutMs));
        allConfigs.reverseLimitSwitchSource = RemoteLimitSwitchSource.valueOf(configGetParameter(ParamEnum.eLimitSwitchSource, 1, timeoutMs));
    
    }
    public void getAllConfigs(VictorSPXConfiguration allConfigs) {
        int timeoutMs = 0;
        getAllConfigs(allConfigs, timeoutMs); 
    }


}
