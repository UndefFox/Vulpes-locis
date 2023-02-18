#include "core.h"

#include "modules/RenderEngine/src/values.h"

#include "modules/RenderEngine/storage.h"
#include "modules/RenderEngine/configurator.h"
#include "modules/RenderEngine/renderer.h"
#include "modules/ECS/ECS.h"

#include "modules/ECS/components/transformation.h"
#include "modules/ECS/components/renderdata.h"
#include "modules/ECS/components/physic.h"

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

    RenderEngine::Mesh mesh{};
    mesh.vertices = vertices1;
    mesh.indexes = indices1;

    RenderEngine::addMesh(mesh);

    mesh.vertices = vertices2;
    mesh.indexes = indices2;

    RenderEngine::addMesh(mesh);
}


void run() {

    Entity* first = new Entity{};

    Transformation* trans1 = new Transformation{};
    trans1->pos = { 1.0f, 0.0f, 0.3f };
    
    RenderData* render1 = new RenderData{};
    render1->meshId = 0;

    first->mask = 1 << 0;

    first->components = {trans1, render1};

    Entity* second = new Entity{};

    Transformation* trans2 = new Transformation{};
    trans2->pos = { -3.0f, 0.2f, -6.0f };
    
    RenderData* render2 = new RenderData{};
    render2->meshId = 1;

    Physic* phys2 = new Physic{};
    phys2->gravity = -9.8f / 10000.0f;
    phys2->velocity.z = 0.10f;

    second->mask = (1 << 0) + (1 << 1);

    second->components = {trans2, render2, phys2};

    ECS::addEntity(first);
    ECS::addEntity(second);

    while (!isGameEnterupted()) {
        glfwPollEvents();

        ECS::execute();

        RenderEngine::drawFrame(ids);
    }
}

bool isGameEnterupted() {
    return glfwWindowShouldClose(window);
}

}