#ifndef H_RENDERENGINE_VALUES
#define H_RENDERENGINE_VALUES

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace RenderEngine {

/**
 * Contains all values needed across library and methods for controll them.
 */
namespace Values {
    extern VkInstance vulkanInstance;
    extern VkSurfaceKHR surfaceKHR;
    extern GLFWwindow* window;
    extern VkPhysicalDevice physcialDevice;
    extern VkDevice logicalDevice;
    extern VkRenderPass renderPass;
    
    extern VkSwapchainKHR swapchainKHR;
    extern std::vector<VkImage> swapchainImages;
    extern std::vector<VkImageView> swapchainImageViews;
    extern std::vector<VkFramebuffer> swapchainFramebuffers;

    extern VkPipelineLayout pipelineLayout;
    extern VkPipeline graphicsPipeline;
    
    extern VkCommandPool commandPool;
    extern VkCommandBuffer commandBuffer;

    extern VkDescriptorSetLayout descriptorSetLayout;
    extern VkDescriptorPool descriptorPool;
    extern VkDescriptorSet descriptorSet;

    // Queue variable
    extern uint32_t graphicFamilyIndex;
    extern uint32_t presentationFamilyIndex;
    extern VkQueue graphicsQueue;
    extern VkQueue presentQueue;
    
    // Swapchain details
    extern VkSurfaceFormatKHR swapchainFormat;
    extern VkExtent2D swapchainExtent;

    // Sync objects
    extern VkSemaphore imageAvailableSemaphore;
    extern VkSemaphore renderFinishedSemaphore;
    extern VkFence inFlightFence;

    // Buffers
    extern VkBuffer vertexBuffer;
    extern VkDeviceMemory vertexBufferMemory;
    extern VkBuffer indexBuffer;
    extern VkDeviceMemory indexBufferMemory;
    extern VkBuffer uniformBuffer;
    extern VkDeviceMemory uniformBufferMemory;

    extern VkImage depthImage;
    extern VkDeviceMemory depthImageMemory;
    extern VkImageView depthImageView;



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
} // namepsace Values

} // namespace RenderEngine

#endif