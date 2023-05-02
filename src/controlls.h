#ifndef H_CONTROLLS
#define H_CONTROLLS

#include "types/vector3.h"


/**
 * \brief Contains all controlls input of the game.
 */
namespace Controlls {

enum Key {
    W,
    A,
    S,
    D,
    ESC
};

enum KeyState {
    NONE,
    PRESS,
    HOLD,
    RELEASE
};

/**
 * Returns delta of the mouse position since last update.
 */
ct::Vector3 getMouseDelta();

/**
 * Return current state of passed key.
 */
KeyState getKeyState(Key key);

/**
 * Updates state of all controlls.
 */
void update();

}

#endif