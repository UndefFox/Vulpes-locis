#ifndef H_RENDERENGINE_VERTEX
#define H_RENDERENGINE_VERTEX

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace RenderEngine {

struct Vertex {
    alignas(16) glm::vec3 pos;
    alignas(16) glm::vec3 color;
    alignas(16) glm::vec2 texCoord;
};

}

#endif