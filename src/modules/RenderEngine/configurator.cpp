#include "configurator.h"

#include "src/valuesfactory.h"


namespace RenderEngine {

namespace {
    bool renderConfigurated = false;

    void destroyValues() {
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

        renderConfigurated = false;
    }
} // namespace <anonymous>

void initializate() {
    createVulkanInstance();
}

void terminate() {
    destroyValues();
}

void configurateRender(RenderSettings& settings) {
    if (renderConfigurated) {
        destroyValues();
    }

    setPhysicalDevice(settings.deviceId);
    window = settings.targetWindow;
    createSurface();
    createDevice();
    updateSwapchainConfiguration();
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicsPipelineLayout();
    createGraphicsPipeline(settings.vertexShaderFile, settings.fragmentShaderFile);
    createCommandPool();
    createCommandBuffer();
    createBuffers();
    createDescriptorPool();
    createDescriptorSet();
    createSyncObjects();
    createSwapchain();
    createDepthResources();
    createFramebuffers();

    renderConfigurated = true;
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