#pragma once

#include "../core/ctre.h"
#include <string>

extern "C" {
	void c_Logger_Close();
	void c_Logger_Open(int language, bool logDriverStation);
	CTR_Code c_Logger_Log(CTR_Code code, const char* origin, int hierarchy, const char *stacktrace);
	void c_Logger_Description(CTR_Code code, std::string & shortDescripToFill, std::string & longDescripToFill);
}
