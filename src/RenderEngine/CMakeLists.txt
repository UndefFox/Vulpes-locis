add_library(values private/values.cpp)
add_library(configurator configurator.cpp)
add_library(renderengine renderengine.cpp)

target_link_libraries(configurator PUBLIC
    vulkan
    glfw3
    X11
    values
    filemanager)

target_link_libraries(renderengine PUBLIC
    configurator)