#ifndef H_RENDERENGINE_STORAGE
#define H_RENDERENGINE_STORAGE

#include "mesh.h"

namespace RenderEngine {

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