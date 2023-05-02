#include "controlls.h"

#include <array>

#include "window.h"


namespace Controlls {

std::array<int, 5> realKeyIndexs = {
    GLFW_KEY_W,
    GLFW_KEY_A,
    GLFW_KEY_S,
    GLFW_KEY_D,
    GLFW_KEY_ESCAPE
};

std::array<KeyState, 5> keysState{};

ct::Vector3 mousePosition;
ct::Vector3 mousePosDelta;

ct::Vector3 getMouseDelta() {
    return mousePosDelta;
}

KeyState getKeyState(Key key) {
    return keysState[realKeyIndexs[key]];
}

void update() {
    GLFWwindow* window = Window::getWindowObject();

    double mousePosX;
    double mousePosY;

    glfwGetCursorPos(window, &mousePosX, &mousePosY);
    if (Window::isCursorLocked) {
        mousePosition = {0.5f, 0.5f, 0.0f};
        mousePosDelta = {mousePosX, mousePosY, 0.0f};
    }
    else {
        mousePosDelta = {mousePosX - mousePosition.x, mousePosY - mousePosition.y, 0.0f};
        mousePosition = {mousePosX, mousePosY, 0.0f};
    }

    for (int i = 0; i < realKeyIndexs.size(); i++) {
        glfwGetKey(window, realKeyIndexs[i]);

        int keyActualState = glfwGetKey(window, realKeyIndexs[i]);

        if (keysState[i] == KeyState::NONE) {
            if (keyActualState == GLFW_PRESS) {
                keysState[i] = KeyState::PRESS;
            }
        }
        else if (keysState[i] == KeyState::PRESS) {
            if (keyActualState == GLFW_PRESS) {
                keysState[i] = KeyState::HOLD;
            }
            else if (keyActualState == GLFW_RELEASE) {
                keysState[i] = KeyState::RELEASE;
            }
        }
        else if (keysState[i] == KeyState::HOLD) {
            if (keyActualState == GLFW_RELEASE) {
                keysState[i] = KeyState::RELEASE;
            }
        }
        else if (keysState[i] == KeyState::RELEASE) {
            if (keyActualState == GLFW_PRESS) {
                keysState[i] = KeyState::PRESS;
            }
            else if (keyActualState == GLFW_RELEASE) {
                keysState[i] = KeyState::NONE;
            }
        }
    
    }
}


}