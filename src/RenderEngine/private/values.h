#ifndef H_RENDERENGINE_VALUES
#define H_RENDERENGINE_VALUES

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace RenderEngine {

    
    extern VkInstance vulkanInstance;
    extern VkSurfaceKHR surfaceKHR;
    extern GLFWwindow* window;
    extern std::vector<VkPhysicalDevice> physicalDevices;
    extern uint8_t currentPhysicalDeviceId;
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
    extern VkFormat swapchainFormat;
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


    extern VkImage v_textureImage;
    extern VkDeviceMemory v_textureImageMemory;
    extern VkImageView v_textureImageView;
    extern VkSampler v_textureSampler;

    extern VkImage v_depthImage;
    extern VkDeviceMemory v_depthImageMemory;
    extern VkImageView v_depthImageView;
}

#endif