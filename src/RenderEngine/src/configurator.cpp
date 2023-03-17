#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "RenderEngine/src/include/valuesfactory.h"
#include "RenderEngine/src/include/values.h"

#include "RenderEngine/include/types/configuration.h"



#include "RenderEngine/include/configurator.h"



namespace RenderEngine {

void configurateRender(Configuration& configuration) {
    currentConfiguration = configuration;

    setPhysicalDevice();
    createSurface();
    createDevice();
    updateSwapchainConfiguration();
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicsPipelineLayout();
    createGraphicsPipeline();
    createCommandPool();
    createCommandBuffer();
    createBuffers();
    createDescriptorPool();
    createDescriptorSet();
    createSyncObjects();
    createSwapchain();
    createDepthResources();
    createFramebuffers();
}

void deconfiguryRenderer() {
    destroySwapchain();
    destroySyncObjects();
    destroyCommandPool();
    destroyDesriptorPool();
    destroyBuffers();
    destroyDepthResources();
    destroyGraphicsPipeline();
    destroyGraphicsPipelineLayout();
    destroyRenderPass();
    destroyDevice();
    destroySurface();

    vertexSavedAmount = 0;
    indexSavedAmount = 0;
    savedObjects.clear();
    lastIndex = 0;
}

void initializate() {
    createVulkanInstance();
}

void terminate() {
    destroyVulkanInstance();
}

std::vector<DeviceInfo> getDevicesSuportedWindow(GLFWwindow* window) {

    std::vector<DeviceInfo> infos{};

    VkSurfaceKHR testSurface;
    if (glfwCreateWindowSurface(vulkanInstance, window, nullptr, &testSurface) != VK_SUCCESS){
        return infos;
    }

    std::vector<VkPhysicalDevice> devices = getAvailablePhysicalDevices();
    
    for (int i = 0; i < devices.size(); i++) {
        if (minimuPhysicalDeviceCheck(devices[i], testSurface)) {
            infos.push_back({});

            VkPhysicalDeviceProperties properties{};
            vkGetPhysicalDeviceProperties(devices[i], &properties);
            
            infos.back().deviceId = properties.deviceID;
            infos.back().deviceName = properties.deviceName;
        }
    }

    vkDestroySurfaceKHR(vulkanInstance, testSurface, nullptr);

    return infos;
}


} // namespace RenderEngine