#ifndef H_PHYSICSENGINE_SYSTEM
#define H_PHYSICSENGINE_SYSTEM

#include "ECS/components/transformation.h"
#include "ECS/components/physic.h"

namespace PhysicsEngineSystem {

    const int mask = 1 << 1;

    void execute(Transformation* transform, Physic* physics);

}

#endif