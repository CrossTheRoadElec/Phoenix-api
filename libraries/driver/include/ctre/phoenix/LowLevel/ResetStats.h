#pragma once

#include <stdint.h>

struct ResetStats
{
	int32_t resetCount;
	int32_t resetFlags;
	int32_t firmVers;
	bool hasReset;
};
