#ifndef H_TYPES_VECTOR3
#define H_TYPES_VECTOR3


/**
 * 'Custom type' - namespace of all custom project types
 */
namespace ct {

class Vector3 {
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vector3();
    Vector3(float X, float Y, float Z);

    Vector3 operator +(Vector3 summand);
    void operator +=(Vector3 summand);
    Vector3 operator -(Vector3 deductible);
    Vector3 operator -();
    void operator -=(Vector3 deductible);
    Vector3 operator *(float coefficient);
    void operator *=(float coefficient);
    Vector3 operator /(float coefficient);
};

float length(Vector3 vector);
float distance(Vector3 first, Vector3 sedcond);
Vector3 normalize(Vector3 vector);
float dot(Vector3 first, Vector3 second);
Vector3 cross(Vector3 first, Vector3 second);
Vector3 transform(Vector3 vector, Vector3 position, Vector3 rotation);

}

#endif