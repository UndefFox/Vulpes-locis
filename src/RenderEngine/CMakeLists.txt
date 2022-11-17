add_library(values private/values.cpp)
add_library(memory private/memory.cpp)
add_library(image private/image.cpp)

add_library(renderengine renderengine.cpp)
add_library(configurator configurator.cpp)

target_link_libraries(renderengine PUBLIC
    configurator
    vulkan
    glfw3
    X11
    values
    filemanager
    memory
    image)