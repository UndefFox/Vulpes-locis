# Libriries:
# Systems libriries:
add_library(sysPhysicsEngine systems/physicsengine.cpp)

add_library(sysRenderEngine systems/renderengine.cpp)
target_link_libraries(sysRenderEngine PUBLIC
    module_RenderEngine)

# Interface libriries:
add_library(entity entity.cpp)

add_library(ECS ECS.cpp)




add_library(module_ECS INTERFACE)
target_link_libraries(module_ECS INTERFACE
    ECS
    entity
    sysPhysicsEngine
    sysRenderEngine)



