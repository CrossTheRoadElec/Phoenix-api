#pragma once
#include <stdint.h>
#include "ctre/phoenix/Platform/CANThreadManager.h"
#include <memory>

namespace ctre {
namespace phoenix {
namespace platform {
namespace can {

class CANProtocol {
public:
	static CANProtocol & GetInstance();

    void SetInterface(const char * interface, bool &success);
	//int GetControlWord(struct ControlWord_t *controlWord);
	void SendMessage(uint32_t messageID, const uint8_t *data, uint8_t dataSize,
			int32_t periodMs, int32_t *status);
	void ReceiveMessage(uint32_t *messageID, uint32_t messageIDMask,
			uint8_t *data, uint8_t *dataSize, uint32_t *timeStamp,
			int32_t *status);
	void OpenStreamSession(uint32_t *sessionHandle, uint32_t messageID,
			uint32_t messageIDMask, uint32_t maxMessages, int32_t *status);
	void CloseStreamSession(uint32_t sessionHandle);
    void ReadStreamSession(uint32_t sessionHandle,
			struct tCANStreamMessage *messages, uint32_t messagesToRead,
			uint32_t *messagesRead, int32_t *status);
	//void GetCANStatus(float *percentBusUtilization, uint32_t *busOffCount,
	//		uint32_t *txFullCount, uint32_t *receiveErrorCount,
	//		uint32_t *transmitErrorCount, int32_t *status);
//	void SendError(int isError, int32_t errorCode, int isLVCode,
//			const char *details, const char *location, const char *callStack);
private:
	CANProtocol();
	~CANProtocol();

    bool _can_device_initialized = false;

    std::shared_ptr<CANThreadManager> _ll;
};

} //namespace can
} //namespace platform
} //namespace phoenix
} //namespace ctre

