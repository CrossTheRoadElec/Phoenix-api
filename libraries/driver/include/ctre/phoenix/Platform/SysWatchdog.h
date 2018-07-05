#pragma once
#include <string>

namespace ctre {
namespace phoenix {
namespace platform {

class SysWatchdog
{
public:
	static SysWatchdog & GetInstance();
	SysWatchdog();
    /**
	 * Processes watchdog outputs, checks if robot is enabled.
	 * @param isEnabled robot is enabled
	 * @return nonzero error code if something is wrong or if still initializing.
	 */
	void Feed(int timeoutMs);
    int Check(bool & isEnabled);
private:
    ~SysWatchdog(); 
};
} // namespace platform
} // namespace phoenix
} // namespace ctre
