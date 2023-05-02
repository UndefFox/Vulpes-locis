#ifndef H_PHYSICSENGINE_SYSTEM
#define H_PHYSICSENGINE_SYSTEM

#include "ECS/entity.h"

/**
 * \brief A physics system.
 * 
 * Aplies physics simulation to objects in a world by resoling colision and
 * aplying physics to them.
 * 
 * \ingroup Systems
 */
namespace PhysicsSystem {

void execute();

}

#endif