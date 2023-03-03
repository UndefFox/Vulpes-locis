#Formaters:
add_library(FileLoaders fileLoaders.cpp)
target_link_libraries(FileLoaders PUBLIC
    lib_StringUtils)


add_library(lib_FileManager INTERFACE)
target_link_libraries(lib_FileManager INTERFACE
    FileLoaders)