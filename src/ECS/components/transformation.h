#ifndef H_TRANSFORMATION_COMPONENT
#define H_TRANSFORMATION_COMPONENT

#include "types/vector3.h"

/**
 * \defgroup Components
 * 
 * \brief Contain all compoents.
 * 
 * \ingroup ECS
 */


/**
 * \ingroup Components
 */
struct Transformation
{
    ct::Vector3 position;
    ct::Vector3 rotation;
};


#endif