package com.ctre.phoenix.motorcontrol.can;

import com.ctre.phoenix.motorcontrol.ControlFrame;
import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.DemandType;
import com.ctre.phoenix.motorcontrol.Faults;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.FollowerType;
import com.ctre.phoenix.motorcontrol.IMotorController;
import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.ctre.phoenix.motorcontrol.RemoteFeedbackDevice;
import com.ctre.phoenix.motorcontrol.RemoteLimitSwitchSource;
import com.ctre.phoenix.motorcontrol.RemoteSensorSource;
import com.ctre.phoenix.motorcontrol.SensorTerm;
import com.ctre.phoenix.motorcontrol.StatusFrame;
import com.ctre.phoenix.motorcontrol.StatusFrameEnhanced;
import com.ctre.phoenix.motorcontrol.StickyFaults;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.can.MotControllerJNI;
import com.ctre.phoenix.ParamEnum;
import com.ctre.phoenix.motion.MotionProfileStatus;
import com.ctre.phoenix.motion.SetValueMotionProfile;
import com.ctre.phoenix.motion.TrajectoryPoint;
import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.ErrorCollection;
import com.ctre.phoenix.ParamEnum;

/**
 * Base motor controller features for all CTRE CAN motor controllers.
 */
public abstract class BaseMotorController implements com.ctre.phoenix.motorcontrol.IMotorController {

	private ControlMode m_controlMode = ControlMode.PercentOutput;
	private ControlMode m_sendMode = ControlMode.PercentOutput;

	private int _arbId = 0;
	private boolean _invert = false;

	protected long m_handle;

	private int [] _motionProfStats = new int[11];

	// --------------------- Constructors -----------------------------//
	/**
	 * Constructor for motor controllers.
	 *
	 * @param arbId
	 */
	public BaseMotorController(int arbId) {
		m_handle = MotControllerJNI.Create(arbId);
		_arbId = arbId;
	}
	/**
	 * @return CCI handle for child classes.
	 */
	public long getHandle() {
		return m_handle;
	}

	/**
	 * Returns the Device ID
	 *
	 * @return Device number.
	 */
	public int getDeviceID() {
		return MotControllerJNI.GetDeviceNumber(m_handle);
	}

	// ------ Set output routines. ----------//
	/**
	 * Sets the appropriate output on the talon, depending on the mode.
	 * @param mode The output mode to apply.
	 * In PercentOutput, the output is between -1.0 and 1.0, with 0.0 as stopped.
	 * In Current mode, output value is in amperes.
	 * In Velocity mode, output value is in position change / 100ms.
	 * In Position mode, output value is in encoder ticks or an analog value,
	 *   depending on the sensor.
	 * In Follower mode, the output value is the integer device ID of the talon to
	 * duplicate.
	 *
	 * @param outputValue The setpoint value, as described above.
	 *
	 *
	 *	Standard Driving Example:
	 *	_talonLeft.set(ControlMode.PercentOutput, leftJoy);
	 *	_talonRght.set(ControlMode.PercentOutput, rghtJoy);
	 */
	public void set(ControlMode mode, double outputValue) {
		set(mode, outputValue, DemandType.Neutral, 0);
	}
	/**
     * @deprecated use 4 parameter set
	 * @param mode Sets the appropriate output on the talon, depending on the mode.
	 * @param demand0 The output value to apply.
	 * 	such as advanced feed forward and/or auxiliary close-looping in firmware.
	 * In PercentOutput, the output is between -1.0 and 1.0, with 0.0 as stopped.
	 * In Current mode, output value is in amperes.
	 * In Velocity mode, output value is in position change / 100ms.
	 * In Position mode, output value is in encoder ticks or an analog value,
	 *   depending on the sensor. See
	 * In Follower mode, the output value is the integer device ID of the talon to
	 * duplicate.
	 *
	 * @param demand1 Supplemental value.  This will also be control mode specific for future features.
	 */
    @Deprecated
	public void set(ControlMode mode, double demand0, double demand1) {
		set(mode, demand0, DemandType.Neutral, demand1);
	}
	/**
	 * @param mode Sets the appropriate output on the talon, depending on the mode.
	 * @param demand0 The output value to apply.
	 * 	such as advanced feed forward and/or auxiliary close-looping in firmware.
	 * In PercentOutput, the output is between -1.0 and 1.0, with 0.0 as stopped.
	 * In Current mode, output value is in amperes.
	 * In Velocity mode, output value is in position change / 100ms.
	 * In Position mode, output value is in encoder ticks or an analog value,
	 *   depending on the sensor. See
	 * In Follower mode, the output value is the integer device ID of the talon to
	 * duplicate.
	 *
	 * @param demand1Type The demand type for demand1.
	 * Neutral: Ignore demand1 and apply no change to the demand0 output.
	 * AuxPID: Use demand1 to set the target for the auxiliary PID 1.
	 * ArbitraryFeedForward: Use demand1 as an arbitrary additive value to the
	 *	 demand0 output.  In PercentOutput the demand0 output is the motor output,
	 *   and in closed-loop modes the demand0 output is the output of PID0.
	 * @param demand1 Supplmental output value.  Units match the set mode.
	 *
	 *
	 *  Arcade Drive Example:
	 *		_talonLeft.set(ControlMode.PercentOutput, joyForward, DemandType.ArbitraryFeedForward, +joyTurn);
	 *		_talonRght.set(ControlMode.PercentOutput, joyForward, DemandType.ArbitraryFeedForward, -joyTurn);
	 *
	 *	Drive Straight Example:
	 *	Note: Selected Sensor Configuration is necessary for both PID0 and PID1.
	 *		_talonLeft.follow(_talonRght, FollwerType.AuxOutput1);
	 *		_talonRght.set(ControlMode.PercentOutput, joyForward, DemandType.AuxPID, desiredRobotHeading);
	 *
	 *	Drive Straight to a Distance Example:
	 *	Note: Other configurations (sensor selection, PID gains, etc.) need to be set.
	 *		_talonLeft.follow(_talonRght, FollwerType.AuxOutput1);
	 *		_talonRght.set(ControlMode.MotionMagic, targetDistance, DemandType.AuxPID, desiredRobotHeading);
	 */
	public void set(ControlMode mode, double demand0, DemandType demand1Type, double demand1){
		m_controlMode = mode;
		m_sendMode = mode;
		int work;

		switch (m_controlMode) {
		case PercentOutput:
			// case TimedPercentOutput:
			MotControllerJNI.Set_4(m_handle, m_sendMode.value, demand0, demand1, demand1Type.value);
			break;
		case Follower:
			/* did caller specify device ID */
			if ((0 <= demand0) && (demand0 <= 62)) { // [0,62]
				work = getBaseID();
				work >>= 16;
				work <<= 8;
				work |= ((int) demand0) & 0xFF;
			} else {
				work = (int) demand0;
			}
			/* single precision guarantees 16bits of integral precision,
		   * so float/double cast on work is safe */
			MotControllerJNI.Set_4(m_handle, m_sendMode.value, (double)work, demand1, demand1Type.value);
			break;
		case Velocity:
		case Position:
		case MotionMagic:
		case MotionProfile:
		case MotionProfileArc:
			MotControllerJNI.Set_4(m_handle, m_sendMode.value, demand0, demand1, demand1Type.value);
			break;
		case Current:
			MotControllerJNI.SetDemand(m_handle, m_sendMode.value, (int) (1000. * demand0), 0); /* milliamps */
			break;
		case Disabled:
			/* fall thru... */
		default:
			MotControllerJNI.SetDemand(m_handle, m_sendMode.value, 0, 0);
			break;
		}

	}

	/**
	 * Neutral the motor output by setting control mode to disabled.
	 */
	public void neutralOutput() {
		set(ControlMode.Disabled, 0);
	}

	/**
	 * Sets the mode of operation during neutral throttle output.
	 *
	 * @param neutralMode
	 *            The desired mode of operation when the Controller output
	 *            throttle is neutral (ie brake/coast)
	 **/
	public void setNeutralMode(NeutralMode neutralMode) {
		MotControllerJNI.SetNeutralMode(m_handle, neutralMode.value);
	}
	/**
	 * Enables a future feature called "Heading Hold".
	 * For now this simply updates the CAN signal to the motor controller.
	 * Future firmware updates will use this.
	 *
	 *	@param enable true/false enable
	 */
	public void enableHeadingHold(boolean enable) {
		/* this routine is moot as the Set() call updates the signal on each call */
		//MotControllerJNI.EnableHeadingHold(m_handle, enable ? 1 : 0);
	}
	/**
	 * For now this simply updates the CAN signal to the motor controller.
	 * Future firmware updates will use this to control advanced auxiliary loop behavior.
	 *
	 *	@param value
	 */
	public void selectDemandType(boolean value) {
		/* this routine is moot as the Set() call updates the signal on each call */
		//MotControllerJNI.SelectDemandType(m_handle, value ? 1 : 0);
	}

	// ------ Invert behavior ----------//
	/**
	 * Sets the phase of the sensor. Use when controller forward/reverse output
	 * doesn't correlate to appropriate forward/reverse reading of sensor.
	 * Pick a value so that positive PercentOutput yields a positive change in sensor.
	 * After setting this, user can freely call SetInverted() with any value.
	 *
	 * @param PhaseSensor
	 *            Indicates whether to invert the phase of the sensor.
	 */
	public void setSensorPhase(boolean PhaseSensor) {
		MotControllerJNI.SetSensorPhase(m_handle, PhaseSensor);
	}

	/**
	 * Inverts the hbridge output of the motor controller.
	 *
	 * This does not impact sensor phase and should not be used to correct sensor polarity.
	 *
	 * This will invert the hbridge output but NOT the LEDs.
	 * This ensures....
	 *  - Green LEDs always represents positive request from robot-controller/closed-looping mode.
	 *  - Green LEDs correlates to forward limit switch.
	 *  - Green LEDs correlates to forward soft limit.
	 *
	 * @param invert
	 *            Invert state to set.
	 */
	public void setInverted(boolean invert) {
		_invert = invert; /* cache for getter */
		MotControllerJNI.SetInverted(m_handle, invert);
	}
	/**
	 * @return invert setting of motor output.
	 */
	public boolean getInverted() {
		return _invert;
	}
	
