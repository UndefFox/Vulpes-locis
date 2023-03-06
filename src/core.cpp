#include <GLFW/glfw3.h>

#include "RenderEngine/include/configurator.h"
#include "RenderEngine/include/renderer.h"
#include "RenderEngine/include/storage.h"

#include "ECS/include/ECS.h"
#include "systems/components/physic.h"
#include "systems/components/renderdata.h"
#include "systems/components/transformation.h"
#include "systems/physicsengine.h"
#include "systems/renderengine.h"

#include "Window/include/window.h"

#include "fileLoaders.h"

#include "typeConverters.h"

#include "core.h"

#define RENDERTEST_SETUP_ON


namespace Core {

namespace {

bool isGameInterupted() {
    return Window::isWindowClosed();
}

} // namespace <anonymous>

void initializate() {
    glfwInit();
    RenderEngine::initializate();
}

void setupInitialState() {
    #ifdef RENDERTEST_SETUP_ON
    // Test setup

    RenderEngine::Configuration renderConf{};

    Window::createNewWindow();
    GLFWwindow* window = Window::getWindowObject();

    std::vector<RenderEngine::DeviceInfo> infos = RenderEngine::getDevicesSuportedWindow(window);
    
    renderConf.deviceId = infos[0].deviceId;
    renderConf.window = window;
    renderConf.verticesShaderPath = "shaders/vertical.spv";
    renderConf.fragmentShaderPath = "shaders/fragment.spv";
    renderConf.memoryAmount = 1024 * 1024;

    RenderEngine::configurateRender(renderConf);

    ECS::addSystemCall(RenderEngineSystem::execute);
    ECS::addSystemCall(PhysicsEngineSystem::execute);

    ECS::addSystemPostCall(RenderEngineSystem::postExecute);

    Object fox = FileLoaders::loadObjectFile("./resources/models/fox.obj");

    RenderEngine::Mesh foxMesh = TypeConverters::objectToMesh(fox);

    RenderEngine::addMesh(foxMesh);

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
    first->addComponent<Physic>(phys1);

    ECS::addEntity(first);

    RenderEngine::setCamera({2, 2, 2}, {});
    #endif
}

void run() {
    while (!isGameInterupted()) {
        Window::updateWindow();

        ECS::execute();
    }
}

void cleanup() {
    RenderEngine::deconfiguryRenderer();
    Window::destroyWindow();
}

void terminate() {
    RenderEngine::terminate();
    glfwTerminate();
}


}