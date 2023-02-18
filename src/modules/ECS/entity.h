#ifndef H_ENTITY
#define H_ENTITY

#include <vector>

struct Entity {
    int id;
    int mask;
    std::vector<void*> components;
};

#endif