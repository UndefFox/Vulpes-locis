#include "Window/include/window.h"


namespace Window {

float lastFrameTimeDuration;
std::chrono::time_point<std::chrono::system_clock> lastFrameTime = std::chrono::system_clock::now();

static float xMouseLastPos = 0.0f;
static float yMouseLastPos = 0.0f;

float xMouseMove = 0.0f;
float yMouseMove = 0.0f;

GLFWwindow* currentWindow = nullptr;

void createNewWindow() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    currentWindow = glfwCreateWindow(430, 200, "Vulpes locis", nullptr, nullptr);

    
    glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(currentWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
}

void destroyWindow() {
    glfwDestroyWindow(currentWindow);
    currentWindow = nullptr;
}

void updateWindow() {
    glfwPollEvents();

    lastFrameTimeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastFrameTime).count();
    lastFrameTime = std::chrono::system_clock::now();

    double xPos = 0.0f;
    double yPos = 0.0f;

    glfwGetCursorPos(currentWindow, &xPos, &yPos);

    xMouseMove = xPos - xMouseLastPos;
    yMouseMove = yPos - yMouseLastPos;

    xMouseLastPos = xPos;
    yMouseLastPos = yPos;
}

bool isKeyPressed(int key) {
    return glfwGetKey(currentWindow, key);
}

bool isWindowClosed() {
    return glfwWindowShouldClose(currentWindow);
}

void setCursorLock(bool state) {
    if (state) {
        glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (glfwRawMouseMotionSupported()) {
            glfwSetInputMode(currentWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }
    }
    else {
        glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

GLFWwindow* getWindowObject() {
    return currentWindow;
}



}