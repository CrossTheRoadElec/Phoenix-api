#include "ctre/phoenix/CTRLogger.h"
#include "ctre/phoenix/CCI/Logger_CCI.h" // c_Logger_*
#include "ctre/phoenix/Platform/Platform.h"

namespace ctre {
namespace phoenix {

void CTRLogger::Open(int language) {
	c_Logger_Open(language, true);
}

static void GetStackTrace(std::string & stackTrace)
{
	stackTrace = ctre::phoenix::platform::GetStackTrace(1);
}
/* original implem before multi-platform support */
//#include <execinfo.h>
//void GetStackTrace(std::string & stackTrace)
//{
//	void *buf[100];
//	char **strings;
//	int size = backtrace(buf, 100);
//	strings = backtrace_symbols(buf, size);
//	for (int i = 1; i < size; i++) {
//		stackTrace += strings[i];
//		stackTrace += "\n";
//	}
//}

ErrorCode CTRLogger::Log(ErrorCode code, std::string origin) {
	std::string stackTrace;
	GetStackTrace(stackTrace);
	return c_Logger_Log(code, origin.c_str(), 3, stackTrace.c_str());
}
void CTRLogger::Close() {
	c_Logger_Close();
}
//void CTRLogger::Description(ErrorCode code, const char *&shrt, const char *&lng) {
//	c_Logger_Description(code, shrt, lng);
//}

}
}
