#ifndef H_WINDOW_WINDOW
#define H_WINDOW_WINDOW

#include <GLFW/glfw3.h>

namespace Window {

void createNewWindow();

void destroyWindow();

void updateWindow();

void isKeyPressed(int key);

bool isWindowClosed();

GLFWwindow* getWindowObject();

}

#endif