#include "core.h"

#include "graphics/renderengine.h"
#include "world.h"

using namespace Game;

Core& Core::getInstance() {
    static Core instance;

    return instance;
}

void Core::initializate() {
    WindowController& windowController = WindowController::getInstance();
    windowController.initializate();
    windowController.createNewWindow();

    World& world = World::getInstance();
    world.initializate();

    RenderEngine& renderEngine = RenderEngine::getInstance();
    renderEngine.initializate();
}

void Core::terminate() {
    RenderEngine::getInstance().terminate();
}

void Core::run() {
    RenderEngine& engine = RenderEngine::getInstance();

    while (!isGameEnterupted()) {
        glfwPollEvents();
        engine.drawFrame();
    }
}

bool Core::isGameEnterupted() {
    return (
        glfwWindowShouldClose(WindowController::getInstance().getWindow()) // Window close signal
    );
}