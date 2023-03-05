#ifndef H_FORMATS_OBJECT
#define H_FORMATS_OBJECT

#include <vector>
#include <array>

struct Object {
    std::vector<std::array<float, 3>> verticesCords;
    std::vector<std::array<float, 3>> normalCords;
    std::vector<std::array<float, 2>> textureCords;
    std::vector<std::array<std::array<int, 3>, 3>> faces;
};

#endif