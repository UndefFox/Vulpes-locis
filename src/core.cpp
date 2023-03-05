#include "core.h"

#include "RenderEngine/configurator.h"
#include "RenderEngine/renderer.h"
#include "RenderEngine/storage.h"

#include "ECS/ECS.h"
#include "ECS/components/physic.h"
#include "ECS/components/renderdata.h"
#include "ECS/components/transformation.h"

#include "FileManager/fileLoaders.h"

#include "converters/typeConverters.h"

#include "ECS/ECS.h"

#define RENDERTEST_SETUP_ON


namespace Core {

GLFWwindow* window = nullptr;

namespace {
    bool isGameEnterupted() {
        return glfwWindowShouldClose(window);
    }
} // namespace <anonymous>


void initializate() {
    glfwInit();
    RenderEngine::initializate();
}

void setupInitialState() {
    #ifdef RENDERTEST_SETUP_ON
    // Test setup
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(430, 200, "Vulpes locis", nullptr, nullptr);

    std::vector<RenderEngine::DeviceInfo> infos = RenderEngine::getAvailableDevices(window);

    RenderEngine::Configuration settings{};
    settings.deviceId = infos[0].deviceId;
    settings.window = window;
    settings.verticesShaderPath = "shaders/vertical.spv";
    settings.fragmentShaderPath = "shaders/fragment.spv";

    RenderEngine::configurateRender(settings);

    Object monkey =  FileLoaders::loadObjectFile("./resources/models/fox.obj");

    RenderEngine::Mesh monkeyMesh = TypeConverters::objectToMesh(monkey);

    RenderEngine::addMesh(monkeyMesh);

    Entity* first = new Entity{};

    Transformation* trans1 = new Transformation{};
    trans1->pos = { 0.0f, 0.0f, 0.0f };
    first->addComponent<Transformation>(trans1);

    RenderData* rend1 = new RenderData{};
    rend1->meshId = 0;
    first->addComponent<RenderData>(rend1);

    Physic* phys1 = new Physic{};
    phys1->gravity = -9.8f / 10000.0f;
    phys1->velocity.z = 0.10f;
    //first->addComponent<Physic>(phys1);

    ECS::addEntity(first);

    RenderEngine::setCamera({2, 2, 2}, {});
    #endif
}

void run() {
    while (!isGameEnterupted()) {
        glfwPollEvents();

        ECS::execute();
    }
}

void cleanup() {
    RenderEngine::deconfiguryRenderer();
    glfwDestroyWindow(Core::window);
}

void terminate() {
    RenderEngine::terminate();
    glfwTerminate();
}


}