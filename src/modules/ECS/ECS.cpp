#include "ECS.h"

#include "entity.h"

#include "systems/systemsheaders.h"
#include "components/componentsHeaders.h"

#include <vector>
#include <array>

static std::vector<Entity*> entities;

namespace ECS {

    void addEntity(Entity* entity) {
        entities.push_back(entity);
    }



    void execute() {
        int counter = 0;

        for (int id = 0; id < entities.size(); id++) {
            Entity entity = *entities[id];

            // RenderEngine
            const static int renderEngineMask = (1 << Entity::getTypeId<Transformation>() | 1 << Entity::getTypeId<RenderData>());
            if ((entity.componentMask & renderEngineMask) == renderEngineMask) {
                RenderEngineSystem::execute(
                    entity.getComponent<Transformation>(), 
                    entity.getComponent<RenderData>()
                );
            }

            // PhysicalEngine
            const static int physicsEngineMask = (1 << Entity::getTypeId<Transformation>() | 1 << Entity::getTypeId<Physic>());
            if ((entity.componentMask & physicsEngineMask) == physicsEngineMask) {
                PhysicsEngineSystem::execute(
                    entity.getComponent<Transformation>(), 
                    entity.getComponent<Physic>()
                );
            }

            counter = 0;
        }
    }

}