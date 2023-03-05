#ifndef H_RENDERENGINE_VALUES
#define H_RENDERENGINE_VALUES

#include <vulkan/vulkan.h>
#include <array>
#include <vector>


namespace RenderEngine {

extern VkInstance vulkanInstance;
extern VkSurfaceKHR surfaceKHR;
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
#define QUEUE_COUNT 2

#define GRAPHICS_QUEUE 0
#define PRESENTATION_QUEUE 1

extern std::array<int, QUEUE_COUNT> queuesFamiliesIndexes;
extern std::array<VkQueue, QUEUE_COUNT> queues;
    
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

// Dynamic memory variables
struct Object {
    int firstVertexIndex;
    int firstIndexIndex;
    int indexAmount;
};

extern int vertexSavedAmount;
extern int indexSavedAmount;
extern std::vector<Object> savedObjects;
extern int lastIndex;

} // namespace RenderEngine

#endif