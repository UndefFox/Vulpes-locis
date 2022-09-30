#include "core.h"

#include <iostream>

int main() {
    
    Game::Core& core = Game::Core::getInstance();

    core.initializate();

    int x;
    std::cin >> x;

    core.terminate();  

    return 0;
}