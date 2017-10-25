#include "ctre/phoenix/MotorControl/CAN/BaseMotorController.h"

namespace CTRE.Phoenix.MotorControl
{
    public abstract class BaseMotorController : IMotorController
    {
        ErrorCode _lastError;
        SensorCollection _sensColl;
        protected MotControllerWithBuffer_LowLevel _ll;

        ControlMode m_controlMode = ControlMode.PercentOutput;
        ControlMode m_sendMode;

        int _arbId;
        float m_setPoint = 0;
        bool _invert;
        int m_profile = 0;

        // FeedbackDevice m_feedbackDevice = FeedbackDevice.QuadEncoder;

        //--------------------- Constructors -----------------------------//
        /**
         * Constructor for the CANTalon device.
         * @param deviceNumber The CAN ID of the Talon SRX
         * @param externalEnable pass true to prevent sending enable frames.
         *  	This can be useful when having one device enable the Talon, and
         * 		another to control it.
         */
        public BaseMotorController(int arbId, bool externalEnable = false)
        {
            _arbId = arbId;
            _ll = new MotControllerWithBuffer_LowLevel(arbId, externalEnable);
            _sensColl = new SensorCollection(_ll);
        }
        //------ Set output routines. ----------//
        /**
        * Sets the appropriate output on the talon, depending on the mode.
        *
        * In PercentOutput, the output is between -1.0 and 1.0, with 0.0 as stopped.
        * In Voltage mode, output value is in volts.
        * In Current mode, output value is in amperes.
        * In Speed mode, output value is in position change / 100ms.
        * In Position mode, output value is in encoder ticks or an analog value,
        *   depending on the sensor.
        * In Follower mode, the output value is the integer device ID of the talon to
        * duplicate.
        *
        * @param outputValue The setpoint value, as described above.
        * @see SelectProfileSlot to choose between the two sets of gains.
        */
        public void Set(ControlMode Mode, float value)
        {
            Set(Mode, value, 0);
        }
        public void Set(ControlMode mode, float demand0, float demand1)
        {
            m_controlMode = mode;
            m_sendMode = mode;
            m_setPoint = demand0;

            int status = 0;

            switch (m_controlMode)
            {
                case ControlMode.PercentOutput:
                case ControlMode.TimedPercentOutput:
                    _ll.SetDemand(m_sendMode, (int)(1023 * demand0), 0);
                    break;
                default:
                    _ll.SetDemand(m_sendMode, 0, 0);
                    break;

            }
            //
            //switch (m_controlMode)
            //{
            //    case ControlMode.PercentOutput:
            //        status = _cci.SetDemand((int)m_sendMode, (int)demand0);
            //        break;
            //    case ControlMode.Follower:
            //        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
            //        break;
            //    case ControlMode.Velocity:
            //        /* if the caller has provided scaling info, apply it */
            //        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
            //        break;
            //    case ControlMode.Position:
            //        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
            //        break;
            //    case ControlMode.MotionProfile:
            //        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
            //        break;
            //    case ControlMode.MotionMagic:
            //        status = _cci.SetDemand((int)demand0, (int)m_sendMode);
            //        break;
            //    default:
            //        Debug.Print("The CTRE MotorController does not support this control mode.");
            //        break;
            //}
            SetLastError(status);
        }
        public void NeutralOutput()
        {
            Set(ControlMode.Disabled, 0);
        }
        public void SetNeutralMode(NeutralMode neutralMode)
        {
            _ll.SetNeutralMode(neutralMode);
        }

        //------ Invert behavior ----------//
        public void SetSensorPhase(bool PhaseSensor)
        {
            _ll.SetSensorPhase(PhaseSensor);
        }
        public void SetInverted(bool invert)
        {
            _invert = invert; /* cache for getter */
            _ll.SetInverted(_invert);
        }
        public bool GetInverted()
        {
            return _invert;
        }

