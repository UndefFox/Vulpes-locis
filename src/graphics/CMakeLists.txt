add_library(renderengine renderengine.cpp)
add_library(renderconfigurator renderconfigurator.cpp)
add_library(windowcontroller windowcontroller.cpp)


target_link_libraries(renderconfigurator PUBLIC
    vulkan
    glfw3
    X11
    filemanager
    windowcontroller)

target_link_libraries(renderengine PUBLIC 
    renderconfigurator
    world)