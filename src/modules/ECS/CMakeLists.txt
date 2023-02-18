add_library(lib_ECS ECS.cpp)
add_library(entity entity.cpp)

# Systems:
add_library(sysPhysicsEngine systems/physicsengine.cpp)

add_library(sysRenderEngine systems/renderengine.cpp)
target_link_libraries(sysRenderEngine PUBLIC
    lib_RenderEngine)

target_link_libraries(lib_ECS PUBLIC
    entity
    sysPhysicsEngine
    sysRenderEngine)