#include "ECS/include/ECS.h"

#include "ECS/include/types/entity.h"

#include <vector>


namespace ECS {

static std::vector<Entity*> entities{};

static std::vector<void (*)(Entity&)> systemsFunctionsCalls{};
static std::vector<void (*)()> systemsFunctionsPostCalls{};

    int addEntity(Entity* entity) {
        entities.push_back(entity);
        return entities.size() - 1;
    }

Entity* getEntity(int id) {
    return entities[id];
}

    void addSystemCall(void (*executionFunction)(Entity&)) {
        systemsFunctionsCalls.push_back(executionFunction);
    }

    void addSystemPostCall(void (*executionFunction)()) {
        systemsFunctionsPostCalls.push_back(executionFunction);
    }


    void execute() {

        for (int id = 0; id < entities.size(); id++) {
            Entity entity = *entities[id];

            for (int i = 0; i < systemsFunctionsCalls.size(); i++) {
                systemsFunctionsCalls[i](entity);
            }
        }


        for (int i = 0; i < systemsFunctionsPostCalls.size(); i++) {
            systemsFunctionsPostCalls[i]();
        }
        
    }

}