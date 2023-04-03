#ifndef H_USER_INPUT
#define H_USER_INPUT

// Don't foget change actualId function in cpp file when changing
// key id!!!
#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3

#define KEY_SPACE 4
#define KEY_ESC 5

namespace UserInput {

enum KeyState {
    NONE,
    PRESS,
    HOLD,
    RELEASE
};

void updateKeyState();

KeyState getKeyState(int key);

float getKeyHoldDuration(int key);
}

#endif