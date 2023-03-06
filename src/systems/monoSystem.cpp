#include "monoSystem.h" 

#include "components/mono.h"

namespace MonoSystem {

namespace {

static bool isEntityCompatable(Entity& entity) {
    static const int systemMask = 
        (1 << Entity::getTypeId<Mono>());

    return (entity.componentMask & systemMask) == systemMask;
}

} // namespace <anonymous>

void execute(Entity& entity) {

    if (!isEntityCompatable(entity)) {
        return;
    }

    Mono* mono = entity.getComponent<Mono>();

    for (int i = 0; i < mono->calls.size(); i++) {
        mono->calls[i](entity);
    }
}

}