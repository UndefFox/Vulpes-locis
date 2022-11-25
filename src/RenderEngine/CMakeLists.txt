add_library(values          src/values.cpp)
add_library(memory          src/memory.cpp)
add_library(image           src/image.cpp)
add_library(io              src/io.cpp)
add_library(configurator    src/configurator.cpp)
add_library(storage         src/storage.cpp)

add_library(renderengine renderengine.cpp)

target_link_libraries(values PUBLIC
    vulkan
    glfw3
    X11)

target_link_libraries(memory PUBLIC
    values)

target_link_libraries(image PUBLIC
    values)

target_link_libraries(configurator PUBLIC
    values
    memory
    image
    io)

target_link_libraries(storage PUBLIC
    memory)

target_link_libraries(renderengine PUBLIC
    storage
    configurator

    vulkan
    glfw3
    X11)