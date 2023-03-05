#include "include/systems/physicsengine.h"

namespace PhysicsEngineSystem {

    void execute(Transformation* transform, Physic* physics) {
        physics->velocity.z += physics->gravity;

        transform->pos.x += physics->velocity.x;
        transform->pos.y += physics->velocity.y;
        transform->pos.z += physics->velocity.z;
    }

}