#include "ctre/phoenix/unmanaged/Unmanaged.h"

namespace ctre {
namespace phoenix {
namespace unmanaged {

void Unmanaged::FeedEnable(int timeoutMs) {
    c_FeedEnable(timeoutMs);
}
bool Unmanaged::GetEnableState() {
    return c_GetEnableState();
}

int Unmanaged::GetPhoenixVersion() {
    return c_GetPhoenixVersion();
}

void Unmanaged::LoadPhoenix() {
    c_LoadPhoenix();
}

}
}
}
