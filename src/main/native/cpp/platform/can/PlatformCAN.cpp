#include "ctre/phoenix/platform/can/PlatformCAN.h"

namespace ctre {
namespace phoenix {
namespace platform {
namespace can {

int32_t PlatformCAN::SetCANInterface(const char * canInterface) {
    return c_SetCANInterface(canInterface); 
}
    
}
}
}
}
