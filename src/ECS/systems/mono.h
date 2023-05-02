#ifndef H_SYSTEM_MONO
#define H_SYSTEM_MONO

#include "ECS/entity.h"

/**
 * \brief A mono system.
 * 
 * Executes more complex bihaviour. Moslty used for executing
 * entity components.
 * 
 * \ingroup Systems
 */
namespace MonoSystem {

void execute();

}

#endif