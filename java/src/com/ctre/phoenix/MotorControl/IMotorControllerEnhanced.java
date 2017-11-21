package com.ctre.phoenix.MotorControl;

import com.ctre.phoenix.ErrorCode;

public interface IMotorControllerEnhanced extends IMotorController {
	 //------ Set output routines. ----------//
    /* in parent */

    //------ Invert behavior ----------//
    /* in parent */

    //----- general output shaping ------------------//
    /* in parent */

    //------ Voltage Compensation ----------//
    /* in parent */

    //------ General Status ----------//
    /* in parent */

    //------ sensor selection ----------//
    /* expand the options */
	 public ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int timeoutMs );

    //------ ??? ----------//
    // public ErrorCode ConfigSensorIsContinuous(bool isContinuous, int timeoutMs = 0);  /* TODO: figure this out later */
    // public ErrorCode ConfigAutoZeroSensor(ZeroSensorCriteria zeroSensorCriteria, int timeoutMs );

    //------- sensor status --------- //
    /* in parent */

    //------ status frame period changes ----------//
    public ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame, int periodMs, int timeoutMs );
    public int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs );

    //----- velocity signal conditionaing ------//
    public ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period, int timeoutMs );
    public ErrorCode ConfigVelocityMeasurementWindow(int windowSize, int timeoutMs );

    //------ remote limit switch ----------//
    /* in parent */

    //------ local limit switch ----------//
    public ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int timeoutMs );
    public ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int timeoutMs );

    //------ soft limit ----------//
    /* in parent */

    //------ Current Lim ----------//
    public ErrorCode ConfigPeakCurrentLimit(int amps, int timeoutMs );
    public ErrorCode ConfigPeakCurrentDuration(int milliseconds, int timeoutMs );
    public ErrorCode ConfigContinuousCurrentLimit(int amps, int timeoutMs );
    public void EnableCurrentLimit(boolean enable);

    //------ General Close loop ----------//
    /* in parent */

    //------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
    /* in parent */

    //------ Motion Profile Buffer ----------//
    /* in parent */

    //------ error ----------//
    /* in parent */

    //------ Faults ----------//
    /* in parent */

    //------ Firmware ----------//
    /* in parent */

    //------ Custom Persistent Params ----------//
    /* in parent */

    //------ Generic Param API, typically not used ----------//
    /* in parent */

    //------ Misc. ----------//
    /* in parent */

    //------ RAW Sensor API ----------//
    /**
     * @retrieve object that can get/set individual RAW sensor values.
     */
    //SensorCollection SensorCollection { get; }
    
    
}