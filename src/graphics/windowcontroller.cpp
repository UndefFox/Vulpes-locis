#include "graphics/windowcontroller.h"

using namespace Game;

void WindowController::createNewWindow() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(400, 300, "Vulpes locis", nullptr, nullptr);
}

GLFWwindow* WindowController::getWindow() {
    return window;
}