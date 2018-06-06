package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.RemoteSensorSource;

public class BaseSlotConfiguration{
    public double SelectedFeedbackCoefficient;
    public SensorTerm sensorTerm;

    //Remote feedback filter information isn't used unless the device is a remote
    public int RemoteFeedbackFilter;
    public int DeviceID;
    public RemoteSensorSource remoteSensorSource;

    public double kP;
    public double kI;
    public double kD;
    public double kF;
    public int IntegralZone;
    public int AllowableClosedloopError;
    public double MaxIntegralAccumulator;
    public double ClosedLoopPeakOutput;
    public int ClosedLoopPeriod;

    public BaseSlotConfiguration() {
        SelectedFeedbackCoefficient = 1.0;
        sensorTerm = SensorTerm.Sum0;
        RemoteFeedbackFilter = 0;
        DeviceID = 0;
        //remoteSensorSource = ; TODO fix
        kP = 0.0;
        kI = 0.0;
        kD = 0.0;
        kF = 0.0;
        IntegralZone = 0;
        AllowableClosedloopError = 0;
        MaxIntegralAccumulator = 0.0;
        ClosedLoopPeakOutput = 1.0;
        ClosedLoopPeriod = 1;
    }
} // class BaseSlotConfiguration

