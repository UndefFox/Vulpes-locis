#include "configurator.h"

#include "private/values.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace RenderEngine::Configurator {


void initializate() {
    glfwInit();

    Values::createVulkanInstance();
    Values::createWindow();
}

void terminate() {
    Values::destroySwapchain();
    Values::destroySyncObjects();
    Values::destroyCommandPool();
    Values::destroyDesriptorPool();
    Values::destroyBuffers();
    Values::destroyDepthResources();
    Values::destroyGraphicsPipeline();
    Values::destroyGraphicsPipelineLayout();
    Values::destroyRenderPass();
    Values::destroyDevice();

    // TODO: free components from others modules.
}

void configurateRender(RenderSettings& settings) {
    Values::setPhysicalDevice(settings.deviceId);
    Values::createDevice();
    Values::updateSwapchainConfiguration();
    Values::createRenderPass();
    Values::createDescriptorSetLayout();
    Values::createGraphicsPipelineLayout();
    Values::createGraphicsPipeline();
    Values::createCommandPool();
    Values::createCommandBuffer();
    Values::createBuffers();
    Values::createDescriptorPool();
    Values::createDescriptorSet();
    Values::createSyncObjects();
    Values::createSwapchain();
    Values::createDepthResources();
    Values::createFramebuffers();
    // TODO: Orginize things a little bit..
}

std::vector<DeviceInfo> getAvailableDevices() {

    std::vector<VkPhysicalDevice> devices = Values::getAvailablePhysicalDevices();
    std::vector<DeviceInfo> infos(devices.size());
    for (int i = 0; i < devices.size(); i++) {
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(devices[i], &properties);
        
        infos[i].deviceId = properties.deviceID;
        infos[i].deviceName = properties.deviceName;
    }

    return infos;
}

} // namespace RenderEngine::Configurator


