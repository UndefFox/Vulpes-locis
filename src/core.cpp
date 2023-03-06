#include <GLFW/glfw3.h>

#include "RenderEngine/include/configurator.h"
#include "RenderEngine/include/renderer.h"
#include "RenderEngine/include/storage.h"

#include "ECS/include/ECS.h"
#include "systems/components/physic.h"
#include "systems/components/renderdata.h"
#include "systems/components/transformation.h"
#include "systems/components/mono.h"
#include "systems/components/playerData.h"
#include "systems/physicsengine.h"
#include "systems/renderengine.h"
#include "systems/monoSystem.h"
#include "player.h"
#include "camera.h"

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
    ECS::addSystemCall(MonoSystem::execute);

    ECS::addSystemPostCall(RenderEngineSystem::postExecute);

    Object fox = FileLoaders::loadObjectFile("./resources/models/fox.obj");

    RenderEngine::Mesh foxMesh = TypeConverters::objectToMesh(fox);

    RenderEngine::addMesh(foxMesh);

    std::array<Entity*, 9> foxes{};
    for (int i = 0; i < 9; i++) {
        foxes[i] = new Entity();

        Transformation* trans1 = new Transformation{};
        trans1->pos = { 
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/20.0f)),
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/20.0f)),
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.0f))};
        trans1->rotation = { 
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5.0f)),
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5.0f)),
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5.0f))};
        foxes[i]->addComponent<Transformation>(trans1);

        RenderData* rend1 = new RenderData{};
        rend1->meshId = 0;
        foxes[i]->addComponent<RenderData>(rend1);

        ECS::addEntity(foxes[i]);
    }

    

    Entity* cameraEntity = new Entity{};

    Transformation* trans3 = new Transformation{};
    trans3->pos = { 2.0f, 2.5f, 2.0f };
    cameraEntity->addComponent<Transformation>(trans3);

    int cameraEntityId = ECS::addEntity(cameraEntity);

    Entity* playerEntity = new Entity{};

    Transformation* trans2 = new Transformation{};
    trans2->pos = { 2.0f, 2.0f, 2.0f };
    trans2->rotation = { 0.0f, 0.0f, 0.0f };
    playerEntity->addComponent<Transformation>(trans2);

    PlayerData* playerData = new PlayerData{};
    playerData->cameraObjectId = cameraEntityId;
    playerEntity->addComponent<PlayerData>(playerData);

    Mono* mono = new Mono{};
    mono->calls.push_back(Player::execute);
    mono->calls.push_back(Camera::execute);
    playerEntity->addComponent<Mono>(mono);

    ECS::addEntity(playerEntity);



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