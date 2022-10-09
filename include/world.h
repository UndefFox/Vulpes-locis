#ifndef H_WORLD
#define H_WORLD

#include <vector>

#include "object.h"

namespace Game {

class World {
public:
    std::vector<Object> objects;

private:


public:
    static World& getInstance();

private:
    World(){};

public:
    void initializate();
};

}

#endif