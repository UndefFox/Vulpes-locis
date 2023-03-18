#ifndef H_COLIDER_COMPONENT
#define H_COLIDER_COMPONENT

enum ColiderType {
    Box
};

struct Colider {
    ColiderType type;

    int xSize;
    int ySize;
    int zSize;
};

#endif