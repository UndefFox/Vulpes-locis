#ifndef H_CONVERTER_OBJECTTOMESH
#define H_CONVERTER_OBJECTTOMESH

#include "RenderEngine/types/mesh.h"
#include "object.h"

namespace TypeConverters {

RenderEngine::Mesh objectToMesh(Object& object);

}

#endif