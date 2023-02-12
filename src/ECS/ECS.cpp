#include "ECS.h"

#include "entity.h"

#include "systems/renderengine.h"
#include "systems/physicsengine.h"

#include <vector>
#include <array>

static std::vector<Entity*> entities;

namespace ECS {

    void addEntity(Entity* entity) {
        entities.push_back(entity);
    }


    

    namespace {
        struct ComponentCell {
            int entityId = -1;
            int componentId = -1;
        };

        
        static int typesCount = 0;

        template <typename T>
        int getTypeCellId() {
            const static int cellId = typesCount++;
            return cellId;
        }
    }

    void execute() {
        std::array<ComponentCell, 10> componentCells{};
        int counter = 0;

        for (int id = 0; id < entities.size(); id++) {
            Entity entity = *entities[id];

            if (entity.mask & RenderEngineSystem::mask) {
                ComponentCell& transformCell = componentCells[getTypeCellId<Transformation>()];
                ComponentCell& renderCell = componentCells[getTypeCellId<RenderData>()];

                if (transformCell.entityId != id) {
                    transformCell.entityId = id;
                    transformCell.componentId = counter++;
                }
                if (renderCell.entityId != id) {
                    renderCell.entityId = id;
                    renderCell.componentId = counter++;
                }

                RenderEngineSystem::execute(
                    (Transformation*) entity.components[transformCell.componentId], 
                    (RenderData*) entity.components[renderCell.componentId]);
            }

            if (entity.mask & PhysicsEngineSystem::mask) {
                ComponentCell& transformCell = componentCells[getTypeCellId<Transformation>()];
                ComponentCell& physicCell = componentCells[getTypeCellId<Physic>()];

                if (transformCell.entityId != id) {
                    transformCell.entityId = id;
                    transformCell.componentId = counter++;
                }
                if (physicCell.entityId != id) {
                    physicCell.entityId = id;
                    physicCell.componentId = counter++;
                }

                PhysicsEngineSystem::execute(
                    (Transformation*) entity.components[transformCell.componentId], 
                    (Physic*) entity.components[physicCell.componentId]);
            }

            counter = 0;
        }
    }

}