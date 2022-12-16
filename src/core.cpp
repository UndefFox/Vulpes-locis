#include "core.h"

#include "RenderEngine/src/values.h"

#include "RenderEngine/storage.h"
#include "RenderEngine/configurator.h"
#include "RenderEngine/renderer.h"

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

    RenderEngine::DrawCall drawCall1{};
    drawCall1.meshId = 0;
    drawCall1.position = {0, 0, 0};

    RenderEngine::DrawCall drawCall2{};
    drawCall2.meshId = 1;
    drawCall2.position = {1, 1, 0};

    while (!isGameEnterupted()) {
        glfwPollEvents();

        i += 0.01;

        drawCall2.position[2] = sin(i) - 1.0f;

        RenderEngine::addDrawCall(drawCall1);
        RenderEngine::addDrawCall(drawCall2);

        RenderEngine::drawFrame(ids);
    }
}

bool isGameEnterupted() {
    return glfwWindowShouldClose(window);
}

}