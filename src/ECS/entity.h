#ifndef H_ENTITY
#define H_ENTITY

#include <array>
#include <vector>


/**
 * \brief Single item in the world.
 * 
 * Represents single thing in a game world with
 * components and stores it.
 * 
 * \ingroup ECS
 */
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
            
        components[getTypeId<T>()] = (void*)newComponent;
    }

    template <typename T>
    T* getComponent() {
        return (T*)components[getTypeId<T>()];
    }
};

#endif