    //----- Factory Default Configuration -----//
	/**
	 * Configure all configurations to factory default values
	 * 
	 * @param timeoutMs
	 *            Timeout value in ms. Function will generate error if config is
	 *            not successful within timeout.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configFactoryDefault(int timeoutMs){
		int retval = MotControllerJNI.ConfigFactoryDefault(m_handle, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configFactoryDefault() {
        int timeoutMs = 50;
		int retval = MotControllerJNI.ConfigFactoryDefault(m_handle, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	// ----- general output shaping ------------------//
	/**
	 * Configures the open-loop ramp rate of throttle output.
	 *
	 * @param secondsFromNeutralToFull
	 *            Minimum desired time to go from neutral to full throttle. A
	 *            value of '0' will disable the ramp.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configOpenloopRamp(double secondsFromNeutralToFull, int timeoutMs) {
		int retval = MotControllerJNI.ConfigOpenLoopRamp(m_handle, secondsFromNeutralToFull, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configOpenloopRamp(double secondsFromNeutralToFull) {
		int timeoutMs = 0;
		return configOpenloopRamp(secondsFromNeutralToFull, timeoutMs);
	}

	/**
	 * Configures the closed-loop ramp rate of throttle output.
	 *
	 * @param secondsFromNeutralToFull
	 *            Minimum desired time to go from neutral to full throttle. A
	 *            value of '0' will disable the ramp.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configClosedloopRamp(double secondsFromNeutralToFull, int timeoutMs) {
		int retval = MotControllerJNI.ConfigClosedLoopRamp(m_handle, secondsFromNeutralToFull, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configClosedloopRamp(double secondsFromNeutralToFull) {
		int timeoutMs = 0;
		return configClosedloopRamp(secondsFromNeutralToFull, timeoutMs);	
	}

	/**
	 * Configures the forward peak output percentage.
	 *
	 * @param percentOut
	 *            Desired peak output percentage. [0,1]
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configPeakOutputForward(double percentOut, int timeoutMs) {
		int retval = MotControllerJNI.ConfigPeakOutputForward(m_handle, percentOut, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configPeakOutputForward(double percentOut) {
		int timeoutMs = 0;
		return configPeakOutputForward(percentOut, timeoutMs);	
	}

	/**
	 * Configures the reverse peak output percentage.
	 *
	 * @param percentOut
	 *            Desired peak output percentage.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configPeakOutputReverse(double percentOut, int timeoutMs) {
		int retval = MotControllerJNI.ConfigPeakOutputReverse(m_handle, percentOut, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configPeakOutputReverse(double percentOut) {
		int timeoutMs = 0;
		return configPeakOutputReverse(percentOut, timeoutMs);	
	}
	/**
	 * Configures the forward nominal output percentage.
	 *
	 * @param percentOut
	 *            Nominal (minimum) percent output. [0,+1]
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configNominalOutputForward(double percentOut, int timeoutMs) {
		int retval = MotControllerJNI.ConfigNominalOutputForward(m_handle, percentOut, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configNominalOutputForward(double percentOut) {
		int timeoutMs = 0;
		return configNominalOutputForward(percentOut, timeoutMs);
	}

	/**
	 * Configures the reverse nominal output percentage.
	 *
	 * @param percentOut
	 *            Nominal (minimum) percent output. [-1,0]
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configNominalOutputReverse(double percentOut, int timeoutMs) {
		int retval = MotControllerJNI.ConfigNominalOutputReverse(m_handle, percentOut, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configNominalOutputReverse(double percentOut) {
		int timeoutMs = 0;
		return configNominalOutputReverse(percentOut, timeoutMs);
	}

	/**
	 * Configures the output deadband percentage.
	 *
	 * @param percentDeadband
	 *            Desired deadband percentage. Minimum is 0.1%, Maximum is 25%.
	 *            Pass 0.04 for 4% (factory default).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configNeutralDeadband(double percentDeadband, int timeoutMs) {
		int retval = MotControllerJNI.ConfigNeutralDeadband(m_handle, percentDeadband, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configNeutralDeadband(double percentDeadband) {
		int timeoutMs = 0;
		return configNeutralDeadband(percentDeadband, timeoutMs);	
	}

	// ------ Voltage Compensation ----------//
	/**
	 * Configures the Voltage Compensation saturation voltage.
	 *
	 * @param voltage
	 *            This is the max voltage to apply to the hbridge when voltage
	 *            compensation is enabled.  For example, if 10 (volts) is specified
	 *            and a TalonSRX is commanded to 0.5 (PercentOutput, closed-loop, etc)
	 *            then the TalonSRX will attempt to apply a duty-cycle to produce 5V.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVoltageCompSaturation(double voltage, int timeoutMs) {
		int retval = MotControllerJNI.ConfigVoltageCompSaturation(m_handle, voltage, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configVoltageCompSaturation(double voltage) {
		int timeoutMs = 0;
		return configVoltageCompSaturation(voltage, timeoutMs);
	}

	/**
	 * Configures the voltage measurement filter.
	 *
	 * @param filterWindowSamples
	 *            Number of samples in the rolling average of voltage
	 *            measurement.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVoltageMeasurementFilter(int filterWindowSamples, int timeoutMs) {
		int retval = MotControllerJNI.ConfigVoltageMeasurementFilter(m_handle, filterWindowSamples, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configVoltageMeasurementFilter(int filterWindowSamples) {
		int timeoutMs = 0;
		return configVoltageMeasurementFilter(filterWindowSamples, timeoutMs);
	}

	/**
	 * Enables voltage compensation. If enabled, voltage compensation works in
	 * all control modes.
	 *
	 * @param enable
	 *            Enable state of voltage compensation.
	 **/
	public void enableVoltageCompensation(boolean enable) {
		MotControllerJNI.EnableVoltageCompensation(m_handle, enable);
	}

	// ------ General Status ----------//
	/**
	 * Gets the bus voltage seen by the device.
	 *
	 * @return The bus voltage value (in volts).
	 */
	public double getBusVoltage() {
		return MotControllerJNI.GetBusVoltage(m_handle);
	}

	/**
	 * Gets the output percentage of the motor controller.
	 *
	 * @return Output of the motor controller (in percent).
	 */
	public double getMotorOutputPercent() {
		return MotControllerJNI.GetMotorOutputPercent(m_handle);
	}

	/**
	 * @return applied voltage to motor  in volts.
	 */
	public double getMotorOutputVoltage() {
		return getBusVoltage() * getMotorOutputPercent();
	}

	/**
	 * Gets the output current of the motor controller.
	 *
	 * @return The output current (in amps).
	 */
	public double getOutputCurrent() {
		return MotControllerJNI.GetOutputCurrent(m_handle);
	}

	/**
	 * Gets the temperature of the motor controller.
	 *
	 * @return Temperature of the motor controller (in 'C)
	 */
	public double getTemperature() {
		return MotControllerJNI.GetTemperature(m_handle);
	}

	// ------ sensor selection ----------//
	/**
	 * Select the remote feedback device for the motor controller.
	 * Most CTRE CAN motor controllers will support remote sensors over CAN.
	 *
	 * @param feedbackDevice
	 *            Remote Feedback Device to select.
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice, int pidIdx, int timeoutMs) {
		int retval = MotControllerJNI.ConfigSelectedFeedbackSensor(m_handle, feedbackDevice.value, pidIdx, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configSelectedFeedbackSensor(RemoteFeedbackDevice feedbackDevice) {
		int pidIdx = 0;
		int timeoutMs = 0;	
		return configSelectedFeedbackSensor(feedbackDevice, pidIdx, timeoutMs);	
	}

	/**
	 * Select the feedback device for the motor controller.
	 *
	 * @param feedbackDevice
	 *            Feedback Device to select.
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSelectedFeedbackSensor(FeedbackDevice feedbackDevice, int pidIdx, int timeoutMs) {
		int retval = MotControllerJNI.ConfigSelectedFeedbackSensor(m_handle, feedbackDevice.value, pidIdx, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configSelectedFeedbackSensor(FeedbackDevice feedbackDevice) {
		int pidIdx = 0;
		int timeoutMs = 0;
		return configSelectedFeedbackSensor(feedbackDevice, pidIdx, timeoutMs);	
	}

	/**
	 * The Feedback Coefficient is a scalar applied to the value of the
	 * feedback sensor.  Useful when you need to scale your sensor values
	 * within the closed-loop calculations.  Default value is 1.
	 *
	 * Selected Feedback Sensor register in firmware is the decoded sensor value
	 * multiplied by the Feedback Coefficient.
	 *
	 * @param coefficient
	 *            Feedback Coefficient value.  Maximum value of 1.
	 *						Resolution is 1/(2^16).  Cannot be 0.
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSelectedFeedbackCoefficient(double coefficient, int pidIdx, int timeoutMs) {
	  int retval = MotControllerJNI.ConfigSelectedFeedbackCoefficient(m_handle, coefficient, pidIdx, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configSelectedFeedbackCoefficient(double coefficient) {
		int pidIdx = 0;
        int timeoutMs = 0;
		return configSelectedFeedbackCoefficient(coefficient, pidIdx, timeoutMs);	
	}
	/**
	 * Select what remote device and signal to assign to Remote Sensor 0 or Remote Sensor 1.
	 * After binding a remote device and signal to Remote Sensor X, you may select Remote Sensor X
	 * as a PID source for closed-loop features.
	 *
	 * @param deviceID
 	 *            The CAN ID of the remote sensor device.
	 * @param remoteSensorSource
	 *            The remote sensor device and signal type to bind.
	 * @param remoteOrdinal
	 *            0 for configuring Remote Sensor 0
	 *            1 for configuring Remote Sensor 1
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configRemoteFeedbackFilter(int deviceID, RemoteSensorSource remoteSensorSource, int remoteOrdinal,
			int timeoutMs) {
		int retval = MotControllerJNI.ConfigRemoteFeedbackFilter(m_handle, deviceID, remoteSensorSource.value, remoteOrdinal,
				timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configRemoteFeedbackFilter(int deviceID, RemoteSensorSource remoteSensorSource, int remoteOrdinal) {
        int timeoutMs = 0;
		return configRemoteFeedbackFilter(deviceID, remoteSensorSource, remoteOrdinal, timeoutMs);	
	}
	/**
	 * Select what sensor term should be bound to switch feedback device.
	 * Sensor Sum = Sensor Sum Term 0 - Sensor Sum Term 1
	 * Sensor Difference = Sensor Diff Term 0 - Sensor Diff Term 1
	 * The four terms are specified with this routine.  Then Sensor Sum/Difference
	 * can be selected for closed-looping.
	 *
	 * @param sensorTerm Which sensor term to bind to a feedback source.
	 * @param feedbackDevice The sensor signal to attach to sensorTerm.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSensorTerm(SensorTerm sensorTerm, FeedbackDevice feedbackDevice, int timeoutMs) {
		int retval = MotControllerJNI.ConfigSensorTerm(m_handle, sensorTerm.value, feedbackDevice.value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configSensorTerm(SensorTerm sensorTerm, FeedbackDevice feedbackDevice) {
		int timeoutMs = 0;	
		return configSensorTerm(sensorTerm, feedbackDevice, timeoutMs);
	}
	public ErrorCode configSensorTerm(SensorTerm sensorTerm, RemoteFeedbackDevice feedbackDevice, int timeoutMs) {
		return configSensorTerm(sensorTerm, feedbackDevice.getFeedbackDevice(), timeoutMs);
	}
	public ErrorCode configSensorTerm(SensorTerm sensorTerm, RemoteFeedbackDevice feedbackDevice) {
		int timeoutMs = 0;	
		return configSensorTerm(sensorTerm, feedbackDevice.getFeedbackDevice(), timeoutMs);
	}

	// ------- sensor status --------- //
	/**
	 * Get the selected sensor position (in raw sensor units).
	 *
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop. See
	 *            Phoenix-Documentation for how to interpret.
	 *
	 * @return Position of selected sensor (in raw sensor units).
	 */
	public int getSelectedSensorPosition(int pidIdx) {
		return MotControllerJNI.GetSelectedSensorPosition(m_handle, pidIdx);
	}
	public int getSelectedSensorPosition() {
		int pidIdx = 0;
		return getSelectedSensorPosition(pidIdx);
	}

