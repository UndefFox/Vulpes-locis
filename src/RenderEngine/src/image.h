#ifndef H_RENDERENGINE_IMAGE
#define H_RENDERENGINE_IMAGE

#include <vulkan/vulkan.h>
#include <vector>

namespace RenderEngine {

void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

}

#endif