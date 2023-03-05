#ifndef H_RENDERENGINE_MESH
#define H_RENDERENGINE_MESH

#include <array>
#include <vector>
#include <cstdint>

namespace RenderEngine {

struct Mesh {
    std::vector<std::array<float, 8>> vertices;
    std::vector<uint16_t> indexes;

};

}

#endif