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
    void createNewWindow();

public:
    GLFWwindow* getWindow();

};

}