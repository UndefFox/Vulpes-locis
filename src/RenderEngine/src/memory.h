#ifndef H_RENDERENGINE_MEMORY
#define H_RENDERENGINE_MEMORY

#include <vulkan/vulkan.h>

/**
 * \file
 * \brief All functionality for memory.
 * 
 * Implements all functionality for manipulation and controlling 
 * memory used by engine.
 * 
 * \ingroup RenderSource
 */

namespace RenderEngine {

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDeviceSize dstOffset);

VkCommandBuffer beginSingleTimeCommands();

void endSingleTimeCommands(VkCommandBuffer commandBuffer);

void allocateMemory(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkMemoryRequirements memoryRequirements, VkDeviceMemory& memory);

void copyDataToMemory(VkDeviceMemory& destinationMemory, VkDeviceSize& size, void* source);

} // namespace RenderEngine

#endif