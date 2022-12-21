add_subdirectory(libs/RenderEngine)

add_executable(vulpeslocis main.cpp)

add_library(core core.cpp)

target_link_libraries(core PUBLIC
    renderengine)

target_link_libraries(vulpeslocis PUBLIC core)