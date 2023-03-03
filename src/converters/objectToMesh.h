#ifndef H_CONVERTER_OBJECTTOMESH
#define H_CONVERTER_OBJECTTOMESH

#include "RenderEngine/mesh.h"
#include "FileManager/object.h"

namespace ObjectToMesh {

RenderEngine::Mesh convert(Object& object);

}

#endif