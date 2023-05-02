#ifndef H_TYPES_MAT3X3
#define H_TYPES_MAT3X3

#include "vector3.h"

#include <array>

namespace ct {

/**
 * \brief Matrix 3 by 3.
 * 
 * \ingroup Types
 */
class Mat3x3 {
    std::array<float, 9> elements{};

public:
    Mat3x3 operator *(const Mat3x3 coefficient);
    Vector3 operator *(const Vector3 coefficient);
    void setCell(int a, int b, float val);
    float getCell(int a, int b);
};

Mat3x3 transpose(const Mat3x3 mat);
Mat3x3 getRotationMatrix(float roll, float pitch, float yaw);

}

#endif