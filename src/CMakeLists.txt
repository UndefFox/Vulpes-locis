add_subdirectory(libs/RenderEngine)

add_subdirectory(ECS)

add_executable(vulpeslocis main.cpp)

add_library(core core.cpp)

target_link_libraries(core PUBLIC
    renderengine
    ECS)

target_link_libraries(vulpeslocis PUBLIC core)