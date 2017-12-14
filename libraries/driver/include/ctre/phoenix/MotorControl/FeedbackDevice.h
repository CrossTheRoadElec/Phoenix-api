#pragma once

#include "ctre/Phoenix/ErrorCode.h"

namespace ctre {
namespace phoenix {
namespace motorcontrol {

/** Motor controller with gadgeteer connector. */
enum FeedbackDevice {
	None = -1,

	QuadEncoder = 0,
	//1
	Analog = 2,
	//3
	Tachometer = 4,
	PulseWidthEncodedPosition = 8,

	SensorSum = 9,
	SensorDifference = 10,
	RemoteSensor0 = 11,
	RemoteSensor1 = 12,
	//13
	//14
	SoftwareEmulatedSensor  = 15,

	CTRE_MagEncoder_Absolute = PulseWidthEncodedPosition,
	CTRE_MagEncoder_Relative = QuadEncoder,
};

enum RemoteFeedbackDevice  {
	RemoteFeedbackDevice_None = -1,

	RemoteFeedbackDevice_SensorSum = 9,
	RemoteFeedbackDevice_SensorDifference = 10,
	RemoteFeedbackDevice_RemoteSensor0 = 11,
	RemoteFeedbackDevice_RemoteSensor1 = 12,
	//13
	//14
	RemoteFeedbackDevice_SoftwareEmulatedSensor = 15,
};

//typedef FeedbackDevice RemoteCANifierOrTalonOrPigeon;

/* forward proto's */
//class TalonSRX;
//class CANifier;

//class RemoteFeedbackDevice {
//public:
//	RemoteCANifierOrTalonOrPigeon _type;
//
//	//----- very specific details here that are not worth exposing. ---- //
//	int _peripheralIndex;
//	int _reserved;
//	int _arbId;
//	//TalonSRX & _talon;
//	//CANifier & _canifier;
//	//void * _pigeon;
//
//	RemoteFeedbackDevice(int baseId, RemoteCANifierOrTalonOrPigeon type);
//	ErrorCode SetPosition(float position, int timeoutMs);
//};

} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
