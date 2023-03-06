#ifndef H_RENDERENGINE_SYSTEM
#define H_RENDERENGINE_SYSTEM

#include "ECS/include/types/entity.h"

namespace RenderEngineSystem {

void execute(Entity& entity);

void postExecute();

}

#endif