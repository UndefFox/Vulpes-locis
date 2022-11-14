#include "core.h"

#include "RenderEngine/configurator.h"
#include "RenderEngine/renderengine.h"

namespace Core {


void initializate() {
    RenderEngine::Configurator::initializate();

    RenderEngine::Configurator::RenderSettings settings;
    settings.deviceId = 0;

    RenderEngine::Configurator::configurateRender(settings);

    RenderEngine::initializate();
    
}

void run() {

    while (!isGameEnterupted()) {
        glfwPollEvents();
        RenderEngine::drawFrame();
    }
}

bool isGameEnterupted() {
    return false;
}

}