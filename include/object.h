#ifndef H_OBJECT
#define H_OBJECT

#include <array>
#include <vector>
#include "graphics/vertex.h"

namespace Game
{

class Object {
public:
    std::array<float, 3> position;
    std::vector<Vertex> mesh;
    std::vector<int> indexes;

private:

};

}

#endif