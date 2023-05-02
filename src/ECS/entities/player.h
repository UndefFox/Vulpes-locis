#ifndef H_PLAYER
#define H_PLAYER

#include "ECS/entity.h"

/**
 * \defgroup Entities
 * \brief All entities components.
 * 
 * Enity component is a component that involves
 * more complex unique bihaviour.
 * 
 * \ingroup ECS
 */

/**
 * \brief Player entity component.
 * 
 * This component for entity wich player will be
 * controlled while playing.
 * 
 * \ingroup Entities
 */
namespace Player {

void execute(Entity& enity);

}

#endif