#include "core.h"

#include "modules/RenderEngine/src/values.h"

#include "modules/RenderEngine/storage.h"
#include "modules/RenderEngine/configurator.h"
#include "modules/RenderEngine/renderer.h"
#include "modules/ECS/ECS.h"

#include "modules/ECS/components/transformation.h"
#include "modules/ECS/components/renderdata.h"
#include "modules/ECS/components/physic.h"

#include "modules/FileManager/formaters/object.h"

#include "converters/objectToMesh.h"

#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <array>

const std::vector<std::array<float, 5>> vertices1 = {
    {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f},
    {0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
    {-0.5f, 0.5f, 0.0f, 1.0f, 0.0f},
    {0.5f, 0.5f, 0.0f, 1.0f, 1.0f}
};

const std::vector<uint16_t> indices1 = {
    0, 1, 2, 1, 2, 3
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


    


    Object cube =  ObjectFormater::loadObjectFile("./objects/monkey.obj");

    RenderEngine::Mesh cubeMesh = ObjectToMesh::convert(cube);

    RenderEngine::addMesh(cubeMesh);
}


void run() {

    Entity* first = new Entity{};

    Transformation* trans1 = new Transformation{};
    trans1->pos = { 1.0f, 0.0f, 0.3f };
    first->addComponent<Transformation>(trans1);

    RenderData* rend1 = new RenderData{};
    rend1->meshId = 0;
    first->addComponent<RenderData>(rend1);

    Entity* second = new Entity{};

    Transformation* trans2 = new Transformation{};
    trans2->pos = { 0.0f, 0.0f, 0.0f };
    second->addComponent<Transformation>(trans2);

    RenderData* rend2 = new RenderData{};
    rend2->meshId = 1;
    second->addComponent<RenderData>(rend2);

    Physic* phys2 = new Physic{};
    phys2->gravity = -9.8f / 10000.0f;
    phys2->velocity.z = 0.10f;
    //second->addComponent<Physic>(phys2);

    //ECS::addEntity(first);
    ECS::addEntity(second);

    while (!isGameEnterupted()) {
        glfwPollEvents();

        ECS::execute();
    }
}

bool isGameEnterupted() {
    return glfwWindowShouldClose(window);
}

}