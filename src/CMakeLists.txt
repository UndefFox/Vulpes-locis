# Source code directories:
include_directories(.)
add_executable(vulpeslocis main.cpp)

#Load modules:
add_subdirectory(converters)
add_subdirectory(shaders)
add_subdirectory(ECS)
add_subdirectory(RenderEngine)
add_subdirectory(FileManager)
add_subdirectory(StringUtils)

# Libriries:
# Interfce libriries:
add_library(core core.cpp)
target_link_libraries(core PUBLIC
    module_RenderEngine
    module_ECS
    lib_FileManager
    converters)





target_link_libraries(vulpeslocis PUBLIC core)