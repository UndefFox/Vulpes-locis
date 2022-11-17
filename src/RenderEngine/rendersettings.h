#ifndef H_RENDERENGINE_RENDERSETTINGS
#define H_RENDERENGINE_RENDERSETTINGS

#include <cstdint>

namespace RenderEngine {

/**
 * Contains settings for render engine.
 */
struct RenderSettings {
    /**
     * Id of the device that must be used for render.
     */
    uint32_t deviceId;
};

}

#endif