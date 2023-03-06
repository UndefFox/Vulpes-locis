#ifndef H_COMPONENTS_MONO
#define H_COMPONENTS_MONO

#include <vector>
#include "ECS/include/types/entity.h"

struct Mono {
    std::vector<void (*)(Entity&)> calls;
};

#endif