#ifndef H_RENDERENGINE_STORAGE
#define H_RENDERENGINE_STORAGE

#include <array>
#include <vector>

#include "values.h"

namespace RenderEngine {

struct AddMeshToMemoryInfo {
    std::vector<std::array<float, 3>> vertices;
    std::vector<uint16_t> indexes;
};

int addMeshToMemory(AddMeshToMemoryInfo& data);

}

#endif