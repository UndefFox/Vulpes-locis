#include "renderengine.h"

#include "RenderEngine/include/renderer.h"

#include "components/transformation.h"
#include "components/renderdata.h"

namespace RenderEngineSystem {

namespace {

static bool isEntityCompatable(Entity& entity) {
    static const int systemMask = 
        (1 << Entity::getTypeId<Transformation>()) |
        (1 << Entity::getTypeId<RenderData>());

    return (entity.componentMask & systemMask) == systemMask;
}

} // namespace <anonymous>

void execute(Entity& entity) {

    if (!isEntityCompatable(entity)) {
        return;
    }

    Transformation* transform = entity.getComponent<Transformation>();
    RenderData* renderData = entity.getComponent<RenderData>();

    RenderEngine::DrawCall drawCall{};
    drawCall.meshId = renderData->meshId;
    drawCall.position[0] = transform->pos.x;
    drawCall.position[1] = transform->pos.y;
    drawCall.position[2] = transform->pos.z;

    RenderEngine::addDrawCall(drawCall);
}

void postExecute() {
    RenderEngine::drawFrame();
}

}