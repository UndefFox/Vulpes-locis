#ifndef RENDERENGINE_DEVICEINFO_H
#define RENDERENGINE_DEVICEINFO_H

#include <string>

namespace RenderEngine {

/**
 * Info about graphical device.
 */
struct DeviceInfo {
    /**
     * Uniqiue id that device have.
     */
    uint32_t deviceId;

    /**
     * Offical device name.
     */
    std::string deviceName;
};

}

#endif