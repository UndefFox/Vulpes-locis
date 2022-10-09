#ifndef H_WINDOWCONTROLLER
#define H_WINDOWCONTROLLER

#include <GLFW/glfw3.h>


namespace Game {

/**
 *  Represent one window object.
 */
class WindowController {
public:

private:
    GLFWwindow* window;


public:
    static WindowController& getInstance();

private:
    WindowController(){};

public:
    void initializate();

public:
    void createNewWindow();

public:
    GLFWwindow* getWindow();

};

}

#endif