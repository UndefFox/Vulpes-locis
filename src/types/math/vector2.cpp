#include "vector2.h"

#include <math.h>

namespace ct
{

Vector2::Vector2() {}

Vector2::Vector2(float X, float Y) {
    x = X;
    y = Y;
}

Vector2 Vector2::operator +(const Vector2 summand) {
    Vector2 output = *this;

    output.x += summand.x;
    output.y += summand.y;

    return output;
}

void Vector2::operator +=(const Vector2 summand) {
    x += summand.x;
    y += summand.y;
}

Vector2 Vector2::operator -(const Vector2 deductible) {
    Vector2 output = *this;

    output.x -= deductible.x;
    output.y -= deductible.y;

    return output;
}

Vector2 Vector2::operator -() {
    Vector2 output = *this;

    output.x = -output.x;
    output.y = -output.y;

    return output;
}

void Vector2::operator -=(const Vector2 deductible) {
    x -= deductible.x;
    y -= deductible.y;
}

Vector2 Vector2::operator *(float coefficient) {
    Vector2 output = *this;

    output.x *= coefficient;
    output.y *= coefficient;

    return output;
}

void Vector2::operator *=(float coefficient) {
    x *= coefficient;
    y *= coefficient;
}

Vector2 Vector2::operator /(float coefficient) {
    Vector2 output = *this;

    output.x = output.x / coefficient;
    output.y = output.y / coefficient;

    return output;
}

float length(Vector2 vector) {
    return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

float distance(Vector2 first, Vector2 second) {
    Vector2 delta = first - second;

    return length(delta);
}

Vector2 normalize(Vector2 vector) {
    float vecLength = length(vector);

    return vector / vecLength;
}

float dot(Vector2 first, Vector2 second) {
    return first.x * second.x + first.y * second.y;
}


}
