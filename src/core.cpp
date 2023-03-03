#include "core.h"

#include "RenderEngine/src/values.h"

#include "RenderEngine/storage.h"
#include "RenderEngine/configurator.h"
#include "RenderEngine/renderer.h"
#include "ECS/ECS.h"

#include "ECS/components/transformation.h"
#include "ECS/components/renderdata.h"
#include "ECS/components/physic.h"

#include "FileManager/fileLoaders.h"

#include "converters/objectToMesh.h"

#include <GLFW/glfw3.h>
#include <vector>

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


// Demonstration setup:

    Object monkey =  ObjectFormater::loadObjectFile("./resources/models/monkey.obj");

    RenderEngine::Mesh monkeyMesh = ObjectToMesh::convert(monkey);

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
}


void run() {
    while (!isGameEnterupted()) {
        glfwPollEvents();

        ECS::execute();
    }
}

void terminate() {
    RenderEngine::deconfiguryRenderer();
    RenderEngine::terminate();


    glfwDestroyWindow(window);
    glfwTerminate();
}

bool isGameEnterupted() {
    return glfwWindowShouldClose(window);
}

}