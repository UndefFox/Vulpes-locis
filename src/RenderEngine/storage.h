#ifndef H_RENDERENGINE_STORAGE
#define H_RENDERENGINE_STORAGE

#include "RenderEngine/types/mesh.h"

/**
 * \file
 * \brief All functionality for storing assets.
 * 
 * Implements all functionality for storing assets that will
 * be used for rendring: meshes, textures, materials and etc.
 * 
 * \ingroup RenderInterface
 */

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