#include "core.h"

#include "RenderEngine/renderengine.h"
#include "RenderEngine/src/values.h"

#include <GLFW/glfw3.h>
#include <math.h>
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

std::vector<int> ids = {1, 0};
std::vector<std::array<float, 3>> posses = {
    {0.0f, 0.0f, -2.0f},
    {1.0f, 0.0f, 0.0f}
};



namespace Core {

GLFWwindow* window;

void initializate() {
    glfwInit();

    RenderEngine::initializate();
   

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(430, 200, "Vulpes locis", nullptr, nullptr);

    std::vector<RenderEngine::DeviceInfo> infos = RenderEngine::getAvailableDevices(window);

    RenderEngine::RenderSettings settings{};
    settings.deviceId = infos[0].deviceId;
    settings.targetWindow = window;
    settings.vertexShaderFile = "shaders/vertical.spv";
    settings.fragmentShaderFile = "shaders/fragment.spv";

    RenderEngine::configurateRender(settings);
    RenderEngine::configurateRender(settings);

    RenderEngine::Mesh mesh{};
    mesh.vertices = vertices1;
    mesh.indexes = indices1;

    RenderEngine::addMesh(mesh);

    mesh.vertices = vertices2;
    mesh.indexes = indices2;

    RenderEngine::addMesh(mesh);
}


void run() {

    float i = 0;

    while (!isGameEnterupted()) {
        glfwPollEvents();

        posses[0][2] = sin(i) - 1.0f;
        i += 0.01;

        RenderEngine::drawFrame(ids, posses);
    }
}

bool isGameEnterupted() {
    return glfwWindowShouldClose(window);
}

}