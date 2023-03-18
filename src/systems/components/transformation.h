#ifndef H_TRANSFORMATION_COMPONENT
#define H_TRANSFORMATION_COMPONENT

struct Transformation
{
    struct Position
    {
        float x;
        float y;
        float z;
    } pos;
    
    struct Rotation {
        float roll;
        float pitch;
        float yaw;
    } rotation;

    bool isStatic = false;

    struct Velocity {
        float x;
        float y;
        float z;
    } velocity;

};


#endif