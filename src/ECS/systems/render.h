#ifndef H_RENDERENGINE_SYSTEM
#define H_RENDERENGINE_SYSTEM

#include "ECS/entity.h"

/**
 * \defgroup Systems
 * \brief All systems of ECS.
 * 
 * System is what implements various bihaviour of entityes dependings
 * on it's components. On execute call must proceed all entities with
 * required signature.
 * 
 * \ingroup ECS
 */

/**
 * \brief Render system.
 * 
 * Procceds all entityes to be rendered on a screen.
 * 
 * \ingroup Systems
 */
namespace RenderSystem {

void execute();

void postExecute();

}

#endif