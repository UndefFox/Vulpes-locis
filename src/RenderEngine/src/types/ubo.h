#ifndef H_RENDERENGINE_UBO
#define H_RENDERENGINE_UBO

#include <glm/glm.hpp>

namespace RenderEngine {
    
struct UniformBufferObject {
    alignas(16) glm::mat4 model;
};

} // namespace RenderEngine

#endif