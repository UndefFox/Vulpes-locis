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

void runSystems() {
    MonoSystem::execute();
    RenderEngineSystem::execute();
    PhysicsEngineSystem::execute();
    

    RenderEngineSystem::postExecute();
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

    Object fox = FileLoaders::loadObjectFile("./resources/models/fox.obj");
    Object plane = FileLoaders::loadObjectFile("./resources/models/plane.obj");
    Object meterCuber = FileLoaders::loadObjectFile("./resources/models/meterCube.obj");

    RenderEngine::Mesh foxMesh = TypeConverters::objectToMesh(fox);
    RenderEngine::Mesh planeMesh = TypeConverters::objectToMesh(plane);
    RenderEngine::Mesh meterCuberMesh = TypeConverters::objectToMesh(meterCuber);

    RenderEngine::addMesh(foxMesh);
    RenderEngine::addMesh(planeMesh);
    RenderEngine::addMesh(meterCuberMesh);
    

    std::array<Entity*, 9> foxes{};
    for (int i = 0; i < 9; i++) {
        foxes[i] = new Entity();

        Transformation* trans1 = new Transformation{};
        trans1->pos = { 
            static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/20.0f)),
            static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/20.0f)),
            static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/2.0f))};
        trans1->rotation = { 
            static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/360.0f)),
            static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/360.0f)),
            static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/360.0f))};
        foxes[i]->addComponent<Transformation>(trans1);

        RenderData* rend1 = new RenderData{};
        rend1->meshId = 0;
        foxes[i]->addComponent<RenderData>(rend1);

        ECS::addEntity(foxes[i]);
    }

    Entity* meterCubeEntity = new Entity{};
    
    Transformation* cubeTrans = new Transformation{};
    meterCubeEntity->addComponent<Transformation>(cubeTrans);

    RenderData* cubeRenderData = new RenderData{};
    cubeRenderData->meshId = 2;
    meterCubeEntity->addComponent<RenderData>(cubeRenderData);

    ECS::addEntity(meterCubeEntity);

    Entity* planeEntity = new Entity{};
    
    Transformation* planeTrans = new Transformation{};
    planeEntity->addComponent<Transformation>(planeTrans);

    RenderData* planeRenderData = new RenderData{};
    planeRenderData->meshId = 1;
    planeEntity->addComponent<RenderData>(planeRenderData);

    ECS::addEntity(planeEntity);

    Entity* cameraEntity = new Entity{};

    Transformation* trans3 = new Transformation{};
    trans3->pos = { 2.0f, 2.5f, 2.0f };
    cameraEntity->addComponent<Transformation>(trans3);

    Mono* monoCamera = new Mono();
    monoCamera->calls.push_back(Camera::execute);
    cameraEntity->addComponent<Mono>(monoCamera);

    int cameraEntityId = ECS::addEntity(cameraEntity);

    Entity* playerEntity = new Entity{};

    RenderData* playerRenderData = new RenderData{};
    playerRenderData->meshId = 0;
    playerEntity->addComponent<RenderData>(playerRenderData);

    Transformation* trans2 = new Transformation{};
    trans2->pos = { 2.0f, 2.0f, 0.0f };
    trans2->rotation = { 0.0f, 0.0f, 0.0f };
    playerEntity->addComponent<Transformation>(trans2);

    PlayerData* playerData = new PlayerData{};
    playerData->cameraObjectId = cameraEntityId;
    playerEntity->addComponent<PlayerData>(playerData);

    Mono* mono = new Mono{};
    mono->calls.push_back(Player::execute);

    playerEntity->addComponent<Mono>(mono);

    ECS::addEntity(playerEntity);



    #endif
}

void run() {
    while (!isGameInterupted()) {
        Window::updateWindow();

        runSystems();
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