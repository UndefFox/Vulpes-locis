add_library(converters INTERFACE)

add_library(objectToMesh objectToMesh.cpp)

target_link_libraries(converters INTERFACE
objectToMesh)