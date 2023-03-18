#include "player.h"

#include "ECS/include/ECS.h"

#include "systems/components/playerData.h"
#include "systems/components/transformation.h"
#include "Window/include/window.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define PLAYER_WALK_SPEED_MPS 15.0f
#define PLAYER_TURN_SPEED_DPS 180.0f

namespace Player {



void execute(Entity& entity) {

    PlayerData* playerData = entity.getComponent<PlayerData>();
    Entity* camera = ECS::getEntity(playerData->cameraObjectId);

    Transformation* playerTransform = entity.getComponent<Transformation>();

    float timeCof = Window::lastFrameTimeDuration / 1000.0f;

    

    if (Window::isKeyPressed(GLFW_KEY_W)) {
        playerTransform->velocity.x = PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->velocity.y = PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    } else if (Window::isKeyPressed(GLFW_KEY_S)) {
        playerTransform->velocity.x = -PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->velocity.y = -PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    } else {
        playerTransform->velocity.x = 0;
        playerTransform->velocity.y = 0;
    }

    static bool faled = true;
    if (playerTransform->velocity.z < 0) {
        faled = true;
    }

    if (Window::isKeyPressed(GLFW_KEY_SPACE) && faled && std::abs(playerTransform->velocity.z) < 0.1f) {
        playerTransform->velocity.z = 20.0f;
        faled = false;
    }

    if (Window::isKeyPressed(GLFW_KEY_A)) {
        playerTransform->rotation.yaw += PLAYER_TURN_SPEED_DPS * timeCof;
    } else if (Window::isKeyPressed(GLFW_KEY_D)) {
        playerTransform->rotation.yaw -= PLAYER_TURN_SPEED_DPS * timeCof;
    }

    Transformation* cameraTransform = camera->getComponent<Transformation>();
    *cameraTransform = *playerTransform;
    cameraTransform->pos.x -= 3.0f * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
    cameraTransform->pos.y -= 3.0f * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    cameraTransform->pos.z += 2.5f;
    

    cameraTransform->rotation.yaw = playerTransform->rotation.yaw;

}

}