        //----- general output shaping ------------------//
        public ErrorCode ConfigOpenloopRamp(float secondsFromNeutralToFull, int timeoutMs = 0)
        {
            return _ll.ConfigOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
        }
        public ErrorCode ConfigClosedloopRamp(float secondsFromNeutralToFull, int timeoutMs = 0)
        {
            return _ll.ConfigClosedloopRamp(secondsFromNeutralToFull, timeoutMs);
        }
        public ErrorCode ConfigPeakOutputForward(float percentOut, int timeoutMs = 0)
        {
            return _ll.ConfigPeakOutputForward(percentOut, timeoutMs);
        }
        public ErrorCode ConfigPeakOutputReverse(float percentOut, int timeoutMs = 0)
        {
            return _ll.ConfigPeakOutputReverse(percentOut, timeoutMs);
        }
        public ErrorCode ConfigNominalOutputForward(float percentOut, int timeoutMs = 0)
        {
            return _ll.ConfigNominalOutputForward(percentOut, timeoutMs);
        }
        public ErrorCode ConfigNominalOutputReverse(float percentOut, int timeoutMs = 0)
        {
            return _ll.ConfigNominalOutputReverse(percentOut, timeoutMs);
        }
        public ErrorCode ConfigOpenLoopNeutralDeadband(float percentDeadband = Constants.DefaultDeadband, int timeoutMs = 0)
        {
            return _ll.ConfigOpenLoopNeutralDeadband(percentDeadband, timeoutMs);
        }
        public ErrorCode ConfigClosedLoopNeutralDeadband(float percentDeadband = 0, int timeoutMs = 0)
        {
            return _ll.ConfigClosedLoopNeutralDeadband(percentDeadband, timeoutMs);
        }

        //------ Voltage Compensation ----------//
        public ErrorCode ConfigVoltageCompSaturation(float voltage, int timeoutMs = 0)
        {
            return _ll.ConfigVoltageCompSaturation(voltage, timeoutMs);
        }
        public ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples, int timeoutMs = 0)
        {
            return _ll.ConfigVoltageMeasurementFilter(filterWindowSamples, timeoutMs);
        }
        public void EnableVoltageCompensation(bool enable)
        {
            _ll.EnableVoltageCompensation(enable);
        }

        //------ General Status ----------//
        public ErrorCode GetBusVoltage(out float param)
        {
            return _ll.GetBusVoltage(out param);
        }
        public ErrorCode GetMotorOutputPercent(out float param)
        {
            return _ll.GetMotorOutputPercent(out param);
        }
        public ErrorCode GetMotorOutputVoltage(out float param)
        {
            ErrorCode er;
            float v, p;
            er = GetBusVoltage(out v);
            GetMotorOutputPercent(out p);

            param = v * p;
            return er;
        }
        public ErrorCode GetOutputCurrent(out float param)
        {
            return _ll.GetOutputCurrent(out param);
        }
        public ErrorCode GetTemperature(out float param)
        {
            return _ll.GetTemperature(out param);
        }

