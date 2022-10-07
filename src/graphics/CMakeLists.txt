add_library(renderengine renderengine.cpp)
add_library(renderengineconfiguration renderengineconfiguration.cpp)
add_library(windowcontroller windowcontroller.cpp)
add_library(vertex vertex.cpp)


target_link_libraries(renderengineconfiguration PUBLIC
    vulkan
    glfw3
    X11
    filemanager
    windowcontroller
    vertex)

target_link_libraries(renderengine PUBLIC 
    renderengineconfiguration)