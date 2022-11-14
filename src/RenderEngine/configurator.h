#ifndef H_RENDERENGINE_CONFIGURATOR
#define H_RENDERENGINE_CONFIGURATOR

#include <cstdint>

namespace RenderEngine::Configurator {

struct RenderSettings {
    uint8_t deviceId;
};

void initializate ();

void configurateRender(RenderSettings& settings);

void recreateSwapchain();
}

#endif