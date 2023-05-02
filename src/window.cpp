#include "window.h"


namespace Window {

GLFWwindow* currentWindow = nullptr;
bool isCursorLocked = true;

void createNewWindow() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    currentWindow = glfwCreateWindow(1920, 1800, "Vulpes locis", nullptr, nullptr);
    
    glfwSetInputMode(currentWindow, GLFW_STICKY_KEYS, GLFW_TRUE);

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

    isCursorLocked = state;
}


GLFWwindow* getWindowObject() {
    return currentWindow;
}



}