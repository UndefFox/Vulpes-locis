#include "Window/include/window.h"


namespace Window {

float lastFrameTimeDuration;
std::chrono::time_point<std::chrono::system_clock> lastFrameTime = std::chrono::system_clock::now();

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
    lastFrameTimeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastFrameTime).count();
    lastFrameTime = std::chrono::system_clock::now();
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