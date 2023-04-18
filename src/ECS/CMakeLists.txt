# Libriries:

add_library(entity entity.cpp)

add_library(ECS ECS.cpp)

add_library(sysPhysicsEngine systems/physics.cpp)
target_link_libraries(sysPhysicsEngine PUBLIC
    module_ECS)
add_library(sysRenderEngine systems/render.cpp)
target_link_libraries(sysRenderEngine PUBLIC
    module_RenderEngine
    module_ECS)
add_library(sysMono systems/mono.cpp)

add_library(module_ECS INTERFACE)
target_link_libraries(module_ECS INTERFACE
    ECS
    entity)



