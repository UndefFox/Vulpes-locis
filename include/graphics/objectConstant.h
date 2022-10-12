#ifndef H_OBJECTCONSTANT
#define H_OBJECTCONSTANT

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

namespace Game {

struct ObjectConstant {
    glm::mat4 rotation;
    glm::vec3 pos;
};

}

#endif