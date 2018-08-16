package com.ctre.phoenix;

import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.ctre.phoenix.motorcontrol.can.VictorSPX;
import com.ctre.phoenix.sensors.PigeonIMU;
import com.ctre.phoenix.CANifier;

import com.ctre.phoenix.ErrorCodeDoubleString;
import com.ctre.phoenix.ParamEnumParameters;

import java.util.Map;
import java.util.List;
import java.util.HashMap;

public class ParamHelper {

    public static Map<ParamEnum, ParamEnumParameters> genericParamEnumStrings = new HashMap<ParamEnum, ParamEnumParameters> () {
        {

            put(ParamEnum.eStatusFramePeriod, new ParamEnumParameters("ParamEnum.eStatusFramePeriod", 0, 1, 0.5));
            put(ParamEnum.eCustomParam, new ParamEnumParameters("ParamEnum.eCustomParam", 0, 1, 0.5));
            put(ParamEnum.eStickyFaults, new ParamEnumParameters("ParamEnum.eStickyFaults", 0, 1, 0.5));
            put(ParamEnum.eDefaultConfig, new ParamEnumParameters("ParamEnum.eDefaultConfig", 0, 1, 0.5));
        }
    };

    public static Map<ParamEnum, ParamEnumParameters> sensorParamEnumStrings = new HashMap<ParamEnum, ParamEnumParameters> () {
        {
            put(ParamEnum.eQuadFilterEn, new ParamEnumParameters("ParamEnum.eQuadFilterEn", 0, 1, 0.5));
            put(ParamEnum.eQuadIdxPolarity, new ParamEnumParameters("ParamEnum.eQuadIdxPolarity", 0, 1, 0.5));
            put(ParamEnum.eClearPositionOnLimitF, new ParamEnumParameters("ParamEnum.eClearPositionOnLimitF", 0, 1, 0.5));
            put(ParamEnum.eClearPositionOnLimitR, new ParamEnumParameters("ParamEnum.eClearPositionOnLimitR", 0, 1, 0.5));
            put(ParamEnum.eClearPositionOnQuadIdx, new ParamEnumParameters("ParamEnum.eClearPositionOnQuadIdx", 0, 1, 0.5));
            put(ParamEnum.eSampleVelocityPeriod, new ParamEnumParameters("ParamEnum.eSampleVelocityPeriod", 0, 1, 0.5));
            put(ParamEnum.eSampleVelocityWindow, new ParamEnumParameters("ParamEnum.eSampleVelocityWindow", 0, 1, 0.5));
            put(ParamEnum.eFeedbackNotContinuous, new ParamEnumParameters("ParamEnum.eFeedbackNotContinuous", 0, 1, 0.5));
            put(ParamEnum.eAnalogPosition, new ParamEnumParameters("ParamEnum.eAnalogPosition", 0, 1, 0.5));
            put(ParamEnum.eQuadraturePosition, new ParamEnumParameters("ParamEnum.eQuadraturePosition", 0, 1, 0.5));
            put(ParamEnum.ePulseWidthPosition, new ParamEnumParameters("ParamEnum.ePulseWidthPosition", 0, 1, 0.5));
            put(ParamEnum.eLimitSwitchNormClosedAndDis, new ParamEnumParameters("ParamEnum.eLimitSwitchNormClosedAndDis", 0, 1, 0.5));
            put(ParamEnum.ePulseWidthPeriod_EdgesPerRot, new ParamEnumParameters("ParamEnum.ePulseWidthPeriod_EdgesPerRot", 0, 1, 0.5));
            put(ParamEnum.ePulseWidthPeriod_FilterWindowSz, new ParamEnumParameters("ParamEnum.ePulseWidthPeriod_FilterWindowSz", 0, 1, 0.5));
        }
    };
    public static Map<ParamEnum, ParamEnumParameters> imuParamEnumStrings = new HashMap<ParamEnum, ParamEnumParameters> () {
        {
            put(ParamEnum.eYawOffset, new ParamEnumParameters("ParamEnum.eYawOffset", 0, 1, 0.5));
            put(ParamEnum.eCompassOffset, new ParamEnumParameters("ParamEnum.eCompassOffset", 0, 1, 0.5));
            put(ParamEnum.eBetaGain, new ParamEnumParameters("ParamEnum.eBetaGain", 0, 1, 0.5));
            put(ParamEnum.eEnableCompassFusion, new ParamEnumParameters("ParamEnum.eEnableCompassFusion", 0, 1, 0.5));
            put(ParamEnum.eGyroNoMotionCal, new ParamEnumParameters("ParamEnum.eGyroNoMotionCal", 0, 1, 0.5));
            put(ParamEnum.eEnterCalibration, new ParamEnumParameters("ParamEnum.eEnterCalibration", 0, 1, 0.5));
            put(ParamEnum.eFusedHeadingOffset, new ParamEnumParameters("ParamEnum.eFusedHeadingOffset", 0, 1, 0.5));
            put(ParamEnum.eAccumZ, new ParamEnumParameters("ParamEnum.eAccumZ", 0, 1, 0.5));
            put(ParamEnum.eTempCompDisable, new ParamEnumParameters("ParamEnum.eTempCompDisable", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_tap_threshX, new ParamEnumParameters("ParamEnum.eMotionMeas_tap_threshX", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_tap_threshY, new ParamEnumParameters("ParamEnum.eMotionMeas_tap_threshY", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_tap_threshZ, new ParamEnumParameters("ParamEnum.eMotionMeas_tap_threshZ", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_tap_count, new ParamEnumParameters("ParamEnum.eMotionMeas_tap_count", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_tap_time, new ParamEnumParameters("ParamEnum.eMotionMeas_tap_time", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_tap_time_multi, new ParamEnumParameters("ParamEnum.eMotionMeas_tap_time_multi", 0, 1, 0.5)); 
            put(ParamEnum.eMotionMeas_shake_reject_thresh, new ParamEnumParameters("ParamEnum.eMotionMeas_shake_reject_thresh", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_shake_reject_time, new ParamEnumParameters("ParamEnum.eMotionMeas_shake_reject_time", 0, 1, 0.5));
            put(ParamEnum.eMotionMeas_shake_reject_timeout, new ParamEnumParameters("ParamEnum.eMotionMeas_shake_reject_timeout", 0, 1, 0.5)); 
        }
    }; 
    public static Map<ParamEnum, ParamEnumParameters> motControllerParamEnumStrings = new HashMap<ParamEnum, ParamEnumParameters> () {
        {        
            put(ParamEnum.eOnBoot_BrakeMode, new ParamEnumParameters("ParamEnum.eOnBoot_BrakeMode", 0, 1, 0.5));
            put(ParamEnum.eMotionProfileHasUnderrunErr, new ParamEnumParameters("ParamEnum.eMotionProfileHasUnderrunErr", 0, 1, 0.5));
            put(ParamEnum.eMotionProfileTrajectoryPointDurationMs, new ParamEnumParameters("ParamEnum.eMotionProfileTrajectoryPointDurationMs", 0, 1, 0.5));
            put(ParamEnum.eSelectedSensorPosition, new ParamEnumParameters("ParamEnum.eSelectedSensorPosition", 0, 1, 0.5));
            put(ParamEnum.eOpenloopRamp, new ParamEnumParameters("ParamEnum.eOpenloopRamp", 0, 1, 0.5));
            put(ParamEnum.eClosedloopRamp, new ParamEnumParameters("ParamEnum.eClosedloopRamp", 0, 1, 0.5));
            put(ParamEnum.eNeutralDeadband, new ParamEnumParameters("ParamEnum.eNeutralDeadband", 0, 1, 0.5));
            put(ParamEnum.ePeakPosOutput, new ParamEnumParameters("ParamEnum.ePeakPosOutput", 0, 1, 0.5));
            put(ParamEnum.eNominalPosOutput, new ParamEnumParameters("ParamEnum.eNominalPosOutput", 0, 1, 0.5));
            put(ParamEnum.ePeakNegOutput, new ParamEnumParameters("ParamEnum.ePeakNegOutput", 0, 1, 0.5));
            put(ParamEnum.eNominalNegOutput, new ParamEnumParameters("ParamEnum.eNominalNegOutput", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_P, new ParamEnumParameters("ParamEnum.eProfileParamSlot_P", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_I, new ParamEnumParameters("ParamEnum.eProfileParamSlot_I", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_D, new ParamEnumParameters("ParamEnum.eProfileParamSlot_D", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_F, new ParamEnumParameters("ParamEnum.eProfileParamSlot_F", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_IZone, new ParamEnumParameters("ParamEnum.eProfileParamSlot_IZone", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_AllowableErr, new ParamEnumParameters("ParamEnum.eProfileParamSlot_AllowableErr", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_MaxIAccum, new ParamEnumParameters("ParamEnum.eProfileParamSlot_MaxIAccum", 0, 1, 0.5));
            put(ParamEnum.eProfileParamSlot_PeakOutput, new ParamEnumParameters("ParamEnum.eProfileParamSlot_PeakOutput", 0, 1, 0.5));
            put(ParamEnum.eFeedbackSensorType, new ParamEnumParameters("ParamEnum.eFeedbackSensorType", 0, 1, 0.5));
            put(ParamEnum.eRemoteSensorSource, new ParamEnumParameters("ParamEnum.eRemoteSensorSource", 0, 1, 0.5));
            put(ParamEnum.eRemoteSensorDeviceID, new ParamEnumParameters("ParamEnum.eRemoteSensorDeviceID", 0, 1, 0.5));
            put(ParamEnum.eSensorTerm, new ParamEnumParameters("ParamEnum.eSensorTerm", 0, 1, 0.5));
            put(ParamEnum.eRemoteSensorClosedLoopDisableNeutralOnLOS, new ParamEnumParameters("ParamEnum.eRemoteSensorClosedLoopDisableNeutralOnLOS", 0, 1, 0.5));
            put(ParamEnum.ePIDLoopPolarity, new ParamEnumParameters("ParamEnum.ePIDLoopPolarity", 0, 1, 0.5));
            put(ParamEnum.ePIDLoopPeriod, new ParamEnumParameters("ParamEnum.ePIDLoopPeriod", 0, 1, 0.5));
            put(ParamEnum.eSelectedSensorCoefficient, new ParamEnumParameters("ParamEnum.eSelectedSensorCoefficient", 0, 1, 0.5));
            put(ParamEnum.eForwardSoftLimitThreshold, new ParamEnumParameters("ParamEnum.eForwardSoftLimitThreshold", 0, 1, 0.5));
            put(ParamEnum.eReverseSoftLimitThreshold, new ParamEnumParameters("ParamEnum.eReverseSoftLimitThreshold", 0, 1, 0.5));
            put(ParamEnum.eForwardSoftLimitEnable, new ParamEnumParameters("ParamEnum.eForwardSoftLimitEnable", 0, 1, 0.5));
            put(ParamEnum.eReverseSoftLimitEnable, new ParamEnumParameters("ParamEnum.eReverseSoftLimitEnable", 0, 1, 0.5));
            put(ParamEnum.eNominalBatteryVoltage, new ParamEnumParameters("ParamEnum.eNominalBatteryVoltage", 0, 1, 0.5));
            put(ParamEnum.eBatteryVoltageFilterSize, new ParamEnumParameters("ParamEnum.eBatteryVoltageFilterSize", 0, 1, 0.5));
            put(ParamEnum.eClosedLoopIAccum, new ParamEnumParameters("ParamEnum.eClosedLoopIAccum", 0, 1, 0.5));
            put(ParamEnum.eMotMag_Accel, new ParamEnumParameters("ParamEnum.eMotMag_Accel", 0, 1, 0.5));
            put(ParamEnum.eMotMag_VelCruise, new ParamEnumParameters("ParamEnum.eMotMag_VelCruise", 0, 1, 0.5));
            put(ParamEnum.eLimitSwitchSource, new ParamEnumParameters("ParamEnum.eLimitSwitchSource", 0, 1, 0.5));
            put(ParamEnum.eLimitSwitchDisableNeutralOnLOS, new ParamEnumParameters("ParamEnum.eLimitSwitchDisableNeutralOnLOS", 0, 1, 0.5));
            put(ParamEnum.eLimitSwitchRemoteDevID, new ParamEnumParameters("ParamEnum.eLimitSwitchRemoteDevID", 0, 1, 0.5));
            put(ParamEnum.eSoftLimitDisableNeutralOnLOS, new ParamEnumParameters("ParamEnum.eSoftLimitDisableNeutralOnLOS", 0, 1, 0.5));
        }
    };
    public static Map<ParamEnum, ParamEnumParameters> currentParamEnumStrings = new HashMap<ParamEnum, ParamEnumParameters> () {
        {
            put(ParamEnum.eContinuousCurrentLimitAmps, new ParamEnumParameters("ParamEnum.eContinuousCurrentLimitAmps", 0, 1, 0.5));
            put(ParamEnum.ePeakCurrentLimitMs, new ParamEnumParameters("ParamEnum.ePeakCurrentLimitMs", 0, 1, 0.5));
            put(ParamEnum.ePeakCurrentLimitAmps, new ParamEnumParameters("ParamEnum.ePeakCurrentLimitAmps", 0, 1, 0.5));
        }
    };
    public static void GetAllParamsTalon(int id, int timeoutMs, Map<ParamEnum, ParamEnumParameters> paramsToGet, List<ErrorCodeDoubleString> errorCodes) {
        TalonSRX testTalon = new TalonSRX(id);
        
        for(Map.Entry<ParamEnum, ParamEnumParameters> entry : paramsToGet.entrySet()) {    
            double value = testTalon.configGetParameter(entry.getKey(), 0, 1);    
            errorCodes.add(new ErrorCodeDoubleString(value, testTalon.getLastError(), "testTalon.configGetParameter(" + entry.getValue().name + ", 0, 1);"));
        }
    }
    public static void GetAllParamsVictor(int id, int timeoutMs, Map<ParamEnum, ParamEnumParameters> paramsToGet, List<ErrorCodeDoubleString> errorCodes) {
        VictorSPX testVictor = new VictorSPX(id);
        
        for(Map.Entry<ParamEnum, ParamEnumParameters> entry : paramsToGet.entrySet()) {    
            double value = testVictor.configGetParameter(entry.getKey(), 0, 1);    
            errorCodes.add(new ErrorCodeDoubleString(value, testVictor.getLastError(), "testVictor.configGetParameter(" + entry.getValue().name + ", 0, 1);"));
        }
    }
    public static void GetAllParamsPigeon(int id, int timeoutMs, Map<ParamEnum, ParamEnumParameters> paramsToGet, List<ErrorCodeDoubleString> errorCodes) {
        PigeonIMU testPigeon = new PigeonIMU(id);
        
        for(Map.Entry<ParamEnum, ParamEnumParameters> entry : paramsToGet.entrySet()) {    
            double value = testPigeon.configGetParameter(entry.getKey(), 0, 1);    
            errorCodes.add(new ErrorCodeDoubleString(value, testPigeon.getLastError(), "testPigeon.configGetParameter(" + entry.getValue().name + ", 0, 1);"));
        }
    }
    public static void GetAllParamsCANifier(int id, int timeoutMs, Map<ParamEnum, ParamEnumParameters> paramsToGet, List<ErrorCodeDoubleString> errorCodes) {
        CANifier testCANifier = new CANifier(id);
        
        for(Map.Entry<ParamEnum, ParamEnumParameters> entry : paramsToGet.entrySet()) {    
            double value = testCANifier.configGetParameter(entry.getKey(), 0, 1);    
            errorCodes.add(new ErrorCodeDoubleString(value, testCANifier.getLastError(), "testCANifier.configGetParameter(" + entry.getValue().name + ", 0, 1);"));
        }
    }
}
