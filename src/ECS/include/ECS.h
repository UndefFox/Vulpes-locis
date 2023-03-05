#ifndef H_ECS
#define H_ECS

#include "types/entity.h"

namespace ECS {

    /**
     * Adds entity to system.
     */
    void addEntity(Entity* entity);

    /**
     * Procceds all entityes to systems.
     */
    void execute();

}

#endif