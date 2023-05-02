#include "player.h"

#include "ECS/ECS.h"

#include "ECS/components/playerData.h"
#include "ECS/components/transformation.h"
#include "ECS/components/physicsData.h"
#include "controlls.h"
#include "RenderEngine/renderer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define PLAYER_WALK_SPEED_MPS 0.04f
#define PLAYER_TURN_HORIZONTAL_SPEED_DPS 0.1f / 180.0f * M_PI
#define PLAYER_TURN_VERTICAL_SPEED_DPS 0.2f / 180.0f * M_PI

namespace Player {



void execute(Entity& entity) {

    PlayerData* playerData = entity.getComponent<PlayerData>();
    Entity* camera = ECS::getEntity(playerData->cameraObjectId);

    Transformation* playerTransform = entity.getComponent<Transformation>();
    PhysicsData* playerPhys = entity.getComponent<PhysicsData>();

    float timeCof = RenderEngine::lastFrameDuration / 1000.0f;

    //playerPhys->velocity.x = 0;
    //playerPhys->velocity.y = 0;

    if (Controlls::getKeyState(Controlls::Key::W) == Controlls::KeyState::HOLD) {
        playerPhys->velocity.x += PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.z);
        playerPhys->velocity.y += PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.z);
    } else if (Controlls::getKeyState(Controlls::Key::S) == Controlls::KeyState::HOLD) {
        playerPhys->velocity.x += -PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.z);
        playerPhys->velocity.y += -PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.z);
    } 
    
    if (Controlls::getKeyState(Controlls::Key::A) == Controlls::KeyState::HOLD) {
        playerPhys->velocity.x += -PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.z);
        playerPhys->velocity.y += PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.z);
    } else if (Controlls::getKeyState(Controlls::Key::D) == Controlls::KeyState::HOLD) {
        playerPhys->velocity.x += PLAYER_WALK_SPEED_MPS * std::sin(playerTransform->rotation.z);
        playerPhys->velocity.y += -PLAYER_WALK_SPEED_MPS * std::cos(playerTransform->rotation.z);
    }

    static bool faled = true;
    if (playerPhys->velocity.z < 0) {
        faled = true;
    }

    
    ct::Vector3 cursorDelta = Controlls::getMouseDelta();
    playerTransform->rotation.z -= PLAYER_TURN_HORIZONTAL_SPEED_DPS * cursorDelta.x;
    

    Transformation* cameraTransform = camera->getComponent<Transformation>();
    (*cameraTransform).position = (*playerTransform).position;
    cameraTransform->position.x -= 5.0f * std::cos(playerTransform->rotation.z);
    cameraTransform->position.y -= 5.0f * std::sin(playerTransform->rotation.z);
    cameraTransform->position.z += 2.5f * std::sin(cameraTransform->rotation.y);
    

    cameraTransform->rotation.z = playerTransform->rotation.z;
    cameraTransform->rotation.y += PLAYER_TURN_VERTICAL_SPEED_DPS * cursorDelta.y;
    cameraTransform->rotation.x = 0.0f;

}

}