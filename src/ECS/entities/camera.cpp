#include "camera.h"

#include <array>

#include "RenderEngine/renderer.h"
#include "ECS/components/transformation.h"

namespace Camera {

void execute(Entity& entity) {

    Transformation* transformation = entity.getComponent<Transformation>();

    std::array<float, 3> pos = {
        transformation->position.x,
        transformation->position.y,
        transformation->position.z
    };

    std::array<float, 3> rotation = {
        transformation->rotation.x,
        transformation->rotation.y,
        transformation->rotation.z
    };

    RenderEngine::setCamera(pos, rotation);

}

}