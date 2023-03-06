# Source code directories:
include_directories(.)
add_executable(vulpeslocis main.cpp)

#Load modules:
add_subdirectory(shaders)
add_subdirectory(ECS)
add_subdirectory(RenderEngine)
add_subdirectory(Window)

# Libriries:

add_library(typeConverters typeConverters.cpp)
add_library(stringUtils stringutils.cpp)
add_library(player player.cpp)
add_library(camera camera.cpp)

add_library(fileLoaders fileLoaders.cpp)
target_link_libraries(fileLoaders PUBLIC
    stringUtils)

add_library(sysPhysicsEngine systems/physicsengine.cpp)
add_library(sysRenderEngine systems/renderengine.cpp)
target_link_libraries(sysRenderEngine PUBLIC
    module_RenderEngine)
add_library(sysMono systems/monoSystem.cpp)

# Interfce libriries:
add_library(core core.cpp)
target_link_libraries(core PUBLIC
    module_RenderEngine
    module_ECS
    fileLoaders
    typeConverters
    sysPhysicsEngine
    sysRenderEngine
    sysMono
    window
    camera
    player)





target_link_libraries(vulpeslocis PUBLIC core)