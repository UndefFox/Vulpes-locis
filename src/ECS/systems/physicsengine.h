#ifndef H_PHYSICSENGINE_SYSTEM
#define H_PHYSICSENGINE_SYSTEM

#include "../components/transformation.h"
#include "../components/physic.h"

namespace PhysicsEngineSystem {

    void execute(Transformation* transform, Physic* physics);

}

#endif