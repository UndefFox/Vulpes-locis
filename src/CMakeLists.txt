# Source code directories:
include_directories(.)
add_executable(vulpeslocis main.cpp)

#Load modules:
add_subdirectory(Shaders)
add_subdirectory(ECS)
add_subdirectory(RenderEngine)

# Libriries:

add_library(stringUtils stringutils.cpp)
add_library(player ECS/entities/player.cpp)
add_library(camera ECS/entities/camera.cpp)

add_library(window window.cpp)
target_link_libraries(window PUBLIC
    glfw3)

add_library(vector2 types/math/vector2.cpp)
add_library(vector3 types/math/vector3.cpp)
add_library(mat3x3 types/math/mat3x3.cpp)

add_library(controlls controlls.cpp)
target_link_libraries(controlls PUBLIC
    window)

add_library(fileLoaders fileLoaders.cpp)
target_link_libraries(fileLoaders PUBLIC
    stringUtils)



# Interfce libriries:
add_library(core core.cpp)
target_link_libraries(core PUBLIC
    module_RenderEngine
    module_ECS
    fileLoaders
    sysPhysicsEngine
    sysRenderEngine
    sysMono
    window
    camera
    player
    controlls
    vector2
    vector3
    mat3x3)





target_link_libraries(vulpeslocis PUBLIC core)