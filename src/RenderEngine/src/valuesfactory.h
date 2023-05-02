#ifndef H_RENDERENGINE_VALUESFACTORY
#define H_RENDERENGINE_VALUESFACTORY

#include <string>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "../types/configuration.h"

/**
 * \file
 * \brief All functionality for values initialization.
 * 
 * Implements all functions that allows to create all values
 * from values file.
 * 
 * \ingroup RenderSource
 */

namespace RenderEngine {

/**
 * Configuration acording to wich all create functions will be
 * creating values. 
 */
//extern Configuration currentConfiguration;

void createVulkanInstance();
void destroyVulkanInstance();

/**
 * Creating surface for a window.
 */
void createSurface(GLFWwindow* window);

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


void setPhysicalDevice(unsigned int deviceId);


void createDevice();
void destroyDevice();

void updateSwapchainConfiguration();

/**
 *  Recuring create swapchain function. If parameters are not passed,
 *  then last passed value is used.
 */
void createSwapchainR(GLFWwindow* newWindow = nullptr);
void destroySwapchain();

void createFramebuffers();

void createRenderPass();
void destroyRenderPass();

void createDescriptorSetLayout();

void createGraphicsPipelineLayout();
void destroyGraphicsPipelineLayout();

void createGraphicsPipeline(std::vector<char> vertShader, std::vector<char> fragShader);
void destroyGraphicsPipeline();

void createCommandPool();
void destroyCommandPool();

void createCommandBuffer();

void createDepthResources();
void destroyDepthResources();

void createBuffers(size_t memoryAmount);
void destroyBuffers();

void createDescriptorPool();
void destroyDesriptorPool();

void createDescriptorSet();

void createSyncObjects();
void destroySyncObjects();

} // namespace RenderEngine

#endif