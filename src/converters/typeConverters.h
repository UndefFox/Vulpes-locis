#ifndef H_CONVERTER_OBJECTTOMESH
#define H_CONVERTER_OBJECTTOMESH

#include "RenderEngine/mesh.h"
#include "FileManager/object.h"

namespace TypeConverters {

RenderEngine::Mesh objectToMesh(Object& object);

}

#endif