#ifndef H_SYSTEM_MONO
#define H_SYSTEM_MONO

#include "ECS/include/types/entity.h"

/**
 * System for executing not widly used scripts like: Player, Camera.
 */
namespace MonoSystem {

void execute(Entity& entity);

}

#endif