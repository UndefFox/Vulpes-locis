#ifndef H_COLIDER_COMPONENT
#define H_COLIDER_COMPONENT

#include <vector>
#include "types/vector3.h"

/**
 * \ingroup Components
 */
enum ColiderType {
    Sphere,
    Box,
    Convex
};

struct Colider {
public:
    ColiderType type;
    std::vector<ct::Vector3> data;
};

class SphereColider : public Colider {
public:
    SphereColider(float radius) {
        type = Sphere;
        data = {{radius, 0.0f, 0.0f}};
    }

    float getRadius() {
        return data[0].x;
    }

};

class BoxColider : public Colider {
public:
    BoxColider(float width, float height, float thic) {
        type = Box;
        data = { {width / 2.0f, height / 2.0f, thic / 2.0f} };
    }

    ct::Vector3 getSize() {
        return data[0] * 2;
    }
};

#endif