#ifndef H_RENDERENGINE_SYSTEM
#define H_RENDERENGINE_SYSTEM

#include "../components/transformation.h"
#include "../components/renderdata.h"

namespace RenderEngineSystem {
    void execute(Transformation* transform, RenderData* renderData);
}

#endif