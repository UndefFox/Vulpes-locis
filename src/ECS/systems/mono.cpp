#include "mono.h" 

#include "ECS/components/mono.h"

#include "ECS/ECS.h"

namespace MonoSystem {

namespace {

static bool isEntityCompatable(Entity& entity) {
    static const int systemMask = 
        (1 << Entity::getTypeId<Mono>());

    return (entity.componentMask & systemMask) == systemMask;
}

} // namespace <anonymous>

void execute() {

    for (int id = 0; id < ECS::getEntityCount(); id++) {

        Entity& entity = *ECS::getEntity(id);

        if (!isEntityCompatable(entity)) {
            continue;
        }

        Mono* mono = entity.getComponent<Mono>();

        for (int i = 0; i < mono->calls.size(); i++) {
            mono->calls[i](entity);
        }

    }
}

}