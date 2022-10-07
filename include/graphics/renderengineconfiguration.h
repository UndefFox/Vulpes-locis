#ifndef H_RENDERENGINECONFIGURATION
#define H_RENDERENGINECONFIGURATION

#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>
#include <vector>

#include "graphics/windowcontroller.h"
#include "filemanager.h"

namespace Game {

/**
 *  Contain set of values and their management wich engine using for render.
 */
class RenderEngineConfiguration {
public:
    VkInstance v_instance;
    WindowController v_windowController;
    VkSurfaceKHR v_surface;
    VkPhysicalDevice v_physicalDevice;
    VkDevice v_device;
    VkSwapchainKHR v_swapchain;
    std::vector<VkImage> v_swapchainImages;
    std::vector<VkImageView> v_swapchainImageViews;
    VkRenderPass v_renderPass;
    VkDescriptorSetLayout v_descriptorSetLayout;
    VkPipelineLayout v_pipelineLayout;
    VkPipeline v_graphicsPipeline;
    std::vector<VkFramebuffer> v_swapchainFramebuffers;
    VkCommandPool v_commandPool;
    VkCommandBuffer v_commandBuffer;
    VkDescriptorPool v_descriptorPool;
    VkDescriptorSet v_descriptorSet;

    // Queue variable
    uint32_t v_graphicFamilyIndex;
    uint32_t v_presentationFamilyIndex;
    VkQueue v_graphicsQueue;
    VkQueue v_presentQueue;
    
    // Swapchain details
    VkFormat v_swapchainFormat;
    VkExtent2D v_swapchainExtent;

    // Sync objects
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;

    // Buffers
    VkBuffer v_vertexBuffer;
    VkDeviceMemory v_vertexBufferMemory;
    VkBuffer v_indexBuffer;
    VkDeviceMemory v_indexBufferMemory;
    VkBuffer v_uniformBuffer;
    VkDeviceMemory v_uniformBufferMemory;

    VkImage v_textureImage;
    VkDeviceMemory v_textureImageMemory;
    VkImageView v_textureImageView;
    VkSampler v_textureSampler;

    VkImage v_depthImage;
    VkDeviceMemory v_depthImageMemory;
    VkImageView v_depthImageView;

private:
    const std::vector<const char*> EXTENSIONS = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };


public:
    void initializate();

public:
    void destroy();

private:
    /**
     * Create new Vkinstance.
     * 
     * Result stored in @ref RenderEngineConfiguration::v_instance "v_instance" variable.
     */
    void createVkInstance();

private:
    /**
     * Create new surface for window stored in @ref RenderEngineConfiguration::v_windowcontroller "v_windowcontroller".
     * 
     * Result stored in @ref RenderEngineConfiguration::v_surface "v_surface".
     */
    void createSurface();

private:
    /**
     * Choose first suitable device for current configuration.
     * 
     * Result stored in @ref RenderEngineConfiguration::v_physicalDevice "v_physicalDevice".
     */
    void choosePhysicalDevice();
    
private:
    /**
     * Choose qeueus families for work.
     * 
     * @param device device for wich need find queues.
     * 
     * @returnC true if manage to find all needed queues.
     */
    bool chooseQueues(VkPhysicalDevice& device);

private:
    /**
     * Creating device for choosen physcial device and queues.
     * 
     * Result stored in @ref RenderEngineConfiguration::v_device "v_device".
     */
    void createDevice();

private:
    /**
     * Creating queues object from device.
     */
    void getQueuesObjects();

private:
    /**
     * Creating swapcahin for current device.
     * 
     * Result stored in @ref RenderEngineConfiguration::v_swapchain "swapchain".
     */
    void createSwapchain();

private:
    /**
     * Geting iamges from current swapcahin.
     * 
     * Images stored in @ref RenderEngineConfiguration::v_swapchainImages "v_swapcahinImages".
     */
    void getSwapchainImages();

private:
    /**
     * Creating image view for images of the swapchain.
     * 
     * Views a stored in @ref RenderEngineConfiguration::v_swapchainImageViews "v_swapchainImageViews".
     */
    void createImagesViews();

private:
    void createRenderPass();

private:
    void createGraphicsPipelineLayout();

private:
    void createGraphicsPipeline();

private:
    void createDescriptorSetLayout();

private:
    void createShaderModule(const std::vector<char>& code, VkShaderModule& shaderModule);

private:
    void createFramebuffers();

private:
    void createCommandPool();

private:
    void createDepthResources();

private:
    void createTextureImage();

private:
    void createTextureImageView();

private:
    void createTextureSampler();

private:
    void createVertexBuffer();

private:
    void createIndecsBuffer();

private:
    void createUniformBuffers();

private:
    void createDescriptorPool();

private:
    void createDescriptorSet();

private:
    void createCommandBuffer();

private:
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

private:
    void createSyncObjects();

public:
    void recreateSwapchain();

private:
    void cleanupSwapchain();

private:
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

public:
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

public:
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

public:
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

public:
    VkCommandBuffer beginSingleTimeCommands();

public:
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

public:
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

public:
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

public:
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

private:
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
};

} // namespace Game

#endif