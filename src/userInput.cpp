#include "userInput.h"

#include <array>

#include <GLFW/glfw3.h>

#include "window.h"

#define KEY_COUNT 6

namespace {
    constexpr int getKeyActualId(int key) {
        const std::array<int, KEY_COUNT> actualId{
            GLFW_KEY_W,
            GLFW_KEY_A,
            GLFW_KEY_S,
            GLFW_KEY_D,
            GLFW_KEY_SPACE,
            GLFW_KEY_ESCAPE
        };

        return actualId[key];
    }
}

namespace UserInput {

static std::array<KeyState, KEY_COUNT> keyStates{};
static std::array<float, KEY_COUNT> holdDuration{};

void updateKeyState() {
    GLFWwindow* window = Window::getWindowObject();

    for (int i = 0; i < KEY_COUNT; i++) {
        int keyActualState = glfwGetKey(window, getKeyActualId(i));

        if (keyStates[i] == KeyState::NONE) {
            if (keyActualState == GLFW_PRESS) {
                keyStates[i] = KeyState::PRESS;
            }
        }
        else if (keyStates[i] == KeyState::PRESS) {
            if (keyActualState == GLFW_PRESS) {
                keyStates[i] = KeyState::HOLD;
            }
            else if (keyActualState == GLFW_RELEASE) {
                keyStates[i] = KeyState::RELEASE;
            }
        }
        else if (keyStates[i] == KeyState::HOLD) {
            if (keyActualState == GLFW_PRESS) {
                holdDuration[i] += Window::lastFrameTimeDuration;
            }
            else if (keyActualState == GLFW_RELEASE) {
                keyStates[i] = KeyState::RELEASE;
            }
        }
        else if (keyStates[i] == KeyState::RELEASE) {
            holdDuration[i] = 0.0f;

            if (keyActualState == GLFW_PRESS) {
                keyStates[i] = KeyState::PRESS;
            }
            else if (keyActualState == GLFW_RELEASE) {
                keyStates[i] = KeyState::NONE;
            }
        }
    }
}

KeyState getKeyState(int key) {
    return keyStates[key];
}

float getKeyHoldDuration(int key) {
    return holdDuration[key];
}

}