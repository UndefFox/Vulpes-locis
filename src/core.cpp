#include <GLFW/glfw3.h>

#include "RenderEngine/include/configurator.h"
#include "RenderEngine/include/renderer.h"
#include "RenderEngine/include/storage.h"

#include "ECS/include/ECS.h"
#include "systems/components/renderdata.h"
#include "systems/components/transformation.h"
#include "systems/components/mono.h"
#include "systems/components/playerData.h"
#include "systems/components/colider.h"
#include "systems/components/physicsData.h"
#include "systems/physicsengine.h"
#include "systems/renderengine.h"
#include "systems/monoSystem.h"
#include "player.h"
#include "camera.h"
#include "userInput.h"

#include "Window/include/window.h"

#include "fileLoaders.h"

#include "typeConverters.h"

#include "core.h"

#define RENDERTEST_SETUP_ON

namespace Core {

namespace {

bool isGameInterupted() {
    return Window::isWindowClosed() || UserInput::getKeyHoldDuration(KEY_ESC) > 2000.0f;
}

void runSystems() {
    //if (UserInput::getKeyState(KEY_W) == UserInput::KeyState::PRESS || UserInput::getKeyHoldDuration(KEY_W) > 200.0f) 
        
    PhysicsEngineSystem::execute();
    MonoSystem::execute();
    RenderEngineSystem::execute();
    

    RenderEngineSystem::postExecute();
}

} // namespace <anonymous>

void initializate() {
    glfwInit();
    RenderEngine::initializate();
}

void setupInitialState() {
    //ct::Vector3 test = ct::transform({-0.990329802f, 0.0853462294f, -0.109375007f}, {0.0f, 0.0f, 0.0f}, {2.47900581f, 1.43160808f, 0});

    
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

    Object sphere = FileLoaders::loadObjectFile("./resources/models/sphere.obj");
    Object plane = FileLoaders::loadObjectFile("./resources/models/meterCube.obj");
    Object meterCuber = FileLoaders::loadObjectFile("./resources/models/indexedCube.obj");
    Object planet = FileLoaders::loadObjectFile("./resources/models/plane.obj");

    RenderEngine::Mesh sphereMesh = TypeConverters::objectToMesh(sphere);
    RenderEngine::Mesh planeMesh = TypeConverters::objectToMesh(plane);
    RenderEngine::Mesh meterCuberMesh = TypeConverters::objectToMesh(meterCuber);
    RenderEngine::Mesh planeTMesh = TypeConverters::objectToMesh(planet);

    RenderEngine::addMesh(sphereMesh);
    RenderEngine::addMesh(planeMesh);
    RenderEngine::addMesh(meterCuberMesh);
    RenderEngine::addMesh(planeTMesh);
    

    Entity* cameraEntity = new Entity{};

    Transformation* trans3 = new Transformation{};
    trans3->position = { 2.0f, 2.5f, 2.0f };
    cameraEntity->addComponent<Transformation>(trans3);

    Mono* monoCamera = new Mono();
    monoCamera->calls.push_back(Camera::execute);
    cameraEntity->addComponent<Mono>(monoCamera);

    int cameraEntityId = ECS::addEntity(cameraEntity);

    Entity* playerEntity = new Entity{};

    RenderData* playerRenderData = new RenderData{};
    playerRenderData->meshId = 2;
    //playerEntity->addComponent<RenderData>(playerRenderData);

    Transformation* trans1 = new Transformation{};
    trans1->position = { 6.0f, 0.0f, 6.0f };
    trans1->rotation = { 0, 0, 0 };
    playerEntity->addComponent<Transformation>(trans1);

    PlayerData* playerData = new PlayerData{};
    playerData->cameraObjectId = cameraEntityId;
    playerEntity->addComponent<PlayerData>(playerData);

    Colider* playerColider = new BoxColider(1.0f, 1.0f, 1.0f);
    //playerEntity->addComponent<Colider>(playerColider);

    PhysicsData* playerPhys = new BoxPhys(1.0f, 1.0f, 1.0f, 1.0f);
    playerPhys->isStatic = true;
    playerPhys->aceleration = {0.0f ,0.0f , -9.8f};
    playerPhys->bouncines = 0.5f;
    playerPhys->mass = 1.0f;
    playerEntity->addComponent<PhysicsData>(playerPhys);

    Mono* mono = new Mono{};
    mono->calls.push_back(Player::execute);

    playerEntity->addComponent<Mono>(mono);

    ECS::addEntity(playerEntity);

    for (int i = 0; i < 1; i++) {
        Entity* dumyEntity = new Entity{};

        RenderData* dumyRenderData = new RenderData{};
        dumyRenderData->meshId = 2;
        dumyEntity->addComponent<RenderData>(dumyRenderData);

        Transformation* dumyTrans = new Transformation{};
        dumyTrans->position = { 6.0f, 0.0f , 6.0f };
        dumyTrans->rotation = { 0, 0, 0};
        dumyEntity->addComponent<Transformation>(dumyTrans);


        Colider* dumyBoxColider = new BoxColider(1.0f, 1.0f, 1.0f);
        dumyEntity->addComponent<Colider>(dumyBoxColider);

        PhysicsData* dumyPhys = new BoxPhys(1.0f, 1.0f, 1.0f, 1.0f);
        dumyPhys->velocity = {0.0f, 0.0f, 0.0f};
        dumyPhys->aceleration = {0.0f, 0.0f, 0.0f};
        dumyPhys->isStatic = false;
        dumyPhys->mass = 1.0f;
        dumyPhys->bouncines = 1.0f;
        dumyEntity->addComponent<PhysicsData>(dumyPhys);

        //ECS::addEntity(dumyEntity);
    }

     {
        Entity* dumyEntity = new Entity{};

        RenderData* dumyRenderData = new RenderData{};
        dumyRenderData->meshId = 1;
        dumyEntity->addComponent<RenderData>(dumyRenderData);

        Transformation* dumyTrans = new Transformation{};
        //dumyTrans->position = { std::rand() % 30 - 15.0f, std::rand() % 30 - 15.0f, 8.0f };
        dumyTrans->position = { 6.0f, -6.0f , 7.0f };
        dumyTrans->rotation = { 0,  0, 0 };
        dumyEntity->addComponent<Transformation>(dumyTrans);

        Colider* dumyBoxColider = new BoxColider(1.0f, 1.0f, 1.0f);
        dumyEntity->addComponent<Colider>(dumyBoxColider);

        PhysicsData* dumyPhys = new BoxPhys(1.0f, 1.0f, 1.0f, 1.0f);
        dumyPhys->velocity = {0.0f, 1.0f, 0.0f};
        dumyPhys->aceleration = {0.0f, 0.0f, -9.8f};
        dumyPhys->isStatic = false;
        dumyPhys->mass = 1.0f;
        dumyPhys->bouncines = 1.0f;
        dumyEntity->addComponent<PhysicsData>(dumyPhys);

        ECS::addEntity(dumyEntity);
    }

    {
        Entity* dumyEntity = new Entity{};

        RenderData* dumyRenderData = new RenderData{};
        dumyRenderData->meshId = 1;
        dumyEntity->addComponent<RenderData>(dumyRenderData);

        Transformation* dumyTrans = new Transformation{};
        //dumyTrans->position = { std::rand() % 30 - 15.0f, std::rand() % 30 - 15.0f, 8.0f };
        dumyTrans->position = { 6.0f, 6.0f , 7.0f };
        dumyTrans->rotation = { 0,  0, 0 };
        dumyEntity->addComponent<Transformation>(dumyTrans);

        Colider* dumyBoxColider = new BoxColider(1.0f, 1.0f, 1.0f);
        dumyEntity->addComponent<Colider>(dumyBoxColider);

        PhysicsData* dumyPhys = new BoxPhys(1.0f, 1.0f, 1.0f, 1.0f);
        dumyPhys->velocity = {0.0f, -1.0f, 0.0f};
        dumyPhys->aceleration = {0.0f, 0.0f, 0};
        dumyPhys->isStatic = false;
        dumyPhys->mass = 1.0f;
        dumyPhys->bouncines = 1.0f;
        dumyEntity->addComponent<PhysicsData>(dumyPhys);

        ECS::addEntity(dumyEntity);
    }
    

    Entity* dumyEntity = new Entity{};

    RenderData* sphereRenderData = new RenderData{};
    sphereRenderData->meshId = 3;
    dumyEntity->addComponent<RenderData>(sphereRenderData);

    Transformation* trans2 = new Transformation{};
    trans2->position = {0, 0, 0};
    trans2->rotation = { 0.0f, 0.0f, 0.0f };
    dumyEntity->addComponent<Transformation>(trans2);

    Colider* boxColider = new BoxColider(500.0f, 500.0f, 1.0f);
    dumyEntity->addComponent<Colider>(boxColider);

    PhysicsData* spherePhys = new BoxPhys(500.0f, 500.0f, 1.0f, 99999999.0f);
    spherePhys->isStatic = true;
    spherePhys->bouncines = 0.0f;
    spherePhys->mass = 99999999.0f;
    dumyEntity->addComponent<PhysicsData>(spherePhys);

    ECS::addEntity(dumyEntity);

    Window::setCursorLock(false);

   

    #endif
}

bool cState = true;
void run() {
    while (!isGameInterupted()) {
        Window::updateWindow();
        UserInput::updateKeyState();

        if (UserInput::getKeyState(KEY_ESC) == UserInput::KeyState::PRESS) {
            Window::setCursorLock(cState);
            cState = !cState;
        }

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