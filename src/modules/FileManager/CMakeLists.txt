#Formaters:
add_library(Object formaters/object.cpp)
target_link_libraries(Object PUBLIC
    lib_StringUtils)


add_library(lib_FileManager INTERFACE)
target_link_libraries(lib_FileManager INTERFACE
    Object)