        //------ sensor selection ----------//
        public ErrorCode ConfigSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int timeoutMs = 0)
        {
            /* we may break this into two APIs */
            ErrorCode e1 = _ll.ConfigRemoteFeedbackFilter(feedbackDevice._arbId, feedbackDevice._peripheralIndex, feedbackDevice._reserved, timeoutMs);

            ErrorCode e2 = _ll.ConfigSelectedFeedbackSensor(FeedbackDevice.RemoteSensor, timeoutMs);

            if (e1 == ErrorCode.OK) { return e2; }
            return e1;
        }
        public ErrorCode ConfigSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int timeoutMs = 0)
        {
            return _ll.ConfigSelectedFeedbackSensor(feedbackDevice, timeoutMs);
        }


        //------- sensor status --------- //
        public int GetSelectedSensorPosition()
        {
            int retval;
            SetLastError(_ll.GetSelectedSensorPosition(out retval));
            return retval;
        }
        public int GetSelectedSensorVelocity()
        {
            int retval;
            ErrorCode err = _ll.GetSelectedSensorVelocity(out retval);
            SetLastError(err);
            return retval;
        }
        public ErrorCode SetSelectedSensorPosition(int sensorPos, int timeoutMs = 0)
        {
            return _ll.SetSelectedSensorPosition(sensorPos, timeoutMs);
        }

        //------ status frame period changes ----------//
        public ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs)
        {
            return _ll.SetControlFramePeriod(frame, periodMs);
        }
        public ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs, int timeoutMs = 0)
        {
            return _ll.SetStatusFramePeriod(frame, periodMs, timeoutMs);
        }
        public ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame, int periodMs, int timeoutMs = 0)
        {
            return _ll.SetStatusFramePeriod(frame, periodMs, timeoutMs);
        }
        public ErrorCode GetStatusFramePeriod(StatusFrame frame, out int periodMs, int timeoutMs = 0)
        {
            return _ll.GetStatusFramePeriod(frame, out periodMs, timeoutMs);
        }
        public ErrorCode GetStatusFramePeriod(StatusFrameEnhanced frame, out int periodMs, int timeoutMs = 0)
        {
            return _ll.GetStatusFramePeriod(frame, out periodMs, timeoutMs);
        }

        //----- velocity signal conditionaing ------//
        public ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period, int timeoutMs = 0)
        {
            return _ll.ConfigVelocityMeasurementPeriod(period, timeoutMs);
        }
        public ErrorCode ConfigVelocityMeasurementWindow(int windowSize, int timeoutMs = 0)
        {
            return _ll.ConfigVelocityMeasurementWindow(windowSize, timeoutMs);
        }


        //------ remote limit switch ----------//
        public ErrorCode ConfigForwardLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0)
        {
            var cciType = LimitSwitchRoutines.Promote(type);
            return _ll.ConfigForwardLimitSwitchSource(cciType, normalOpenOrClose, deviceID, timeoutMs);
        }

        public ErrorCode ConfigReverseLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int deviceID, int timeoutMs = 0)
        {
            var cciType = LimitSwitchRoutines.Promote(type);
            return _ll.ConfigReverseLimitSwitchSource(cciType, normalOpenOrClose, deviceID, timeoutMs);
        }
        public void EnableLimitSwitches(bool enable)
        {
            _ll.EnableLimitSwitches(enable);
        }

        //------ local limit switch ----------//
        public ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0)
        {
            return _ll.ConfigForwardLimitSwitchSource(type, normalOpenOrClose, 0, timeoutMs);
        }
        public ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0)
        {
            return _ll.ConfigReverseLimitSwitchSource(type, normalOpenOrClose, 0, timeoutMs);
        }


        //------ soft limit ----------//
        public ErrorCode ConfigForwardSoftLimit(int forwardSensorLimit, int timeoutMs = 0)
        {
            return _ll.ConfigForwardSoftLimit(forwardSensorLimit, timeoutMs);
        }

        public ErrorCode ConfigReverseSoftLimit(int reverseSensorLimit, int timeoutMs = 0)
        {
            return _ll.ConfigReverseSoftLimit(reverseSensorLimit, timeoutMs);
        }

        public void EnableSoftLimits(bool enable)
        {
            _ll.EnableSoftLimits(enable);
        }

        //------ Current Lim ----------//
        /* not available in base */

        //------ General Close loop ----------//
        public ErrorCode Config_kP(int slotIdx, float value, int timeoutMs = 0)
        {
            return _ll.Config_kP(slotIdx, value, timeoutMs);
        }
        public ErrorCode Config_kI(int slotIdx, float value, int timeoutMs = 0)
        {
            return _ll.Config_kI(slotIdx, value, timeoutMs);
        }
        public ErrorCode Config_kD(int slotIdx, float value, int timeoutMs = 0)
        {
            return _ll.Config_kD(slotIdx, value, timeoutMs);
        }
        public ErrorCode Config_kF(int slotIdx, float value, int timeoutMs = 0)
        {
            return _ll.Config_kF(slotIdx, value, timeoutMs);
        }
        public ErrorCode Config_IntegralZone(int slotIdx, int izone, int timeoutMs = 0)
        {
            return _ll.Config_IntegralZone(slotIdx, izone, timeoutMs);
        }
        public ErrorCode ConfigAllowableClosedloopError(int slotIdx, int allowableCloseLoopError, int timeoutMs = 0)
        {
            return _ll.ConfigAllowableClosedloopError(slotIdx, allowableCloseLoopError, timeoutMs);
        }
        public ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, float iaccum = 0, int timeoutMs = 0)
        {
            return _ll.ConfigMaxIntegralAccumulator(slotIdx, iaccum, timeoutMs);
        }

        public ErrorCode SetIntegralAccumulator(float iaccum = 0, int timeoutMs = 0)
        {
            return _ll.SetIntegralAccumulator(iaccum, timeoutMs);
        }

        public ErrorCode GetClosedLoopError(out int closedLoopError)
        {
            return SetLastError(_ll.GetClosedLoopError(out closedLoopError));
        }
        public ErrorCode GetIntegralAccumulator(out float iaccum)
        {
            return _ll.GetIntegralAccumulator(out iaccum);
        }
        public ErrorCode GetErrorDerivative(out float derror)
        {
            return SetLastError(_ll.GetErrorDerivative(out derror));
        }
        /**
         * SRX has two available slots for PID.
         * @param slotIdx one or zero depending on which slot caller wants.
         */
        public void SelectProfileSlot(int slotIdx)
        {
            m_profile = slotIdx; /* only get two slots for now */
            _ll.SelectProfileSlot(m_profile);
        }

        //------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//
        public ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms, int timeoutMs = 0)
        {
            return ErrorCode.FeatureNotSupported;
        }
        public ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec, int timeoutMs = 0)
        {
            return ErrorCode.FeatureNotSupported;
        }

        //------ Motion Profile Buffer ----------//
        public void ClearMotionProfileTrajectories()
        {
            _ll.ClearMotionProfileTrajectories();
        }
        public int GetMotionProfileTopLevelBufferCount()
        {
            return _ll.GetMotionProfileTopLevelBufferCount();
        }
        public bool IsMotionProfileTopLevelBufferFull()
        {
            return _ll.IsMotionProfileTopLevelBufferFull();
        }
        public void ProcessMotionProfileBuffer()
        {
            _ll.ProcessMotionProfileBuffer();
        }
        public void GetMotionProfileStatus(Motion.MotionProfileStatus statusToFill)
        {
            _ll.GetMotionProfileStatus(statusToFill);
        }
        public ErrorCode PushMotionProfileTrajectory(Motion.TrajectoryPoint trajPt)
        {
            return _ll.PushMotionProfileTrajectory(trajPt);
        }
        public void ClearMotionProfileHasUnderrun(int timeoutMs = 0)
        {
            _ll.ClearMotionProfileHasUnderrun(timeoutMs);
        }

        //------ error ----------//
        public ErrorCode GetLastError()
        {
            return _lastError.GetLastError();
        }
        ErrorCode SetLastError(int error)
        {
            return (ErrorCode)_lastError.SetLastError(error);
        }
        ErrorCode SetLastError(ErrorCode error)
        {
            return (ErrorCode)_lastError.SetLastError(error);
        }

        //------ Faults ----------//
        public ErrorCode GetFaults(Faults toFill)
        {
            return ErrorCode.FeatureNotSupported;
        }
        public ErrorCode GetStickyFaults(Faults toFill)
        {
            return ErrorCode.FeatureNotSupported;
        }
        public ErrorCode ClearStickyFaults()
        {
            return ErrorCode.FeatureNotSupported;
        }

        //------ Firmware ----------//
        public int GetFirmwareVersion()
        {
            return _ll.GetFirmwareVersion();
        }
        public bool HasResetOccured()
        {
            return _ll.HasResetOccured();
        }

        //------ Custom Persistent Params ----------//
        public ErrorCode ConfigSetCustomParam(int newValue, int paramIndex, int timeoutMs = 0)
        {
            return _ll.ConfigSetCustomParam(newValue, paramIndex, timeoutMs);
        }
        public ErrorCode ConfigGetCustomParam(out int readValue, int paramIndex, int timeoutMs = Constants.GetParamTimeoutMs)
        {
            return _ll.ConfigGetCustomParam(out readValue, paramIndex, timeoutMs);
        }

        //------ Generic Param API, typically not used ----------//
        public ErrorCode ConfigSetParameter(ParamEnum param, float value, byte subValue, int ordinal = 0, int timeoutMs = 0)
        {
            return _ll.ConfigSetParameter(param, value, subValue, ordinal, timeoutMs);

        }
        public ErrorCode ConfigGetParameter(ParamEnum param, out float value, int ordinal = 0, int timeoutMs = Constants.GetParamTimeoutMs)
        {
            ErrorCode retval = _ll.ConfigGetParameter(param, out value, ordinal, timeoutMs);

            return SetLastError(retval);
        }
        //------ Misc. ----------//
        public int GetBaseID()
        {
            return _arbId;
        }
        // ----- Follower ------//
        public void Follow(Object masterToFollow)
        {
            IMotorController master = (IMotorController)masterToFollow;
            /* set it up */
            Set(ControlMode.Follower, master.GetBaseID());
        }
        public void ValueUpdated()
        {
            //do nothing
        }

        //------ RAW Sensor API ----------//
        /**
         * @retrieve object that can get/set individual RAW sensor values.
         */
        SensorCollection SensorCollection
        {
            get
            {
                return _sensColl;
            }
        }
    }
}
