#ifndef H_COMPONENTS_MONO
#define H_COMPONENTS_MONO

#include <vector>
#include "ECS/entity.h"

/**
 * \ingroup Components
 */
struct Mono {
    std::vector<void (*)(Entity&)> calls;
};

#endif