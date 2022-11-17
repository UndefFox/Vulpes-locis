#ifndef H_RENDERENGINE_DEVICEINFO
#define H_RENDERENGINE_DEVICEINFO

#include <cstdint>
#include <string>

namespace RenderEngine {

struct DeviceInfo {
    uint32_t deviceId;
    std::string deviceName;
};

}

#endif