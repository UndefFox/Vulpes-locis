#ifndef H_TYPES_VECTOR2
#define H_TYPES_VECTOR2


namespace ct {

/**
 * \brief A math vector.
 * 
 * Represents a trigonometrical vector, or in other words,
 * a set of 2 float numbers.
 * 
 * \ingroup Types
 */
class Vector2 {
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector2();
    Vector2(float X, float Y);

    Vector2 operator +(Vector2 summand);
    void operator +=(Vector2 summand);
    Vector2 operator -(Vector2 deductible);
    Vector2 operator -();
    void operator -=(Vector2 deductible);
    Vector2 operator *(float coefficient);
    void operator *=(float coefficient);
    Vector2 operator /(float coefficient);
};

float length(Vector2 vector);
float distance(Vector2 first, Vector2 sedcond);
Vector2 normalize(Vector2 vector);
float dot(Vector2 first, Vector2 second);

}

#endif