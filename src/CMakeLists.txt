add_subdirectory(graphics)

add_executable(vulpeslocis main.cpp)

add_library(core core.cpp)
add_library(filemanager filemanager.cpp)

target_link_libraries(core PUBLIC renderengine)
target_link_libraries(vulpeslocis PUBLIC core)