#pragma once

#include "../core/ctre.h"
#include <string>

extern "C" {
	void c_Logger_Close();
	void c_Logger_Open(int language, bool logDriverStation);
	CTR_Code c_Logger_Log(CTR_Code CTRCode, const char* origin, const char *stacktrace);
	void c_Logger_Description(CTR_Code code, const char *&shortD, const char *&longD);
	char *c_Logger_GetShort(CTR_Code code);
	char *c_Logger_GetVerbose(CTR_Code code);
}