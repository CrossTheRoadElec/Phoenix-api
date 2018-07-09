#pragma once
#include "ctre/Phoenix/Platform/Platform-pack.h"
#include <stdint.h>
#include <string>

namespace ctre {
namespace phoenix {
namespace platform {
namespace can {
	/**
	 * "plain old data" container for holding a CAN Frame Event.
	 * Assignment of this type resolves to a copy-by-value.
	 */
	typedef struct _canframe_t {
		uint32_t arbID; //!< ArbID of the CAN frame.
		uint32_t timeStampUs; //!< Timestamp if receive event.  Zero otherwise.
		uint8_t data[8]; //!< Data bytes
		uint32_t flags; //!< Zero for now.  Can be used for detecting arbID type (29bit vs 11bit).
		uint8_t dlc; //!< Number of bytes in payload
	} canframe_t;

	//-------------- Low Level CANBus interface, this is required if using Phoenix-canutil--------------------------//
	void CANbus_GetStatus(float *busUtilPerc, uint32_t *busOffCount, uint32_t *txFullCount, uint32_t *rec, uint32_t *tec, int32_t *status);
	int32_t CANbus_SendFrame(uint32_t messageID, const uint8_t *data, uint8_t dataSize);
	int32_t CANbus_ReceiveFrames(canframe_t * toFill, int capacity, int & size);

	//-------------- Mid Level CANBus interface, this is required if NOT using Phoenix-canutil, --------------------------//
	void CANComm_SendMessage(uint32_t messageID, const uint8_t *data, uint8_t dataSize, int32_t periodMs, int32_t *status);
	/**
	 * @param messageIDMask Completely ignored, TODO remove this.
	 */
	void CANComm_ReceiveMessage(uint32_t *messageID, uint32_t messageIDMask, uint8_t *data, uint8_t *dataSize, uint32_t *timeStamp, int32_t *status);
	void CANComm_OpenStreamSession(uint32_t *sessionHandle, uint32_t messageID, uint32_t messageIDMask, uint32_t maxMessages, int32_t *status);
	void CANComm_CloseStreamSession(uint32_t sessionHandle);
	void CANComm_ReadStreamSession(uint32_t sessionHandle, canframe_t *messages, uint32_t messagesToRead, uint32_t *messagesRead, int32_t *status);
	int32_t CANComm_GetTxSchedulerStatus(void *unusedControlWorld); // used to be GetControlWord

} //namespace can
} //namespace platform
} //namespace phoenix
} //namespace ctre

namespace ctre {
namespace phoenix {
namespace platform {
	/**
	 * @param [out] isEnabled	Set to true to enable actuators (Talons for example).
	 *							Sometimes this is called robot-enable.
	 * @return 0 if routine is successful. Nonzero for error code, and 
	 *							caller will disable system regardless of isEnabled.
	 */
	int IsSystemActuatorEnabled(bool & isEnabled);

	/**
	 * @param timeUs	How long to yield current thread in microseconds (us).  
	 *					If platform cannot honor us resolution, round to nearest
	 *					value that platform can honor.
	 */
	void SleepUs(int timeUs);

	/**
	 * Get a stack trace, ignoring the first "offset" symbols.
	 *
	 * @param offset The number of symbols at the top of the stack to ignore
	 */
	std::string GetStackTrace(int offset);

	void ReportError(int isError, int32_t errorCode, int isLVCode,
		const char *details, const char *location, const char *callStack);

} // namespace platform
} // namespace phoenix
} // namespace ctre
