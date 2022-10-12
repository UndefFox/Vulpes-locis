#ifndef H_UBO
#define H_UBO

#include <glm/glm.hpp>

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
};

#endif