#include "renderengine.h"

#include "libs/RenderEngine/renderer.h"

namespace RenderEngineSystem {

    void execute(Transformation* transform, RenderData* renderData) {
        RenderEngine::DrawCall drawCall{};
        drawCall.meshId = renderData->meshId;
        drawCall.position[0] = transform->pos.x;
        drawCall.position[1] = transform->pos.y;
        drawCall.position[2] = transform->pos.z;

        RenderEngine::addDrawCall(drawCall);
    }

}