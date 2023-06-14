#ifndef H_MESH
#define H_MESH

#include <vector>

#include "vertice.h"
#include "face.h"

struct Mesh {
    std::vector<Vertice> vertices;
    std::vector<Face> faces;
};

#endif