# Libriries:
# Systems libriries:
add_library(sysPhysicsEngine src//physicsengine.cpp)

add_library(sysRenderEngine src//renderengine.cpp)
target_link_libraries(sysRenderEngine PUBLIC
    module_RenderEngine)

# Interface libriries:
add_library(entity src/entity.cpp)

add_library(ECS src/ECS.cpp)




add_library(module_ECS INTERFACE)
target_link_libraries(module_ECS INTERFACE
    ECS
    entity
    sysPhysicsEngine
    sysRenderEngine)



