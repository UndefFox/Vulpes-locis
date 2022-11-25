#include "core.h"

#include "RenderEngine/renderengine.h"
#include "RenderEngine/src/values.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <array>

const std::vector<std::array<float, 3>> vertices1 = {
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.5f, 0.5f, 0.0f},
    {-0.5f, 0.5f, 0.0f}
};

const std::vector<uint16_t> indices1 = {
    0, 1, 2, 2, 3, 0
};

const std::vector<std::array<float, 3>> vertices2 = {
    {-0.5f, -0.5f, 1.0f},
    {0.0f, -0.5f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    {-0.5f, 0.0f, 1.0f}
};

const std::vector<uint16_t> indices2 = {
    0, 1, 2, 2, 3, 0
};

std::vector<int> ids = {1};
std::vector<std::array<float, 3>> posses = {
    {0.0f, 0.0f, -0.5f}
};



namespace Core {


void initializate() {
    RenderEngine::initializate();

    std::vector<RenderEngine::DeviceInfo> infos = RenderEngine::getAvailableDevices();

    RenderEngine::RenderSettings settings{};
    settings.deviceId = infos[0].deviceId;
    settings.vertexShaderFile = "shaders/vertical.spv";
    settings.fragmentShaderFile = "shaders/fragment.spv";

    RenderEngine::configurateRender(settings);


    RenderEngine::Mesh mesh{};
    mesh.vertices = vertices1;
    mesh.indexes = indices1;

    RenderEngine::addObject(mesh);

    mesh.vertices = vertices2;
    mesh.indexes = indices2;

    RenderEngine::addObject(mesh);
}


void run() {

    while (!isGameEnterupted()) {
        glfwPollEvents();

        RenderEngine::drawFrame(ids, posses);
    }
}

bool isGameEnterupted() {
    return glfwWindowShouldClose(RenderEngine::window);
}

}