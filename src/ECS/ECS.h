#ifndef H_ECS
#define H_ECS

#include "entity.h"

/**
 * \defgroup ECS
 * \brief Entity Component System
 */

/**
 * \brief Contain all ECS system components.
 * \ingroup ECS
 */
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