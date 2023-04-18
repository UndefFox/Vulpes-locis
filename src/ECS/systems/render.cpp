#include "render.h"

#include "RenderEngine/renderer.h"

#include "ECS/components/transformation.h"
#include "ECS/components/renderdata.h"

#include "ECS/ECS.h"

namespace RenderSystem {

namespace {

static bool isEntityCompatable(Entity& entity) {
    static const int systemMask = 
        (1 << Entity::getTypeId<Transformation>()) |
        (1 << Entity::getTypeId<RenderData>());

    return (entity.componentMask & systemMask) == systemMask;
}

} // namespace <anonymous>

void execute() {

    for (int id = 0; id < ECS::getEntityCount(); id++) {

        Entity& entity = *ECS::getEntity(id);

        if (!isEntityCompatable(entity)) {
            continue;
        }

        Transformation* transform = entity.getComponent<Transformation>();
        RenderData* renderData = entity.getComponent<RenderData>();

        RenderEngine::DrawCall drawCall{};
        drawCall.meshId = renderData->meshId;
        drawCall.position[0] = transform->position.x;
        drawCall.position[1] = transform->position.y;
        drawCall.position[2] = transform->position.z;
        drawCall.rotation[0] = transform->rotation.x;
        drawCall.rotation[1] = transform->rotation.y;
        drawCall.rotation[2] = transform->rotation.z;

        RenderEngine::addDrawCall(drawCall);

    }
}

void postExecute() {
    RenderEngine::drawFrame();
}

}