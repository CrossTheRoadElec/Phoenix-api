#include "ctre/phoenix/core/ctre.h"
#include "ctre/phoenix/core/ErrorCode.h" // CTR_Code
#include <string>

namespace CTRE {

class CTRLogger {
public: 
	static void Close();
	static CTR_Code Log(CTR_Code code, std::string origin);
	static void Open(int language);
	//static void Description(CTR_Code code, const char *&shrt, const char *&lng);
};

}
