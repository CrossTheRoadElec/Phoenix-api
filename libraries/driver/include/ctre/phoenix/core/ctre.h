/**
 * @file ctre.h
 * Common header for all CTRE HAL modules.
 */
#ifndef CTRE_H
#define CTRE_H

//Bit Defines
#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
#define BIT8  0x0100
#define BIT9  0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000

//Signed
typedef	signed char	INT8;
typedef	signed short	INT16;
typedef	signed int	INT32;
typedef	signed long long INT64;

//Unsigned
typedef	unsigned char	UINT8;
typedef	unsigned short	UINT16;
typedef	unsigned int	UINT32;
typedef	unsigned long long UINT64;

//Other
typedef	unsigned char	UCHAR;
typedef unsigned short	USHORT;
typedef	unsigned int	UINT;
typedef unsigned long	ULONG;

#define UNUSED(x) (void)(x)

typedef enum {
		OKAY = 0,					//!< No Error - Function executed as expected
		
		//CAN-Related
		TxFailed = -1,				//!< Could not transmit the CAN frame.
		InvalidParamValue = -2, 	//!< Caller passed an invalid param
		RxTimeout = -3,				//!< CAN frame has not been received within specified period of time.
		TxTimeout = -4,				//!< Not used.
		UnexpectedArbId = -5,		//!< Specified CAN Id is invalid.
		BufferFull = -6,			//!< Caller attempted to insert data into a buffer that is full.
		SensorNotPresent = -7,		//!< Sensor is not present
		
		//General
		GeneralError = -100,		//!< User Specified General Error		
		
		//??
		SigNotUpdated = -200,			//!< Have not received an value response for signal.
		NotAllPIDValuesUpdated = -201,
		
		//API
		WheelRadiusTooSmall = -500,
		TicksPerRevZero = -501,
		DistanceBetweenWheelsTooSmall = -502,
		
		//Higher Level
		IncompatibleMode = -600,
		InvalidHandle = -601,		//!< Handle does not match stored map of handles
		
		
		//CAN Related
		PulseWidthSensorNotPresent = 1,	//!< Special Code for "isSensorPresent"
		
		//General
		GeneralWarning = 100,
		FeatureNotSupported = 101,
		
}CTR_Code;

#endif /* CTRE_H */
