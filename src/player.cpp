#include "player.h"

#include "ECS/include/ECS.h"

#include "systems/components/playerData.h"
#include "systems/components/transformation.h"
#include "Window/include/window.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define PLAYER_WALK_SPEED_MPS 15.0f
#define PLAYER_TURN_HORIZONTAL_SPEED_DPS 0.5f
#define PLAYER_TURN_VERTICAL_SPEED_DPS 0.2f

namespace Player {



void execute(Entity& entity) {

    PlayerData* playerData = entity.getComponent<PlayerData>();
    Entity* camera = ECS::getEntity(playerData->cameraObjectId);

    Transformation* playerTransform = entity.getComponent<Transformation>();

    float timeCof = Window::lastFrameTimeDuration / 1000.0f;

    playerTransform->velocity.x = 0;
    playerTransform->velocity.y = 0;

    if (Window::isKeyPressed(GLFW_KEY_W)) {
        playerTransform->velocity.x += PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->velocity.y += PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    } else if (Window::isKeyPressed(GLFW_KEY_S)) {
        playerTransform->velocity.x += -PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->velocity.y += -PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    } 
    
    if (Window::isKeyPressed(GLFW_KEY_A)) {
        playerTransform->velocity.x += -PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->velocity.y += PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
    } else if (Window::isKeyPressed(GLFW_KEY_D)) {
        playerTransform->velocity.x += PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
        playerTransform->velocity.y += -PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
    }

    static bool faled = true;
    if (playerTransform->velocity.z < 0) {
        faled = true;
    }

    if (Window::isKeyPressed(GLFW_KEY_SPACE) && faled && std::abs(playerTransform->velocity.z) < 0.1f) {
        playerTransform->velocity.z = 20.0f;
        faled = false;
    }

    
    playerTransform->rotation.yaw -= PLAYER_TURN_HORIZONTAL_SPEED_DPS * Window::xMouseMove;
    

    Transformation* cameraTransform = camera->getComponent<Transformation>();
    (*cameraTransform).pos = (*playerTransform).pos;
    cameraTransform->pos.x -= 5.0f * std::cos(playerTransform->rotation.yaw / 180.0f * M_PI);
    cameraTransform->pos.y -= 5.0f * std::sin(playerTransform->rotation.yaw / 180.0f * M_PI);
    cameraTransform->pos.z += 2.5f + 2.5f * std::sin(cameraTransform->rotation.pitch / 180 * M_PI);
    

    cameraTransform->rotation.yaw = playerTransform->rotation.yaw;
    cameraTransform->rotation.pitch += PLAYER_TURN_VERTICAL_SPEED_DPS * Window::yMouseMove;
    cameraTransform->rotation.roll = 0.0f;

}

}