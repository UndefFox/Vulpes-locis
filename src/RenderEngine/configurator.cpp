#include "configurator.h"

#include "src/valuesfactory.h"
#include "src/values.h"


namespace RenderEngine {

void configurateRender(Configuration& settings) {
    setPhysicalDevice(settings.deviceId);
    window = settings.window;
    createSurface();
    createDevice();
    updateSwapchainConfiguration();
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicsPipelineLayout();
    createGraphicsPipeline(settings.verticesShaderPath, settings.fragmentShaderPath);
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

std::vector<DeviceInfo> getAvailableDevices(GLFWwindow* window) {

    VkSurfaceKHR testSurface;
    glfwCreateWindowSurface(vulkanInstance, window, nullptr, &testSurface);

    std::vector<VkPhysicalDevice> devices =  getAvailablePhysicalDevices();
    std::vector<DeviceInfo> infos{};
    for (int i = 0; i < devices.size(); i++) {
        if (minimuPhysicalDeviceCheck(devices[i], testSurface)) {
            infos.push_back({});

            VkPhysicalDeviceProperties properties{};
            vkGetPhysicalDeviceProperties(devices.back(), &properties);
            
            infos.back().deviceId = properties.deviceID;
            infos.back().deviceName = properties.deviceName;
        }
    }

    vkDestroySurfaceKHR(vulkanInstance, testSurface, nullptr);

    return infos;
}


} // namespace RenderEngine