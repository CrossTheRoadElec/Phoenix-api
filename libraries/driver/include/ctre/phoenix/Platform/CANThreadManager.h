#pragma once
#include <stdint.h>
#include <chrono>
#include <queue>
#include "ctre/phoenix/LowLevel/Device_LowLevel.h"
#include <linux/can.h>

namespace ctre {
namespace phoenix {
namespace platform {
namespace can {
//Clean up these structs?
struct StoredReceiveData {
    uint32_t timeStamp;
    uint8_t data[8];
    uint8_t dataSize;
    std::chrono::time_point<std::chrono::high_resolution_clock> localStamp;
};
struct StoredSendData {
    struct can_frame msg;
    
    int32_t periodMs;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastSent;

    StoredSendData() :
        periodMs(0xFFFFFFFF),
        lastSent(std::chrono::high_resolution_clock::now())
    {
        msg.can_dlc = 8;
    }
};

struct Stream {
    std::queue<tCANStreamMessage> collectedMsgs;
    uint32_t messageID;
    uint32_t messageIDMask;
};

class CANThreadManager {
public:
    CANThreadManager(bool &success);
    CANThreadManager(bool &success, const char* interface);
    
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
    ~CANThreadManager();
private:
    uint32_t _iterator = 1;
};
}
}
}
}
