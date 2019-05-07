#include "ctre/phoenix/platform/can/PlatformCAN.h"

namespace ctre {
namespace phoenix {
namespace platform {
namespace can {

int32_t PlatformCAN::SetCANInterface(const char * canInterface) {
    return c_SetCANInterface(canInterface); 
}
    
int32_t PlatformCAN::DestroyAll() {
    return c_DestroyAll();
}

int32_t PlatformCAN::StartAll() {
    return c_StartAll();
}

void PlatformCAN::SetAutocacheLevel(ctre::phoenix::AutocacheState state){
    c_Autocache_SetAutocacheLevel(state);
}

}
}
}
}
