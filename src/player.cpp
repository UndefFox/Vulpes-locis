#include "player.h"

#include "ECS/include/ECS.h"

#include "systems/components/playerData.h"
#include "systems/components/transformation.h"
#include "Window/include/window.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define PLAYER_WALK_SPEED 0.1f
#define PLAYER_TURN_SPEED 5.0f

namespace Player {

void execute(Entity& entity) {

    PlayerData* playerData = entity.getComponent<PlayerData>();
    Entity* camera = ECS::getEntity(playerData->cameraObjectId);

    Transformation* playerTransform = entity.getComponent<Transformation>();
    if (Window::isKeyPressed(GLFW_KEY_W)) {
        playerTransform->pos.x += PLAYER_WALK_SPEED * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->pos.y += PLAYER_WALK_SPEED * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    } else if (Window::isKeyPressed(GLFW_KEY_S)) {
        playerTransform->pos.x -= PLAYER_WALK_SPEED * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->pos.y -= PLAYER_WALK_SPEED * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    }

    if (Window::isKeyPressed(GLFW_KEY_A)) {
        playerTransform->rotation.yaw += PLAYER_TURN_SPEED;
    } else if (Window::isKeyPressed(GLFW_KEY_D)) {
        playerTransform->rotation.yaw -= PLAYER_TURN_SPEED;
    }

    Transformation* cameraTransform = camera->getComponent<Transformation>();
    *cameraTransform = *playerTransform;
    cameraTransform->pos.z += 0.5f;

    cameraTransform->rotation.yaw = playerTransform->rotation.yaw;

}

}