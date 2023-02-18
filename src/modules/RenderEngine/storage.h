#ifndef H_RENDERENGINE_STORAGE
#define H_RENDERENGINE_STORAGE

#include <array>
#include <vector>
#include <cstdint>

namespace RenderEngine {

struct Mesh {
    std::vector<std::array<float, 5>> vertices;
    std::vector<uint16_t> indexes;

};


/**
 * Adding mesh to memory and returnng it's ID.
 * 
 * \param mesh 
 * sees drawFrame() wich will be added to memory.
 * 
 * \returns ID wich associeted with this object.
 */
int addMesh(Mesh& mesh);

} // namespace RenderEngine

#endif