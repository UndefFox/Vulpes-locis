#include "core.h"

int main() {

    Core::initializate();
    Core::setupInitialState();
    Core::run();
    Core::cleanup();
    Core::terminate();
    
    return 0;
}