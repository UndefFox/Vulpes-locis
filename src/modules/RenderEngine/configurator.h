#ifndef H_RENDERENGINE_CONFIGURATOR
#define H_RENDERENGINE_CONFIGURATOR

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>


namespace RenderEngine {

struct RenderSettings {
    /**
     * Id of the device that must be used for render.
     */
    uint32_t deviceId;

    /**
     * Window on wich rendered images will be presented. 
     */
    GLFWwindow* targetWindow;

    std::string vertexShaderFile;
    std::string fragmentShaderFile;
};

/**
 * Info about graphical device.
 */
struct DeviceInfo {
    /**
     * Uniqiue id that device have.
     */
    uint32_t deviceId;

    /**
     * Offical device name.
     */
    std::string deviceName;
};

/**
 * Innitializing all components of library for work. Must be run 
 * before anything else.
 */
void initializate();
    
/**
 * Terminating all components and freeing all resources memory.
 */
void terminate();


/**
 * Configuring rendder acording to settings. 
 * 
 * @param settings Settings for wich render engine will be configurated.
 */
void configurateRender(RenderSettings& settings);

/**
 * Deinitializating all render systems. If rendered is already configured, must be
 * executed before calling configurateRender another time.
 */
void deconfiguryRenderer();

/**
 * Returns all devices that can atleast run game.
 * 
 * @returns Array of all available devices.
 */
std::vector<DeviceInfo> getAvailableDevices(GLFWwindow* window);


} // namespace RenderEngine

#endif