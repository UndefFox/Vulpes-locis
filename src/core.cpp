#include "core.h"

using namespace Game;

Core& Core::getInstance() {
    static Core instance;

    return instance;
}

void Core::initializate() {
    RenderEngine::getInstance().initializate();

}

void Core::terminate() {
    RenderEngine::getInstance().terminate();
}