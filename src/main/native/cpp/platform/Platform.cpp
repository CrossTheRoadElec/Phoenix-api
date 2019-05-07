#include "ctre/phoenix/platform/PlatformSim.h"

namespace ctre {
namespace phoenix {
namespace platform {

int32_t PlatformSim::SimCreate(DeviceType type, int id) {
    return c_SimCreate(type, id);
}
int32_t PlatformSim::SimDestroy(DeviceType type, int id) {
    return c_SimDestroy(type, id);
}
int32_t PlatformSim::SimDestroyAll() {
    return c_SimDestroyAll();
}
int32_t PlatformSim::SimConfigGet(DeviceType type, uint32_t param, uint32_t valueToSend, uint32_t & outValueReceived, uint32_t & outSubvalue, uint32_t ordinal, int32_t id) {
    return c_SimConfigGet(type, param, valueToSend, outValueReceived, outSubvalue, ordinal, id); 
}
int32_t PlatformSim::SimConfigSet(DeviceType type, uint32_t param, uint32_t value, uint32_t subValue, uint32_t ordinal, int32_t id) {
    return c_SimConfigSet(type, param, value, subValue, ordinal, id);
}
}
}
}
