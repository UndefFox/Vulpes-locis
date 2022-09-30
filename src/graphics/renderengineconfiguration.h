#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>
#include <vector>

#include "graphics/windowcontroller.h"

namespace Game {

/**
 *  Contain set of values and their management wich engine using for render.
 */
class RenderEngineConfiguration {
public:
    VkInstance v_instance;
    WindowController v_windowController;
    VkSurfaceKHR v_surface;
    VkPhysicalDevice v_physicalDevice;
    VkDevice v_device;
    VkSwapchainKHR v_swapchain;
    std::vector<VkImage> v_swapchainImages;

    // Queue variable
    uint32_t v_graphicFamilyIndex;
    uint32_t v_presentationFamilyIndex;
    VkQueue v_graphicsQueue;
    VkQueue v_presentQueue;
    
    // Swapchain details
    VkFormat v_swapchainFormat;
    VkExtent2D v_swapchainExtent;

private:
    const std::vector<const char*> EXTENSIONS = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };


public:
    void initializate();

public:
    void destroy();

private:
    /**
     * Create new Vkinstance.
     * 
     * Result stored in @ref RenderEngineConfiguration::v_instance "v_instance" variable.
     */
    void createVkInstance();

private:
    /**
     * Create new surface for window stored in @ref RenderEngineConfiguration::v_windowcontroller "v_windowcontroller".
     * 
     * Result stored in @ref RenderEngineConfiguration::v_surface "v_surface".
     */
    void createSurface();

private:
    /**
     * Choose first suitable device for current configuration.
     * 
     * Result stored in @ref RenderEngineConfiguration::v_physicalDevice "v_physicalDevice".
     */
    void choosePhysicalDevice();
    
private:
    /**
     * Choose qeueus families for work.
     * 
     * @param device device for wich need find queues.
     * 
     * @return true if manage to find all needed queues.
     */
    bool chooseQueues(VkPhysicalDevice& device);

private:
    /**
     * Creating device for choosen physcial device and queues.
     * 
     * Result stored in @ref RenderEngineConfiguration::v_device "v_device".
     */
    void createDevice();

private:
    /**
     * Creating queues object from device.
     */
    void createQueuesObjects();

private:
    /**
     * 
     */
    void createSwapchain();
};

} // namespace Game