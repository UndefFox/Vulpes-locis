#ifndef H_PHYSICSDATA
#define H_PHYSICSDATA

#include "types/math/vector3.h"
#include "types/math/mat3x3.h"

#include <array>
#include <math.h>

/**
 * \ingroup Components
 */
struct PhysicsData {

ct::Vector3 velocity{};
ct::Vector3 aceleration{};

ct::Vector3 angularSpeed{};
ct::Vector3 angularAceleration{};

float mass;
float bouncines;
ct::Mat3x3 inertiaTensor{};

bool isStatic;

};

class SpeherePhys : public PhysicsData {
    SpeherePhys(float radius) {

    }
};

class BoxPhys : public PhysicsData {
public:
    BoxPhys(float width, float height, float thic, float mass) {
        width /= 2.0f;
        height /= 2.0f;
        thic /= 2.0f;

        float b1 = mass * (std::pow(height, 2.0f) + std::pow(thic, 2.0f)) / 3.0f;
        float b2 = mass * (std::pow(width, 2.0f) + std::pow(thic, 2.0f)) / 3.0f;
        float b3 = mass * (std::pow(width, 2.0f) + std::pow(height, 2.0f)) / 3.0f;

        inertiaTensor.setCell(0, 0, 1.0f / b1);
        inertiaTensor.setCell(1, 1, 1.0f / b2);
        inertiaTensor.setCell(2, 2, 1.0f / b3);
    }
};

#endif