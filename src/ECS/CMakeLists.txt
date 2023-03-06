# Libriries:

add_library(entity src/entity.cpp)

add_library(ECS src/ECS.cpp)

add_library(module_ECS INTERFACE)
target_link_libraries(module_ECS INTERFACE
    ECS
    entity)



