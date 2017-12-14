#include "ctre/Phoenix/ErrorCode.h" // CTR_Code
#include <string>

namespace ctre {
namespace phoenix {

class CTRLogger {
public:
	static void Close();
	static CTR_Code Log(CTR_Code code, std::string origin);
	static void Open(int language);
	//static void Description(CTR_Code code, const char *&shrt, const char *&lng);
};

}
}
