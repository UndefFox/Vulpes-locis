#include "values.h"

namespace RenderEngine {

VkInstance vulkanInstance;
VkSurfaceKHR surfaceKHR;
GLFWwindow* window;
VkPhysicalDevice physcialDevice;
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
VkSurfaceFormatKHR swapchainFormat;
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

VkImage depthImage;
VkDeviceMemory depthImageMemory;
VkImageView depthImageView;

int vertexSavedAmount = 0;
int indexSavedAmount = 0;
std::vector<Object> savedObjects{};
int lastIndex = 0;


} // namespace RenderEngine::Values