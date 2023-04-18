#include "ECS.h"

#include "entity.h"

#include <vector>


namespace ECS {

static std::vector<Entity*> entities{};

int addEntity(Entity* entity) {
    entities.push_back(entity);
    return entities.size() - 1;
}

Entity* getEntity(int id) {
    return entities[id];
}

int getEntityCount() {
    return entities.size();
}


}