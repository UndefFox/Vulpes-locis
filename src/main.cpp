#include "core.h"

#include <iostream>

int main() {
    
    Game::Core& core = Game::Core::getInstance();

    core.initializate();
    core.run();

    core.terminate();  

    return 0;
}