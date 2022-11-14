#ifndef H_RENDERENGINE_RENDERENGINE
#define H_RENDERENGINE_RENDERENGINE

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "private/vertex.hpp"

namespace RenderEngine {

const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
};



void initializate();

void drawFrame();


void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);


void writeVertexBuffer();


void writeIndexBuffer();


void updateUniformBuffer();
}

#endif