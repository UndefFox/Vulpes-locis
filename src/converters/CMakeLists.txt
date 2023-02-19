# Libriries:#
# Interface libriries:
add_library(objectToMesh objectToMesh.cpp)




add_library(converters INTERFACE)
target_link_libraries(converters INTERFACE
objectToMesh)