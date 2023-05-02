#ifndef H_RENDERENGINE_CONFIGURATOR
#define H_RENDERENGINE_CONFIGURATOR

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "types/configuration.h"
#include "types/deviceInfo.h"

/**
 * \file
 * \brief All functionality for configuring render.
 * 
 * Implements all functionality for configuring render like resolution,
 * presentaion target, render settings and etc.
 * 
 * \ingroup RenderInterface
 */

namespace RenderEngine {

/**
 * Initializing module. Before calling glfwInit() must be executed.
 * Must be run once before usage. 
 */
void initializate();
    
/**
 * Terminating module. Must be run after ending usage.
 */
void terminate();

/**
 * Returns all devices that can work with the given window.
 * 
 * @returns Array of all available devices.
 */
std::vector<DeviceInfo> getDevicesSuportedWindow(GLFWwindow* window);



/**
 * Configuring rendder acording to settings. If render were already configurated, deconfiguryRender must be
 * called before executing again.
 * 
 * @param settings Settings for wich render engine will be configurated.
 */
void configurateRender(Configuration& settings);

/**
 * Deinitializating all render systems. If rendered is already configured, must be
 * executed before calling configurateRender another time.
 */
void deconfiguryRenderer();




} // namespace RenderEngine

#endif