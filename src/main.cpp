#include <GLFW/glfw3.h>
#include <vector>


#include "core.h"


int main() {

    Core::initializate();
    Core::setupInitialState();
    Core::run();
    Core::cleanup();
    Core::terminate();
    
    return 0;
}