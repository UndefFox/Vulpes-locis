#include "Window/include/window.h"

#include <GLFW/glfw3.h>

namespace Window {

GLFWwindow* currentWindow = nullptr;

void createNewWindow() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    currentWindow = glfwCreateWindow(430, 200, "Vulpes locis", nullptr, nullptr);
}

void destroyWindow() {
    glfwDestroyWindow(currentWindow);
    currentWindow = nullptr;
}

void updateWindow() {
    glfwPollEvents();
}

bool isKeyPressed(int key) {
    return glfwGetKey(currentWindow, key);
}

bool isWindowClosed() {
    return glfwWindowShouldClose(currentWindow);
}

GLFWwindow* getWindowObject() {
    return currentWindow;
}



}