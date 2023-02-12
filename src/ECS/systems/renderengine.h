#ifndef H_RENDERENGINE_SYSTEM
#define H_RENDERENGINE_SYSTEM

#include "ECS/components/transformation.h"
#include "ECS/components/renderdata.h"

namespace RenderEngineSystem {
    const int mask = 1 << 0;

    void execute(Transformation* transform, RenderData* renderData);
}

#endif