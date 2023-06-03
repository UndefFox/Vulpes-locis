#ifndef H_CONVERTER_OBJECTTOMESH
#define H_CONVERTER_OBJECTTOMESH

#include "RenderEngine/types/mesh.h"
#include "types/files/object.h"

/**
 * \brief Contaions all methods for converting one type to another.
 * 
 * Represents a abstraction layer to create less dependices on used file
 * formats. 
 */
namespace TypeConverters {

/**
 * Converts object file to RenderEngine mesh.
 */
RenderEngine::Mesh objectToMesh(Object& object);

}

#endif