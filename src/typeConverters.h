#ifndef H_CONVERTER_OBJECTTOMESH
#define H_CONVERTER_OBJECTTOMESH

#include "RenderEngine/include/types/mesh.h"
#include "object.h"

namespace TypeConverters {

RenderEngine::Mesh objectToMesh(Object& object);

}

#endif