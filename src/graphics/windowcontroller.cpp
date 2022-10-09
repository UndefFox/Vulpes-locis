#include "graphics/windowcontroller.h"

using namespace Game;

WindowController& WindowController::getInstance() {
    static WindowController instance;

    return instance;
}

void WindowController::initializate() {
    glfwInit();
}

void WindowController::createNewWindow() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(400, 300, "Vulpes locis", nullptr, nullptr);
}

GLFWwindow* WindowController::getWindow() {
    return window;
}