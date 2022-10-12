#include "world.h"

using namespace Game;

World& World::getInstance() {
    static World instance;

    return instance;
}

void World::initializate() {
    objects.resize(2);

    objects[0].position = {1, 0, 0};
    objects[1].position = {0, 1, 0};

    objects[0].rotation = {45.0f, 0.0f, 0.0f};
}


