#ifndef H_CONVERTER_OBJECTTOMESH
#define H_CONVERTER_OBJECTTOMESH

#include "modules/RenderEngine/storage.h"
#include "modules/FileManager/formats/object.h"

namespace ObjectToMesh {

RenderEngine::Mesh convert(Object& object);

}

#endif