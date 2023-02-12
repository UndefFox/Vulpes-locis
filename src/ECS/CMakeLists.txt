add_library(ECS ECS.cpp)

#systems
add_library(rendersystem systems/renderengine.cpp)
add_library(physicsystem systems/physicsengine.cpp)

target_link_libraries(ECS PUBLIC
    rendersystem
    physicsystem)