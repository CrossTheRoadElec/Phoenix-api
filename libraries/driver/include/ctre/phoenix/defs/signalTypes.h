#ifndef signalTypes__h_
#define signalTypes__h_

enum{
	modeDutyCycleControl = 0,	//!< Demand is signed 16bit 0.16fixedPt. 7FFF is fullfor.  8000 is fullRev.
	modePosControl = 1,			//!< Demand 24bit position.
	modeSpeedControl = 2,		//!< Demand is 24 bit speed.
	modeCurrentControl = 3,		//!< Demand is 24 bit current.
	//modeVoltageControl = 4,		//!< Demand is 8.8 voltage command.
	modeSlaveFollower = 5,		//!< Demand is the can node to follow.
	modeMotionProfile = 6,		//!< Demand is unused,could be used in future. Control6 has everything we want.
	modeMotionMagic = 7,		//!< Reserved
	//8
	//9
	//10
	//11
	//12
	//13
#ifdef SUPPORT_ONE_SHOT_CONTROL_MODE
	modeOneShot = 14,
#endif
	modeNoDrive = 15,
};

typedef enum _feedbackDevice_t{
	kFeedback_DigitalQuadEnc=0,
	//1
	kFeedback_AnalogPot=2,
	kFeedback_AnalogEncoder=3,
	kFeedback_CountEveryRisingEdge=4,
	kFeedback_CountEveryFallingEdge=5,
	kFeedback_CtreMagEncoder_Relative = 6, //!< Cross The Road Electronics Magnetic Encoder in Absolute/PulseWidth Mode
	kFeedback_CtreMagEncoder_Absolute = 7, //!< Cross The Road Electronics Magnetic Encoder in Relative/Quadrature Mode
	kFeedback_PosIsPulseWidth=8,
	
	kFeedback_OtherTalonPos=9,
	kFeedback_RobotPosition=10,
	kFeedback_RobotHeading=11,
	//10
	//11
	//12
	//13
	//14
	kFeedback_RampingPos=15,
}feedbackDevice_t;

typedef enum _MotProf_OutputType_t {
	MotProf_OutputType_Disabled = 0,
	MotProf_OutputType_Enabled,
	MotProf_OutputType_Hold,
	MotProf_OutputType_Invalid,
}MotProf_OutputType_t;

#endif // signalTypes__h_
