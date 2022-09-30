#include "graphics/renderengine.h"

using namespace Game;

RenderEngine& RenderEngine::getInstance() {
    static RenderEngine instance;

    return instance;
}

void RenderEngine::initializate() {
    glfwInit();

    config.initializate();
}

void RenderEngine::terminate() {
    config.destroy();

    glfwTerminate();
}
