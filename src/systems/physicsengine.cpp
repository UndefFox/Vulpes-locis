#include "physicsengine.h"

#include "components/transformation.h"
#include "components/colider.h"

#include "ECS/include/ECS.h"
#include "Window/include/window.h"

#include <math.h>

namespace PhysicsEngineSystem {

namespace {

static bool isEntityCompatable(Entity& entity) {
    static const int systemMask = 
        (1 << Entity::getTypeId<Transformation>()) |
        (1 << Entity::getTypeId<Colider>());

    return (entity.componentMask & systemMask) == systemMask;
}

} // namespace <anonymous>

void execute() {

    std::vector<int> proccededObjects;

    for (int id = 0; id < ECS::getEntityCount(); id++) {

        Entity& entity = *ECS::getEntity(id);

        if (!isEntityCompatable(entity)) {
            continue;
        }

        Transformation* transform = entity.getComponent<Transformation>();
        Colider* colider = entity.getComponent<Colider>();

        if (!transform->isStatic) {

            float cof = Window::lastFrameTimeDuration / 1000.0f;

            transform->velocity.z -= 9.8f * cof;

            transform->pos.x += transform->velocity.x * cof;
            transform->pos.y += transform->velocity.y * cof;
            transform->pos.z += transform->velocity.z * cof;
        
        }

        proccededObjects.push_back(id);

    }



    for (int x : proccededObjects) {

        Transformation* transformX = ECS::getEntity(x)->getComponent<Transformation>();
        Colider* coliderX = ECS::getEntity(x)->getComponent<Colider>();

        for (int y : proccededObjects) {

            if (x == y) {
                continue;
            }

            Transformation* transformY = ECS::getEntity(y)->getComponent<Transformation>();
            Colider* coliderY = ECS::getEntity(y)->getComponent<Colider>();

            if (coliderX->type == ColiderType::Box && coliderY->type == ColiderType::Box) {
                if (
                    std::abs(transformX->pos.x - transformY->pos.x) < coliderX->xSize + coliderY->xSize &&
                    std::abs(transformX->pos.y - transformY->pos.y) < coliderX->ySize + coliderY->ySize &&
                    std::abs(transformX->pos.z - transformY->pos.z) < coliderX->zSize + coliderY->zSize
                ) {

                    float biggestConf = -1.0f;
                    float cof = 0.0f;
                    int cord = 0;

                    if (transformX->velocity.x != 0) {
                        cof = -std::abs(((coliderX->xSize + coliderY->xSize) - std::abs(transformX->pos.x - transformY->pos.x)) / transformX->velocity.x);
                        if (cof > biggestConf) {
                            biggestConf = cof;
                            cord = 0;
                        }
                    }
                    if (transformX->velocity.y != 0) {
                        cof = -std::abs(((coliderX->ySize + coliderY->ySize) - std::abs(transformX->pos.y - transformY->pos.y)) / transformX->velocity.y);
                        if (cof > biggestConf) {
                            biggestConf = cof;
                            cord = 1;
                        }
                    }
                    if (transformX->velocity.z != 0) {
                        cof = -std::abs(((coliderX->zSize + coliderY->zSize) - std::abs(transformX->pos.z - transformY->pos.z)) / transformX->velocity.z);
                        if (cof > biggestConf) {
                            biggestConf = cof;
                            cord = 2;
                        }
                    }

                    
                    
                    

                    if (cord == 0) {
                        transformX->pos.x += transformX->velocity.x * biggestConf;
                        transformX->velocity.x = 0;
                    } else if (cord == 1) {
                        transformX->pos.y += transformX->velocity.y * biggestConf;
                        transformX->velocity.y = 0;
                    } else if (cord == 2) {
                        transformX->pos.z += transformX->velocity.z * biggestConf;
                        transformX->velocity.z = 0;
                    }

                }
            }
        }
    }

    proccededObjects.clear();
}

}