#ifndef H_ENTITY
#define H_ENTITY

#include "components/componentsHeaders.h"
#include "systems/systemsheaders.h"

#include <array>
#include <vector>



class Entity {


public:
    int componentMask;
    std::vector<void*> components = {};

public:
    static int typeIdCounter;

    template <typename T>
    static int getTypeId() {
        static const int id = typeIdCounter++;

        return id;
    }


public:

    template <typename T>
    void addComponent(T* newComponent = nullptr) {
        if (!newComponent) {
            newComponent = new T{};
        }

        componentMask |= (1 << getTypeId<T>());

        if (components.size() < getTypeId<T>() + 1)
            components.resize(getTypeId<T>() + 1);
        components[getTypeId<T>()] = newComponent;
    }

    template <typename T>
    T* getComponent() {
        return (T*)components[getTypeId<T>()];
    }
};

#endif