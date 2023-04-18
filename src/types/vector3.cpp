#include "types/vector3.h"

#include <math.h>

#include "mat3x3.h"
namespace ct
{

Vector3::Vector3() {}

Vector3::Vector3(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
}

Vector3 Vector3::operator +(const Vector3 summand) {
    Vector3 output = *this;

    output.x += summand.x;
    output.y += summand.y;
    output.z += summand.z;

    return output;
}

void Vector3::operator +=(const Vector3 summand) {
    x += summand.x;
    y += summand.y;
    z += summand.z;
}

Vector3 Vector3::operator -(const Vector3 deductible) {
    Vector3 output = *this;

    output.x -= deductible.x;
    output.y -= deductible.y;
    output.z -= deductible.z;

    return output;
}

Vector3 Vector3::operator -() {
    Vector3 output = *this;

    output.x = -output.x;
    output.y = -output.y;
    output.z = -output.z;

    return output;
}

void Vector3::operator -=(const Vector3 deductible) {
    x -= deductible.x;
    y -= deductible.y;
    z -= deductible.z;
}



Vector3 Vector3::operator *(float coefficient) {
    Vector3 output = *this;

    output.x *= coefficient;
    output.y *= coefficient;
    output.z *= coefficient;

    return output;
}

void Vector3::operator *=(float coefficient) {
    x *= coefficient;
    y *= coefficient;
    z *= coefficient;
}

Vector3 Vector3::operator /(float coefficient) {
    Vector3 output = *this;

    output.x = output.x / coefficient;
    output.y = output.y / coefficient;
    output.z = output.z / coefficient;

    return output;
}



float length(Vector3 vector) {
    return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2) + std::pow(vector.z, 2));
}

float distance(Vector3 first, Vector3 second) {
    Vector3 delta = first - second;

    return length(delta);
}

Vector3 normalize(Vector3 vector) {
    float vecLength = length(vector);

    return vector / vecLength;
}

float dot(Vector3 first, Vector3 second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

Vector3 cross(Vector3 first, Vector3 second) {
    Vector3 output;

    output.x = first.y * second.z - first.z * second.y;
    output.y = first.z * second.x - first.x * second.z;
    output.z = first.x * second.y - first.y * second.x;

    return output;
}

Vector3 transform(Vector3 vector, Vector3 position, Vector3 rotation) {
    Vector3 output{};
    Mat3x3 ttt = ct::getRotationMatrix(rotation.x, rotation.y, rotation.z);

    float c1 = std::cos(rotation.x);
    float s1 = std::sin(rotation.x);
    float x1 = vector.x;
    float y1 = vector.y * c1 - vector.z * s1;
    float z1 = vector.y * s1 + vector.z * c1;

    float c2 = std::cos(rotation.y);
    float s2 = std::sin(rotation.y);
    float x2 = x1 * c2 + z1 * s2;
    float y2 = y1;
    float z2 = -x1 * s2 + z1 * c2;

    float c3 = std::cos(rotation.z);
    float s3 = std::sin(rotation.z);
    float x3 = c3 * x2 - s3 * y2;
    float y3 = s3 * x2 + c3 * y2;
    float z3 = z2;

    output = (ct::Vector3){x3, y3, z3} + position;

    return output;
}

}
