#include "physicsengine.h"

#include "components/transformation.h"
#include "components/physic.h"

#include "ECS/include/ECS.h"

namespace PhysicsEngineSystem {

namespace {

static bool isEntityCompatable(Entity& entity) {
    static const int systemMask = 
        (1 << Entity::getTypeId<Transformation>()) |
        (1 << Entity::getTypeId<Physic>());

    return (entity.componentMask & systemMask) == systemMask;
}

} // namespace <anonymous>

void execute() {

    for (int id = 0; id < ECS::getEntityCount(); id++) {

        Entity& entity = *ECS::getEntity(id);

        if (!isEntityCompatable(entity)) {
            continue;
        }

        Transformation* transform = entity.getComponent<Transformation>();
        Physic* physics = entity.getComponent<Physic>();

        physics->velocity.z += physics->gravity;

        transform->pos.x += physics->velocity.x;
        transform->pos.y += physics->velocity.y;
        transform->pos.z += physics->velocity.z;

    }
}

}