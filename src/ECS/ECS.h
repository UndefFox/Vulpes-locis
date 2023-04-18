#ifndef H_ECS
#define H_ECS

#include "entity.h"

namespace ECS {

    /**
     * Adds entity to system.
     */
    int addEntity(Entity* entity);

    /**
     * Retunr entity by ID.
     */
    Entity* getEntity(int id);

    int getEntityCount();

}

#endif