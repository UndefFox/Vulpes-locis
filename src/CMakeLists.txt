add_subdirectory(graphics)

add_executable(vulpeslocis main.cpp)

add_library(core core.cpp)
add_library(filemanager filemanager.cpp)
add_library(world world.cpp)
add_library(object object.cpp)

target_link_libraries(world PUBLIC object)

target_link_libraries(core PUBLIC
    renderengine
    world)

target_link_libraries(vulpeslocis PUBLIC core)