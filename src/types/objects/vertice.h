#ifndef H_VERTICE
#define H_VERTICE

#include "types/math/vector3.h"
#include "types/math/vector2.h"

struct Vertice {
    ct::Vector3 cords;
    ct::Vector3 normal;
    ct::Vector2 UV;
};

#endif