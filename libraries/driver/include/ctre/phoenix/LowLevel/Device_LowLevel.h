#pragma once

#include <map>
#include "ctre/Phoenix/LowLevel/ResetStats.h"
#include <FRC_NetworkCommunication/CANSessionMux.h>  // tCANStreamMessage
/* forward proto's */
enum ErrorCode
: int32_t;
enum ParamEnum
: uint32_t;

class Device_LowLevel {

protected:
	int32_t _baseArbId;
	/** child class has to provide a way to enable/disable firm status */
	virtual void EnableFirmStatusFrame(bool enable) = 0;
	virtual ErrorCode SetLastError(ErrorCode enable) = 0;

	/**
	 * Change the periodMs of a TALON's status frame.  See kStatusFrame_* enums for
	 * what's available.
	 */
	ErrorCode SetStatusFramePeriod_(int32_t statusArbID, int32_t periodMs,
			int32_t timeoutMs);
	ErrorCode GetStatusFramePeriod_(int32_t statusArbID, int32_t &periodMs,
			int32_t timeoutMs);

	int32_t GetStartupStatus();

	void CheckFirm(int minMajor, int minMinor, const std::string & origin);
	void CheckFirm(int minMajor, int minMinor, const char * origin);

	ErrorCode ConfigSetParameter(ParamEnum paramEnum, int32_t value,
			uint8_t subValue, int32_t ordinal, int32_t timeoutMs);

	ErrorCode ConfigGetParameter(ParamEnum paramEnum, int32_t valueToSend,
			int32_t & valueReceived, uint8_t subValue, int32_t ordinal,
			int32_t timeoutMs);

	ErrorCode ConfigGetParameter(ParamEnum paramEnum, int32_t &value,
			int32_t ordinal, int32_t timeoutMs);
private:
	int32_t _deviceNumber;

	int32_t _arbIdStartupFrame;
	int32_t _arbIdFrameApiStatus;

	uint64_t _cache = 0;
	int32_t _len = 0;

	uint32_t _arbIdParamRequest;
	uint32_t _arbIdParamResp;
	uint32_t _arbIdParamSet;
	int32_t kParamArbIdMask;

	uint32_t _can_h = 0;
	int32_t _can_stat = 0;
	struct tCANStreamMessage _msgBuff[20];
	static const uint32_t kMsgCapacity = 20;

	ResetStats _resetStats;
	int32_t _firmVers = -1; /* invalid */

	std::map<int32_t, int32_t> _sigs_Value;
	std::map<int32_t, int32_t> _sigs_SubValue;
	std::map<int32_t, int32_t> _sigs_Ordinal;

	const int32_t kFullMessageIDMask = 0x1fffffff;
	const double FLOAT_TO_FXP_10_22 = (double) 0x400000;
	const double FXP_TO_FLOAT_10_22 = 0.0000002384185791015625f;
	const double FLOAT_TO_FXP_0_8 = (double) 0x100;
	const double FXP_TO_FLOAT_0_8 = 0.00390625f;

	int _failedVersionChecks = 0;
	void OpenSessionIfNeedBe();
	void ProcessStreamMessages();


	ErrorCode RequestParam(ParamEnum paramEnum, int32_t value, uint8_t subValue,
			int32_t ordinal);

	ErrorCode PollForParamResponse(ParamEnum paramEnum, int32_t & value, int32_t & subValue, int32_t & ordinal);

public:

	Device_LowLevel(int32_t baseArbId, int32_t arbIdStartupFrame,
			int32_t paramReqId, int32_t paramRespId, int32_t paramSetId,
			int32_t arbIdFrameApiStatus);
	Device_LowLevel(const Device_LowLevel &) = delete;
	virtual ~Device_LowLevel() {}

	int GetDeviceNumber();
	ErrorCode GetDeviceNumber(int & deviceNumber);
	int32_t GetFirmStatus();

	ErrorCode GetResetCount(int & param);
	ErrorCode GetResetFlags(int &param);
	/** return -1 if not available, return 0xXXYY format if available */
	ErrorCode GetFirmwareVersion(int &param);
	int GetFirmwareVersion();
	/**
	 * @return true iff a reset has occured since last call.
	 */
	ErrorCode HasResetOccurred(bool & param);
	bool HasResetOccurred();

	ErrorCode ConfigSetParameter(ParamEnum paramEnum, double value,
			uint8_t subValue, int32_t ordinal, int32_t timeoutMs);

	ErrorCode ConfigGetParameter(ParamEnum paramEnum, double &value,
			int32_t ordinal, int32_t timeoutMs);

	ErrorCode ConfigSetCustomParam(int value, int paramIndex, int timeoutMs);
	ErrorCode ConfigGetCustomParam(int & value, int paramIndex, int timeoutMs);

};
