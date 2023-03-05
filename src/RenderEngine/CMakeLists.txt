add_library(values src/values.cpp)
target_link_libraries(values PUBLIC
    vulkan
    glfw3
    X11)

add_library(memory src/memory.cpp)
target_link_libraries(memory PUBLIC
    values)

add_library(image src/image.cpp)
target_link_libraries(image PUBLIC
    values)

add_library(io src/io.cpp)

add_library(valuesfactory src/valuesfactory.cpp)
target_link_libraries(valuesfactory PUBLIC
    values
    memory
    image
    io)

add_library(storage src/storage.cpp)
target_link_libraries(storage PUBLIC
    memory
    values
    vulkan)

add_library(configurator src/configurator.cpp)
target_link_libraries(configurator PUBLIC
    glfw3
    valuesfactory)

add_library(renderer src/renderer.cpp)
target_link_libraries(renderer PUBLIC
    vulkan)




add_library(module_RenderEngine INTERFACE)
target_link_libraries(module_RenderEngine INTERFACE
    storage
    configurator
    renderer)


