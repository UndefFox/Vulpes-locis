#Load libraries
add_subdirectory(modules)

add_executable(vulpeslocis main.cpp)

add_library(core core.cpp)

target_link_libraries(core PUBLIC
    lib_RenderEngine
    lib_ECS)

target_link_libraries(vulpeslocis PUBLIC core)