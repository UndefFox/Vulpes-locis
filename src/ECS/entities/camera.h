#ifndef H_CAMERA
#define H_CAMERA

#include "ECS/entity.h"

/**
 * \brief Camera entity component.
 * 
 * This component for entity wich will be used as
 * camera for rendering scene on draw call.
 * 
 * \ingroup Entities
 */
namespace Camera {

void execute(Entity& entity);

}

#endif