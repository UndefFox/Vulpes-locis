#include "ECS.h"

#include "entity.h"

// All systems headers
#include "systems/physicsengine.h"
#include "systems/renderengine.h"

// All components headers
#include "components/physic.h"
#include "components/renderdata.h"
#include "components/transformation.h"

#include "RenderEngine/renderer.h"

#include <vector>
#include <array>

static std::vector<Entity*> entities;

namespace ECS {

    void addEntity(Entity* entity) {
        entities.push_back(entity);
    }



    void execute() {

        for (int id = 0; id < entities.size(); id++) {
            Entity entity = *entities[id];

            // RenderEngine
            const int renderEngineMask = (1 << Entity::getTypeId<Transformation>() | 1 << Entity::getTypeId<RenderData>());
            if ((entity.componentMask & renderEngineMask) == renderEngineMask) {
                RenderEngineSystem::execute(
                    entity.getComponent<Transformation>(), 
                    entity.getComponent<RenderData>()
                );
            }
            
            

            // PhysicalEngine
            const int physicsEngineMask = (1 << Entity::getTypeId<Transformation>() | 1 << Entity::getTypeId<Physic>());
            if ((entity.componentMask & physicsEngineMask) == physicsEngineMask) {
                PhysicsEngineSystem::execute(
                    entity.getComponent<Transformation>(), 
                    entity.getComponent<Physic>()
                );
            }

        }

        RenderEngine::drawFrame();

        
    }

}