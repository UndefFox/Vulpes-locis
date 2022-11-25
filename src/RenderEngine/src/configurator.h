#ifndef H_RENDERENGINE_CONFIGURATOR
#define H_RENDERENGINE_CONFIGURATOR

#include <string>

#include "values.h"

namespace RenderEngine {

void createVulkanInstance();
void destroyVulkanInstance();

/**
 * Creates window and surface where rendered image will be presented.
 */
void createWindow();

/**
 * Gets all devices detected on the computer.
 * 
 * @return Vector of all detected devices.
 */
std::vector<VkPhysicalDevice> getAvailablePhysicalDevices();

/**
 * Checks minimum requirements for game.
 * 
 * @param device The device that must be checked. 
 * 
 * @returns true if device capable for running the game, but some
 * settings maybe unavailable.
 * @returns false if device can't render game at all.
 */
bool minimuPhysicalDeviceCheck(VkPhysicalDevice& device);


void setPhysicalDevice(uint32_t deviceId);


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

void createGraphicsPipeline(std::string vertexShader, std::string fragmentShader);
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

}

#endif