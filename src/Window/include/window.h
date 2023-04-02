#ifndef H_WINDOW_WINDOW
#define H_WINDOW_WINDOW


#include <GLFW/glfw3.h>
#include <chrono>


/**
 * @brief Static window.
 * 
 * This class is wrapper around GLFW library for abstraction.
 */
namespace Window {

extern float lastFrameTimeDuration;
extern std::chrono::time_point<std::chrono::system_clock> lastFrameTime;

extern float xMouseMove;
extern float yMouseMove;

/**
 * Creates new widnow with preseted settings.
 */
void createNewWindow();

/**
 * Destroying current window and nulling its pointer.
 */
void destroyWindow();

/**
 * Polls all windows events and updates state.
 */
void updateWindow();

/**
 * Checks if key is pressed. Info about key press
 * updating on updateWindow() call.
 */
bool isKeyPressed(int key);

/**
 * Checks if window recived a close call.
 */
bool isWindowClosed();

/**
 * Change state of cursor locking. If true set, then cursor will be locked to the window.
 */
void setCursorLock(bool state);

/**
 * Return object of a the current widnow.
 */
GLFWwindow* getWindowObject();

}

#endif