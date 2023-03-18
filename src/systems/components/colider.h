#ifndef H_COLIDER_COMPONENT
#define H_COLIDER_COMPONENT

enum ColiderType {
    Box
};

struct Colider {
    ColiderType type;

    float xSize;
    float ySize;
    float zSize;
};

#endif