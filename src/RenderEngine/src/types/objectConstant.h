#ifndef H_RENDERENGINE_OBJECTCONSTANTS
#define H_RENDERENGINE_OBJECTCONSTANTS

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

namespace RenderEngine {

struct ObjectConstant {
    glm::mat4 model;
};

} // namespace RenderEngine

#endif