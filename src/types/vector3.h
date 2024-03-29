#ifndef H_TYPES_VECTOR3
#define H_TYPES_VECTOR3

/**
 * \defgroup Types
 * \brief All custom types presented in a project.
 */

/**
 * \brief Namespace of all custom project types.
 * 
 * Contains custom types and operations on them.
 * 
 * \ingroup Types
 */
namespace ct {

/**
 * \brief A math vector.
 * 
 * Represents a trigonometrical vector, or in other words,
 * a set of 3 float numbers.
 * 
 * \ingroup Types
 */
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