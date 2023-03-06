#include "camera.h"

#include <array>

#include "RenderEngine/include/renderer.h"
#include "systems/components/transformation.h"

namespace Camera {

void execute(Entity& entity) {

    Transformation* transformation = entity.getComponent<Transformation>();

    std::array<float, 3> pos = {
        transformation->pos.x,
        transformation->pos.y,
        transformation->pos.z
    };

    std::array<float, 3> rotation = {
        transformation->rotation.roll,
        transformation->rotation.pitch,
        transformation->rotation.yaw
    };

    RenderEngine::setCamera(pos, rotation);

}

}