# Source code directories:
include_directories(.)
add_executable(vulpeslocis main.cpp)

#Load modules:
add_subdirectory(modules)
add_subdirectory(converters)


# Libriries:
# Interfce libriries:
add_library(core core.cpp)
target_link_libraries(core PUBLIC
    module_RenderEngine
    module_ECS
    lib_FileManager
    converters)





target_link_libraries(vulpeslocis PUBLIC core)