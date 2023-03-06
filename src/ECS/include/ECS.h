#ifndef H_ECS
#define H_ECS

#include "types/entity.h"

namespace ECS {

    /**
     * Adds entity to system.
     */
    void addEntity(Entity* entity);

    /**
     * Adding system function call to proceed entities.
     * 
     * @param executionFunction Pointer to a function of that format: void execution(Entity& entity);
     * function must take Entity as param, check if it's have needed components.
     */
    void addSystemCall(void (*executionFunction)(Entity&));

    /**
     * Adding system function call to call after all entities were processed.
     */
    void addSystemPostCall(void (*executionFunction)());

    /**
     * Procceds all entityes to systems.
     */
    void execute();

}

#endif