	/**
	 * Get the selected sensor velocity.
	 *
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @return selected sensor (in raw sensor units) per 100ms.
	 * See Phoenix-Documentation for how to interpret.
	 */
	public int getSelectedSensorVelocity(int pidIdx) {
		return MotControllerJNI.GetSelectedSensorVelocity(m_handle, pidIdx);
	}
	public int getSelectedSensorVelocity() {
		int pidIdx = 0;
		return getSelectedSensorVelocity(pidIdx);
	}

	/**
	 * Sets the sensor position to the given value.
	 *
	 * @param sensorPos
	 *            Position to set for the selected sensor (in raw sensor units).
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setSelectedSensorPosition(int sensorPos, int pidIdx, int timeoutMs) {
		int retval = MotControllerJNI.SetSelectedSensorPosition(m_handle, sensorPos, pidIdx, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode setSelectedSensorPosition(int sensorPos) {
		int pidIdx = 0;
		int timeoutMs = 0;
		return setSelectedSensorPosition(sensorPos, pidIdx, timeoutMs);
	}

	// ------ status frame period changes ----------//
	/**
	 * Sets the period of the given control frame.
	 *
	 * @param frame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setControlFramePeriod(ControlFrame frame, int periodMs) {
		int retval = MotControllerJNI.SetControlFramePeriod(m_handle, frame.value, periodMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Sets the period of the given status frame.
	 *
	 * User ensure CAN Bus utilization is not high.
	 *
	 * This setting is not persistent and is lost when device is reset.
	 * If this is a concern, calling application can use HasReset()
	 * to determine if the status frame needs to be reconfigured.
	 *
	 * @param frame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setControlFramePeriod(int frame, int periodMs) {
		int retval = MotControllerJNI.SetControlFramePeriod(m_handle, frame, periodMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Sets the period of the given status frame.
	 *
	 * User ensure CAN Bus utilization is not high.
	 *
	 * This setting is not persistent and is lost when device is reset. If this
	 * is a concern, calling application can use HasReset() to determine if the
	 * status frame needs to be reconfigured.
	 *
	 * @param frameValue
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setStatusFramePeriod(int frameValue, int periodMs, int timeoutMs) {
		int retval = MotControllerJNI.SetStatusFramePeriod(m_handle, frameValue, periodMs, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode setStatusFramePeriod(int frameValue, int periodMs) {
		int timeoutMs = 0;
		return 	setStatusFramePeriod(frameValue, periodMs,timeoutMs);
	}

	/**
	 * Sets the period of the given status frame.
	 *
	 * @param frame
	 *            Frame whose period is to be changed.
	 * @param periodMs
	 *            Period in ms for the given frame.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setStatusFramePeriod(StatusFrame frame, int periodMs, int timeoutMs) {
		return setStatusFramePeriod(frame.value, periodMs, timeoutMs);
	}
	public ErrorCode setStatusFramePeriod(StatusFrame frame, int periodMs) {
		int timeoutMs = 0;
		return setStatusFramePeriod(frame,periodMs, timeoutMs);
	}

	/**
	 * Gets the period of the given status frame.
	 *
	 * @param frame
	 *            Frame to get the period of.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Period of the given status frame.
	 */
	public int getStatusFramePeriod(int frame, int timeoutMs) {
		return MotControllerJNI.GetStatusFramePeriod(m_handle, frame, timeoutMs);
	}
	public int getStatusFramePeriod(int frame) {
		int timeoutMs = 0;
		return getStatusFramePeriod(frame, timeoutMs);
	}

	/**
	 * Gets the period of the given status frame.
	 *
	 * @param frame
	 *            Frame to get the period of.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Period of the given status frame.
	 */
	public int getStatusFramePeriod(StatusFrame frame, int timeoutMs) {
		return MotControllerJNI.GetStatusFramePeriod(m_handle, frame.value, timeoutMs);
	}
	public int getStatusFramePeriod(StatusFrame frame) {
		int timeoutMs = 0;
		return getStatusFramePeriod(frame, timeoutMs);
	}

