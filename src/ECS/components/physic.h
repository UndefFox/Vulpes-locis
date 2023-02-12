#ifndef H_PHYSIC_COMPONENT
#define H_PHYSIC_COMPONENT

struct Physic {
    float gravity;

    struct Velocity {
        float x;
        float y;
        float z;
    } velocity;
};

#endif