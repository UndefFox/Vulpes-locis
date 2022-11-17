#include "core.h"

#include "RenderEngine/configurator.h"
#include "RenderEngine/renderengine.h"

#include <GLFW/glfw3.h>

// const std::vector<RenderEngine::Vertex> vertices = {
//     {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//     {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
//     {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//     {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
// };

// const std::vector<uint16_t> indices = {
//     0, 1, 2, 2, 3, 0
// };

namespace Core {


void initializate() {
    RenderEngine::Configurator::initializate();

    std::vector<RenderEngine::DeviceInfo> infos = RenderEngine::Configurator::getAvailableDevices();

    RenderEngine::RenderSettings settings{};
    settings.deviceId =infos[0].deviceId;

    RenderEngine::Configurator::configurateRender(settings);
}

void run() {

    while (!isGameEnterupted()) {
        glfwPollEvents();
        RenderEngine::drawFrame();
    }
}

bool isGameEnterupted() {
    return false;
}

}