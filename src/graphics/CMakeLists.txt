add_library(renderengine renderengine.cpp)
add_library(renderengineconfiguration renderengineconfiguration.cpp)
add_library(windowcontroller windowcontroller.cpp)


target_link_libraries(renderengineconfiguration PUBLIC
    vulkan
    glfw3
    X11
    filemanager
    windowcontroller)

target_link_libraries(renderengine PUBLIC 
    renderengineconfiguration)