	/**
	 * Gets the period of the given status frame.
	 *
	 * @param frame
	 *            Frame to get the period of.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Period of the given status frame.
	 */
	public int getStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs) {
		return MotControllerJNI.GetStatusFramePeriod(m_handle, frame.value, timeoutMs);
	}
	public int getStatusFramePeriod(StatusFrameEnhanced frame) {
		int timeoutMs = 0;
		return  getStatusFramePeriod(frame, timeoutMs);
	}

	// ----- velocity signal conditionaing ------//

	/**
	 * Sets the period over which velocity measurements are taken.
	 *
	 * @param period
	 *            Desired period for the velocity measurement. @see
	 *            #VelocityMeasPeriod
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVelocityMeasurementPeriod(VelocityMeasPeriod period, int timeoutMs) {
		int retval = MotControllerJNI.ConfigVelocityMeasurementPeriod(m_handle, period.value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configVelocityMeasurementPeriod(VelocityMeasPeriod period) {
		int timeoutMs = 0;
		return configVelocityMeasurementPeriod(period, timeoutMs);		
	}

	/**
	 * Sets the number of velocity samples used in the rolling average velocity
	 * measurement.
	 *
	 * @param windowSize
	 *            Number of samples in the rolling average of velocity
	 *            measurement. Valid values are 1,2,4,8,16,32. If another value
	 *            is specified, it will truncate to nearest support value.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configVelocityMeasurementWindow(int windowSize, int timeoutMs) {
		int retval = MotControllerJNI.ConfigVelocityMeasurementWindow(m_handle, windowSize, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configVelocityMeasurementWindow(int windowSize) {
		int timeoutMs = 0;
		return configVelocityMeasurementWindow(windowSize, timeoutMs);
	}

	// ------ remote limit switch ----------//
	/**
	 * Configures the forward limit switch for a remote source. For example, a
	 * CAN motor controller may need to monitor the Limit-F pin of another Talon
	 * or CANifier.
	 *
	 * @param type
	 *            Remote limit switch source. User can choose between a remote
	 *            Talon SRX, CANifier, or deactivate the feature.
	 * @param normalOpenOrClose
	 *            Setting for normally open, normally closed, or disabled. This
	 *            setting matches the web-based configuration drop down.
	 * @param deviceID
	 *            Device ID of remote source (Talon SRX or CANifier device ID).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configForwardLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs) {
		return configForwardLimitSwitchSource(type.value, normalOpenOrClose.value, deviceID, timeoutMs);
	}
	public ErrorCode configForwardLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID) {
		int timeoutMs = 0;
		return configForwardLimitSwitchSource(type, normalOpenOrClose, deviceID, timeoutMs);	
	}

	/**
	 * Configures the reverse limit switch for a remote source. For example, a
	 * CAN motor controller may need to monitor the Limit-R pin of another Talon
	 * or CANifier.
	 *
	 * @param type
	 *            Remote limit switch source. User can choose between a remote
	 *            Talon SRX, CANifier, or deactivate the feature.
	 * @param normalOpenOrClose
	 *            Setting for normally open, normally closed, or disabled. This
	 *            setting matches the web-based configuration drop down.
	 * @param deviceID
	 *            Device ID of remote source (Talon SRX or CANifier device ID).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configReverseLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs) {
		int retval = MotControllerJNI.ConfigReverseLimitSwitchSource(m_handle, type.value, normalOpenOrClose.value,
				deviceID, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configReverseLimitSwitchSource(RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID) {
		int timeoutMs = 0;
		return configReverseLimitSwitchSource(type, normalOpenOrClose, deviceID, timeoutMs);	
	}

	/**
	 * Configures a limit switch for a local/remote source.
	 *
	 * For example, a CAN motor controller may need to monitor the Limit-R pin
	 * of another Talon, CANifier, or local Gadgeteer feedback connector.
	 *
	 * If the sensor is remote, a device ID of zero is assumed. If that's not
	 * desired, use the four parameter version of this function.
	 *
	 * @param type
	 *            Limit switch source. @see #LimitSwitchSource User can choose
	 *            between the feedback connector, remote Talon SRX, CANifier, or
	 *            deactivate the feature.
	 * @param normalOpenOrClose
	 *            Setting for normally open, normally closed, or disabled. This
	 *            setting matches the web-based configuration drop down.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configForwardLimitSwitchSource(LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int timeoutMs) {
		return configForwardLimitSwitchSource(type.value, normalOpenOrClose.value, 0x00000000, timeoutMs);
	}
	public ErrorCode configForwardLimitSwitchSource(LimitSwitchSource type, LimitSwitchNormal normalOpenOrClose) {
		int timeoutMs = 0;
		return configForwardLimitSwitchSource(type, normalOpenOrClose, timeoutMs);
	}

	protected ErrorCode configForwardLimitSwitchSource(int typeValue, int normalOpenOrCloseValue, int deviceID,
			int timeoutMs) {
		int retval = MotControllerJNI.ConfigForwardLimitSwitchSource(m_handle, typeValue, normalOpenOrCloseValue,
				deviceID, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Configures a limit switch for a local/remote source.
	 *
	 * For example, a CAN motor controller may need to monitor the Limit-R pin
	 * of another Talon, CANifier, or local Gadgeteer feedback connector.
	 *
	 * If the sensor is remote, a device ID of zero is assumed. If that's not
	 * desired, use the four parameter version of this function.
	 *
	 * @param typeValue
	 *            Limit switch source. @see #LimitSwitchSource User can choose
	 *            between the feedback connector, remote Talon SRX, CANifier, or
	 *            deactivate the feature.
	 * @param normalOpenOrCloseValue
	 *            Setting for normally open, normally closed, or disabled. This
	 *            setting matches the web-based configuration drop down.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	protected ErrorCode configReverseLimitSwitchSource(int typeValue, int normalOpenOrCloseValue, int deviceID,
			int timeoutMs) {
		int retval = MotControllerJNI.ConfigReverseLimitSwitchSource(m_handle, typeValue, normalOpenOrCloseValue,
				deviceID, timeoutMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Sets the enable state for limit switches.
	 *
	 * @param enable
	 *            Enable state for limit switches.
	 **/
	public void overrideLimitSwitchesEnable(boolean enable) {
		MotControllerJNI.OverrideLimitSwitchesEnable(m_handle, enable);
	}

	// ------ soft limit ----------//
	/**
	 * Configures the forward soft limit threhold.
	 *
	 * @param forwardSensorLimit
	 *            Forward Sensor Position Limit (in raw sensor units).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configForwardSoftLimitThreshold(int forwardSensorLimit, int timeoutMs) {
		int retval = MotControllerJNI.ConfigForwardSoftLimitThreshold(m_handle, forwardSensorLimit, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configForwardSoftLimitThreshold(int forwardSensorLimit) {
		int timeoutMs = 0;
		return configForwardSoftLimitThreshold(forwardSensorLimit, timeoutMs);	
	}

	/**
	 * Configures the reverse soft limit threshold.
	 *
	 * @param reverseSensorLimit
	 *            Reverse Sensor Position Limit (in raw sensor units).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configReverseSoftLimitThreshold(int reverseSensorLimit, int timeoutMs) {
		int retval = MotControllerJNI.ConfigReverseSoftLimitThreshold(m_handle, reverseSensorLimit, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configReverseSoftLimitThreshold(int reverseSensorLimit) {
		int timeoutMs = 0;
		return configReverseSoftLimitThreshold(reverseSensorLimit, timeoutMs);	
	}

	/**
	 * Configures the forward soft limit enable.
	 *
	 * @param enable
	 *            Forward Sensor Position Limit Enable.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configForwardSoftLimitEnable(boolean enable, int timeoutMs) {
		int retval = MotControllerJNI.ConfigForwardSoftLimitEnable(m_handle, enable, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configForwardSoftLimitEnable(boolean enable) {
		int timeoutMs = 0;
		return configForwardSoftLimitEnable(enable, timeoutMs);	
	}

	/**
	 * Configures the reverse soft limit enable.
	 *
	 * @param enable
	 *            Reverse Sensor Position Limit Enable.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configReverseSoftLimitEnable(boolean enable, int timeoutMs) {
		int retval = MotControllerJNI.ConfigReverseSoftLimitEnable(m_handle, enable, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configReverseSoftLimitEnable(boolean enable) {
		int timeoutMs = 0;
		return configReverseSoftLimitEnable(enable, timeoutMs);
	}

	/**
	 * Can be used to override-disable the soft limits.
	 * This function can be used to quickly disable soft limits without
	 * having to modify the persistent configuration.
	 *
	 * @param enable
	 *            Enable state for soft limit switches.
	 */
	public void overrideSoftLimitsEnable(boolean enable) {
		MotControllerJNI.OverrideSoftLimitsEnable(m_handle, enable);
	}

	// ------ Current Lim ----------//
	/* not available in base */

	// ------ General Close loop ----------//
	/**
	 * Sets the 'P' constant in the given parameter slot.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param value
	 *            Value of the P constant.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode config_kP(int slotIdx, double value, int timeoutMs) {
		int retval = MotControllerJNI.Config_kP(m_handle, slotIdx,  value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode config_kP(int slotIdx, double value) {
		int timeoutMs = 0;
		return config_kP( slotIdx,  value,  timeoutMs);	
	}

	/**
	 * Sets the 'I' constant in the given parameter slot.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param value
	 *            Value of the I constant.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode config_kI(int slotIdx, double value, int timeoutMs) {
		int retval = MotControllerJNI.Config_kI(m_handle, slotIdx,  value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode config_kI(int slotIdx, double value) {
        int timeoutMs = 0;

		return config_kI( slotIdx,  value,  timeoutMs);
	}

	/**
	 * Sets the 'D' constant in the given parameter slot.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param value
	 *            Value of the D constant.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode config_kD(int slotIdx, double value, int timeoutMs) {
		int retval = MotControllerJNI.Config_kD(m_handle, slotIdx,  value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode config_kD(int slotIdx, double value) {
        int timeoutMs = 0;
		return config_kD( slotIdx,  value,  timeoutMs);
	}

	/**
	 * Sets the 'F' constant in the given parameter slot.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param value
	 *            Value of the F constant.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode config_kF(int slotIdx, double value, int timeoutMs) {
		int retval = MotControllerJNI.Config_kF(m_handle, slotIdx,  value, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode config_kF(int slotIdx,  double value) {
        int timeoutMs = 0;
		return config_kF( slotIdx,  value,  timeoutMs);	
	}

	/**
	 * Sets the Integral Zone constant in the given parameter slot. If the
	 * (absolute) closed-loop error is outside of this zone, integral
	 * accumulator is automatically cleared. This ensures than integral wind up
	 * events will stop after the sensor gets far enough from its target.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param izone
	 *            Value of the Integral Zone constant (closed loop error units X
	 *            1ms).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode config_IntegralZone(int slotIdx, int izone, int timeoutMs) {
		int retval = MotControllerJNI.Config_IntegralZone(m_handle, slotIdx,  izone, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode config_IntegralZone(int slotIdx, int izone) {
        int timeoutMs = 0;
		return config_IntegralZone( slotIdx,  izone,  timeoutMs);
	}

	/**
	 * Sets the allowable closed-loop error in the given parameter slot.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param allowableClosedLoopError
	 *            Value of the allowable closed-loop error.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configAllowableClosedloopError(int slotIdx, int allowableClosedLoopError, int timeoutMs) {
		int retval = MotControllerJNI.ConfigAllowableClosedloopError(m_handle, slotIdx, allowableClosedLoopError,
				timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configAllowableClosedloopError(int slotIdx, int allowableClosedLoopError) {
        int timeoutMs = 0;
	
		return configAllowableClosedloopError( slotIdx,  allowableClosedLoopError,  timeoutMs);
	}

	/**
	 * Sets the maximum integral accumulator in the given parameter slot.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param iaccum
	 *            Value of the maximum integral accumulator (closed loop error
	 *            units X 1ms).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configMaxIntegralAccumulator(int slotIdx, double iaccum, int timeoutMs) {
		int retval = MotControllerJNI.ConfigMaxIntegralAccumulator(m_handle, slotIdx, iaccum, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configMaxIntegralAccumulator(int slotIdx, double iaccum) {
        int timeoutMs = 0;
		return configMaxIntegralAccumulator( slotIdx,  iaccum,  timeoutMs);	
	}

	/**
	 * Sets the peak closed-loop output.  This peak output is slot-specific and
	 *   is applied to the output of the associated PID loop.
	 * This setting is seperate from the generic Peak Output setting.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param percentOut
	 *            Peak Percent Output from 0 to 1.  This value is absolute and
	 *						the magnitude will apply in both forward and reverse directions.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configClosedLoopPeakOutput(int slotIdx, double percentOut, int timeoutMs) {
		int retval = MotControllerJNI.ConfigClosedLoopPeakOutput(m_handle, slotIdx, percentOut, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configClosedLoopPeakOutput(int slotIdx, double percentOut) {
        int timeoutMs = 0;

		return configClosedLoopPeakOutput( slotIdx,  percentOut,  timeoutMs);
	}

	/**
	 * Sets the loop time (in milliseconds) of the PID closed-loop calculations.
	 * Default value is 1 ms.
	 *
	 * @param slotIdx
	 *            Parameter slot for the constant.
	 * @param loopTimeMs
	 *            Loop timing of the closed-loop calculations.  Minimum value of
	 *						1 ms, maximum of 64 ms.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
  	public ErrorCode configClosedLoopPeriod(int slotIdx, int loopTimeMs, int timeoutMs) {
		int retval = MotControllerJNI.ConfigClosedLoopPeriod(m_handle, slotIdx, loopTimeMs, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
  	public ErrorCode configClosedLoopPeriod(int slotIdx, int loopTimeMs) {
        int timeoutMs = 0;
		return configClosedLoopPeriod( slotIdx,  loopTimeMs,  timeoutMs);
	}

	/**
	 * Configures the Polarity of the Auxiliary PID (PID1).
	 *
	 * Standard Polarity:
	 *    Primary Output = PID0 + PID1
	 *    Auxiliary Output = PID0 - PID1
	 *
	 * Inverted Polarity:
	 *    Primary Output = PID0 - PID1
	 *    Auxiliary Output = PID0 + PID1
	 *
	 * @param invert
	 *            If true, use inverted PID1 output polarity.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code
	 */
	public ErrorCode configAuxPIDPolarity(boolean invert, int timeoutMs){
		return configSetParameter(ParamEnum.ePIDLoopPolarity, invert ? 1:0, 0, 1, timeoutMs);
	}
	public ErrorCode configAuxPIDPolarity(boolean invert){
		int timeoutMs = 0;
		return configAuxPIDPolarity(invert,  timeoutMs);
	}

	/**
	 * Sets the integral accumulator. Typically this is used to clear/zero the
	 * integral accumulator, however some use cases may require seeding the
	 * accumulator for a faster response.
	 *
	 * @param iaccum
	 *            Value to set for the integral accumulator (closed loop error
	 *            units X 1ms).
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode setIntegralAccumulator(double iaccum, int pidIdx, int timeoutMs) {
		int retval = MotControllerJNI.SetIntegralAccumulator(m_handle,  iaccum, pidIdx, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode setIntegralAccumulator(double iaccum) {
		int pidIdx = 0;
		int timeoutMs = 0;
		return setIntegralAccumulator( iaccum,  pidIdx,  timeoutMs);
	}

	/**
	 * Gets the closed-loop error. The units depend on which control mode is in
	 * use. See Phoenix-Documentation information on units.
	 *
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @return Closed-loop error value.
	 */
	public int getClosedLoopError(int pidIdx) {
		return MotControllerJNI.GetClosedLoopError(m_handle, pidIdx);
	}
	public int getClosedLoopError() {
		int pidIdx = 0;
		return getClosedLoopError( pidIdx);
	}

	/**
	 * Gets the iaccum value.
	 *
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @return Integral accumulator value (Closed-loop error X 1ms).
	 */
	public double getIntegralAccumulator(int pidIdx) {
		return MotControllerJNI.GetIntegralAccumulator(m_handle, pidIdx);
	}
	public double getIntegralAccumulator() {
		int pidIdx = 0;
		return getIntegralAccumulator(pidIdx);
	}


	/**
	 * Gets the derivative of the closed-loop error.
	 *
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @return The error derivative value.
	 */
	public double getErrorDerivative(int pidIdx) {
		return MotControllerJNI.GetErrorDerivative(m_handle, pidIdx);
	}
	public double getErrorDerivative() {
		int pidIdx = 0;

		return getErrorDerivative(pidIdx);
	}	

	/**
	 * Selects which profile slot to use for closed-loop control.
	 *
	 * @param slotIdx
	 *            Profile slot to select.
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 **/
	public void selectProfileSlot(int slotIdx, int pidIdx) {
		MotControllerJNI.SelectProfileSlot(m_handle, slotIdx, pidIdx);
	}

	/**
	 * Gets the current target of a given closed loop.
	 *
	 * @param pidIdx
	 *            0 for Primary closed-loop. 1 for auxiliary closed-loop.
	 * @return The closed loop target.
	 */
	public int getClosedLoopTarget(int pidIdx) {
		return MotControllerJNI.GetClosedLoopTarget(m_handle, pidIdx);
	}
	public int getClosedLoopTarget() {
		int pidIdx = 0;
		return getClosedLoopTarget(pidIdx);
	}

	/**
	 * Gets the active trajectory target position using
	 * MotionMagic/MotionProfile control modes.
	 *
	 * @return The Active Trajectory Position in sensor units.
	 */
	public int getActiveTrajectoryPosition() {
		return MotControllerJNI.GetActiveTrajectoryPosition(m_handle);
	}

	/**
	 * Gets the active trajectory target velocity using
	 * MotionMagic/MotionProfile control modes.
	 *
	 * @return The Active Trajectory Velocity in sensor units per 100ms.
	 */
	public int getActiveTrajectoryVelocity() {
		return MotControllerJNI.GetActiveTrajectoryVelocity(m_handle);
	}

	/**
	 * Gets the active trajectory target heading using
	 * MotionMagicArc/MotionProfileArc control modes.
	 *
	 * @return The Active Trajectory Heading in degreees.
	 */
	public double getActiveTrajectoryHeading() {
		return MotControllerJNI.GetActiveTrajectoryHeading(m_handle);
	}

	// ------ Motion Profile Settings used in Motion Magic and Motion Profile ----------//

	/**
	 * Sets the Motion Magic Cruise Velocity. This is the peak target velocity
	 * that the motion magic curve generator can use.
	 *
	 * @param sensorUnitsPer100ms
	 *            Motion Magic Cruise Velocity (in raw sensor units per 100 ms).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configMotionCruiseVelocity(int sensorUnitsPer100ms, int timeoutMs) {
		int retval = MotControllerJNI.ConfigMotionCruiseVelocity(m_handle, sensorUnitsPer100ms, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configMotionCruiseVelocity(int sensorUnitsPer100ms) {
		int timeoutMs = 0;
		return configMotionCruiseVelocity( sensorUnitsPer100ms,  timeoutMs);	
	}

	/**
	 * Sets the Motion Magic Acceleration. This is the target acceleration that
	 * the motion magic curve generator can use.
	 *
	 * @param sensorUnitsPer100msPerSec
	 *            Motion Magic Acceleration (in raw sensor units per 100 ms per
	 *            second).
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configMotionAcceleration(int sensorUnitsPer100msPerSec, int timeoutMs) {
		int retval = MotControllerJNI.ConfigMotionAcceleration(m_handle, sensorUnitsPer100msPerSec, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configMotionAcceleration(int sensorUnitsPer100msPerSec) {
		int timeoutMs = 0;
		return configMotionAcceleration( sensorUnitsPer100msPerSec,  timeoutMs);
	}

	//------ Motion Profile Buffer ----------//
	/**
	 * Clear the buffered motion profile in both controller's RAM (bottom), and in the
	 * API (top).
	 */
	public ErrorCode clearMotionProfileTrajectories() {
		int retval = MotControllerJNI.ClearMotionProfileTrajectories(m_handle);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Retrieve just the buffer count for the api-level (top) buffer. This
	 * routine performs no CAN or data structure lookups, so its fast and ideal
	 * if caller needs to quickly poll the progress of trajectory points being
	 * emptied into controller's RAM. Otherwise just use GetMotionProfileStatus.
	 *
	 * @return number of trajectory points in the top buffer.
	 */
	public int getMotionProfileTopLevelBufferCount() {
		return MotControllerJNI.GetMotionProfileTopLevelBufferCount(m_handle);
	}
	/**
	 * Push another trajectory point into the top level buffer (which is emptied
	 * into the motor controller's bottom buffer as room allows).
	 * @param trajPt to push into buffer.
	 * The members should be filled in with these values...
	 *
	 * 		targPos:  servo position in sensor units.
	 *		targVel:  velocity to feed-forward in sensor units
	 *                 per 100ms.
	 * 		profileSlotSelect0  Which slot to get PIDF gains. PID is used for position servo. F is used
	 *						   as the Kv constant for velocity feed-forward. Typically this is hardcoded
	 *						   to the a particular slot, but you are free gain schedule if need be.
	 *						   Choose from [0,3]
	 *		profileSlotSelect1 Which slot to get PIDF gains for auxiliary PId.
	 *						   This only has impact during MotionProfileArc Control mode.
	 *						   Choose from [0,1].
	 * 	   isLastPoint  set to nonzero to signal motor controller to keep processing this
	 *                     trajectory point, instead of jumping to the next one
	 *                     when timeDurMs expires.  Otherwise MP executer will
	 *                     eventually see an empty buffer after the last point
	 *                     expires, causing it to assert the IsUnderRun flag.
	 *                     However this may be desired if calling application
	 *                     never wants to terminate the MP.
	 *		zeroPos  set to nonzero to signal motor controller to "zero" the selected
	 *                 position sensor before executing this trajectory point.
	 *                 Typically the first point should have this set only thus
	 *                 allowing the remainder of the MP positions to be relative to
	 *                 zero.
	 *		timeDur Duration to apply this trajectory pt.
	 * 				This time unit is ADDED to the exising base time set by
	 * 				configMotionProfileTrajectoryPeriod().
	 * @return CTR_OKAY if trajectory point push ok. ErrorCode if buffer is
	 *         full due to kMotionProfileTopBufferCapacity.
	 */
	public ErrorCode pushMotionProfileTrajectory(TrajectoryPoint trajPt) {
		int retval = MotControllerJNI.PushMotionProfileTrajectory2(m_handle,
				trajPt.position, trajPt.velocity, trajPt.auxiliaryPos,
				trajPt.profileSlotSelect0, trajPt.profileSlotSelect1,
				trajPt.isLastPoint, trajPt.zeroPos, trajPt.timeDur.value);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Retrieve just the buffer full for the api-level (top) buffer. This
	 * routine performs no CAN or data structure lookups, so its fast and ideal
	 * if caller needs to quickly poll. Otherwise just use
	 * GetMotionProfileStatus.
	 *
	 * @return number of trajectory points in the top buffer.
	 */
	public boolean isMotionProfileTopLevelBufferFull() {
		return MotControllerJNI.IsMotionProfileTopLevelBufferFull(m_handle);
	}

	/**
	 * This must be called periodically to funnel the trajectory points from the
	 * API's top level buffer to the controller's bottom level buffer. Recommendation
	 * is to call this twice as fast as the execution rate of the motion
	 * profile. So if MP is running with 20ms trajectory points, try calling
	 * this routine every 10ms. All motion profile functions are thread-safe
	 * through the use of a mutex, so there is no harm in having the caller
	 * utilize threading.
	 */
	public void processMotionProfileBuffer() {
		MotControllerJNI.ProcessMotionProfileBuffer(m_handle);
	}
	/**
	 * Retrieve all status information.
	 * For best performance, Caller can snapshot all status information regarding the
	 * motion profile executer.
	 *
	 * @param statusToFill  Caller supplied object to fill.
	 *
	 * The members are filled, as follows...
	 *
	 *	topBufferRem:	The available empty slots in the trajectory buffer.
	 * 	 				The robot API holds a "top buffer" of trajectory points, so your applicaion
	 * 	 				can dump several points at once.  The API will then stream them into the
	 * 	 		 		low-level buffer, allowing the motor controller to act on them.
	 *
	 *	topBufferRem: The number of points in the top trajectory buffer.
	 *
	 *	btmBufferCnt: The number of points in the low level controller buffer.
	 *
	 *	hasUnderrun: 	Set if isUnderrun ever gets set.
	 * 	 	 	 	 	Only is cleared by clearMotionProfileHasUnderrun() to ensure
	 *
	 *	isUnderrun:		This is set if controller needs to shift a point from its buffer into
	 *					the active trajectory point however
	 *					the buffer is empty.
	 *					This gets cleared automatically when is resolved.
	 *
	 *	activePointValid:	True if the active trajectory point has not empty, false otherwise. The members in activePoint are only valid if this signal is set.
	 *
	 *	isLast:	is set/cleared based on the MP executer's current
	 *                trajectory point's IsLast value.  This assumes
	 *                IsLast was set when PushMotionProfileTrajectory
	 *                was used to insert the currently processed trajectory
	 *                point.
	 *
	 *	profileSlotSelect: The currently processed trajectory point's
	 *      			  selected slot.  This can differ in the currently selected slot used
	 *       				 for Position and Velocity servo modes
	 *
	 *	outputEnable:		The current output mode of the motion profile
	 *						executer (disabled, enabled, or hold).  When changing the set()
	 *						value in MP mode, it's important to check this signal to
	 *						confirm the change takes effect before interacting with the top buffer.
	 */
	public ErrorCode getMotionProfileStatus(MotionProfileStatus statusToFill) {
		int retval = MotControllerJNI.GetMotionProfileStatus2(m_handle, _motionProfStats);
		statusToFill.topBufferRem = _motionProfStats[0];
		statusToFill.topBufferCnt = _motionProfStats[1];
		statusToFill.btmBufferCnt = _motionProfStats[2];
		statusToFill.hasUnderrun = _motionProfStats[3] != 0;
		statusToFill.isUnderrun = _motionProfStats[4] != 0;
		statusToFill.activePointValid = _motionProfStats[5] != 0;
		statusToFill.isLast = _motionProfStats[6] != 0;
		statusToFill.profileSlotSelect = _motionProfStats[7];
		statusToFill.outputEnable = SetValueMotionProfile.valueOf(_motionProfStats[8]);
		statusToFill.timeDurMs = _motionProfStats[9];
		statusToFill.profileSlotSelect1 = _motionProfStats[10];
		return ErrorCode.valueOf(retval);
	}

	/**
	 * Clear the "Has Underrun" flag. Typically this is called after application
	 * has confirmed an underrun had occured.
	 *
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode clearMotionProfileHasUnderrun(int timeoutMs) {
		int retval = MotControllerJNI.ClearMotionProfileHasUnderrun(m_handle, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode clearMotionProfileHasUnderrun() {
		int timeoutMs = 0;
		return clearMotionProfileHasUnderrun(timeoutMs);
	}

	/**
	 * Calling application can opt to speed up the handshaking between the robot
	 * API and the controller to increase the download rate of the controller's Motion
	 * Profile. Ideally the period should be no more than half the period of a
	 * trajectory point.
	 *
	 * @param periodMs
	 *            The transmit period in ms.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode changeMotionControlFramePeriod(int periodMs) {
		int retval = MotControllerJNI.ChangeMotionControlFramePeriod(m_handle, periodMs);
		return ErrorCode.valueOf(retval);
	}

	/**
	 * When trajectory points are processed in the motion profile executer, the MPE determines
	 * how long to apply the active trajectory point by summing baseTrajDurationMs with the
	 * timeDur of the trajectory point (see TrajectoryPoint).
	 *
	 * This allows general selection of the execution rate of the points with 1ms resolution,
	 * while allowing some degree of change from point to point.
	 * @param baseTrajDurationMs The base duration time of every trajectory point.
	 * 							This is summed with the trajectory points unique timeDur.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configMotionProfileTrajectoryPeriod(int baseTrajDurationMs, int timeoutMs) {
		int retval = MotControllerJNI.ConfigMotionProfileTrajectoryPeriod(m_handle, baseTrajDurationMs, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configMotionProfileTrajectoryPeriod(int baseTrajDurationMs) {
		int timeoutMs = 0;
		return configMotionProfileTrajectoryPeriod( baseTrajDurationMs,  timeoutMs);
	}

    //------Feedback Device Interaction Settings---------//
    
    /**
     * Disables wrapping the position. If the signal goes from 1023 to 0 a motor 
     * controller will by default go to 1024. If wrapping the position is disabled,
     * it will go to 0;
     *
     * @param feedbackNotContinuous     disable wrapping the position. 
     *
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configFeedbackNotContinuous(boolean feedbackNotContinuous, int timeoutMs) {
        int retval = MotControllerJNI.ConfigFeedbackNotContinuous(m_handle, feedbackNotContinuous, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    
    /**
     * Disables going to neutral (brake/coast) when a remote sensor is no longer detected.
     *
     * @param remoteSensorClosedLoopDisableNeutralOnLOS     disable going to neutral 
     *
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configRemoteSensorClosedLoopDisableNeutralOnLOS(boolean remoteSensorClosedLoopDisableNeutralOnLOS, int timeoutMs) {
        int retval = MotControllerJNI.ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(m_handle, remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    /**
     * Enables clearing the position of the feedback sensor when the forward 
     * limit switch is triggered
     *
     * @param clearPositionOnLimitF     Whether clearing is enabled, defaults false
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configClearPositionOnLimitF(boolean clearPositionOnLimitF, int timeoutMs) {
        int retval = MotControllerJNI.ConfigClearPositionOnLimitF(m_handle, clearPositionOnLimitF, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    
    /**
     * Enables clearing the position of the feedback sensor when the reverse 
     * limit switch is triggered
     *
     * @param clearPositionOnLimitR     Whether clearing is enabled, defaults false
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configClearPositionOnLimitR(boolean clearPositionOnLimitR, int timeoutMs) {
        int retval = MotControllerJNI.ConfigClearPositionOnLimitR(m_handle, clearPositionOnLimitR, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    
    /**
     * Enables clearing the position of the feedback sensor when the quadrature index signal
     * is detected
     *
     * @param clearPositionOnQuadIdx    Whether clearing is enabled, defaults false
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configClearPositionOnQuadIdx(boolean clearPositionOnQuadIdx, int timeoutMs) {
        int retval = MotControllerJNI.ConfigClearPositionOnQuadIdx(m_handle, clearPositionOnQuadIdx, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    
    /**
     * Disables limit switches triggering (if enabled) when the sensor is no longer detected.
     *
     * @param limitSwitchDisableNeutralOnLOS    disable triggering
     *
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configLimitSwitchDisableNeutralOnLOS(boolean limitSwitchDisableNeutralOnLOS, int timeoutMs) {
        int retval = MotControllerJNI.ConfigLimitSwitchDisableNeutralOnLOS(m_handle, limitSwitchDisableNeutralOnLOS, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    
    /**
     * Disables soft limits triggering (if enabled) when the sensor is no longer detected.
     *
     * @param softLimitDisableNeutralOnLOS    disable triggering
     *
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configSoftLimitDisableNeutralOnLOS(boolean softLimitDisableNeutralOnLOS, int timeoutMs) {
        int retval = MotControllerJNI.ConfigSoftLimitDisableNeutralOnLOS(m_handle, softLimitDisableNeutralOnLOS, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    
    /**
     * Sets the edges per rotation of a pulse width sensor. (This should be set for 
     * tachometer use).
     *
     * @param pulseWidthPeriod_EdgesPerRot    edges per rotation
     *
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configPulseWidthPeriod_EdgesPerRot(int pulseWidthPeriod_EdgesPerRot, int timeoutMs) {
        int retval = MotControllerJNI.ConfigPulseWidthPeriod_EdgesPerRot(m_handle, pulseWidthPeriod_EdgesPerRot, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
    
    /**
     * Sets the number of samples to use in smoothing a pulse width sensor with a rolling 
     * average. Default is 1 (no smoothing).
     *
     * @param pulseWidthPeriod_FilterWindowSz   samples for rolling avg
     *
     * @param timeoutMs
     *            Timeout value in ms. If nonzero, function will wait for
     *            config success and report an error if it times out.
     *            If zero, no blocking or checking is performed.
     * @return Error Code generated by function. 0 indicates no error.
     */
    public ErrorCode configPulseWidthPeriod_FilterWindowSz(int pulseWidthPeriod_FilterWindowSz, int timeoutMs) {
        int retval = MotControllerJNI.ConfigPulseWidthPeriod_FilterWindowSz(m_handle, pulseWidthPeriod_FilterWindowSz, timeoutMs);
        return ErrorCode.valueOf(retval);
    }
	// ------ error ----------//
	/**
	 * Gets the last error generated by this object. Not all functions return an
	 * error code but can potentially report errors. This function can be used
	 * to retrieve those error codes.
	 *
	 * @return Last Error Code generated by a function.
	 */
	public ErrorCode getLastError() {
		int retval = MotControllerJNI.GetLastError(m_handle);
		return ErrorCode.valueOf(retval);
	}

	// ------ Faults ----------//
	/**
	 * Polls the various fault flags.
	 *
	 * @param toFill
	 *            Caller's object to fill with latest fault flags.
	 * @return Last Error Code generated by a function.
	 */
	public ErrorCode getFaults(Faults toFill) {
		int bits = MotControllerJNI.GetFaults(m_handle);
		toFill.update(bits);
		return getLastError();
	}

	/**
	 * Polls the various sticky fault flags.
	 *
	 * @param toFill
	 *            Caller's object to fill with latest sticky fault flags.
	 * @return Last Error Code generated by a function.
	 */
	public ErrorCode getStickyFaults(StickyFaults toFill) {
		int bits = MotControllerJNI.GetStickyFaults(m_handle);
		toFill.update(bits);
		return getLastError();
	}

	/**
	 * Clears all sticky faults.
	 *
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Last Error Code generated by a function.
	 */
	public ErrorCode clearStickyFaults(int timeoutMs) {
		int retval = MotControllerJNI.ClearStickyFaults(m_handle, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode clearStickyFaults() {
		int timeoutMs = 0;
		return clearStickyFaults(timeoutMs);
	}

	// ------ Firmware ----------//
	/**
	 * Gets the firmware version of the device.
	 *
	 * @return Firmware version of device. For example: version 1-dot-2 is
	 *         0x0102.
	 */
	public int getFirmwareVersion() {
		return MotControllerJNI.GetFirmwareVersion(m_handle);
	}

	/**
	 * Returns true if the device has reset since last call.
	 *
	 * @return Has a Device Reset Occurred?
	 */
	public boolean hasResetOccurred() {
		return MotControllerJNI.HasResetOccurred(m_handle);
	}

	//------ Custom Persistent Params ----------//
	/**
	 * Sets the value of a custom parameter. This is for arbitrary use.
	 *
	 * Sometimes it is necessary to save calibration/limit/target information in
	 * the device. Particularly if the device is part of a subsystem that can be
	 * replaced.
	 *
	 * @param newValue
	 *            Value for custom parameter.
	 * @param paramIndex
	 *            Index of custom parameter [0,1]
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetCustomParam(int newValue, int paramIndex, int timeoutMs) {
		int retval = MotControllerJNI.ConfigSetCustomParam(m_handle, newValue, paramIndex, timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configSetCustomParam(int newValue, int paramIndex) {
		int timeoutMs = 0;
		return configSetCustomParam( newValue,  paramIndex,  timeoutMs);
	}

	/**
	 * Gets the value of a custom parameter.
	 *
	 * @param paramIndex
	 *            Index of custom parameter [0,1].
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Value of the custom param.
	 */
	public int configGetCustomParam(int paramIndex, int timeoutMs) {
		int retval = MotControllerJNI.ConfigGetCustomParam(m_handle, paramIndex, timeoutMs);
		return retval;
	}
	public int configGetCustomParam(int paramIndex) {
		int timeoutMs = 0;
		return configGetCustomParam( paramIndex,  timeoutMs);
	}

	// ------ Generic Param API ----------//
	/**
	 * Sets a parameter. Generally this is not used. This can be utilized in -
	 * Using new features without updating API installation. - Errata
	 * workarounds to circumvent API implementation. - Allows for rapid testing
	 * / unit testing of firmware.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param value
	 *            Value of parameter.
	 * @param subValue
	 *            Subvalue for parameter. Maximum value of 255.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for config
	 *            success and report an error if it times out. If zero, no
	 *            blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetParameter(ParamEnum param, double value, int subValue, int ordinal, int timeoutMs) {
		return configSetParameter(param.value, value, subValue, ordinal, timeoutMs);
	}
	public ErrorCode configSetParameter(ParamEnum param, double value, int subValue, int ordinal) {
		int timeoutMs = 0;
		return configSetParameter(param, value,  subValue,  ordinal,  timeoutMs);
	}
	/**
	 * Sets a parameter.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param value
	 *            Value of parameter.
	 * @param subValue
	 *            Subvalue for parameter. Maximum value of 255.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Error Code generated by function. 0 indicates no error.
	 */
	public ErrorCode configSetParameter(int param, double value, int subValue, int ordinal, int timeoutMs) {
		int retval = MotControllerJNI.ConfigSetParameter(m_handle, param,  value, subValue, ordinal,
				timeoutMs);
		return ErrorCode.valueOf(retval);
	}
	public ErrorCode configSetParameter(int param, double value, int subValue, int ordinal) {
		int timeoutMs = 0;
		return configSetParameter( param,  value,  subValue,  ordinal,  timeoutMs);
	}
	/**
	 * Gets a parameter.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Value of parameter.
	 */
	public double configGetParameter(ParamEnum param, int ordinal, int timeoutMs) {
		return configGetParameter(param.value, ordinal, timeoutMs);
	}
	public double configGetParameter(ParamEnum param, int ordinal) {
		int timeoutMs = 0;
		return configGetParameter(param, ordinal, timeoutMs);
	}
	/**
	 * Gets a parameter.
	 *
	 * @param param
	 *            Parameter enumeration.
	 * @param ordinal
	 *            Ordinal of parameter.
	 * @param timeoutMs
	 *            Timeout value in ms. If nonzero, function will wait for
	 *            config success and report an error if it times out.
	 *            If zero, no blocking or checking is performed.
	 * @return Value of parameter.
	 */
	public double configGetParameter(int param, int ordinal, int timeoutMs) {
		return MotControllerJNI.ConfigGetParameter(m_handle, param, ordinal, timeoutMs);
	}
	public double configGetParameter(int param, int ordinal) {
		int timeoutMs = 0;
		return configGetParameter( param,  ordinal,  timeoutMs);	
	}

	// ------ Misc. ----------//
	public int getBaseID() {
		return _arbId;
	}

	/**
	 * @return control mode motor controller is in
	 */
	public ControlMode getControlMode() {
		return m_controlMode;
	}

	// ----- Follower ------//
	/**
	 * Set the control mode and output value so that this motor controller will
	 * follow another motor controller. Currently supports following Victor SPX
	 * and Talon SRX.
	 *
	 * @param masterToFollow
	 *						Motor Controller object to follow.
	 * @param followerType
	 *						Type of following control.  Use AuxOutput1 to follow the master
	 *						device's auxiliary output 1.
	 *						Use PercentOutput for standard follower mode.
	 */
	public void follow(IMotorController masterToFollow, FollowerType followerType) {
		int id32 = masterToFollow.getBaseID();
		int id24 = id32;
		id24 >>= 16;
		id24 = (short) id24;
		id24 <<= 8;
		id24 |= (id32 & 0xFF);
		set(ControlMode.Follower, id24);

		switch (followerType){
			case PercentOutput:
				set(ControlMode.Follower, (double)id24);
				break;
			case AuxOutput1:
			  /* follow the motor controller, but set the aux flag
		     * to ensure we follow the processed output */
			  set(ControlMode.Follower, (double)id24, DemandType.AuxPID, 0);
				break;
			default:
			  neutralOutput();
				break;
		}
	}
	/**
	 * Set the control mode and output value so that this motor controller will
	 * follow another motor controller. Currently supports following Victor SPX
	 * and Talon SRX.
	 */
	public void follow(IMotorController masterToFollow) {
    follow(masterToFollow, FollowerType.PercentOutput);
	}
	/**
	 * When master makes a device, this routine is called to signal the update.
	 */
	public void valueUpdated() {
		// MT
	}

    //------Config All------//

    /**
     * Configures all base persistant settings.
     *
	 * @param allConfigs        Object with all of the base persistant settings
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
    protected ErrorCode baseConfigAllSettings(BaseMotorControllerConfiguration allConfigs, int timeoutMs) {
        
    
        ErrorCollection errorCollection = new ErrorCollection();
    
        errorCollection.NewError(configFactoryDefault(timeoutMs));
		
		// https://docs.google.com/spreadsheets/d/1mU-WOaCnMYSTGq7mqHnahamwzSpflqNpogikiyQMGl8/edit?usp=sharing
        if(BaseMotorControllerUtil.openloopRampDifferent(allConfigs)) errorCollection.NewError(configOpenloopRamp(allConfigs.openloopRamp, timeoutMs));
		if(BaseMotorControllerUtil.closedloopRampDifferent(allConfigs)) errorCollection.NewError(configClosedloopRamp(allConfigs.closedloopRamp, timeoutMs));
		if(BaseMotorControllerUtil.peakOutputForwardDifferent(allConfigs)) errorCollection.NewError(configPeakOutputForward(allConfigs.peakOutputForward, timeoutMs));
		if(BaseMotorControllerUtil.peakOutputReverseDifferent(allConfigs)) errorCollection.NewError(configPeakOutputReverse(allConfigs.peakOutputReverse, timeoutMs));
		if(BaseMotorControllerUtil.nominalOutputForwardDifferent(allConfigs)) errorCollection.NewError(configNominalOutputForward(allConfigs.nominalOutputForward, timeoutMs));
		if(BaseMotorControllerUtil.nominalOutputReverseDifferent(allConfigs)) errorCollection.NewError(configNominalOutputReverse(allConfigs.nominalOutputReverse, timeoutMs));
		if(BaseMotorControllerUtil.neutralDeadbandDifferent(allConfigs)) errorCollection.NewError(configNeutralDeadband(allConfigs.neutralDeadband, timeoutMs));
		if(BaseMotorControllerUtil.voltageCompSaturationDifferent(allConfigs)) errorCollection.NewError(configVoltageCompSaturation(allConfigs.voltageCompSaturation, timeoutMs));
		if(BaseMotorControllerUtil.voltageMeasurementFilterDifferent(allConfigs)) errorCollection.NewError(configVoltageMeasurementFilter(allConfigs.voltageMeasurementFilter, timeoutMs));
		if(BaseMotorControllerUtil.velocityMeasurementPeriodDifferent(allConfigs)) errorCollection.NewError(configVelocityMeasurementPeriod(allConfigs.velocityMeasurementPeriod, timeoutMs));
		if(BaseMotorControllerUtil.velocityMeasurementWindowDifferent(allConfigs)) errorCollection.NewError(configVelocityMeasurementWindow(allConfigs.velocityMeasurementWindow, timeoutMs));
		if(BaseMotorControllerUtil.forwardSoftLimitThresholdDifferent(allConfigs)) errorCollection.NewError(configForwardSoftLimitThreshold(allConfigs.forwardSoftLimitThreshold, timeoutMs));
		if(BaseMotorControllerUtil.reverseSoftLimitThresholdDifferent(allConfigs)) errorCollection.NewError(configReverseSoftLimitThreshold(allConfigs.reverseSoftLimitThreshold, timeoutMs));
		if(BaseMotorControllerUtil.forwardSoftLimitEnableDifferent(allConfigs)) errorCollection.NewError(configForwardSoftLimitEnable(allConfigs.forwardSoftLimitEnable, timeoutMs));
		if(BaseMotorControllerUtil.reverseSoftLimitEnableDifferent(allConfigs)) errorCollection.NewError(configReverseSoftLimitEnable(allConfigs.reverseSoftLimitEnable, timeoutMs));
		if(BaseMotorControllerUtil.auxPIDPolarityDifferent(allConfigs)) errorCollection.NewError(configAuxPIDPolarity(allConfigs.auxPIDPolarity, timeoutMs));
		if(BaseMotorControllerUtil.motionCruiseVelocityDifferent(allConfigs)) errorCollection.NewError(configMotionCruiseVelocity(allConfigs.motionCruiseVelocity, timeoutMs));
		if(BaseMotorControllerUtil.motionAccelerationDifferent(allConfigs)) errorCollection.NewError(configMotionAcceleration(allConfigs.motionAcceleration, timeoutMs));
		if(BaseMotorControllerUtil.motionProfileTrajectoryPeriodDifferent(allConfigs)) errorCollection.NewError(configMotionProfileTrajectoryPeriod(allConfigs.motionProfileTrajectoryPeriod, timeoutMs));
		if(BaseMotorControllerUtil.feedbackNotContinuousDifferent(allConfigs)) errorCollection.NewError(configFeedbackNotContinuous(allConfigs.feedbackNotContinuous, timeoutMs));
		if(BaseMotorControllerUtil.remoteSensorClosedLoopDisableNeutralOnLOSDifferent(allConfigs)) errorCollection.NewError(configRemoteSensorClosedLoopDisableNeutralOnLOS(allConfigs.remoteSensorClosedLoopDisableNeutralOnLOS, timeoutMs));
		if(BaseMotorControllerUtil.clearPositionOnLimitFDifferent(allConfigs)) errorCollection.NewError(configClearPositionOnLimitF(allConfigs.clearPositionOnLimitF, timeoutMs));
		if(BaseMotorControllerUtil.clearPositionOnLimitRDifferent(allConfigs)) errorCollection.NewError(configClearPositionOnLimitR(allConfigs.clearPositionOnLimitR, timeoutMs));
		if(BaseMotorControllerUtil.clearPositionOnQuadIdxDifferent(allConfigs)) errorCollection.NewError(configClearPositionOnQuadIdx(allConfigs.clearPositionOnQuadIdx, timeoutMs));
		if(BaseMotorControllerUtil.limitSwitchDisableNeutralOnLOSDifferent(allConfigs)) errorCollection.NewError(configLimitSwitchDisableNeutralOnLOS(allConfigs.limitSwitchDisableNeutralOnLOS, timeoutMs));
		if(BaseMotorControllerUtil.softLimitDisableNeutralOnLOSDifferent(allConfigs)) errorCollection.NewError(configSoftLimitDisableNeutralOnLOS(allConfigs.softLimitDisableNeutralOnLOS, timeoutMs));
		if(BaseMotorControllerUtil.pulseWidthPeriod_EdgesPerRotDifferent(allConfigs)) errorCollection.NewError(configPulseWidthPeriod_EdgesPerRot(allConfigs.pulseWidthPeriod_EdgesPerRot, timeoutMs));
		if(BaseMotorControllerUtil.pulseWidthPeriod_FilterWindowSzDifferent(allConfigs)) errorCollection.NewError(configPulseWidthPeriod_FilterWindowSz(allConfigs.pulseWidthPeriod_FilterWindowSz, timeoutMs));
		
		//Custom Parameters
		if(BaseMotorControllerUtil.customParam0Different(allConfigs)) errorCollection.NewError(configSetCustomParam(allConfigs.customParam0, 0, timeoutMs));
		if(BaseMotorControllerUtil.customParam1Different(allConfigs)) errorCollection.NewError(configSetCustomParam(allConfigs.customParam1, 1, timeoutMs));

        //--------Slots---------------//
        errorCollection.NewError(configureSlot(allConfigs.slot0, 0, timeoutMs, allConfigs.enableOptimizations));
        errorCollection.NewError(configureSlot(allConfigs.slot1, 1, timeoutMs, allConfigs.enableOptimizations));
        errorCollection.NewError(configureSlot(allConfigs.slot2, 2, timeoutMs, allConfigs.enableOptimizations));
        errorCollection.NewError(configureSlot(allConfigs.slot3, 3, timeoutMs, allConfigs.enableOptimizations));
		
        //----------Remote Feedback Filters----------//
		errorCollection.NewError(configureFilter(allConfigs.remoteFilter0, 0, timeoutMs, allConfigs.enableOptimizations));
        errorCollection.NewError(configureFilter(allConfigs.remoteFilter1, 1, timeoutMs, allConfigs.enableOptimizations));
            
        return errorCollection._worstError;
    }



    
    /**
     * Configures all slot persistant settings.
     *
	 * @param slot        Object with all of the slot persistant settings
	 * @param slotIdx     Parameter slot for the constant.
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
    public ErrorCode configureSlot( SlotConfiguration slot, int slotIdx, int timeoutMs, boolean enableOptimization) {
    
        ErrorCollection errorCollection = new ErrorCollection();
        //------ General Close loop ----------//    
		
		
        
		if(SlotConfigurationUtil.kPDifferent(slot) || !enableOptimization) errorCollection.NewError(config_kP(slotIdx, slot.kP, timeoutMs));
		if(SlotConfigurationUtil.kIDifferent(slot) || !enableOptimization) errorCollection.NewError(config_kI(slotIdx, slot.kI, timeoutMs));
		if(SlotConfigurationUtil.kDDifferent(slot) || !enableOptimization) errorCollection.NewError(config_kD(slotIdx, slot.kD, timeoutMs));
		if(SlotConfigurationUtil.kFDifferent(slot) || !enableOptimization) errorCollection.NewError(config_kF(slotIdx, slot.kF, timeoutMs));
		if(SlotConfigurationUtil.integralZoneDifferent(slot) || !enableOptimization) errorCollection.NewError(config_IntegralZone(slotIdx, slot.integralZone, timeoutMs));
		if(SlotConfigurationUtil.allowableClosedloopErrorDifferent(slot) || !enableOptimization) errorCollection.NewError(configAllowableClosedloopError(slotIdx, slot.allowableClosedloopError, timeoutMs));
		if(SlotConfigurationUtil.maxIntegralAccumulatorDifferent(slot) || !enableOptimization) errorCollection.NewError(configMaxIntegralAccumulator(slotIdx, slot.maxIntegralAccumulator, timeoutMs));
		if(SlotConfigurationUtil.closedLoopPeakOutputDifferent(slot) || !enableOptimization) errorCollection.NewError(configClosedLoopPeakOutput(slotIdx, slot.closedLoopPeakOutput, timeoutMs));
		if(SlotConfigurationUtil.closedLoopPeriodDifferent(slot) || !enableOptimization) errorCollection.NewError(configClosedLoopPeriod(slotIdx, slot.closedLoopPeriod, timeoutMs));
    
        return errorCollection._worstError;
    
    }

   
    /**
     * Configures all slot persistant settings (overloaded so timeoutMs is 50 ms
     * and slotIdx is 0
     *
	 * @param slot        Object with all of the slot persistant settings
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
    public ErrorCode configureSlot( SlotConfiguration slot) {
        int slotIdx = 0;
        int timeoutMs = 50;
        return configureSlot(slot, slotIdx, timeoutMs, true);
    }
    /**
     * Gets all slot persistant settings.
     *
	 * @param slot        Object with all of the slot persistant settings
	 * @param slotIdx     Parameter slot for the constant.
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     */
    public void getSlotConfigs(SlotConfiguration slot, int slotIdx, int timeoutMs) {
        slot.kP = (double) configGetParameter(ParamEnum.eProfileParamSlot_P, slotIdx, timeoutMs);
        slot.kI = (double) configGetParameter(ParamEnum.eProfileParamSlot_I, slotIdx, timeoutMs);
        slot.kD = (double) configGetParameter(ParamEnum.eProfileParamSlot_D, slotIdx, timeoutMs);
        slot.kF = (double) configGetParameter(ParamEnum.eProfileParamSlot_F, slotIdx, timeoutMs);
        slot.integralZone = (int) configGetParameter(ParamEnum.eProfileParamSlot_IZone, slotIdx, timeoutMs);
        slot.allowableClosedloopError = (int) configGetParameter(ParamEnum.eProfileParamSlot_AllowableErr, slotIdx, timeoutMs);
        slot.maxIntegralAccumulator = (double) configGetParameter(ParamEnum.eProfileParamSlot_MaxIAccum, slotIdx, timeoutMs);
        slot.closedLoopPeakOutput = (double) configGetParameter(ParamEnum.eProfileParamSlot_PeakOutput, slotIdx, timeoutMs);
        slot.closedLoopPeriod = (int) configGetParameter(ParamEnum.ePIDLoopPeriod, slotIdx, timeoutMs);
    }
    /**
     * Gets all slot persistant settings (overloaded so timeoutMs is 50 ms
     * and slotIdx is 0
     *
	 * @param slot        Object with all of the slot persistant settings
     */
    public void getSlotConfigs( SlotConfiguration slot) {
        int slotIdx = 0;
        int timeoutMs = 50;
        getSlotConfigs(slot, slotIdx, timeoutMs);
    }
    
    
    /**
     * Configures all filter persistant settings.
     *
	 * @param filter        Object with all of the filter persistant settings
     * @param ordinal       0 for remote sensor 0 and 1 for remote sensor 1.
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
    public ErrorCode configureFilter( FilterConfiguration filter, int ordinal, int timeoutMs, boolean enableOptimizations) {
		if(FilterConfigUtil.filterConfigurationDifferent(filter) || !enableOptimizations)
			return configRemoteFeedbackFilter(filter.remoteSensorDeviceID, filter.remoteSensorSource, ordinal, timeoutMs);
		
		return ErrorCode.OK;
    }
    /**
     * Configures all filter persistant settings (overloaded so timeoutMs is 50 ms
     * and ordinal is 0).
     *
	 * @param filter        Object with all of the filter persistant settings
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
    public ErrorCode configureFilter( FilterConfiguration filter) {
        int ordinal = 0;
        int timeoutMs = 50;
        return configureFilter(filter, ordinal, timeoutMs, true);
    }
    
    /**
     * Gets all filter persistant settings.
     *
	 * @param filter        Object with all of the filter persistant settings
     * @param ordinal       0 for remote sensor 0 and 1 for remote sensor 1.
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     */
    public void getFilterConfigs(FilterConfiguration filter, int ordinal, int timeoutMs) {
    
        filter.remoteSensorDeviceID = (int) configGetParameter(ParamEnum.eRemoteSensorDeviceID, ordinal, timeoutMs);
        filter.remoteSensorSource = RemoteSensorSource.valueOf(configGetParameter(ParamEnum.eRemoteSensorSource, ordinal, timeoutMs));
    
    }
    /**
     * Gets all filter persistant settings (overloaded so timeoutMs is 50 ms 
     * and ordinal is 0).
     *
	 * @param filter        Object with all of the filter persistant settings
     */
    public void getFilterConfigs(FilterConfiguration filter) {
        int ordinal = 0;
        int timeoutMs = 50;
        getFilterConfigs(filter, ordinal, timeoutMs);
    }
    /**
     * Configures all base PID set persistant settings.
     *
	 * @param pid           Object with all of the base PID set persistant settings
     * @param pidIdx        0 for Primary closed-loop. 1 for auxiliary closed-loop.       
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     *
     * @return Error Code generated by function. 0 indicates no error. 
     */
    protected ErrorCode baseConfigurePID(BasePIDSetConfiguration pid, int pidIdx, int timeoutMs) {
    
        return configSelectedFeedbackCoefficient(pid.selectedFeedbackCoefficient, pidIdx, timeoutMs);
    
    }
    /**
     * Gets all base PID set persistant settings.
     *
	 * @param pid           Object with all of the base PID set persistant settings
     * @param pidIdx        0 for Primary closed-loop. 1 for auxiliary closed-loop.       
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     */
    protected void baseGetPIDConfigs(BasePIDSetConfiguration pid, int pidIdx, int timeoutMs) {
    
        pid.selectedFeedbackCoefficient = (double) configGetParameter(ParamEnum.eSelectedSensorCoefficient, pidIdx, timeoutMs);
    
    }
    /**
     * Gets all base persistant settings.
     *
	 * @param allConfigs        Object with all of the base persistant settings
     * @param timeoutMs
     *              Timeout value in ms. If nonzero, function will wait for
     *              config success and report an error if it times out.
     *              If zero, no blocking or checking is performed.
     */
    protected void baseGetAllConfigs(BaseMotorControllerConfiguration allConfigs, int timeoutMs) {


        allConfigs.openloopRamp = (double) configGetParameter(ParamEnum.eOpenloopRamp, 0, timeoutMs);
        allConfigs.closedloopRamp = (double) configGetParameter(ParamEnum.eClosedloopRamp, 0, timeoutMs);
        allConfigs.peakOutputForward = (double) configGetParameter(ParamEnum.ePeakPosOutput, 0, timeoutMs);
        allConfigs.peakOutputReverse = (double) configGetParameter(ParamEnum.ePeakNegOutput, 0, timeoutMs);
        allConfigs.nominalOutputForward = (double) configGetParameter(ParamEnum.eNominalPosOutput, 0, timeoutMs);
        allConfigs.nominalOutputReverse = (double) configGetParameter(ParamEnum.eNominalNegOutput, 0, timeoutMs);
        allConfigs.neutralDeadband = (double) configGetParameter(ParamEnum.eNeutralDeadband, 0, timeoutMs);
        allConfigs.voltageCompSaturation = (double) configGetParameter(ParamEnum.eNominalBatteryVoltage, 0, timeoutMs);
        allConfigs.voltageMeasurementFilter = (int) configGetParameter(ParamEnum.eBatteryVoltageFilterSize, 0, timeoutMs);
        allConfigs.velocityMeasurementPeriod = VelocityMeasPeriod.valueOf(configGetParameter(ParamEnum.eSampleVelocityPeriod, 0, timeoutMs));
        allConfigs.velocityMeasurementWindow = (int) configGetParameter(ParamEnum.eSampleVelocityWindow, 0, timeoutMs);
        allConfigs.forwardSoftLimitThreshold = (int) configGetParameter(ParamEnum.eForwardSoftLimitThreshold, 0, timeoutMs);
        allConfigs.reverseSoftLimitThreshold = (int) configGetParameter(ParamEnum.eReverseSoftLimitThreshold, 0, timeoutMs);
        allConfigs.forwardSoftLimitEnable = configGetParameter(ParamEnum.eForwardSoftLimitEnable, 0, timeoutMs) != 0.0;
        allConfigs.reverseSoftLimitEnable = configGetParameter(ParamEnum.eReverseSoftLimitEnable, 0, timeoutMs) != 0.0; //Note, fix in firmware
    
        getSlotConfigs(allConfigs.slot0, 0, timeoutMs);
        getSlotConfigs(allConfigs.slot1, 1, timeoutMs);
        getSlotConfigs(allConfigs.slot2, 2, timeoutMs);
        getSlotConfigs(allConfigs.slot3, 3, timeoutMs);
    
        allConfigs.auxPIDPolarity = configGetParameter(ParamEnum.ePIDLoopPolarity, 1, timeoutMs) != 0.0;
    
        getFilterConfigs(allConfigs.remoteFilter0, 0, timeoutMs);
        getFilterConfigs(allConfigs.remoteFilter1, 1, timeoutMs);
    
        allConfigs.motionCruiseVelocity = (int) configGetParameter(ParamEnum.eMotMag_VelCruise, 0, timeoutMs);
        allConfigs.motionAcceleration = (int) configGetParameter(ParamEnum.eMotMag_Accel, 0, timeoutMs);
        allConfigs.motionProfileTrajectoryPeriod = (int) configGetParameter(ParamEnum.eMotionProfileTrajectoryPointDurationMs, 0, timeoutMs);
        allConfigs.customParam0 = (int) configGetParameter(ParamEnum.eCustomParam, 0,  timeoutMs);
        allConfigs.customParam1 = (int) configGetParameter(ParamEnum.eCustomParam, 1,  timeoutMs);
    
    
        allConfigs.feedbackNotContinuous = configGetParameter(ParamEnum.eFeedbackNotContinuous, 0, timeoutMs) != 0.0;
        allConfigs.remoteSensorClosedLoopDisableNeutralOnLOS = configGetParameter(ParamEnum.eRemoteSensorClosedLoopDisableNeutralOnLOS, 0, timeoutMs) != 0.0;
        allConfigs.clearPositionOnLimitF = configGetParameter(ParamEnum.eClearPositionOnLimitF, 0, timeoutMs) != 0.0;
        allConfigs.clearPositionOnLimitR = configGetParameter(ParamEnum.eClearPositionOnLimitR, 0, timeoutMs) != 0.0;
        allConfigs.clearPositionOnQuadIdx = configGetParameter(ParamEnum.eClearPositionOnQuadIdx, 0, timeoutMs) != 0.0;
        allConfigs.limitSwitchDisableNeutralOnLOS = configGetParameter(ParamEnum.eLimitSwitchDisableNeutralOnLOS, 0, timeoutMs) != 0.0;
        allConfigs.softLimitDisableNeutralOnLOS = configGetParameter(ParamEnum.eSoftLimitDisableNeutralOnLOS, 0, timeoutMs) != 0.0;
        allConfigs.pulseWidthPeriod_EdgesPerRot = (int) configGetParameter(ParamEnum.ePulseWidthPeriod_EdgesPerRot, 0, timeoutMs);
        allConfigs.pulseWidthPeriod_FilterWindowSz = (int) configGetParameter(ParamEnum.ePulseWidthPeriod_FilterWindowSz, 0, timeoutMs);
    
    
    }

}
