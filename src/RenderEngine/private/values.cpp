#include "values.h"

namespace RenderEngine {

    VkInstance vulkanInstance;
    VkSurfaceKHR surfaceKHR;
    GLFWwindow* window;
    std::vector<VkPhysicalDevice> physicalDevices;
    uint8_t currentPhysicalDeviceId;
    VkDevice logicalDevice;
    VkRenderPass renderPass;
    

    VkSwapchainKHR swapchainKHR;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapchainFramebuffers;

    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;

    // Queue variable
    uint32_t graphicFamilyIndex;
    uint32_t presentationFamilyIndex;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    
    // Swapchain details
    VkFormat swapchainFormat;
    VkExtent2D swapchainExtent;

    // Sync objects
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;

    // Buffers
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;


    VkImage v_textureImage;
    VkDeviceMemory v_textureImageMemory;
    VkImageView v_textureImageView;
    VkSampler v_textureSampler;

    VkImage v_depthImage;
    VkDeviceMemory v_depthImageMemory;
    VkImageView v_depthImageView;
}