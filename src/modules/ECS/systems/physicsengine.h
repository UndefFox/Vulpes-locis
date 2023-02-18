#ifndef H_PHYSICSENGINE_SYSTEM
#define H_PHYSICSENGINE_SYSTEM

#include "../components/transformation.h"
#include "../components/physic.h"

namespace PhysicsEngineSystem {

    const int mask = 1 << 1;

    void execute(Transformation* transform, Physic* physics);

}

#endif