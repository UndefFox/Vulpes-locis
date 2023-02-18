#Load libraries
add_subdirectory(modules)
add_subdirectory(converters)

add_executable(vulpeslocis main.cpp)

add_library(core core.cpp)

target_link_libraries(core PUBLIC
    lib_RenderEngine
    lib_ECS
    lib_FileManager
    converters)

target_link_libraries(vulpeslocis PUBLIC core)