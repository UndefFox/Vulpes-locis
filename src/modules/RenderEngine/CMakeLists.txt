# src files
add_library(values          src/values.cpp)
add_library(memory          src/memory.cpp)
add_library(image           src/image.cpp)
add_library(io              src/io.cpp)
add_library(valuesfactory   src/valuesfactory.cpp)


target_link_libraries(values PUBLIC
    vulkan
    glfw3
    X11)

target_link_libraries(memory PUBLIC
    values)

target_link_libraries(image PUBLIC
    values)

target_link_libraries(valuesfactory PUBLIC
    values
    memory
    image
    io)


# interface files
add_library(storage         storage.cpp)
add_library(configurator    configurator.cpp)
add_library(renderer        renderer.cpp)

add_library(lib_RenderEngine INTERFACE)

target_link_libraries(storage PUBLIC
    memory
    values
    vulkan)

target_link_libraries(configurator PUBLIC
    glfw3
    valuesfactory)

target_link_libraries(renderer PUBLIC
    vulkan)

target_link_libraries(lib_RenderEngine INTERFACE
    storage
    configurator
    renderer)


