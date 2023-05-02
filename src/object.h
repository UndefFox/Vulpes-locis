#ifndef H_FORMATS_OBJECT
#define H_FORMATS_OBJECT

#include <vector>
#include <array>

/**
 * Struct that represents object file data.
 */
struct Object {

    /**
     * Vertices coordinates of mesh.
     */
    std::vector<std::array<float, 3>> verticesCords;

    /**
     * Texture coordinates on the surface of the mesh.
     */
    std::vector<std::array<float, 2>> textureCords;

    /**
     * Vector coordinates of normals.
     */
    std::vector<std::array<float, 3>> normalCords;

    /**
     * Faces represented in object file format. 
     * [0] - vertices coords index
     * [1] - texture coords index
     * [2] - normal coords index
     */
    std::vector<std::array<std::array<int, 3>, 3>> faces;
};

#endif