#ifndef H_RENDERENGINE_VALUESFACTORY
#define H_RENDERENGINE_VALUESFACTORY

#include <string>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "../types/configuration.h"

namespace RenderEngine {

/**
 * Configuration acording to wich all create functions will be
 * creating values. 
 */
extern Configuration currentConfiguration;

void createVulkanInstance();
void destroyVulkanInstance();

/**
 * Creating surface for a window.
 */
void createSurface();

void destroySurface();


/**
 * Gets all devices detected on the computer.
 * 
 * @return Vector of all detected devices.
 */
std::vector<VkPhysicalDevice> getAvailablePhysicalDevices();

/**
 * @brief Checks minimum requirements for game.
 * 
 * If device passed, it can run game in minimal conditions, so
 * not all settings available for it.
 * 
 * @param device The device that must be checked. 
 */
bool minimuPhysicalDeviceCheck(VkPhysicalDevice& device, VkSurfaceKHR testSurface);


void setPhysicalDevice();


void createDevice();
void destroyDevice();

void updateSwapchainConfiguration();

void createSwapchain();
void destroySwapchain();

void createFramebuffers();

void createRenderPass();
void destroyRenderPass();

void createDescriptorSetLayout();

void createGraphicsPipelineLayout();
void destroyGraphicsPipelineLayout();

void createGraphicsPipeline();
void destroyGraphicsPipeline();

void createCommandPool();
void destroyCommandPool();

void createCommandBuffer();

void createDepthResources();
void destroyDepthResources();

void createBuffers();
void destroyBuffers();

void createDescriptorPool();
void destroyDesriptorPool();

void createDescriptorSet();

void createSyncObjects();
void destroySyncObjects();

} // namespace RenderEngine

#endif